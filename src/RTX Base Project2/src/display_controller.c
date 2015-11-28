/**
  ******************************************************************************
  * @file    main.c
  * @author  Bassam Riman 		260367410
	*					 Matthew Beirouti 	260405550
  * @version V1.0.0
  * @date    19-October-2015
  * @brief   This file initializes all hardware and defines a few experiment
	*					 experiment specific functions. Modularizing this particular code
	*					 would be too time consuming and so Lab 3 will be coded with modularizing
	*					 in mind.
  ****************************************************************************** 
  */


#include "initialization.h"

osPoolDef(acc_mpool, 16, message_acc);
osMessageQDef(acc_mqueue, 16, message_acc);
osMessageQDef(temp_mqueue, 16, float);
osMessageQDef(kp_mqueue, 16, int);

osPoolId  acc_mpool;
osMessageQId  acc_mqueue;
osMessageQId  temp_mqueue;
osMessageQId  kp_mqueue;

/**
  * @brief  temperature thread
  * @param  None
  * @retval None
  */
void display_controller_thread(void const *argument){
	st_system_state state = ST_INIT ;	
	err_type	error	= NONE;
	display_state dState = DISPLAY_TEMP;
	display_acc_state dACCState = DISPLAY_PITCH;
	display_alarm_state dAlarmState = ALARM_OFF;
	display_ON_OFF dONOFF = DISPLAY_ON;
	float pitch = 0;
	float roll = 0;
	float temp = 0;
	int kp = -1;
	int alarm_counter =0;
	int tempThreshold =50;
	int displayToggleTime = 80;
	
	while (1) {
		int numberToDisplay = 0;
		switch ( state ){
			case ST_INIT :
				/**************************************/
				/************ initialization **********/
				/**************************************/
				acc_mpool = osPoolCreate(osPool(acc_mpool));
				acc_mqueue = osMessageCreate(osMessageQ(acc_mqueue), NULL);
				temp_mqueue = osMessageCreate(osMessageQ(temp_mqueue), NULL);
				kp_mqueue = osMessageCreate(osMessageQ(kp_mqueue), NULL);
				seg_7_display_init();
			
				/**************************************/
				state = ST_IDLE ;
				break ;
			case ST_IDLE :
				/**************************************/
				/**************** idle ****************/
				/**************************************/
		
				state = ST_RUNNING ;
			
				/**************************************/
				break ;
			case ST_RUNNING :{
				/**************************************/
				/***************** run ****************/
				/**************************************/
				osSignalWait(0x1,osWaitForever);
				
				//get acceleration from acc thread
				osEvent acc_evt = osMessageGet(acc_mqueue, 0);
				if (acc_evt.status == osEventMessage) {
            message_acc *message = (message_acc*)acc_evt.value.p;
						pitch = message->pitch;
						roll = message ->roll;
  
            osPoolFree(acc_mpool, message);
        }
				
				//get temp pressed from keypad thread
				osEvent temp_evt = osMessageGet(temp_mqueue, 0);
				if (temp_evt.status == osEventMessage) {
            temp = (float)temp_evt.value.v;  
        }
				
				//get keypad pressed from keypad thread
				osEvent kp_evt = osMessageGet(kp_mqueue, 0);
				if (kp_evt.status == osEventMessage) {
            kp = (int)kp_evt.value.v; 
						if(kp == 10){
							dState = DISPLAY_TEMP;
						}else if (kp == 11){
							dState = DISPLAY_ACC;
						}else if (kp == 1){
							dACCState = DISPLAY_PITCH;
						}else if (kp == 2){
							dACCState = DISPLAY_ROLL;
						}else{
							//Illegal keypress received
							state = ST_ERROR;
							error = ERR_ERROR_1;
						}
					
        }
	
				switch ( dState ){
					case DISPLAY_TEMP :
						numberToDisplay = temp;
						break ;
					
					case DISPLAY_ACC :
						
					
							switch (dACCState){
								case DISPLAY_PITCH :
									numberToDisplay = pitch;
									break ;
								case DISPLAY_ROLL :
									numberToDisplay = roll;
									break ;
							}	
							break ;
				}
				
						
				switch (dAlarmState){
					case ALARM_OFF :
						displayNumber(numberToDisplay);
						if(temp >= tempThreshold){
							dAlarmState = ALARM_ON;
						}
						break ;
					case ALARM_ON :
						
						switch (dONOFF){
							case DISPLAY_ON :						
								if(alarm_counter < displayToggleTime){
									displayNumber(numberToDisplay);
									alarm_counter++;
								}else{
									alarm_counter = 0;
									dONOFF = DISPLAY_OFF;
								}
								break ;
							case DISPLAY_OFF :
								if(alarm_counter < displayToggleTime){
									displayNothing();
									alarm_counter++;
								}else{
									alarm_counter = 0;
									dONOFF = DISPLAY_ON;
								}
								break ;
						}	
						if(temp < tempThreshold){
							dAlarmState = ALARM_OFF;
						}
						break ;
				}	

				/**************************************/
				break ;
			}	
			case ST_ERROR :
				/**************************************/
				/**************** error ***************/
				/**************************************/
				switch ( error ){
					case NONE :
						//You didn't set error type...
						break ;
					case ERR_ERROR_1 :
						printf("Illegal keypress received");
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

	}
}
	