#ifndef MY_FRAM_H
	#define MY_FRAM_H
	#include "Driver_I2C.h"
	
	void I2C_Init();
	
	// do wpisania kodu do pamieci FRAM na adresy od 0x00 4 bajty
	void FRAM_Write_Code(uint8_t *data);
	
	// do odczytania kodu do pamieci FRAM na adresy od 0x00 4 bajty
	void FRAM_Read_Code(uint8_t *data);

#endif