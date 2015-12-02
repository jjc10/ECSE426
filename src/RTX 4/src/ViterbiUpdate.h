#include <stdio.h>

#define NUM_STATES 4
#define NUM_OBS 20
#define OBS_TYPE 3

typedef struct hmm_desc {
	int S; // number of states
	int V; // number of observations
	float transition[NUM_STATES][NUM_STATES]; // S x S transition probability matrix
	float emission[NUM_STATES][OBS_TYPE]; // S x V emission probability matrix
	float prior[NUM_STATES]; // Sx1 prior probability matrix
	
} hmm_desc;


int ViterbiUpdate_C(float* InputArray, float* OutputArray, hmm_desc* hmm, int Observation);
void printFloatArray(float * ptr, int size);
void termByTermMatrixMult(float* result, float * psivit, float * transition, int S);
float* getRowPointer(float* matrix, int row, int col);
int getIndexOfMax(float* matrix, int s);
float getSumOfArray(float * arr, int size);
int Viterbi_C(int* Observations, int Nobs, int* EstimatedStates, hmm_desc* hmm);
int findMaxIndexInColumn (float matrix[][NUM_OBS], int column, int numberOfRows);
void populateWithZeros(float* array, int size);
void printIntArray(int * ptr, int size);
void printFloatMatrix(float matrix[][NUM_OBS], int rows, int cols);
int getSegmentForFloat(float value, float a1, float a2);
void processValues(float* input, int* output, int* Nobs, int accObs, float a1, float a2, int n1, int n2, int n3);
int findMin(int a[], int length);
int Viterbi_ASM(int* Observations, int Nobs, int* EstimatedStates, hmm_desc* hmm);
