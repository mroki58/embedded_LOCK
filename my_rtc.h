#ifndef MY_RTC_H
	#define MY_RTC_H
	#include "utils.h"
	#include "dates.h"
	
	// do uzycia tylko raz
	void RTC_init();
	
	// do uzycia do ustawienia daty
	void RTC_set_date();

	// full RTC experience
	void pobierzDate(short * rok, uint8_t * miesiac, uint8_t * dzien, uint8_t * godzina, uint8_t * minuta, uint8_t * sekunda);
	
#endif