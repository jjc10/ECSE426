#include "initialization.h"

int tick = 0;

void displayNothing(){
	GPIO_ResetBits		(pinGroup, segA);
	GPIO_ResetBits		(pinGroup, segB);
	GPIO_ResetBits		(pinGroup, segC);
	GPIO_ResetBits		(pinGroup, segD);
	GPIO_ResetBits		(pinGroup, segE);
	GPIO_ResetBits		(pinGroup, segF);
	GPIO_ResetBits		(pinGroup, segG);
	GPIO_ResetBits		(pinGroup, segDP);	
}

void displayZero(){
	GPIO_SetBits		(pinGroup, segA);
	GPIO_SetBits		(pinGroup, segB);
	GPIO_SetBits		(pinGroup, segC);
	GPIO_SetBits		(pinGroup, segD);
	GPIO_SetBits		(pinGroup, segE);
	GPIO_SetBits		(pinGroup, segF);
	GPIO_ResetBits	(pinGroup, segG);
	GPIO_ResetBits	(pinGroup, segDP);	
}

void displayOne(){
	GPIO_ResetBits	(pinGroup, segA);
	GPIO_SetBits		(pinGroup, segB);
	GPIO_SetBits		(pinGroup, segC);
	GPIO_ResetBits	(pinGroup, segD);
	GPIO_ResetBits	(pinGroup, segE);
	GPIO_ResetBits	(pinGroup, segF);
	GPIO_ResetBits	(pinGroup, segG);
	GPIO_ResetBits	(pinGroup, segDP);	
}
void displayTwo(){
	GPIO_SetBits		(pinGroup, segA);
	GPIO_SetBits		(pinGroup, segB);
	GPIO_ResetBits	(pinGroup, segC);
	GPIO_SetBits		(pinGroup, segD);
	GPIO_SetBits		(pinGroup, segE);
	GPIO_ResetBits	(pinGroup, segF);
	GPIO_SetBits		(pinGroup, segG);
	GPIO_ResetBits	(pinGroup, segDP);
}
void displayThree(){
	GPIO_SetBits		(pinGroup, segA);
	GPIO_SetBits		(pinGroup, segB);
	GPIO_SetBits		(pinGroup, segC);
	GPIO_SetBits		(pinGroup, segD);
	GPIO_ResetBits	(pinGroup, segE);
	GPIO_ResetBits	(pinGroup, segF);
	GPIO_SetBits		(pinGroup, segG);
	GPIO_ResetBits	(pinGroup, segDP);	
}
void displayFour(){
	GPIO_ResetBits	(pinGroup, segA);
	GPIO_SetBits		(pinGroup, segB);
	GPIO_SetBits		(pinGroup, segC);
	GPIO_ResetBits	(pinGroup, segD);
	GPIO_ResetBits	(pinGroup, segE);
	GPIO_SetBits		(pinGroup, segF);
	GPIO_SetBits		(pinGroup, segG);
	GPIO_ResetBits	(pinGroup, segDP);
}
void displayFive(){
	GPIO_SetBits		(pinGroup, segA);
	GPIO_ResetBits	(pinGroup, segB);
	GPIO_SetBits		(pinGroup, segC);
	GPIO_SetBits		(pinGroup, segD);
	GPIO_ResetBits	(pinGroup, segE);
	GPIO_SetBits		(pinGroup, segF);
	GPIO_SetBits		(pinGroup, segG);
	GPIO_ResetBits	(pinGroup, segDP);
}
void displaySix(){
	GPIO_SetBits		(pinGroup, segA);
	GPIO_ResetBits	(pinGroup, segB);
	GPIO_SetBits		(pinGroup, segC);
	GPIO_SetBits		(pinGroup, segD);
	GPIO_SetBits		(pinGroup, segE);
	GPIO_SetBits		(pinGroup, segF);
	GPIO_SetBits		(pinGroup, segG);
	GPIO_ResetBits	(pinGroup, segDP);	
}
void displaySeven(){
	GPIO_SetBits		(pinGroup, segA);
	GPIO_SetBits		(pinGroup, segB);
	GPIO_SetBits		(pinGroup, segC);
	GPIO_ResetBits	(pinGroup, segD);
	GPIO_ResetBits	(pinGroup, segE);
	GPIO_ResetBits	(pinGroup, segF);
	GPIO_ResetBits	(pinGroup, segG);
	GPIO_ResetBits	(pinGroup, segDP);
}
void displayEight(){
	GPIO_SetBits		(pinGroup, segA);
	GPIO_SetBits		(pinGroup, segB);
	GPIO_SetBits		(pinGroup, segC);
	GPIO_SetBits		(pinGroup, segD);
	GPIO_SetBits		(pinGroup, segE);
	GPIO_SetBits		(pinGroup, segF);
	GPIO_SetBits		(pinGroup, segG);
	GPIO_ResetBits	(pinGroup, segDP);	
}
void displayNine(){
	GPIO_SetBits		(pinGroup, segA);
	GPIO_SetBits		(pinGroup, segB);
	GPIO_SetBits		(pinGroup, segC);
	GPIO_SetBits		(pinGroup, segD);
	GPIO_ResetBits	(pinGroup, segE);
	GPIO_SetBits		(pinGroup, segF);
	GPIO_SetBits		(pinGroup, segG);
	GPIO_ResetBits	(pinGroup, segDP);	
}
void displayLine(){
	GPIO_ResetBits		(pinGroup, segA);
	GPIO_ResetBits		(pinGroup, segB);
	GPIO_ResetBits		(pinGroup, segC);
	GPIO_SetBits			(pinGroup, segD);
	GPIO_ResetBits		(pinGroup, segE);
	GPIO_ResetBits		(pinGroup, segF);
	GPIO_ResetBits		(pinGroup, segG);
	GPIO_ResetBits		(pinGroup, segDP);	
}
void displayDegree(){
	GPIO_SetBits			(pinGroup, segA);
	GPIO_SetBits			(pinGroup, segB);
	GPIO_ResetBits		(pinGroup, segC);
	GPIO_ResetBits		(pinGroup, segD);
	GPIO_ResetBits		(pinGroup, segE);
	GPIO_SetBits		(pinGroup, segF);
	GPIO_SetBits		(pinGroup, segG);
	GPIO_ResetBits		(pinGroup, segDP);	
}
void displayNumber(int number){
	if(number > 9999){
		number=number%10000;
	}
	int digit[4];
	
	/* Separate Digits  MAKE FUNCTION*/
	digit[3]=number%10;
	number  = (number-digit[3])/10;
	digit[2]= (number%10);
	number  = (number-digit[2])/10;
	digit[1]= (number%10);
	number  = (number-digit[1])/10;
	digit[0]= (number%10);
	
	switch (tick){
		case 0:
			selectDigit(0);
			displayDigit(digit[1]);
			break;
		case 1:
			selectDigit(1);
			displayDigit(digit[2]);
			break;
		case 2:
			selectDigit(2);
			displayDigit(digit[3]);
			break;
		case 3:
			selectDigit(3);
			displayDegree();
			break;
	}
	
	tick = (tick+1)%4;
}
void selectDigit(int digitNumber){
	switch (digitNumber){
		case 0:
			GPIO_ResetBits	(pinGroup, dig1);
			GPIO_SetBits		(pinGroup, dig2);
			GPIO_SetBits		(pinGroup, dig3);
			GPIO_SetBits		(pinGroup, dig4);
			break;
		case 1:
			GPIO_SetBits		(pinGroup, dig1);
			GPIO_ResetBits	(pinGroup, dig2);
			GPIO_SetBits		(pinGroup, dig3);
			GPIO_SetBits		(pinGroup, dig4);
			break;
		case 2:
			GPIO_SetBits		(pinGroup, dig1);
			GPIO_SetBits		(pinGroup, dig2);
			GPIO_ResetBits	(pinGroup, dig3);
			GPIO_SetBits		(pinGroup, dig4);
			break;
		case 3:
			GPIO_SetBits		(pinGroup, dig1);
			GPIO_SetBits		(pinGroup, dig2);
			GPIO_SetBits		(pinGroup, dig3);
			GPIO_ResetBits	(pinGroup, dig4);
			break;
	}
}
void displayDigit(int digitNumber){
	switch (digitNumber){
		case 0:
			displayZero();
			break;
		case 1:
			displayOne();
			break;
		case 2:
			displayTwo();
			break;
		case 3:
			displayThree();
			break;
		case 4:
			displayFour();
			break;
		case 5:
			displayFive();
			break;
		case 6:
			displaySix();
			break;
		case 7:
			displaySeven();
			break;
		case 8:
			displayEight();
			break;
		case 9:
			displayNine();
			break;
		case 10:
			displayLine();
			break;
			
	}
}
void displayDPAt(int position){
	switch (tick){
		case 0:
			if (position == tick){
				GPIO_SetBits(pinGroup, segDP);	
			} else {
				GPIO_ResetBits(pinGroup, segDP);	
			}
			break;
		case 1:
			if (position == tick){
				GPIO_SetBits(pinGroup, segDP);	
			} else {
				GPIO_ResetBits(pinGroup, segDP);	
			}
			break;
		case 2:
			if (position == tick){
				GPIO_SetBits(pinGroup, segDP);	
			} else {
				GPIO_ResetBits(pinGroup, segDP);	
			}
			break;
		case 3:
			if (position == tick){
				GPIO_SetBits(pinGroup, segDP);	
			} else {
				GPIO_ResetBits(pinGroup, segDP);	
			}
			break;
	}
}

void display_thread(void const *argument){
	st_system_state state = ST_INIT ;	
	err_type	error	= NONE;
	
	while (1) {

		switch ( state ){
			case ST_INIT :
				/**************************************/
				/************ initialization **********/
				/**************************************/

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
	}
}
