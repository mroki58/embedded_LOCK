#ifndef MY_LCD_H
	#define MY_LCD_H
	#include "./lcd_lib/Open1768_LCD.h"   // wyswietlacz LCD
	#include "./lcd_lib/LCD_ILI9325.h"   // sterownik wyswietlacza
	#include "./lcd_lib/asciiLib.h"      // czcionki
	
	void zamazPiksel(unsigned int x, unsigned int y, uint16_t color);
	void zamaz(uint16_t color);
	void rysujAscii(char ascii, unsigned int pozycjaX, unsigned int pozycjaY, uint16_t color);
	void piszTekst(char *tekst, unsigned pozycjaX, unsigned pozycjaY, uint16_t color);
	void aktualizujLCD(char *data, char *czas, char *odblokowano, char *zablokowano);
	void LCD_init();
	void RTC_getTime(char *data, char *czas);
	

#endif