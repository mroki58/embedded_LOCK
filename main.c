#include <stdbool.h>
#include <string.h>
#include "my_uart.h"
#include "my_fram.h"
#include "my_keyboard.h"
#include "my_LCD.h"
#include "my_buttons.h"
#include "utils.h"
#include "my_rtc.h"

// globalna tablica sluzaca do przechowywania 40 bajtow dat - wychodzi z tego 10 dat
uint8_t _logs[40];

volatile bool scan_keyboard_flag = false;
volatile bool button_click_flag = false;
volatile int n;
volatile bool change_date_on_screen_flag = false;

void cmp_codes(char * code_1, char * code_2)
{
    if(!strncmp(code_1, code_2, 4))
    {
        // odblokuj zamek
				LPC_GPIO0->FIOSET = (1u << 10);
        // trzeba jeszcze zalogowac dostanie sie do srodka
        send_str("Zamek otwarty\t");
        ustawTlo(LCDGreen); // Zielone tlo dla poprawnego kodu
        piszTekst("Zamek otwarty", 60, 50, LCDWhite);
			
				// odczytanie daty wejscia
				short rok;
			  uint8_t miesiac, dzien, godzina,  minuta, sekunda;
				pobierzDate(&rok, &miesiac,&dzien ,&godzina, &minuta, &sekunda);
				
				// wypisanie daty na ekran
				char data_txt[22];
				sprintf(data_txt, "%02d:%02d:%02d %02d/%02d/%d", godzina % 100, minuta % 100, sekunda % 100, dzien % 100, miesiac % 100, rok % 10000);
				piszTekst(data_txt, 120, 30, LCDWhite);
				
			
				//dodanie daty do pamieci
				uint8_t data[4];
				decode_date(data, 0, rok, miesiac, dzien, godzina, minuta, sekunda);
				dodaj_date(data);
				
				
    }
    else
    {
        // nie odblokowywuj zamka
        send_str("Zly kod\t");
        ustawTlo(LCDRed); // Czerwone tlo dla blednego kodu
        piszTekst("Zly kod", 150, 70, LCDWhite);
    }
}



void SysTick_Handler(void)
{
    n--;
}

void EINT1_IRQHandler()
{
	button_click_flag = true;
	LPC_SC->EXTINT = 1 << 1; 
}

// przerwanie na bloku GPIO wykorzystany do znalezienia nastepnego 
// znaku pobranego z klawiatury
void EINT3_IRQHandler()
{
    scan_keyboard_flag = true;
    // wylaczenie INTerrupta 
    LPC_GPIOINT->IO0IntClr = (15u << 27);
}

void RTC_IRQHandler(void)
{
	change_date_on_screen_flag = true;
	// wylaczenie interrupta od countera
	LPC_RTC->ILR = 1;
}

int main()
{
    SysTick_Config(SystemCoreClock/1000);

    // klawiatura 
    GPIO_init();
    // komunikacja debug
    UART0_init();
    // dostep do modulu pamieci fram
    I2C_Init();
    // wyswietlacz LCD
    LCD_init();
    // przyciski
		Buttons_init();
		// inicjalizacja RTC dla przerwania
		RTC_init();
		// Jednorazowa inicjalizacja daty
		//RTC_set_date();
	
    // ZMIENNE WYKORZYSTYWANE PRZEZ PROGRAM

    // sluzy do przechowywania informacji o aktualnym indexie kodu ktory jest wpisywany
    uint8_t index = 0;
    // sprawdza czy jestesmy w trybie zmiany kodu
    bool change_code_mode = false;

    // kod docelowy z ktorym porownujemy kod wejsciowy
    char kod_docelowy[5] = "1234";
    char kod_wejsciowy[5];
    // ostatni znak kodu wejsciowego to znak konca lancucha
    kod_wejsciowy[4] = '\0';
				
		FRAM_Read_Code((unsigned char *)kod_docelowy);
		FRAM_Read_Logs();
		
		trybNormalny(0);
		

    while(1)
    {
        // sprawdzamy czy nie jestesmy w trybie zmiany kodu 
        if(scan_keyboard_flag && (!change_code_mode))
        {
            send_str("Wykryto wcisniecie klawisza\t");
            scan_keyboard(kod_wejsciowy, &index);

            // Wyswietlanie gwiazdek w trybie normalnym
            trybNormalny(index);

            if(index >= 4)
            {
                index = 0;
                cmp_codes(kod_wejsciowy, kod_docelowy);
								delay(5000);
								LPC_GPIO0->FIOCLR = (1u << 10);
								trybNormalny(0);
            }
            scan_keyboard_flag = false;
        }

				if(button_click_flag)
        {
						// debouncing
						delay(100);
						send_str("Wcisnieto przycisk\t");
            change_code_mode = true;
            index = 0;
            // zmien tlo na kolor trybu zmiany kodu
						trybZmianaKodu(index, kod_docelowy);
            wypisz_daty();
						button_click_flag = false;
        }

        if(scan_keyboard_flag && change_code_mode)
        {
            send_str("Wykryto wcisniecie klawisza\t");
            scan_keyboard(kod_docelowy, &index);

            // Wyswietlanie cyfr w trybie zmiany kodu
            trybZmianaKodu(index, kod_docelowy);

            if(index >= 4)
            {
                index = 0;
                // wyslij kod do modulu pamieci
                FRAM_Write_Code((unsigned char *)kod_docelowy);
								// utrzymuje widoczny kod jeszcze przez chwile na ekranie
								delay(1500);
								// zmienic kolor na kolor normalnego trybu
                ustawTlo(LCDRed);
                piszTekst("Kod zmieniony", 120, 40, LCDWhite);
								delay(3000);
								// powrot do normalnego trybu
								trybNormalny(0);
								change_code_mode = false;
            }
            scan_keyboard_flag = false;
        }
				
				// zmieniamy date bo jestesmy w trybie normalnym
				if(change_date_on_screen_flag && !change_code_mode)
				{
					trybNormalny(index);
					change_date_on_screen_flag = false;
				}
    }
}



