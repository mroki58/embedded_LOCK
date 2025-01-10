#ifndef UTILS_H
	#define UTILS_H
	#include <stdint.h>
	
	void decode_date(uint8_t * tab, short year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
	void encode_date(uint8_t * tab, short * year, uint8_t * month, uint8_t * day, uint8_t * hour, uint8_t * minute, uint8_t * second);
	


#endif