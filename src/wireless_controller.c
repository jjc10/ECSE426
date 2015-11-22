#include "wireless_controller.h"
#include <stdio.h>

uint8_t dummy_byte = DUMMY_BYTE;
uint8_t status_byte = 0; // status byte
uint8_t state_mask = 112;
uint8_t available_byte_mask = 15; // why 4 bits if 64 bytes in buffer
uint8_t buffer[32]; // to read and write from fifo

void fill_with_zeros(uint8_t* array, int length) {
	int i;
	for (i = 0; i < length; i++) {
		array[i] = 0;
	}
}

void setup() {
	config_wireless();
	CC2500_Read(&status_byte, CC2500_STX, 1); // signal
	fill_with_zeros(buffer, 64);
}

void set_transmit_mode() {
	uint8_t flag = status_byte & state_mask;
	while (flag != 32) {
		flush_TXFIFO(); // flush in case of overflow
		CC2500_Read(&status_byte, CC2500_STX, 1);
		flag = status_byte & state_mask;
	}
	
	
}

void set_receive_mode() {
	uint8_t flag = status_byte & state_mask;
	while (flag != 16) {
		flush_RXFIFO();
		CC2500_Read(&status_byte, CC2500_SRX, 1);
		flag = status_byte & state_mask;
	}
}

void flush_RXFIFO() {
	CC2500_Write(&dummy_byte, CC2500_SFRX, 1);
}

void flush_TXFIFO() {
	CC2500_Write(&dummy_byte, CC2500_SFTX, 1);
}

//TODO: Investigate how to receive multiple bytes. 
void read_RXFIFO() {
	int readable_bytes = 0;
	CC2500_Read(&status_byte, CC2500_SNOP, 1);
	readable_bytes = status_byte & available_byte_mask;
	int counter = 0;
	CC2500_Read(buffer, CC2500_FIFO, readable_bytes);
	
}


