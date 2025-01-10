#include "my_uart.h"
#include "my_keyboard.h"
#include <stdbool.h>

#define ROWS 4
#define COLS 4

	
char keys[ROWS][COLS] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'0', 'F', 'E', 'D'}
};

uint8_t kolejnoscR[4] = {2,3,1,0};
uint8_t kolejnoscC[4] = {2,3,1,0};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void GPIO_init()
{    
	//	r/k 1.14 1.15 1.16 1.17
	// 0.27 
	// 0.28 
	// 0.29 
	// 0.30 
	
	for(uint8_t i=0; i < ROWS; ++i) 
	{
		PIN_Configure(0,27 + i, 0, 2, 0); // rzedy bez pull upa
		PIN_Configure(1,14 + i, 0, 0, 1); // kolumny jako OPEN DRAIN dziala dla 0 nornalnie a dla 1 dziala jak open drain (stan wysokiej impedancji)
	}		
	
	// Rzedy jako wejscia
	LPC_GPIO0->FIODIR &= ~(15u << 27); 

	// Kolumny jako wyjscia
	LPC_GPIO1->FIODIR |= (15u << 14); 

	// przerwania na falling edge dla pinow 0.27-0.30
	LPC_GPIOINT->IO0IntEnF |= (15u << 27);
	
	// ustawienie 0 na wyjsciu	
	LPC_GPIO1->FIOCLR = (15u << 14);

	// interrupt dla GPIO enablniety
	NVIC_EnableIRQ(EINT3_IRQn);
	
}

extern int n;
void delay(int ms)
{
	n = ms;
	while(n > 0);
	//for(long i = 0; i < ms * 10000; ++i);
}

void scan_keyboard(char * code, uint8_t * index)
{
	
	// 1 na kolumnie powoduje w open drain stan wysokiej impedancji Z
	LPC_GPIO1->FIOPIN |= (15u << 14) ;
	
	for (uint8_t col = 0; col < COLS; ++col) 
	{		
		// zmiana na 0 na jednym wyjsciu
		LPC_GPIO1->FIOCLR = (1 << (14 + col));
		
		delay(100);
		
		for(uint8_t row = 0; row < ROWS; ++row)
		{
				if( !( LPC_GPIO0->FIOPIN & (1 << (row + 27))  ) )
				{
						if(*index < 4)
						{
							code[*index] = keys[kolejnoscR[row]][kolejnoscC[col]];
							send_char(code[*index % 4]);
							++(*index);
						}
				}
		}
		
		// powrot do stanu wysokiej impedancji na tym pinie
		LPC_GPIO1->FIOSET = (1 << (14 + col));
			
	}
		
	// wszystkie ustawiamy na koncu na 0
	LPC_GPIO1->FIOCLR |= (15u << 14);
	
	delay(30);

	
}


