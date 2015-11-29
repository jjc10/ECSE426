#include <stdio.h>

static const int MAXBUFFERSIZE = 200;

typedef struct {
	
	int bufferSize;
	 /*!< Circular Queue: Values are placed in the tail and taken out of the head with each iteration */
	float filterValues[MAXBUFFERSIZE]; /*!< This is a circular buffer */// USING GLOBALLY DEFINED CONSTANT
	int bufferPointer; /*!< This points to the head index in the circular buffer and should be MOD[BUFFERSIZE] */
	/* End Circular Queue */
	float filterAverage; /*!< The average of all values in the filter buffer which is computed after every time modify_filterState is called */

} filterState;

/* Function Prototypes for Header File*/
int initializeFilter(filterState* currentFilter, int filterSize);
float modify_filterState(filterState* thisFilter, float value);
