#ifndef MY_LCD_H
	#define MY_LCD_H
	#include "./lcd_lib/Open1768_LCD.h"   // wyswietlacz LCD
	#include "./lcd_lib/LCD_ILI9325.h"   // sterownik wyswietlacza
	#include "./lcd_lib/asciiLib.h"      // czcionki
	#include "my_rtc.h" // pobieranie daty
	
	void zamazPiksel(unsigned int x, unsigned int y, uint16_t color);
	void zamaz(uint16_t color);
	void rysujAscii(char ascii, unsigned int pozycjaX, unsigned int pozycjaY, uint16_t color);
	void aktualizujLCD(char *data, char *czas, char *odblokowano, char *zablokowano);
	void LCD_init();
	void RTC_getTime(char *data, char *czas);
	
		// Ustawienie tla na ekranie
	void ustawTlo(uint16_t color);

	// Wyswietlenie tekstu na ekranie
	void piszTekst(char *tekst, unsigned pozycjaX, unsigned pozycjaY, uint16_t color);

	// Wyswietlanie w trybie normalnym
	void trybNormalny(uint8_t wpisaneZnaki);

	// Wyswietlanie w trybie zmiany kodu 
	void trybZmianaKodu(uint8_t wpisaneZnaki, char * code);

	// Wyswietlanie logów z pamieci FRAM
	void wyswietlLogi(void);
	
	void aktualizujGUI(bool trybZmiana, uint8_t wpisaneZnaki, const char *kod_wejsciowy, char *log_odblokowania, char *log_zablokowania);
	

#endif

