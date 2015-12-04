/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "stm32f4xx.h"                  // Device header

#include "stm32f4xx_conf.h"
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_l3gd20.h"
#include "background16bpp.h"

#include <stdio.h>
#include <string.h>


#include "wireless_controller.h"


uint8_t test[2];
uint8_t m_state = 0;
uint8_t write_test_sed[4]= {'2', '2', 'X', '2'};
int main (void) {
	CC2500_LowLevel_Init();
	setup();
	printf("running\n");
	//flush_RXFIFO();
	//read_RXFIFO();
	flush_TXFIFO();
	set_transmit_mode();
	transmit(write_test_sed, 4);
	//set_receive_mode();
	CC2500_Read(&m_state, CC2500_MARCSTATE, 2);
	
}