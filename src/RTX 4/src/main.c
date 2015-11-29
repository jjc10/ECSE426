/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#include "initialization.h"

void Blinky_GPIO_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
}

void Blinky(void const *argument){
	while(1){
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		//printf("hello world\n");
		osDelay(250);
	}
}

osThreadDef(Blinky, osPriorityNormal,1, 0);
osThreadDef(temp_thread, osPriorityNormal, 1, 0);
osThreadDef(acc_thread, osPriorityNormal, 1, 0);
//osThreadDef(gyro_thread, osPriorityNormal, 1, 0);
osThreadDef(display_controller_thread, osPriorityRealtime, 1, 0);
osThreadDef(keypad_thread, osPriorityNormal, 1, 0);

// ID for thread
osThreadId	Blinky_thread;
osThreadId	Temp_thread;
osThreadId	Acc_thread;
osThreadId	Gyro_thread;
osThreadId	Display_controller_thread;
osThreadId	Keypad_thread;

/*
 * main: initialize and start the system
 */
int int0 = 0;
int int1 = 0;
float offset = 0;
int calibrationThreshold = 500;
filterState  gyroFilter;

int main (void) {
  //osKernelInitialize ();                    // initialize CMSIS-RTOS
		
	
	// initialize			
	//Blinky_thread = osThreadCreate(osThread(Blinky), NULL);
	//Temp_thread = osThreadCreate(osThread(temp_thread), NULL);
	//Acc_thread = osThreadCreate(osThread(acc_thread), NULL);
	//Gyro_thread = osThreadCreate(osThread(gyro_thread), NULL);
	//Display_controller_thread = osThreadCreate(osThread(display_controller_thread), NULL);
	//Keypad_thread = osThreadCreate(osThread(keypad_thread), NULL);
	
	//osKernelStart ();                         // start thread execution 

	acc_init();
	gyro_init();
	float xlData[3];
	float gdData[3];
	int counter = 0;
	initializeFilter(&gyroFilter, 100);
	
	while(1){
		if(int1 == 1){
			int1 = 0;
			LSM9DS1_ReadACC(xlData);
			//printf("la");		
		}
		LSM9DS1_ReadGYRO(gdData);
		if (int0 == 1 && counter <= calibrationThreshold) {
			int0 = 0;
			
			offset = offset + gdData[1];
			if (counter == calibrationThreshold) {
				offset = offset / calibrationThreshold;
			}
			counter++;
			continue;
		}
		
		if(int0 == 1){
			int0 = 0;

			LSM9DS1_ReadGYRO(gdData);
			float calibrated = gdData[1] - offset;
			float filtered = modify_filterState(&gyroFilter, calibrated);
			printf("%f\n", filtered/*y*/);
		}
		
		
	}
	
	
}

void EXTI0_IRQHandler(void){
	int0 = 1;
	EXTI_ClearITPendingBit(EXTI_Line0);
	//osSignalSet(Acc_thread, 0x1);
}

void EXTI1_IRQHandler(void){
	int1 = 1;
	EXTI_ClearITPendingBit(EXTI_Line1);
	//osSignalSet(Gyro_thread, 0x1);
}

void TIM2_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	osSignalSet(Temp_thread, 0x1);
}

void TIM3_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	osSignalSet(Display_controller_thread, 0x1);
}

