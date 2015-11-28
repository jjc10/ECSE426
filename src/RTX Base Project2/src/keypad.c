#include "initialization.h"



void scanKeypad(int* rows, int* columns){
	rows[0]= GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1);
	rows[1]= GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2);
	rows[2]= GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4);
	rows[3]= GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5);
	columns[0]= GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6);
	columns[1]= GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8);
	columns[2]=	GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9);
	columns[3]= GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_11);
}

//void switchToOutput(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef pinInitializationStruct)
void switchRowToOutput(){
	GPIO_InitTypeDef initializeOUTPins_C;
	GPIO_StructInit(&initializeOUTPins_C);
	initializeOUTPins_C.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5;
	initializeOUTPins_C.GPIO_Mode = GPIO_Mode_OUT;
	initializeOUTPins_C.GPIO_Speed = GPIO_Speed_100MHz;
	initializeOUTPins_C.GPIO_OType = GPIO_OType_PP;
	initializeOUTPins_C.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &initializeOUTPins_C);
}
//void switchToInput(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef pinInitializationStruct)
void switchRowToInput(){
	GPIO_InitTypeDef initializeINPins_C;
	GPIO_StructInit(&initializeINPins_C);
	initializeINPins_C.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5;
	initializeINPins_C.GPIO_Mode = GPIO_Mode_IN;
	initializeINPins_C.GPIO_Speed = GPIO_Speed_100MHz;
	initializeINPins_C.GPIO_OType = GPIO_OType_PP;
	initializeINPins_C.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &initializeINPins_C);
}
void switchColumnToOutput(){
	GPIO_InitTypeDef initializeOUTPins_C;
	GPIO_StructInit(&initializeOUTPins_C);
	initializeOUTPins_C.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11;
	initializeOUTPins_C.GPIO_Mode = GPIO_Mode_OUT;
	initializeOUTPins_C.GPIO_Speed = GPIO_Speed_100MHz;
	initializeOUTPins_C.GPIO_OType = GPIO_OType_PP;
	initializeOUTPins_C.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &initializeOUTPins_C);
}
//void switchToInput(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef pinInitializationStruct)
void switchColumnToInput(){
	GPIO_InitTypeDef initializeINPins_C;
	GPIO_StructInit(&initializeINPins_C);
	initializeINPins_C.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11;
	initializeINPins_C.GPIO_Mode = GPIO_Mode_IN;
	initializeINPins_C.GPIO_Speed = GPIO_Speed_100MHz;
	initializeINPins_C.GPIO_OType = GPIO_OType_PP;
	initializeINPins_C.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &initializeINPins_C);
}
/* scans a single array and returns the index of the 0 in that array */
int scanInputArray(int* array, int size){
	int gtrdn, index = 0;
	for(gtrdn=0; gtrdn < size; gtrdn++){
		if(array[gtrdn] == 0){
			index = gtrdn;
			return index;
		}
	}
	return -1;
		
}

int keypadArray[4][4] = {{1,2,3,10},{4,5,6,11},{7,8,9,12},{16,0,17,13}};
	
int getPressedButton(){
		int rows[4], columns[4];
		int row = -1;
		int column = -1;
		/* Place high and low values into the arrays rows and columns */
		scanKeypad(rows, columns);
		/* Scan these arrays to check if a button has been pressed and if so what column it's in */
		column = scanInputArray(columns, 4);
		/* If a button was pressed */
		if(column >= 0){
			switchRowToInput();
			switchColumnToOutput();
			/* Place high and low values into the arrays rows and columns */
			scanKeypad(rows, columns);
			/* Check to see which row the button is in and place index in row */
			row = scanInputArray(rows, 4);
			switchRowToOutput();
			switchColumnToInput();
		}
		if(column >= 0 && rows >= 0){
			return keypadArray[row][column];
		}else{
			return -1;
		}

}

void keypad_thread(void const *argument){
	st_system_state state = ST_INIT ;	
	err_type	error	= NONE;
	keypad_state kp_state = WAIT_KEY;

	int pressedNumber = -1;

	
	while (1) {
		switch ( state ){
			case ST_INIT :
				/**************************************/
				/************ initialization **********/
				/**************************************/
				alpha_num_kp_init();
			
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
			case ST_RUNNING :{
				/**************************************/
				/***************** run ****************/
				/**************************************/
				
				switch (kp_state){
					case WAIT_KEY :
						pressedNumber = getPressedButton();
						
						if(pressedNumber == 1 || pressedNumber == 2 || pressedNumber == 10 || pressedNumber == 11 ){
							kp_state = ACTION;
						}
					
						break ;
					case ACTION :
						
						/* Create message */
						osMessagePut(kp_mqueue, (uint32_t)pressedNumber, osWaitForever);	

						kp_state = IDLE;
						break ;
					case IDLE :{
						int tempPress = getPressedButton();
						if(tempPress != pressedNumber){
							kp_state = WAIT_KEY;
							pressedNumber = -1;
						}
						break ;
					}
				}	

				/**************************************/
				break ;
			}	
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
		delay(200);
	}
}
