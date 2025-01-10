// zabiera piny 0.0 i 0.1
#include "my_fram.h"
#include "my_uart.h"
#include <stdio.h>

#define I2C_ADDR_FRAM  (0xA0 >> 1)   // Adres I2C urzadzenia FRAM (7-bitowy)
#define I2C_ADDR_FRAM_LOGS (0xA2 >> 1)

extern ARM_DRIVER_I2C Driver_I2C1;

void I2C_Init() 
{   
		Driver_I2C1.Initialize(NULL);                   // Inicjalizacja sterownika
    Driver_I2C1.PowerControl(ARM_POWER_FULL);       // Zasilenie I2C
    Driver_I2C1.Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST); // Ustawienie predkosci magistrali
    Driver_I2C1.Control(ARM_I2C_BUS_CLEAR, 0);      // Czyszczenie magistrali
}

// dla length == 4 - 4 bajty kodu przesylane sa
// kody sa na 0x00
void FRAM_Write_Code(unsigned char *data) 
{	
		int status; 
		char buf[5];
	
    uint8_t buffer[5]; // bajt adresu + dane
		buffer[0] = 0x00;
	
    for (uint8_t i = 0; i < 4; i++) {
        buffer[1 + i] = data[i];  // Dane do zapisania
    }
		

    // Wyslanie danych do FRAM
    status = Driver_I2C1.MasterTransmit(I2C_ADDR_FRAM, buffer, 5, false); // false = stop
		sprintf(buf, "%d", status);
		send_str(buf);
		
		
    while (Driver_I2C1.GetStatus().busy);  // Czekaj na zakonczenie transmisji
}

// kody sa na 0x00
void FRAM_Read_Code(unsigned char *data) 
{
		int status; 
		char buf[5];
	
		uint8_t addr = 0x00;
	
    // Wyslanie adresu pamieci do odczytu
    status = Driver_I2C1.MasterTransmit(I2C_ADDR_FRAM, &addr, 1, true); // true = repeated start
		sprintf(buf, "%d", status);
		send_str(buf);
    while (Driver_I2C1.GetStatus().busy);

    // Odczyt danych
    status = Driver_I2C1.MasterReceive(I2C_ADDR_FRAM, data, 4, false); // false = stop
		sprintf(buf, "%d", status);
		send_str(buf);
    while (Driver_I2C1.GetStatus().busy);
}
