#ifndef MY_FRAM_H
	#define MY_FRAM_H
	#include "Driver_I2C.h"
	
	void I2C_Init();
	
	// do wpisania kodu do pamieci FRAM na adresy od 0x00 4 bajty
	void FRAM_Write_Code(unsigned char *data);
	
	// do odczytania kodu do pamieci FRAM na adresy od 0x00 4 bajty
	void FRAM_Read_Code(unsigned char *data);
	
	// bedzie sluzyc do zapisywania dat do FRAM
	void FRAM_Write_Logs();
	
	// bedzie sluzyc do odczytywania dat zapisywanych w FRAM
	void FRAM_Read_Logs();
	


#endif