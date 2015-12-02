#include "ViterbiUpdate.h"
#include <stdlib.h>


float vitpsi[2 * NUM_STATES][NUM_OBS];
float outputArray[2 * NUM_STATES];
int mouj[NUM_OBS];

void createTestGiven(hmm_desc* hmm) {
    hmm->S = NUM_STATES;
    hmm->V = OBS_TYPE;
		hmm->transition[0][0] = 0.09;
    hmm->transition[0][1] = 0.9;
    hmm->transition[0][2] = 0.01;
    hmm->transition[0][3] = 0;
    
    hmm->transition[1][0] = 0.09;
    hmm->transition[1][1] = 0.01;
    hmm->transition[1][2] = 0.9;
    hmm->transition[1][3] = 0;
    
    hmm->transition[2][0] = 0.09;
    hmm->transition[2][1] = 0.45;
    hmm->transition[2][2] = 0.01;
    hmm->transition[2][3] = 0.45;
    
    hmm->transition[3][0] = 0.5;
    hmm->transition[3][1] = 0.5;
    hmm->transition[3][2] = 0;
    hmm->transition[3][3] = 0;
    // DONE WITH TRANS
    //EMISSION
    hmm->emission[0][0] = 1;
    hmm->emission[0][1] = 0;
    hmm->emission[0][2] = 0;
    
    hmm->emission[1][0] = 0;
    hmm->emission[1][1] = 1;
    hmm->emission[1][2] = 0;
    
    hmm->emission[2][0] = 0;
    hmm->emission[2][1] = 0;
    hmm->emission[2][2] = 1;
    
    hmm->emission[3][0] = 0;
    hmm->emission[3][1] = 1;
    hmm->emission[3][2] = 0;
    
    hmm->prior[0] = 0.25;
    hmm->prior[1] = 0.25;
    hmm->prior[2] = 0.25;
    hmm->prior[3] = 0.25;
}

int getIndexOfMax(float* matrix, int s) {
	float max = matrix[0];
	int res = 0;
	int i;
	for (i = 1; i < s; i++) {
		float val = matrix[i];
		if (val > max) {
			max = val;
			res = i;
		}
	}
	return res;
}

float* getRowPointer(float* matrix, int row, int col) {
	 return (matrix + (row * col));
}

float getSumOfArray(float * arr, int size) {
	int i;
	float result = 0.0f;
	for (i = 0; i < size; i++) {
		result += *(arr + i);
	}
	return result;
}

int ViterbiUpdate_C(float* inputArray, float* outputArray, hmm_desc* hmm, int observation) {
	int s;
	float trans_p[hmm->S];
	
	for (s = 0; s < 2 * hmm->S; s++) {
		outputArray[s] = 0.0f;
	}
	
	for (s = 0; s < hmm->S; s++) {
		termByTermMatrixMult(trans_p, inputArray, hmm->transition[s], hmm->S);
		int maxIndex = getIndexOfMax(trans_p, hmm->S);
		float max = trans_p[maxIndex];
		
		outputArray[s] = max;
		outputArray[hmm->S + s] = maxIndex * 1.0;
		
		float* observationRow = hmm->emission[s];
		outputArray[s] = outputArray[s] * observationRow[observation];
	}
	

	
	float c = 1.0f / getSumOfArray(outputArray, hmm->S);
	for (s = 0; s < hmm->S; s++) {
		outputArray[s] = outputArray[s] * c;
	}
	return 0;
}

int viterbiUpdateColumn_C(float* inputArray, float* outputArray, hmm_desc* hmm, int observation) {
    float trans_p[hmm->S];
    int s;
		for (s = 0; s < 2 * hmm->S; s++) {
			outputArray[s] = 0.0f;
		}
		
    for (s = 0; s < hmm->S; s++) {
        float secondArg[hmm->S];
        int i;
        for (i = 0; i < hmm->S; i++) {
            secondArg[i] = hmm->transition[i][s];
        }
        termByTermMatrixMult(trans_p, inputArray, secondArg, hmm->S);
        int maxIndex = getIndexOfMax(trans_p, hmm->S);
        float max = trans_p[maxIndex];
				
        outputArray[s] = max;
        outputArray[hmm->S + s] = maxIndex * 1.0;
        float* observationRow = hmm->emission[s];

        outputArray[s] = outputArray[s] * observationRow[observation];
        
    }

    float sum = getSumOfArray(outputArray, hmm->S);
		
    if (sum < 0.0000001) {
        sum = 1.0;
    }
		
    float c = 1.0f / sum;
    for (s = 0; s < hmm->S; s++) {
        outputArray[s] = outputArray[s] * c;
    }
    return 0;
}



void termByTermMatrixMult(float* result, float * psivit, float * transition, int S) {
	int i;
	for (i = 0; i < S; i++) {
		result[i] = psivit[i] * transition[i];
	}
}


int Viterbi_C(int* Observations, int Nobs, int* EstimatedStates, hmm_desc* hmm){
	// Section A
	float c[Nobs];	
	
	// Section B
	int i;
	float sum = 0;
	for (i = 0; i < hmm->S; i++) {
		vitpsi[i][0] = hmm->prior[i] * hmm->emission[i][Observations[0]];
		sum += vitpsi[i][0];
	}
	
	c[0] = 1.0 / sum;
	for (i = 0; i < hmm->S; i++) {
		vitpsi[i][0] *= c[0];
	}
	
	//Section C
	int t;
	for (t = 1; t < Nobs; t++) {
		float inputArray[hmm->S];
		int j;
		for (j = 0; j < hmm->S; j++) {
			inputArray[j] = vitpsi[j][t - 1];
		}
		
		viterbiUpdateColumn_C(inputArray, outputArray, hmm, Observations[t]);
		
		for (j = 0; j < 2 * hmm->S; j++) {
				vitpsi[j][t] = outputArray[j];
		}
	}
	//Section D
	
	int index = findMaxIndexInColumn (vitpsi, Nobs - 1 , hmm->S);
	
	EstimatedStates[Nobs - 1] = index;
	
	for (i = Nobs - 1; i >= 0; i--) {
		EstimatedStates[i - 1] = vitpsi[hmm-> S + EstimatedStates[i]][i];
	}
	return 0;
}


void printFloatArray(float * ptr, int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("%0.4f| ", ptr[i]);
	}
	printf("\n\r");
}

void printIntArray(int * ptr, int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("%d| ", ptr[i]);
	}
	printf("\n\r");
}

void populateWithZeros(float* array, int size) { // DELETE
	int i;
	for (i = 0; i < size; i++) {
		*(array + i) = 0.0;
	}
}

int findMaxIndexInColumn (float matrix[][NUM_OBS], int column, int numberOfRows) {
	float max = matrix[0][column];
	int indexOfMax = 0;
	int i;
	for (i = 1; i < numberOfRows; i++) {
		if (matrix[i][column] > max) {
			max = matrix[i][column];
			indexOfMax = i;
		}
	}
	return indexOfMax;
}

void printFloatMatrix(float matrix[][NUM_OBS], int rows, int cols){
	int row;
	int col;
	for (row = 0; row < rows; row++) {
		for (col = 0; col < cols; col++){
			printf("%.5f | ", matrix[row][col]);
		}
		printf("\n\n");
	}
}
	
	







