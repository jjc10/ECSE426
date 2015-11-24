#include "CC2500_driver.h"
void setup();
void set_transmit_mode();
void get_state();
void set_receive_mode();
void flush_RXFIFO();
void flush_TXFIFO();
void read_RXFIFO();
void transmit(uint8_t* array, int length);
//set Csn low during transfer. Then SO should go low too.