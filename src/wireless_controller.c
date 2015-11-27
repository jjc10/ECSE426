#include "wireless_controller.h"
#include <stdio.h>


uint8_t dummy_byte = DUMMY_BYTE;
uint8_t status_byte = 0; // status byte
uint8_t s2[2];
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

uint8_t m_state_set_transmit = 0;
void set_transmit_mode() {
	CC2500_Read(&m_state_set_transmit, CC2500_MARCSTATE, 2);
	while (m_state_set_transmit != 19 && m_state_set_transmit != 20) {
		if (m_state_set_transmit == 22) {
			flush_TXFIFO();
		}
		CC2500_Read(&status_byte, CC2500_STX, 1);
		CC2500_Read(&m_state_set_transmit, CC2500_MARCSTATE, 2);
	}
}

uint8_t m_state_set_receive = 0;
void set_receive_mode() {
	CC2500_Read(&m_state_set_receive, CC2500_MARCSTATE, 2);
	while(m_state_set_receive != 13 && m_state_set_receive != 14 && m_state_set_receive != 15) {
	if (m_state_set_receive == 17) {
		flush_RXFIFO();
	}
		CC2500_Read(&status_byte, CC2500_SRX, 1);
		CC2500_Read(&m_state_set_receive, CC2500_MARCSTATE, 2);
	}
	
	/*
	uint8_t flag = status_byte & state_mask;
	while (flag != 16) {
		flush_RXFIFO();
		CC2500_Read(&status_byte, CC2500_SRX, 1);
		flag = status_byte & state_mask;
	}
	*/
}

void flush_RXFIFO() {
	CC2500_Write(&dummy_byte, CC2500_SFRX, 1);
}

void flush_TXFIFO() {
	CC2500_Write(&dummy_byte, CC2500_SFTX, 1);
}

//TODO: proper timer to avoid skipping values
uint8_t bytes_received = 0;
uint8_t m_state_read_rxfifo;
void read_RXFIFO() {
	set_receive_mode();
	CC2500_Read(&bytes_received, CC2500_RXBYTES, 2);
	int bytes_read = 0;
	uint32_t i;
	
	//TODO: Investigate why bytes_received is acting like a mofo
	/*
	while (bytes_received == 0) { // busy wait
		CC2500_Read(&bytes_received, CC2500_RXBYTES, 2);
		for (i = 0; i < 16800000; i++);
	}*/
	while (1) { // this should be replaced with check on number of bytes received
		CC2500_Read((buffer + bytes_read), CC2500_FIFO, 1);
		CC2500_Read(&bytes_received, CC2500_RXBYTES, 2);
		for (i = 0; i < 16800000; i++); // delay
		CC2500_Read(&m_state_read_rxfifo, CC2500_MARCSTATE, 2);
		if (m_state_read_rxfifo != 13 && m_state_read_rxfifo != 14 && m_state_read_rxfifo != 15) {
			set_receive_mode();
		}
		bytes_read = (bytes_read + 1)  % 32; // change to buffer length for greater modularity
	}
}

uint8_t write_test[5]= {2, 2, 'A', 'X', 'T'};
void transmit(uint8_t* array, int length) {
	uint8_t i = 0;
	uint8_t pending_write = 0;
	
	do {
		CC2500_Read(s2, CC2500_MARCSTATE | 0xC0, 1);
		if (s2[0] != 19) {
			CC2500_Read(s2 + 1, CC2500_STX | 0xC0, 1);
		} else {
			break;
		}
	} while (1);
	
	while (1) {
		/*set_transmit_mode();
		uint8_t a = 2;
		CC2500_Write(&a, CC2500_FIFO, 1);
		int i;
		for (i = 0; i < 16900000; i++);
		a = 5;
		CC2500_Write(&a, CC2500_FIFO, 1);
		for (i = 0; i < 16900000; i++);*/
		
		
		
		
		CC2500_Read(s2, CC2500_MARCSTATE, 2);
		
		if (s2[0] == 22) {
			i = 1;
		} else if (s2[0] == 19 && pending_write == 0) {
			CC2500_Write(write_test + i, CC2500_FIFO, 1);
			i = (i + 1) % 5;
			pending_write = 1;
		} else {
			CC2500_Read(s2 + 1, CC2500_STX, 1);
			pending_write = 0;
		}
		for (uint32_t j = 0; j < 18641351; j++);
		
//		uint8_t num_bytes = 4;
//		CC2500_Write(&num_bytes, CC2500_FIFO, 1);
//		int i;
//		for (i = 0; i < 1690000; i++);
//		CC2500_Write(write_test, CC2500_FIFO, num_bytes);
//		
//		for (i = 0; i < 1690000; i++);
//		set_transmit_mode();
		
	}
	
}


