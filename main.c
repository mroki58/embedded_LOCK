#include <stdbool.h>
#include <string.h>
#include "Board_Buttons.h"
#include "my_uart.h"
#include "my_fram.h"
#include "my_keyboard.h"
#include "my_LCD.h"

volatile bool scan_keyboard_flag = false;
volatile int n;

void cmp_codes(char * code_1, char * code_2)
{
	if(!strncmp(code_1, code_2, 4))
	{
		// odblokuj zamek
		// trzeba jeszcze zalogowac dostanie sie do srodka
		send_str("Zamek otwarty");
	}else{
		// nie odblokowywuj zamka
		send_str("Zly kod");
	}
}


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

	// klawiatura 
	GPIO_init();
	// komunikacja debug
	UART0_init();
	// dostep do modulu pamieci fram
	I2C_Init();
	// wyswietlacz LCD
	LCD_init();
	// przyciski
	Buttons_Initialize();
	
	//char data[20], czas[20];
	
	/*for(int i=0 ; i < 4 ; ++i)
	{
		kod_docelowy[i] = '0';
	}
	
	FRAM_Write_Code(kod_docelowy);
	
	kod_docelowy[2] = '3';
	
	FRAM_Read_Code(kod_docelowy);
	
	send_str((char *)kod_docelowy);*/
	
	
	// ZMIENNE WYKORZYSTYWANE PRZEZ PROGRAM
	
	// sluzy do przechowywania informacji o aktualnym indexie kodu ktory jest wpisywany
	uint8_t index = 0;
	// sprawdza czy jestesmy w trybie zmiany kodu
	bool change_code_mode = false;
	
	// kod docelowy z ktorym porownujemy kod wejsciowy
	char kod_docelowy[5] = "1234";
	char kod_wejsciowy[5];
	// ostatni znak kodu wejsciowego to znak konca lancucha
	kod_wejsciowy[4] = '\0';
	
	
	while(1)
	{
		// sprawdzamy czy nie jestesmy w trybie zmiany kodu 
			if( scan_keyboard_flag && (!change_code_mode) )
			{
				send_char('-');
				scan_keyboard(kod_wejsciowy, &index);
				if(index >= 4)
				{
					index = 0;
					cmp_codes(kod_wejsciowy, kod_docelowy);	
				}
				scan_keyboard_flag = false;
			}
			
			// wchodzimy w tryb zmiany kodu
			// moglibysmy tez wykorzystac przycisk do powrotu do trybu normalnego
			// oraz do resetowania kodu
			if(Buttons_GetState() != 0)
			{
					change_code_mode = true;
					index = 0;
				// tutaj mozna wyswietlic logi z pamieci
				// oraz zmienic kolor na kolor trybu zmiany
			}
			
			if(scan_keyboard_flag && change_code_mode )
			{
				send_char('&');
				scan_keyboard(kod_docelowy, &index);
				if(index >= 4)
				{
					index = 0;
					change_code_mode = false;
					// wyslij kod do modulu pamieci
					// zmienic kolor na kolor normalnego trybu
				}
				scan_keyboard_flag = false;
			}
			
				
	}
	
	
}



