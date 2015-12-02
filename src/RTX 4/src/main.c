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
		printf("hello world\n");
		osDelay(250);
	}
}

//osThreadDef(Blinky, osPriorityNormal,1, 0);
//osThreadDef(temp_thread, osPriorityNormal, 1, 0);
osThreadDef(acc_thread, osPriorityNormal, 1, 0);
osThreadDef(gyro_thread, osPriorityNormal, 1, 0);
//osThreadDef(display_controller_thread, osPriorityRealtime, 1, 0);
//osThreadDef(keypad_thread, osPriorityNormal, 1, 0);

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

step_states step_state = high;
int high_count = 0;
int low_count = 0;
int zero_count = 0;

int high_count_threshold = 30;
int low_count_threshold = 30;
int zero_count_threshold = 30;

int high_threshold = 60000;
int low_threshold = -60000;
int zero_threshold = 8000;

int calibration_count = 0;
int calibration_limit = 200;
int observations[40];
int obs_count = 0;

void updateStepState(float gyro_y){
		switch ( step_state ){
				
				/* Initialization state */
				case zero : {
					if(gyro_y >= high_threshold){
						high_count++;
						if (high_count >= high_count_threshold) {
							step_state = high;
							high_count = 0;
							low_count = 0;
							zero_count = 0;
							printf("High\n");
							observations[obs_count] = high;
							obs_count++;
						}
					}
					break;
				}
				case high : {
					if(gyro_y <= low_threshold){
						low_count++;
						if (low_count >= low_count_threshold) {
							step_state = low;
							high_count = 0;
							low_count = 0;
							zero_count = 0;
							printf("Low\n");
							observations[obs_count] = low;
							obs_count++;
						}
					}
					else if(fabs(gyro_y) <= zero_threshold){
						zero_count++;
						if (zero_count >= zero_count_threshold) {
							step_state = zero;
							high_count = 0;
							low_count = 0;
							zero_count = 0;
							printf("Zero\n");
							observations[obs_count] = zero;
							obs_count++;
						}
					}
					break;
				}
				case low :{
					if(gyro_y >= high_threshold){
						high_count++;
						if (high_count >= high_count_threshold) {
							step_state = high;
							high_count = 0;
							low_count = 0;
							zero_count = 0;
							printf("High\n");
							observations[obs_count] = high;
							obs_count++;
						}
					}
					break;
				}
			}
}
	
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
	float calibration_gyro_y_sum = 0;
	float calibration_gyro_z_sum = 0;
	filterState gyroYFilter;
	initializeFilter(&gyroYFilter,25);
	filterState gyroZFilter;
	initializeFilter(&gyroZFilter,25);
	
	while(1){
//		if(int1 == 1){
//			int1 = 0;
//			LSM9DS1_ReadACC(xlData);
//			printf("la");		
//		}
		
		if(int0 == 1){
			int0 = 0;
			LSM9DS1_ReadGYRO(gdData);
			if (calibration_count <= calibration_limit) {
				calibration_gyro_y_sum += gdData[1];
				calibration_gyro_z_sum += gdData[2];
				if (calibration_count == calibration_limit) {
					calibration_gyro_y_sum = calibration_gyro_y_sum / calibration_limit;
					calibration_gyro_z_sum = calibration_gyro_z_sum / calibration_limit;
				}
				calibration_count++;
				continue;
			}
			float calibrated_y_data = gdData[1] - calibration_gyro_y_sum;			
			float calibrated_z_data = gdData[2] - calibration_gyro_z_sum;
			float filtered_gyro_y = modify_filterState(&gyroYFilter,calibrated_y_data);
			float filtered_gyro_z = modify_filterState(&gyroZFilter,calibrated_z_data);
			
			
			updateStepState(filtered_gyro_y);	
			if (obs_count == 40) {
				printf("DONE\n");
			}
			float gyroZAngle = gyroZAngle + (filtered_gyro_z / 238000.0); 
			
			printf("%f\n", gyroZAngle);
			//printf("%f\t%f\t%f\n", gdData[0]/*x*/, gdData[1]/*y*/, gdData[2]/*z*/);
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

