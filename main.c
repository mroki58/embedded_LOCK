#include <stdbool.h>
#include "my_uart.h"
#include "my_fram.h"
#include "my_keyboard.h"
#include "my_LCD.h"

unsigned char kod_docelowy[5] = "1234";
unsigned char kod_wejsciowy[5];

uint8_t index = 0;

volatile bool scan_keyboard_flag = false;

char czas_odblokowania[20] = "N/A";
char czas_zablokowania[20] = "N/A";

volatile int n;
void SysTick_Handler(void)
{
	n--;
}

// przerwanie na bloku GPIO wykorzystany do znalezienia nastepnego 
// znaku pobranego z klawiatury
void EINT3_IRQHandler()
{
	scan_keyboard_flag = true;
	// wylaczenie INTerrupta 
	LPC_GPIOINT->IO0IntClr = (15u << 27);
}

int main()
{
	SysTick_Config(SystemCoreClock/1000);
	kod_wejsciowy[4] = '\0';
	GPIO_init();
	UART0_init();
	I2C_Init();
	
	char data[20], czas[20];
	
	/*for(int i=0 ; i < 4 ; ++i)
	{
		kod_docelowy[i] = '0';
	}
	
	FRAM_Write_Code(kod_docelowy);
	
	kod_docelowy[2] = '3';
	
	FRAM_Read_Code(kod_docelowy);
	
	send_str((char *)kod_docelowy);*/
	
	LCD_init();
	
	while(1)
	{
			aktualizujLCD(data, czas, czas_odblokowania, czas_zablokowania);
			if(scan_keyboard_flag)
			{
				send_char('-');
				scan_keyboard();
				scan_keyboard_flag = false;
			}
	}
	
	
}



