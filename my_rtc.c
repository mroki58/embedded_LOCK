#include "my_rtc.h"

void RTC_init()
{
	// wylacza kalibracje 4 bit i wlacza counter 1 bit
	LPC_RTC->CCR = 1u | (1u << 4);	
	RTC_set_date();
	
}

// do uzycia jednorazowo
void RTC_set_date()
{
	LPC_RTC->SEC = 45;
	LPC_RTC->MIN = 45;
	LPC_RTC->HOUR = 13;

	// Ustawianie rejestrów daty
	LPC_RTC->DOM = 14;
	LPC_RTC->MONTH = 1;
	LPC_RTC->YEAR = 2025;
}

void pobierzDate(short * rok, uint8_t * miesiac, uint8_t * dzien, uint8_t * godzina, uint8_t * minuta, uint8_t * sekunda)
{
    // Sekundy, minuty, godziny
    uint32_t ctime0 = LPC_RTC->CTIME0; 
    // Dzien, miesiac, rok
    uint32_t ctime1 = LPC_RTC->CTIME1; 

    // maski bitowe - patrz tabele w rozdziale 27.6.3 
    *sekunda = ctime0 & 0x3F;
    *minuta = (ctime0 >> 8) & 0x3F;
    *godzina = (ctime0 >> 16) & 0x1F;
    *dzien = ctime1 & 0x1F;
    *miesiac = (ctime1 >> 8) & 0x0F;
    *rok = (ctime1 >> 16) & 0x0FFF;
	
		
}

	
	
