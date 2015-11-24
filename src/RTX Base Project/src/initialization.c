/**
  ******************************************************************************
  * @file    initialization.c
  * @author  Bassam Riman 		260367410
	*					 Matthew Beiruti 	XXXXXXXXX
  * @version V1.0.0
  * @date    10-October-2015
  * @brief   This file handles different component initialization in the system     
  ****************************************************************************** 
  */

#include "initialization.h"



/**
  * @brief  MEMS accelerometer initialization
  * @param  None
  * @retval None
  */
void acc_init(){
	
	/*Configure MEMS */
	LIS3DSH_InitTypeDef mems_init_struct;
	mems_init_struct.Power_Mode_Output_DataRate = LIS3DSH_DATARATE_100;
	mems_init_struct.Axes_Enable = LIS3DSH_X_ENABLE | LIS3DSH_Y_ENABLE | LIS3DSH_Z_ENABLE;
  mems_init_struct.Continous_Update = LIS3DSH_ContinousUpdate_Disabled;
	mems_init_struct.AA_Filter_BW = LIS3DSH_AA_BW_50;				/* Not sure */
  mems_init_struct.Full_Scale = LIS3DSH_FULLSCALE_2;
  mems_init_struct.Self_Test = LIS3DSH_SELFTEST_NORMAL;
  LIS3DSH_Init(&mems_init_struct);
	
	/*Configure MEMS interrupts */
	LIS3DSH_DRYInterruptConfigTypeDef mems_int_config_s;
	mems_int_config_s.Dataready_Interrupt = LIS3DSH_DATA_READY_INTERRUPT_ENABLED; //Enable (Not sure if INT1 or INT2 or both get activated
	mems_int_config_s.Interrupt_signal = LIS3DSH_ACTIVE_HIGH_INTERRUPT_SIGNAL; // Inturrupt on High
	mems_int_config_s.Interrupt_type = LIS3DSH_INTERRUPT_REQUEST_LATCHED; // Not sure if LATCHED or PULSED
	LIS3DSH_DataReadyInterruptConfig(&mems_int_config_s);
	
	/*Activating clocks*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); /* Activate SYSCFG in order to link PE0 to EXTI0 
																														Check Figure 27 in Reference Manual*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);	 /* Activate E in order to use pin PE0, PE1, PE3 
																														used by MEMS */
	
	/*Configure PE0 used by MEMS_INT1 output of MEMS (check Schematics)*/
	GPIO_InitTypeDef GPIO_config_s;
	GPIO_config_s.GPIO_Mode = GPIO_Mode_IN;
  GPIO_config_s.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_config_s.GPIO_Pin = GPIO_Pin_0;
	GPIO_config_s.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_config_s.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOE, &GPIO_config_s);
	
	/*Configure EXTI0 to linsten to intturupts */
	EXTI_InitTypeDef EXTI_config_s;
	EXTI_config_s.EXTI_Line = EXTI_Line0;
  EXTI_config_s.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_config_s.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_config_s.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_config_s);
	
	/*Link PE0 to EXTI0*/ 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);
	
	/*Enable interrupt control and set priority of EXTI0*/
	NVIC_InitTypeDef   NVIC_config_s;
  NVIC_config_s.NVIC_IRQChannel = EXTI0_IRQn;							//Channel
  NVIC_config_s.NVIC_IRQChannelPreemptionPriority = 0x00; //Set x higher than y
  NVIC_config_s.NVIC_IRQChannelSubPriority = 0x00;				//Set x1 higher the x2
  NVIC_config_s.NVIC_IRQChannelCmd = ENABLE;							//Enable
  NVIC_Init(&NVIC_config_s);

}

/**
  * @brief  MEMS accelerometer initialization
  * @param  None
  * @retval None
  */
void acc_ext_init(){
	
	/*Configure MEMS */
	LSM9DS1_InitTypeDef mems_init_struct;
	mems_init_struct.Power_Mode_Output_DataRate = LSM9DS1_DATARATE_119_XL;
	mems_init_struct.Axes_Enable = LSM9DS1_X_ENABLE | LSM9DS1_Y_ENABLE | LSM9DS1_Z_ENABLE;
  mems_init_struct.Decimation = LSM9DS1_DECIMATION_0;
	mems_init_struct.BW_select = LSM9DS1_BW_SELECT_ODR;				/* Not sure */
  mems_init_struct.Full_Scale = LSM9DS1_FULLSCALE_2_XL;
  mems_init_struct.AA_Filter_BW = LSM9DS1_AA_BW_XL_50;
  LSM9DS1_Init(&mems_init_struct);
	
	/*Configure Gyro */
	LSM9DS1_InitTypeDef mems_init_struct1;
	mems_init_struct1.Power_Mode_Output_DataRate = LSM9DS1_DATARATE_238_G;
  mems_init_struct1.Full_Scale = LSM9DS1_FULLSCALE_245_G;
  mems_init_struct1.AA_Filter_BW = LSM9DS1_AA_BW_G_00;
  LSM9DS1_Gyro_Init(&mems_init_struct1);
	
	
	/*Configure MEMS interrupts */
	LSM9DS1_DRYInterruptConfigTypeDef mems_int_config_s;
	mems_int_config_s.XL_Dataready_Interrupt = 0X00;//LSM9DS1_INT1_DRDY_XL_ENABLE; 
	mems_int_config_s.G_Dataready_Interrupt = LSM9DS1_INT1_DRDY_G_ENABLE;
	LSM9DS1_INT1_Config(&mems_int_config_s);
	
	/*Activating clocks*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); /* Activate SYSCFG in order to link PE0 to EXTI0 
																														Check Figure 27 in Reference Manual*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);	 /* Activate E in order to use pin PE0, PE1, PE3 
																														used by MEMS */
	
	/*Configure PE0 used by MEMS_INT1 output of MEMS (check Schematics)*/
	GPIO_InitTypeDef GPIO_config_s;
	GPIO_config_s.GPIO_Mode = GPIO_Mode_IN;
  GPIO_config_s.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_config_s.GPIO_Pin = GPIO_Pin_0;
	GPIO_config_s.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_config_s.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOE, &GPIO_config_s);
	
	/*Configure EXTI0 to linsten to intturupts */
	EXTI_InitTypeDef EXTI_config_s;
	EXTI_config_s.EXTI_Line = EXTI_Line0;
  EXTI_config_s.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_config_s.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_config_s.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_config_s);
	
	/*Link PE0 to EXTI0*/ 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);
	
	/*Enable interrupt control and set priority of EXTI0*/
	NVIC_InitTypeDef   NVIC_config_s;
  NVIC_config_s.NVIC_IRQChannel = EXTI0_IRQn;							//Channel
  NVIC_config_s.NVIC_IRQChannelPreemptionPriority = 0x00; //Set x higher than y
  NVIC_config_s.NVIC_IRQChannelSubPriority = 0x00;				//Set x1 higher the x2
  NVIC_config_s.NVIC_IRQChannelCmd = ENABLE;							//Enable
  NVIC_Init(&NVIC_config_s);

}

/**
  * @brief  Enabling the ADC and temperature sensor. Initializing them and defining GPIO pins.
  * @param  None
  * @retval None
  */
void temp_init(){

	//GPIO D Init
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  //Clock Gating
	
	GPIO_InitTypeDef gpio_init_s;
	GPIO_StructInit(&gpio_init_s);
	gpio_init_s.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;// Select pin 4
	gpio_init_s.GPIO_Mode = GPIO_Mode_OUT; // Set as output
	gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate
	gpio_init_s.GPIO_OType = GPIO_OType_PP; // Push-pull
	gpio_init_s.GPIO_PuPd = GPIO_PuPd_NOPULL; // Not input, don't pull
	
	GPIO_Init(GPIOD, &gpio_init_s);	//Initialize GPIOD

	//ADC Init
	ADC_DeInit();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //Enabling Clock (Clock Gating)
	
	ADC_CommonInitTypeDef adc_common_init_s;
	adc_common_init_s.ADC_Mode = ADC_Mode_Independent;
	adc_common_init_s.ADC_Prescaler = ADC_Prescaler_Div2;
	adc_common_init_s.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	adc_common_init_s.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&adc_common_init_s); //Initialization
	
	ADC_InitTypeDef adc_init_s;
	adc_init_s.ADC_Resolution = ADC_Resolution_12b;
	adc_init_s.ADC_ScanConvMode = DISABLE; // To ensure one sample at a time
	adc_init_s.ADC_ContinuousConvMode = DISABLE;
	adc_init_s.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	adc_init_s.ADC_DataAlign = ADC_DataAlign_Right; // Aligns data to the right, filling empty left with 0s
	adc_init_s.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &adc_init_s); //Initialization

	//Enable
	ADC_TempSensorVrefintCmd(ENABLE); //Enable Temperature Sensor
	ADC_Cmd(ADC1, ENABLE); //Enable ADC1
	
	//Initialize Timer 2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef timerInitStructure; 
	timerInitStructure.TIM_Prescaler = 100 - 1;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 500 - 1;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timerInitStructure);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
	
	//Enable interrupt control and set priority of TIM2_IRQn
	NVIC_InitTypeDef   NVIC_config_s;
  NVIC_config_s.NVIC_IRQChannel = TIM2_IRQn; //Channel
  NVIC_config_s.NVIC_IRQChannelPreemptionPriority = 0x00; //Set x higher than y
  NVIC_config_s.NVIC_IRQChannelSubPriority = 0x02; //Set x1 higher the x2
  NVIC_config_s.NVIC_IRQChannelCmd = ENABLE; //Enable
  NVIC_Init(&NVIC_config_s);
}

/**
  * @brief  7 segment display iniatialization
  * @param  None
  * @retval None
  */
void seg_7_display_init(){
	/* Initializing GPIO for 7 Segment Display */
	/* GPIO B */
	/*
	Key:
	B0: 	Digit 1
	B1: 	Digit 2
	B2: 	Digit 3
	B4: 	Digit 4
	B5: 	A
	B7: 	B
	B8: 	C
	B11:	D
	B12: 	E
	B13:	F
	B14:	G
	B15:	DP
	*/
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef initializePins_B;
	GPIO_StructInit(&initializePins_B);
	
	initializePins_B.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	initializePins_B.GPIO_Mode = GPIO_Mode_OUT;
	initializePins_B.GPIO_Speed = GPIO_Speed_100MHz;
	initializePins_B.GPIO_OType = GPIO_OType_PP;
	initializePins_B.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOB, &initializePins_B);
	
	/*Initialize Timer 3*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseInitTypeDef timerInitStructure; 
	timerInitStructure.TIM_Prescaler = 100 - 1;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 500 - 1;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &timerInitStructure);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM3, ENABLE);

	/*Enable interrupt control and set priority of TIM3_IRQn*/
	NVIC_InitTypeDef   NVIC_config_s;
  NVIC_config_s.NVIC_IRQChannel = TIM3_IRQn; //Channel
  NVIC_config_s.NVIC_IRQChannelPreemptionPriority = 0x00; //Set x higher than y
  NVIC_config_s.NVIC_IRQChannelSubPriority = 0x01; //Set x1 higher the x2
  NVIC_config_s.NVIC_IRQChannelCmd = ENABLE; //Enable
  NVIC_Init(&NVIC_config_s);
}

/**
  * @brief  Numberpad intialization
  * @param  None
  * @retval None
  */
void alpha_num_kp_init(){
	/* Initializing GPIO for Keypad */
	/* Key */
	/*
	C1:		R0
	C2:		R1
	C4:		R2
	C5:		R3
	C6:		C0
	C8:		C1
	C9:		C2
	C11:	C3
	*/
	
	GPIO_InitTypeDef initializeOUTPins_C;
	GPIO_InitTypeDef initializeINPins_C;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	/* Output Pins */ /*ROWS*/
	
	GPIO_StructInit(&initializeOUTPins_C);
	initializeOUTPins_C.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5;
	initializeOUTPins_C.GPIO_Mode = GPIO_Mode_OUT;
	initializeOUTPins_C.GPIO_Speed = GPIO_Speed_100MHz;
	initializeOUTPins_C.GPIO_OType = GPIO_OType_PP;
	initializeOUTPins_C.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &initializeOUTPins_C);
	
	/* Input Pins */ /*COLUMNS*/
	
	GPIO_StructInit(&initializeINPins_C);
	initializeINPins_C.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11;
	initializeINPins_C.GPIO_Mode = GPIO_Mode_IN;
	initializeINPins_C.GPIO_Speed = GPIO_Speed_100MHz;
	initializeINPins_C.GPIO_OType = GPIO_OType_PP;
	initializeINPins_C.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &initializeINPins_C);
}
/**
  * @brief  Calibration of Data
  * @param  None
  * @retval None
  */
void offsetAccData(float* array){
	array[0] += xOffset;
	array[1] += yOffset;
	array[2] += zOffset;
}
/**
  * @brief  Initializing LED's on the board
  * @param  None
  * @retval None
  */
void board_led_init(){
	//GPIO D Init
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  //Clock Gating
	
	GPIO_InitTypeDef gpio_init_s;
	GPIO_StructInit(&gpio_init_s);
	gpio_init_s.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; // So far I have only selected pins for LED alarm
	gpio_init_s.GPIO_Mode = GPIO_Mode_OUT; // Set as output
	gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate
	gpio_init_s.GPIO_OType = GPIO_OType_PP; // Push-pull
	gpio_init_s.GPIO_PuPd = GPIO_PuPd_NOPULL; // Not input, don't pull
	
	GPIO_Init(GPIOD, &gpio_init_s);	//Initialize GPIOD
}
