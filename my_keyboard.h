#ifndef MY_KEYBOARD_H
	#define MY_KEYBOARD_H
	#include <stdint.h>
	
	void GPIO_init();
	void delay(int ms);
	void scan_keyboard(char * code, uint8_t * index);

#endif