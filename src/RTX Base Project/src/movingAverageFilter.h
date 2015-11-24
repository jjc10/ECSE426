#include <stdio.h>

static const int BUFFERSIZE = 35;

typedef struct {

	/* Circular Queue: Values are placed in the tail and taken out of the head with each iteration */
	float filterValues[BUFFERSIZE];// This is a circular buffer // USING GLOBALLY DEFINED CONSTANT
	int bufferPointer; // This points to the head index in the circular buffer and should be MOD[BUFFERSIZE]
	/* End Circular Queue */
	float filterAverage; // The average of all values in the filter buffer which is computed after every time modify_filterState is called

} filterState;

/* Function Prototypes for Header File*/
int initializeFilter(filterState* currentFilter);
float modify_filterState(filterState* thisFilter, float value);
