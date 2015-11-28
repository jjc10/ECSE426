/**
  ******************************************************************************
  * @file    program.c
  * @author  Bassam Riman 		260367410
	*					 Matthew Beiruti 	XXXXXXXXX
  * @version V1.0.0
  * @date    10-October-2015
  * @brief   This file contains all general helper funtions usable in different 
	*					 parts of the system.     
  ****************************************************************************** 
  */
	
#include "program.h"



void delay(int x){
		for(int j = 0; j<x; j++ ){
			//do nothing
		}
}

float calculatePitch(float* data){
	return atan2(data[0],sqrt((data[1]*data[1]+data[2]*data[2])));
}
float calculateRoll(float* data){
	return atan2(data[1],sqrt((data[0]*data[0]+data[2]*data[2])));
}

float convertToDegrees(float radians){
	return radians*180/PI;
}
