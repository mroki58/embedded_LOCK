#include "utils.h"

void decode_date(uint8_t * tab, uint8_t i, short year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second)
{
	  year -= 2024;
    
    // zakodowanie danych do wyslania
    tab[4*i] = (year << 2) | (month >> 2);
    tab[4*i + 1] =  (month << 6) | (day << 1) | (hour >> 4);
    tab[4*i + 2] = (hour << 4) | (minute >> 2);
    tab[4*i + 3] = (minute << 6) | second;
	
}

void encode_date(uint8_t * tab, uint8_t i, short * year, uint8_t * month, uint8_t * day, uint8_t * hour, uint8_t * minute, uint8_t * second)
{
		// odkodowanie danych
	  *year = (tab[4*i] >> 2) + 2024;  
    *month = ((tab[4*i + 1] >> 6) & 0x03) | ((tab[4*i] & 0x03) << 2);  
    *day = (tab[4*i + 1] >> 1) & 0x1F;  
    *hour = ((tab[4*i + 1] & 1) << 4) | (tab[4*i + 2] >> 4);  
    *minute = ((tab[4*i + 2] & 0x0F) << 2) | (tab[4*i + 3] >> 6); 
    *second = tab[4*i + 3] & 0x3F;
}