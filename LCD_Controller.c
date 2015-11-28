#include "initialization.h"
#include <stdio.h>
#include "STM32F4xx_ltdc.h"
#include "STM32F4xx_fmc.h"
#include "STM32F4xx_dma2d.h"
#include "STM32F429i_discovery.h"
#include "STM32F429i_discovery_lcd.h"
#include "STM32F429i_discovery_sdram.h"
#include "fonts.h"


int main () {
	
	
		st_system_state state = ST_INIT ;	
	
	
		while (1) {
		
		/* The system can be in multiple states, this is just good coding practice */
		switch ( state ){
			
			/* Initialization state */
			case ST_INIT :
				/**************************************/
				/************ initialization **********/
				/**************************************/			
					
					LCD_Init();
	
					LCD_LayerInit();
	
					LTDC_Cmd(ENABLE);
	
					LCD_SetLayer(LCD_FOREGROUND_LAYER);
			
				/**************************************/
				state = ST_IDLE ;
				break ;
			
			/* Idle State */
			case ST_IDLE :
				/**************************************/
				/**************** idle ****************/
				/**************************************/
			
				/* WAIT FOR MESSAGE TO BE PASSED HERE */
			
				/**************************************/
				state = ST_RUNNING ;
				break ;
			
			/* The system is running here the majority of the time */
			case ST_RUNNING :
				/**************************************/
				/***************** run ****************/
				/**************************************/

				/* DRAW THE NECESSARY LINES AND MAKE ANY ADJUSTMENTS TO SCALE */
				// update_status(newStatus); // indicates on the screen whether person is stopped or moving
				// update_heading(angle); // indicates on the screen what heading the person has
				// add_lines(ViterbiDataStructure[] someArray); //array acts as a buffer to ensure no data is lost or skipped
				// modify_scale(); // this function should check to see if the lines are reachnig the edge of the map area, if so zoom out
				// 
				
				/**************************************/
				break ;
				
				
			case ST_ERROR :
				/**************************************/
				/**************** error ***************/
				/**************************************/
				
			
			
				/* IF INVALID VITERBI DATA IS SENT GO HERE */
				/* INDICATE DISCONNECTION AND OTHER THINGS HERE */
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
		//osDelay(250);
	}
	

	
	return 0;
}


