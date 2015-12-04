/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#include "initialization.h"
#include "wireless_controller.h"

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
uint8_t write_test_sed[4]= {'2', '2', 'X', '2'};
uint8_t m_state = 0;
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
		int calibration_count = 0;
		int calibration_limit = 200;
		
	//	while(1){
	//		if(int1 == 1){
	//			int1 = 0;
	//			LSM9DS1_ReadACC(xlData);
	//			printf("la");		
	//		}
			
//			if(int0 == 1){
//				int0 = 0;
//				LSM9DS1_ReadGYRO(gdData);
//				if (calibration_count <= calibration_limit) {
//					calibration_gyro_y_sum += gdData[1];
//					calibration_gyro_z_sum += gdData[2];
//					if (calibration_count == calibration_limit) {
//						calibration_gyro_y_sum = calibration_gyro_y_sum / calibration_limit;
//						calibration_gyro_z_sum = calibration_gyro_z_sum / calibration_limit;
//					}
//					calibration_count++;
//					continue;
//				}
//				float calibrated_y_data = gdData[1] - calibration_gyro_y_sum;			
//				float calibrated_z_data = gdData[2] - calibration_gyro_z_sum;
//				float filtered_gyro_y = modify_filterState(&gyroYFilter,calibrated_y_data);
//				float filtered_gyro_z = modify_filterState(&gyroZFilter,calibrated_z_data);
//				
//				int heading = getHeading(filtered_gyro_z);
//				//printf("%d\n", heading);
//				//printf("%f\n", heading);
//				updateStepState(filtered_gyro_y);	
//				updateTrajectory(heading);

				
				//printf("%f\n", gyroZAngle);
				//printf("%f\t%f\t%f\n", gdData[0]/*x*/, gdData[1]/*y*/, gdData[2]/*z*/);
			//}
					CC2500_LowLevel_Init();
					setup();
					//printf("running\n");
					set_receive_mode();
					//CC2500_Read();
					uint8_t a = 7;
					CC2500_Write(&a, CC2500_TEST0, 1);
					uint8_t b = 0;
					CC2500_Read(&b, CC2500_TEST0, 1);
					//CC2500_Read(&bytes_received, CC2500_RXBYTES, 2);
					//flush_RXFIFO();
					//read_RXFIFO();
					//flush_TXFIFO();
					//set_transmit_mode();
					//transmit(write_test_sed, 4);
	//set_receive_mode();
					//CC2500_Read(&m_state, CC2500_MARCSTATE, 2);
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

