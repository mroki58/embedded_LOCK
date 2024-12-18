#include "my_uart.h"
#include <stdbool.h>

#define ROWS 4
#define COLS 4

extern char kod_wejsciowy[5];
extern char kod_docelowy[5];
extern int index;
	

char keys[ROWS][COLS] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'0', 'F', 'E', 'D'}
};

uint8_t kolejnoscR[4] = {3,2,1,0};
uint8_t kolejnoscC[4] = {2,3,1,0};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void GPIO_init()
{    
	//	r/k 0.17 0.18 0.15 0.16
	// 0.27 
	// 0.28 
	// 0.29 
	// 0.30 
	
	for(uint8_t i=0; i < ROWS; ++i) 
	{
		PIN_Configure(0,27 + i, 0, 0, 0); // rzedy chyba jednak powinny miec pull-up
		PIN_Configure(0,15 + i, 0, 0, 3); // kolumny jako OPEN DRAIN dziala dla 0 nornalnie a dla 1 dziala jak open drain (stan wysokiej impedancji)
	}		
	
	// Rzedy jako wejscia
	LPC_GPIO0->FIODIR &= ~(15u << 27); 

	// Kolumny jako wyjscia
	LPC_GPIO0->FIODIR |= (15u << 15); 

	// przerwania na falling edge dla pinow 0.27-0.30
	LPC_GPIOINT->IO0IntEnF |= (15u << 27);
	
	// ustawienie 0 na wyjsciu	
	for(uint8_t col = 0; col < COLS; ++col)
	{
		LPC_GPIO0->FIOPIN &= ~(1 << (15 + col));
	}

	// interrupt dla GPIO enablniety
	NVIC_EnableIRQ(EINT3_IRQn);
	
}

extern int n;
void delay(int ms)
{
	/*
	n = ms;
	while(n > 0);*/
	for(long i = 0; i < ms * 10000; ++i);
}

void scan_keyboard()
{
	delay(30);
	
	// 1 na kolumnie powoduje w open drain stan wysokiej impedancji Z
	LPC_GPIO0->FIOPIN |= (15 << 15);

	delay(20);
	
	for (uint8_t col = 0; col < COLS; ++col) 
	{
		
		// zmiana na 0 na wyjsciu
		LPC_GPIO0->FIOPIN &= ~(1 << (15 + col));
		
		delay(30);
		
		for(uint8_t row = 0; row < ROWS; ++row)
		{
				if( !( LPC_GPIO0->FIOPIN & (1 << (row + 27))  ) )
				{
						kod_wejsciowy[index % 4] = keys[kolejnoscR[row]][kolejnoscC[col]];
						send_char(kod_wejsciowy[index % 4]);
						++index;
				}
				delay(10);
		}
		
		// powrot do stanu wysokiej impedancji na tym pinie
		LPC_GPIO0->FIOPIN |= (1 << (15 + col));
	}
		
	// wszystkie ustawiamy na koncu na 0
	LPC_GPIO0->FIOPIN &= ~(15u << 15);

	// wylaczenie INTerrupta 
	LPC_GPIOINT->IO0IntClr = (15 << 27);
	
}


