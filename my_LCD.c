#include "my_LCD.h"
#include <stdio.h>

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
                zamazPiksel(pozycjaY + 15 - j, pozycjaX + i, color);
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



// to do zmiany
void RTC_getTime(char *data, char *czas) {
    sprintf(data, "2024-12-19");
    sprintf(czas, "13:15:00");
}

// Tryb normalny:
void trybNormalny(uint8_t wpisaneZnaki) {
    ustawTlo(LCDRed); 

    piszTekst("Wpisz kod:", 10, 10, LCDWhite);
    
    // Wyswietlanie gwiazdek
    char maskowaneZnaki[5] = "    ";
    for (uint8_t i = 0; i < wpisaneZnaki; i++) {
        maskowaneZnaki[i] = '*';
    }
    piszTekst(maskowaneZnaki, 30, 30, LCDWhite);
}

////////////////////////////////////////////////////////////////
// Funkcja do czyszczenia ekranu i ustawiania tla
void ustawTlo(uint16_t color) {
    zamaz(color);
}


// Tryb zmiany kodu
void trybZmianaKodu(uint8_t wpisaneZnaki, char * code) {
    ustawTlo(LCDBlue);

    piszTekst("Zmiana kodu:", 10, 10, LCDWhite);

    // Wyswietlanie wpisanych cyfr
    char wpisaneZnakiBufor[5] = "    "; // Bufor dla aktualnie wpisanych cyfr
    for (uint8_t i = 0; i < wpisaneZnaki; i++) {
        wpisaneZnakiBufor[i] = code[i];
    }
    piszTekst(wpisaneZnakiBufor, 30, 30, LCDWhite);
}

////////////////////////////////////////////////////////////////

// Funkcja do wyswietlenia logów
void wyswietlLogi() {
    char log[50];
    
    // Pobieranie logow z FRAM
    //sprintf(log, "Odblokowano: %s", czas_odblokowania);
    //piszTekst(log, 10, 50, LCDWhite);

    //sprintf(log, "Zablokowano: %s", czas_zablokowania);
    //piszTekst(log, 10, 70, LCDWhite);
}

