#include "my_LCD.h"
#include <stdio.h>

////////////////////////////////////////////////////////////////

// Zmienne globalne dla logów czasu
extern char czas_odblokowania[20];
extern char czas_zablokowania[20];

////////////////////////////////////////////////////////////////

// Inicjalizacja LCD
void LCD_init() {
    lcdConfiguration(); // Konfiguracja LCD z biblioteki
    init_ILI9325();     // Inicjalizacja sterownika ILI9325
    zamaz(LCDBlack);    // Czyszczenie ekranu
}

// Funkcja do rysowania pojedynczego piksela
void zamazPiksel(unsigned int x, unsigned int y, uint16_t color) {
    lcdWriteReg(0x20, x);         // ustawienie X
    lcdWriteReg(0x21, y);         // ustawienie Y
    lcdWriteIndex(0x0022);        
    lcdWriteData(color);          
}

void zamaz(uint16_t color)
{
	lcdWriteReg(0x20,0);
	lcdWriteReg(0x21,0);
	lcdWriteIndex(0x0022);
	for(int i=0; i < 240; ++i)
	{
		for(int j=0; j < 320; ++j)
		{
			lcdWriteData(color);
		}
	}
}

// Funkcja do rysowania pojedynczego znaku ASCII na LCD
void rysujAscii(char ascii, unsigned int pozycjaX, unsigned int pozycjaY, uint16_t color) {
    unsigned char buffer[16];
    GetASCIICode(0, buffer, ascii); 
    
    for (int i = 0; i < 16; ++i) {      // Wysokosc znaku (16 pikseli)
        for (int j = 0; j < 8; ++j) {   // Szerokosc znaku (8 pikseli)
            if (buffer[i] & (1 << j)) { 
                zamazPiksel(pozycjaX + i, pozycjaY + j, color);
            }
        }
    }
}


void piszTekst(char *tekst, unsigned pozycjaX, unsigned pozycjaY, uint16_t color) {
    int j = 0;
    while (*tekst) {
        rysujAscii(*tekst, pozycjaX, pozycjaY + j, color);
        j += 10; // Odstep miedzy literami
        ++tekst;
    }
}

// Aktualizacja wyswietlacza LCD z danymi
/*void aktualizujLCD(char *data, char *czas, char *odblokowano, char *zablokowano) {
    zamaz(LCDBlack); // Czyszczenie ekranu
    
    // Wyswietlanie daty i czasu
    piszTekst("Data i godzina:", 10, 10, LCDWhite);
    piszTekst(data, 30, 20, LCDBlue);
    piszTekst(czas, 30, 40, LCDBlue);

    // Wyswietlanie logów
    piszTekst("Ostatnie odblokowanie:", 10, 70, LCDWhite);
    piszTekst(odblokowano, 30, 90, LCDBlue);

    piszTekst("Ostatnia blokada:", 10, 120, LCDWhite);
    piszTekst(zablokowano, 30, 140, LCDBlue);
}*/




// to do zmiany
void RTC_getTime(char *data, char *czas) {
    sprintf(data, "2024-12-19");
    sprintf(czas, "13:15:00");
}

