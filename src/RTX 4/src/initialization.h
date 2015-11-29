/**
  ******************************************************************************
  * @file    initialization.c
  * @author  Bassam Riman 		260367410
	*					 Matthew Beiruti 	XXXXXXXXX
  * @version V1.0.0
  * @date    10-October-2015
  * @brief   This file contains all function prototypes of the initialization 
	*					 functions in the system     
  ****************************************************************************** 
  */

#include "program.h" 

#define X 0
#define Y 1
#define Z 2
#define AxOffset -45.11
#define AyOffset 10.44
#define AzOffset 20.90

#define GxOffset 10 //
#define GyOffset 10
#define GzOffset 10



/** @defgroup Initialization_Exported_Functions
  * @{
  */
void acc_init(void);
void gyro_init(void);
void temp_init(void);
void offsetAccData(float* array);
void offsetGyroData(float* array);
void acc_calibrate(void);
void seg_7_display_init(void);
void alpha_num_kp_init(void);
void board_led_init(void);

