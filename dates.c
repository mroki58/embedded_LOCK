#include "dates.h"

extern uint8_t _logs[40];

// data to 4 zakodowane bajty, dostep w taki sposob w celu optymalizacji wykorzystania miejsca
// od razu zapisuje nowe daty we FRAM
// razem z decode bedzie uzyte w funkcjach pobierajacych czas wykorzystujacych RTC
void dodaj_date(uint8_t * nowa_data)
{
	  for(int i=0; i < 36; i += 4)
    {
        _logs[i] = _logs[i + 4];
        _logs[i + 1] = _logs[i + 5];
        _logs[i + 2] = _logs[i + 6];
        _logs[i + 3] = _logs[i + 7];
    }
    _logs[36] = nowa_data[0];
    _logs[37] = nowa_data[1];
    _logs[38] = nowa_data[2];
    _logs[39] = nowa_data[3];
		FRAM_Write_Logs();
}

// wypisuje jedna date na wyjscie uart
void wypisz_date_uart(int i)
{
	char data_txt[22];
	
	short year;
	uint8_t hour, minute, second, day, month;
	
	encode_date(_logs, i, &year, &month, &day, &hour, &minute, &second);

	sprintf(data_txt, "%02d:%02d:%02d %02d/%02d/%d", hour % 100, minute % 100, second % 100, day % 100, month % 100, year % 10000);
	
	send_str(data_txt);
	send_char('\t');
	
	
}

void wypisz_daty()
{
		send_str("Daty ostatnich odblokowan:\t");
		for(int i=0; i < 10; ++i)
		{
				wypisz_date_uart(i);
		}
}