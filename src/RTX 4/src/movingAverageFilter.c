/**
  ******************************************************************************
  * @file    main.c
  * @author  Bassam Riman 		260367410
	*					 Matthew Beirouti 	260405550
  * @version V1.0.0
  * @date    19-October-2015
  * @brief   This file is the abstraction of a moving average filter. It contains
	*					 all the necessary functions to initialize and modify a filter of this type.
  ****************************************************************************** 
  */
#include <stdio.h>

static const int MAXBUFFERSIZE = 200;

/*! \class filterState
 *  \brief The filterState structure definition.
 *
 * Contains an array of size BUFFERSIZE defined in the header file. The buffer pointer, which contains the index of the next value to be replaced in the array. 
 * Also contains filter average, the average value of all numbers in the buffer.
 */
typedef struct {
	
	int bufferSize;
	 /*!< Circular Queue: Values are placed in the tail and taken out of the head with each iteration */
	float filterValues[MAXBUFFERSIZE]; /*!< This is a circular buffer */// USING GLOBALLY DEFINED CONSTANT
	int bufferPointer; /*!< This points to the head index in the circular buffer and should be MOD[BUFFERSIZE] */
	/* End Circular Queue */
	float filterAverage; /*!< The average of all values in the filter buffer which is computed after every time modify_filterState is called */

} filterState;

/**
  * @brief  		Initializes the arrays and index pointers in a filter of type filterState.
	* @param[in]  currentFilter This is the filter which we want to initialize.
  * @retval returnState Returns 1 if everything worked correctly and 0 otherwise.
  */
int initializeFilter(filterState* currentFilter, int filterSize){
	/* Loop and Indicator Variables */
	int gtrdn;
	int returnState=0; // No problems have occured if value stays at 1

	if(filterSize > 200){
		currentFilter->bufferSize = 200;
	} else {
		currentFilter->bufferSize = filterSize;
	}
	
	
	currentFilter->bufferPointer=0; // Points
	currentFilter->filterAverage=0;
	
	for(gtrdn = 0; gtrdn < MAXBUFFERSIZE; gtrdn++){ 
		currentFilter->filterValues[gtrdn] = -333; // Initializes unused the buffer to -333
	}
	
	for(gtrdn = 0; gtrdn < filterSize; gtrdn++){ 
		currentFilter->filterValues[gtrdn] = 0; // Initializes used buffer to 0
	}
	
	returnState=1;
	return returnState;
}


/**
  * @brief  		Adds a value to the filter, taking care of all necesssary logistics, then returns the average of all the values in the buffer.
	* @param[in]  thisFilter The instance of the filter which we currently want to modify. Defined by the type (struct) filterState.
	* @param[in]	value The value we are about to add into the buffer.
  * @retval average The average of all the values in the buffer.
  */
float modify_filterState(filterState* thisFilter, float value){

	/* Loop and Indicator Variables */
	int gtrdn;

	/* Calculation Variables */
	float sum=0;
	float average;
	
	// placing index of head and size into a more readable variable
	int headPointer = thisFilter->bufferPointer;
	int size = thisFilter->bufferSize;
	
	// placing value into buffer
	thisFilter->filterValues[headPointer]=value;
	
	// increment and ensure circularity maintained by modding by bufferSize (size)
	headPointer++;
	if(headPointer >= size){
		headPointer %= size;
	}
	
	// place value of head pointer back into struct element
	thisFilter->bufferPointer=headPointer;

	// calculate average (not the most efficient way)
	for(gtrdn = 0; gtrdn < size; gtrdn++){
		sum+=thisFilter->filterValues[gtrdn];
		
//		printf("THE SUM IN THE LOOP IS:\t%f\n", sum);
	}
	average=sum/size; // USING GLOBALLY DEFINED CONSTANT
	thisFilter->filterAverage=average;
//	printf("Inner Filter Average is: %f\n", average);
	// return average
	return average;
}
