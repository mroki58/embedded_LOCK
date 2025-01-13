#ifndef DATES_H
	#define DATES_H
	#include <stdint.h>
	#include <stdio.h>
	#include "my_uart.h"
	#include "my_fram.h"
	#include "utils.h"
	
	void dodaj_date(uint8_t * nowa_data);
	void wypisz_date_uart(int i);
	void wypisz_daty();
	

#endif