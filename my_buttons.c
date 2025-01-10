#include "my_buttons.h"

// inicjalizuje drugi przcycisk na pinie 2.11
void Buttons_init()
{
	PIN_Configure(2, 11 , 1, 0 ,0);
	LPC_SC->EXTMODE = 1 << 1;
	LPC_SC->EXTPOLAR = 0 << 1;

	NVIC_EnableIRQ(EINT1_IRQn);
}