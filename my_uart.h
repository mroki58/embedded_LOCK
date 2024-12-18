#ifndef MY_UART_H
	#define MY_UART_H
	#include "LPC17xx.h"
	#include "PIN_LPC17xx.h"
	#include "GPIO_LPC17xx.h"
	#include <string.h>
	
	// inicjalizuje komunikacje UART o predkosci 115200
	void UART0_init();
	
	// wysyla znak UART
	void send_char(char c);
	
	// wysyla string UART
	void send_str(char * str);
	
#endif