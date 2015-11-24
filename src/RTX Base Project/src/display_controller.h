#include "osObjects.h"   

extern osPoolId  acc_mpool;
extern osMessageQId  acc_mqueue;
extern osMessageQId  temp_mqueue;
extern osMessageQId  kp_mqueue;

//Display State
typedef enum {
	DISPLAY_TEMP,
	DISPLAY_ACC		
}display_state;

//Display Acc States
typedef enum {
	DISPLAY_PITCH,
	DISPLAY_ROLL		
}display_acc_state;

//Display Acc States
typedef enum {
	ALARM_ON,
	ALARM_OFF		
}display_alarm_state;

//Display Acc States
typedef enum {
	DISPLAY_ON,
	DISPLAY_OFF		
}display_ON_OFF;


void display_controller_thread(void const *argument);
