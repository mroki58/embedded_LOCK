// zabiera piny 0.0 i 0.1
#include "my_fram.h"
#include "my_uart.h"
#include <stdio.h>

#define I2C_ADDR_FRAM  (0xA0 >> 1)   // Adres I2C urzadzenia FRAM (7-bitowy)
#define ADDR_CODES 0x00
#define ADDR_LOGS 0x04

extern ARM_DRIVER_I2C Driver_I2C1;
extern uint8_t _logs[40];

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
    uint8_t buffer[5]; // bajt adresu + dane
		buffer[0] = ADDR_CODES;
	
    for (uint8_t i = 0; i < 4; i++) {
        buffer[1 + i] = data[i];  // Dane do zapisania
    }
		
    // Wyslanie danych do FRAM
    Driver_I2C1.MasterTransmit(I2C_ADDR_FRAM, buffer, 5, false); // false = stop
    while (Driver_I2C1.GetStatus().busy);  // Czekaj na zakonczenie transmisji
		send_str("Przeslano kod do pamieci FRAM\t");
}

// kody sa na 0x00
void FRAM_Read_Code(unsigned char *data) 
{	
		uint8_t addr = ADDR_CODES;
	
    // Wyslanie adresu pamieci do odczytu
    Driver_I2C1.MasterTransmit(I2C_ADDR_FRAM, &addr, 1, true); // true = repeated start
    while (Driver_I2C1.GetStatus().busy);

    // Odczyt danych
    Driver_I2C1.MasterReceive(I2C_ADDR_FRAM, data, 4, false); // false = stop
    while (Driver_I2C1.GetStatus().busy);
		send_str("Pobrano kod z pamieci FRAM\t");
}

void FRAM_Write_Logs()
{	
    uint8_t buffer[41]; // bajt adresu + dane
		buffer[0] = ADDR_LOGS;
	
    for (uint8_t i = 0; i < 40; i++) {
        buffer[1 + i] = _logs[i];  // Dane do zapisania
    }
		
    // Wyslanie danych do FRAM
    Driver_I2C1.MasterTransmit(I2C_ADDR_FRAM, buffer, 41, false); // false = stop
    while (Driver_I2C1.GetStatus().busy);  // Czekaj na zakonczenie transmisji
		send_str("Zapisano daty do pamieci FRAM\t");
}

void FRAM_Read_Logs()
{
	
		uint8_t addr = ADDR_LOGS;
	
    // Wyslanie adresu pamieci do odczytu
    Driver_I2C1.MasterTransmit(I2C_ADDR_FRAM, &addr, 1, true); // true = repeated start
    while (Driver_I2C1.GetStatus().busy);
	
		Driver_I2C1.MasterReceive(I2C_ADDR_FRAM, _logs, 40, false);
		while (Driver_I2C1.GetStatus().busy);
		send_str("Pobrano daty z pamieci FRAM\t");
}




