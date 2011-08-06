#include "polaczenia.h"
#include "okno_glowne.h"

polaczenie_szeregowe::polaczenie_szeregowe(element * jeden, element * dwa): pierwszy(jeden), drugi(dwa), kasowany(FALSE)
	{
   nazwa = "polaczenie_szeregowe";
   }

polaczenie_szeregowe::~polaczenie_szeregowe()
	{
   if (!kasowany)
   	{
	   if (pierwszy)
	   	delete pierwszy;
	   if (drugi)
	   	delete drugi;
      }
   }

void polaczenie_szeregowe::podaj_rozmiar(int & szerokosc, int & wysokosc, int)
	{
	pierwszy->podaj_rozmiar(szerokosc, wysokosc);
	int temp1, temp2;
	drugi->podaj_rozmiar(temp1, temp2);
	szerokosc+=temp1;
	if (temp2>wysokosc)
		wysokosc = temp2;
   }

int polaczenie_szeregowe::dzialaj(int wejscie)
	{
	return drugi->dzialaj(pierwszy->dzialaj(wejscie));
   }

void polaczenie_szeregowe::narysuj(HDC kontekst, int, int x, int y)
	{
	pierwszy->narysuj(kontekst, RYSUJ_NAZWE|RYSUJ_ADRES, x, y);
   int szerokosc, wysokosc;
   pierwszy->podaj_rozmiar(szerokosc, wysokosc);
   drugi->narysuj(kontekst, RYSUJ_NAZWE|RYSUJ_ADRES, x+szerokosc, y);
	MoveToEx(kontekst, akt_program_LD->mapuj_x(x+szerokosc)-20, akt_program_LD->mapuj_y(y)+Y_WYJSCIA, NULL);
	LineTo(kontekst, akt_program_LD->mapuj_x(x+szerokosc), akt_program_LD->mapuj_y(y)+Y_WYJSCIA);
	}

void polaczenie_szeregowe::dodaj_hotspot(int x, int y)
	{
   int szer, wys;
   pierwszy->podaj_rozmiar(szer, wys);
	pierwszy->dodaj_hotspot(x, y);
   drugi->dodaj_hotspot(x+szer, y);
   }

ZDARZENIE polaczenie_szeregowe::edytuj(int x, int y, ZDARZENIE zdarzenie, element * &edytowany)
	{
   int temp_x, temp_y, temp2_x, temp2_y;
   pierwszy->podaj_rozmiar(temp_x, temp_y);
   if ((x<temp_x)&&(y<temp_y))
   	{
      switch (pierwszy->edytuj(x, y, zdarzenie, edytowany))
      	{
         case NIC_NIE_ROB:
         	return NIC_NIE_ROB;
         case SKASUJ_MNIE:
         	delete pierwszy;
            edytowany = drugi;
            kasowany = TRUE;
				return ZASTAP_MNIE;
         case ZASTAP_MNIE:
         	delete pierwszy;
            pierwszy = edytowany;
				return NIC_NIE_ROB;
         case ZASTAP_MNIE_I_NIE_KASUJ:
         	pierwszy = edytowany;
            return NIC_NIE_ROB;
         }
      return NIC_NIE_ROB;
      }
   drugi->podaj_rozmiar(temp2_x, temp2_y);
   if ((x<temp2_x+temp_x)&&(y<temp2_y)&&(x>=temp_x))
   	{
      switch (drugi->edytuj(x-temp_x, y, zdarzenie, edytowany))
      	{
         case NIC_NIE_ROB:
         	return NIC_NIE_ROB;
         case SKASUJ_MNIE:
         	delete drugi;
            edytowany = pierwszy;
            kasowany = TRUE;
				return ZASTAP_MNIE;
         case ZASTAP_MNIE:
         	delete drugi;
            drugi = edytowany;
            return NIC_NIE_ROB;
         case ZASTAP_MNIE_I_NIE_KASUJ:
         	drugi = edytowany;
            return NIC_NIE_ROB;
         }
      return NIC_NIE_ROB;
      }
   return NIC_NIE_ROB;
   }

void polaczenie_szeregowe::zapisz(FILE * plik)
	{
   fwrite(nazwa, 1, strlen(nazwa)+1, plik);
   pierwszy->zapisz(plik);
   drugi->zapisz(plik);
   }

polaczenie_szeregowe::polaczenie_szeregowe(FILE * plik)
	{
   nazwa = "polaczenie_szeregowe";
   pierwszy = akt_narzedzia->rozpoznaj_i_wczytaj(plik);
   drugi = akt_narzedzia->rozpoznaj_i_wczytaj(plik);
   }

polaczenie_rownolegle::polaczenie_rownolegle(element * jeden, element * dwa): pierwszy(jeden), drugi(dwa), kasowany(FALSE)
	{
   nazwa = "polaczenie_rownolegle";
   }

polaczenie_rownolegle::~polaczenie_rownolegle()
	{
   if (!kasowany)
   	{
	   if (pierwszy)
	   	delete pierwszy;
	   if (drugi)
	   	delete drugi;
      }
   }

void polaczenie_rownolegle::podaj_rozmiar(int & szerokosc, int & wysokosc, int)
	{
	pierwszy->podaj_rozmiar(szerokosc, wysokosc);
	int temp1, temp2;
	drugi->podaj_rozmiar(temp1, temp2);
	wysokosc+=temp2;
	if (temp1>szerokosc)
		szerokosc = temp1;
	}

int polaczenie_rownolegle::dzialaj(int wejscie)
	{
   if (pierwszy->dzialaj(wejscie) + drugi->dzialaj(wejscie))
   	return 1;
   else
   	return 0;
	}

void polaczenie_rownolegle::narysuj(HDC kontekst, int, int x, int y)
	{
	pierwszy->narysuj(kontekst, RYSUJ_NAZWE|RYSUJ_ADRES, x, y);
	int szerokosc1, wysokosc1, szerokosc2, wysokosc2;
	pierwszy->podaj_rozmiar(szerokosc1, wysokosc1);
	drugi->podaj_rozmiar(szerokosc2, wysokosc2);
	drugi->narysuj(kontekst, RYSUJ_NAZWE|RYSUJ_ADRES, x, y+wysokosc1);
	if (szerokosc1>szerokosc2)
		{
		MoveToEx(kontekst, akt_program_LD->mapuj_x(x+szerokosc2)-20, akt_program_LD->mapuj_y(y+wysokosc1)+Y_WYJSCIA, NULL);
		LineTo(kontekst, akt_program_LD->mapuj_x(x+szerokosc1)-10, akt_program_LD->mapuj_y(y+wysokosc1)+Y_WYJSCIA);
      MoveToEx(kontekst, akt_program_LD->mapuj_x(x+szerokosc1)-20, akt_program_LD->mapuj_y(y)+Y_WYJSCIA, NULL);
      LineTo(kontekst, akt_program_LD->mapuj_x(x+szerokosc1)-10, akt_program_LD->mapuj_y(y)+Y_WYJSCIA);
		}
	if (szerokosc2>=szerokosc1)
		{
		MoveToEx(kontekst, akt_program_LD->mapuj_x(x+szerokosc1)-20, akt_program_LD->mapuj_y(y)+Y_WYJSCIA, NULL);
		LineTo(kontekst, akt_program_LD->mapuj_x(x+szerokosc2)-10, akt_program_LD->mapuj_y(y)+Y_WYJSCIA);
      MoveToEx(kontekst, akt_program_LD->mapuj_x(x+szerokosc2)-20, akt_program_LD->mapuj_y(y+wysokosc1)+Y_WYJSCIA, NULL);
      LineTo(kontekst, akt_program_LD->mapuj_x(x+szerokosc2)-10, akt_program_LD->mapuj_y(y+wysokosc1)+Y_WYJSCIA);
		szerokosc1 = szerokosc2;
		}
	MoveToEx(kontekst, akt_program_LD->mapuj_x(x), akt_program_LD->mapuj_y(y)+Y_WYJSCIA, NULL);
	LineTo(kontekst, akt_program_LD->mapuj_x(x), akt_program_LD->mapuj_y(y+wysokosc1)+Y_WYJSCIA);
	MoveToEx(kontekst, akt_program_LD->mapuj_x(x+szerokosc1)-10, akt_program_LD->mapuj_y(y)+Y_WYJSCIA, NULL);
	LineTo(kontekst, akt_program_LD->mapuj_x(x+szerokosc1)-10, akt_program_LD->mapuj_y(y+wysokosc1)+Y_WYJSCIA);
	}


void polaczenie_rownolegle::dodaj_hotspot(int x, int y)
	{
   int szer, wys;
   pierwszy->podaj_rozmiar(szer, wys);
   pierwszy->dodaj_hotspot(x, y);
   drugi->dodaj_hotspot(x, y+wys);
   }

ZDARZENIE polaczenie_rownolegle::edytuj(int x, int y, ZDARZENIE zdarzenie, element * &edytowany)
	{
	int temp_x, temp_y, temp2_x, temp2_y;
	pierwszy->podaj_rozmiar(temp_x, temp_y);
   if ((x<temp_x)&&(y<temp_y))
   	{
      switch (pierwszy->edytuj(x, y, zdarzenie, edytowany))
      	{
         case NIC_NIE_ROB:
         	return NIC_NIE_ROB;
         case SKASUJ_MNIE:
         	delete pierwszy;
            edytowany = drugi;
            kasowany = TRUE;
				return ZASTAP_MNIE;
         case ZASTAP_MNIE:
         	delete pierwszy;
            pierwszy = edytowany;
            return NIC_NIE_ROB;
         case ZASTAP_MNIE_I_NIE_KASUJ:
         	pierwszy = edytowany;
            return NIC_NIE_ROB;
         }
      return NIC_NIE_ROB;
      }
   drugi->podaj_rozmiar(temp2_x, temp2_y);
   if ((x<temp2_x)&&(y<temp_y+temp2_y)&&(y>=temp_y))
   	{
      switch (drugi->edytuj(x, y-temp_y, zdarzenie, edytowany))
      	{
         case NIC_NIE_ROB:
         	return NIC_NIE_ROB;
         case SKASUJ_MNIE:
         	delete drugi;
            edytowany = pierwszy;
            kasowany = TRUE;
				return ZASTAP_MNIE;
         case ZASTAP_MNIE:
         	delete drugi;
            drugi = edytowany;
            return NIC_NIE_ROB;
			case ZASTAP_MNIE_I_NIE_KASUJ:
				drugi = edytowany;
				return NIC_NIE_ROB;
			}
		return NIC_NIE_ROB;
		}
	return NIC_NIE_ROB;
	}

void polaczenie_rownolegle::zapisz(FILE * plik)
	{
   fwrite(nazwa, 1, strlen(nazwa)+1, plik);
   pierwszy->zapisz(plik);
   drugi->zapisz(plik);
   }

polaczenie_rownolegle::polaczenie_rownolegle(FILE * plik)
	{
   nazwa = "polaczenie_rownolegle";
   pierwszy = akt_narzedzia->rozpoznaj_i_wczytaj(plik);
   drugi = akt_narzedzia->rozpoznaj_i_wczytaj(plik);
   }


