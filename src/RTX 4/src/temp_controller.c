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

static const int MS_IN_SECONDS = 1000;
static const int ALARM_THRESHOLD = 50;
static const float VT = 1.2;
static const float TEMP_SENSOR_V25_V = 0.760;
static const float TEMP_SENSOR_AVG_SLOPE_V = 0.0025;
static const float DAC_MAX= 0xfff;

uint8_t  interrupt_TIM2 = 0;

#define TS_CAL1     *((uint16_t*) 0x1FFF7A2C)             
#define TS_CAL2     *((uint16_t*) 0x1FFF7A2E)             
#define AVG_SLOPE   (float)((TS_CAL1 - TS_CAL2)/80.0)
#define UNIT_TIME_PER_TEMP (MAX_MOTOR_LOOP_DELAY - MIN_MOTOR_LOOP_DELAY)/(MAX_TEMP-MIN_TEMP)


/**
  * @brief  temperature thread
  * @param  None
  * @retval None
  */
void temp_thread(void const *argument){
	st_system_state state = ST_INIT ;	
	err_type	error	= NONE;
	uint32_t returnCode;
	filterState smoothingFilter;
	float averageTemp;
	
	while (1) {
		switch ( state ){
			case ST_INIT :
				/**************************************/
				/************ initialization **********/
				/**************************************/
			
				temp_init();
				initializeFilter(&smoothingFilter,34);
			
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
			case ST_RUNNING :
				/**************************************/
				/***************** run ****************/
				/**************************************/
				//if(interrupt_TIM2 == 1){
				//	interrupt_TIM2 = 0;
					osSignalWait(0x1,osWaitForever);
					//Read temperature
					//Fetch Temperature Sensor
					ADC_RegularChannelConfig(ADC1, ADC_Channel_TempSensor, 1, ADC_SampleTime_480Cycles); //Setting Channel and ADC
					ADC_SoftwareStartConv(ADC1); //Starting Conversion, waiting for it to finish, clearing the flag, reading the result
					while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); //Could be through interrupts (Later)
			 		float adcValue = (float)ADC_GetConversionValue(ADC1); // Result available in ADC1->DR
					ADC_ClearFlag(ADC1, ADC_FLAG_EOC); //EOC means End Of Conversion
					
					//calculate reference voltage
					float ref_Voltage_V = 2.85;
					
					//Calibrate adc output
					adcValue = adcValue * ref_Voltage_V / 3.3;
					
					//Calculate Temperature
					float temperature = ((((float) TS_CAL1 - adcValue))/AVG_SLOPE) + 30;
					
					averageTemp = modify_filterState(&smoothingFilter, temperature);
					
					/* Create message */
					osMessagePut(temp_mqueue, (uint32_t)averageTemp, osWaitForever);	
					
					
					//printf("%.2f\t%.2f\n", temperature, averageTemp);
					//printf("%d\n", averageTemp);
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
	}
}

void setInterruptTIM2(){
		interrupt_TIM2 = 1;
}
	