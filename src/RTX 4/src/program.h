/**
  ******************************************************************************
  * @file    program.c
  * @author  Bassam Riman 		260367410
	*					 Matthew Beiruti 	XXXXXXXXX
  * @version V1.0.0
  * @date    10-October-2015
  * @brief   This file contains funtion prototypes of general helper funtions 
	*					 usable in differents parts of the system.     
  ****************************************************************************** 
  */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
#include "stm32f4xx_adc.h"
#include <stdint.h>
#include "lis3dsh.h"
#include "LSM9DS1.h"
#include "math.h"
#include "movingAverageFilter.h"
#include "segmentDisplay.h"
#include "keypad.h"
#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "temp_controller.h"
#include "acc_controller.h"
#include "gyro_controller.h"
#include "display_controller.h"
#include "cmsis_os.h"
#include "ViterbiUpdate.h"
#include "trajectory_handler.h"
#include "heading_handler.h"
#include "step_handler.h"
#include "wireless_controller.h"


#define PI 3.141592653589
typedef struct {
    float    pitch;  
		float    roll;   
} message_acc;

//System States
typedef enum {
	ST_INIT,    //Initialization
	ST_IDLE,		//Idleling
	ST_RUNNING,	//Running
	ST_ERROR		//Error Occured
}st_system_state;

//Error
typedef enum {
	NONE,
	ERR_ERROR_1	,
	ERR_ERROR_2	,
	ERR_ERROR_3	,
	ERR_ERROR_4		
}err_type;



//Constant




/** @defgroup Program_Exported_Functions
  * @{
  */ 
void delay(int x);
float calculatePitch(float* data);
float calculateRoll(float* data);
float convertToDegrees(float radians);
	




#endif // PROGRAM_H_
