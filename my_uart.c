// zabiera piny 0.2 0.3
#include "my_uart.h"


void UART0_init()
{
	PIN_Configure(0 , 2 , 1u , 0, 0);
	PIN_Configure(0 , 3 , 1u , 0, 0);
	
	LPC_UART0->LCR |= (1<<7); // DLAB odpalony
	
	LPC_UART0->DLL = 9u;
	LPC_UART0->DLM = 0u;
	
	LPC_UART0->FDR = 0u;
	LPC_UART0->FDR = (1u) | (1u << 5); 
	
	
	LPC_UART0->LCR &= 0; // DLAB skasowany
	LPC_UART0->LCR = 3u; 
}


void send_char(char c)
{
	while ( !(LPC_UART0->LSR & 1<<5) );
	LPC_UART0->THR = c;
}



void send_str(char * str)
{
	while(*str != '\0')
	{
		send_char(*str);
		str++;
	}
}