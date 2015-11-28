#ifndef __os
#define __os
#include <cmsis_os.h>              // CMSIS RTOS header file

typedef struct {
    float    pitch;  
		float    roll;   
} message_acc;

extern osPoolDef(acc_mpool, 16, message_acc);
extern osMessageQDef(acc_mqueue, 16, message_acc);
extern osPoolId  acc_mpool;
extern osMessageQId  acc_mqueue;



#endif // __os