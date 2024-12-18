#include <stdbool.h>
#include "my_uart.h"
#include "my_fram.h"
#include "my_keyboard.h"

char kod_docelowy[5] = "1234";
char kod_wejsciowy[5];

uint8_t index = 0;

bool scan_keyboard_flag = false;

int n;
void SysTick_Handler(void)
{
	n--;
}

// przerwanie na bloku GPIO wykorzystany do znalezienia nastepnego 
// znaku pobranego z klawiatury
void EINT3_IRQHandler()
{
	scan_keyboard_flag = true;
}

int main()
{
	SysTick_Config(SystemCoreClock/1000);
	kod_wejsciowy[4] = '\0';
	GPIO_init();
	UART0_init();
	I2C_Init();
	
	while(1)
	{
			if(scan_keyboard_flag)
			{
				scan_keyboard();
				scan_keyboard_flag = false;
			}
	}
	
	
}



