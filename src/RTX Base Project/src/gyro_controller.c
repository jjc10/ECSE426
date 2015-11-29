/**
  ******************************************************************************
  * @file    main.c
  * @author  Bassam Riman 		260367410
	*					 Matthew Beiruti 	260405550
  * @version V1.0.0
  * @date    10-October-2015
  * @brief   This file runs the main system states and delegates system actions 
  *          based on the what state the systen is currenly in.
  ****************************************************************************** 
  */

#include "initialization.h"

uint8_t  interrupt_EXTI1 = 0; // Used for interrupt handeling
	
/**
  * @brief  System starts here and delegates different actions.
  * @param  None
  * @retval None
  */
void gyro_thread(void const *argument){
	st_system_state state = ST_INIT ;	
	err_type	error	= NONE;
	float pitchRadians, rollRadians, pitchDegrees, rollDegrees;
	/* global variable */
	int init_time = 0;	

	filterState accPitchFilter;
	filterState accRollFilter;
	
	float filteredPitch=0.0;
	float filteredRoll=0.0;
	
	/* Main function */
	while (1) {
		
		/* The system can be in multiple states, this is just good coding practice */
		switch ( state ){
			
			/* Initialization state */
			case ST_INIT :
				/**************************************/
				/************ initialization **********/
				/**************************************/			
			
				gyro_init();
				//initializeFilter(&accPitchFilter);
				//initializeFilter(&accRollFilter);
			
				/**************************************/
				state = ST_IDLE ;
				break ;
			
			/* Idle State */
			case ST_IDLE :
				/**************************************/
				/**************** idle ****************/
				/**************************************/
			
				delay(init_time);	
			
				/**************************************/
				state = ST_RUNNING ;
				break ;
			
			/* The system is running here the majority of the time */
			case ST_RUNNING :
				/**************************************/
				/***************** run ****************/
				/**************************************/

				/* Accelerometer Interrupt. When high run the following: */
				//if(interrupt_EXTI0 == 1){
					
					osSignalWait(0x1,osWaitForever);
					/* Reset flag */
					interrupt_EXTI1 = 0;
					/* Read accelerometer data X,Y,Z into */
					float data[3];

					LSM9DS1_ReadGYRO(data);
					offsetAccData(data);
					
/* 					//printf("%f\t%f\t%f\n", data[0]/*x, data[1]/*y, data[2]/*z);
					
					culate the pitch and roll in radians based on the following equation:
					Pitch = arctan(Ax1/sqrt((Ay1)^2+(Az1)^2
					Roll = arctan(Ay1/sqrt((Ax1)^2+(Az1)^2
					pitchRadians = calculatePitch(data);
					rollRadians = calculateRoll(data);
					
					Converting pitch and roll to degrees
					pitchDegrees = convertToDegrees(pitchRadians);
					rollDegrees =  convertToDegrees(rollRadians);
					
					Filtering the pitch and roll angles in degrees using a moving average filter
					filteredPitch = modify_filterState(&accPitchFilter, pitchDegrees);
					filteredRoll = modify_filterState(&accRollFilter, rollDegrees);
					
					
					Create message
					message_acc* acc_message = (message_acc*) osPoolAlloc(acc_mpool);
					acc_message->pitch = filteredPitch;
					acc_message->roll = filteredRoll;
					osMessagePut(acc_mqueue, (uint32_t)acc_message, osWaitForever);					
					
					
					
					printf("%lf\t%f\t%lf\t%f\n", pitchDegrees, filteredPitch, rollDegrees, filteredRoll);
				//} */ 
				
				/**************************************/
				break ;
				
				
			case ST_ERROR :
				/**************************************/
				/**************** error ***************/
				/**************************************/
			
				switch ( error ){
					case NONE :
						//You didn't set error type...
						break ;
					case ERR_ERROR_1 :
						break ;
					case ERR_ERROR_2 :
						break ;
					case ERR_ERROR_3 :
						break ;
					case ERR_ERROR_4 :
						break ;
				}
				
				/**************************************/
				break ;

		}
		//osDelay(250);
	}

}

