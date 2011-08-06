#include "rung.h"
#include "okno_glowne.h"

rung::rung(element * el, element * cew)
	{
	elementy = el;
	cewki = cew;
	}

rung::~rung(void)
	{
	if (elementy)
   	delete elementy;
   if (cewki)
   	delete cewki;
	}

void rung::podaj_rozmiar(int & szerokosc, int & wysokosc, int)
	{
	if (elementy)
		elementy->podaj_rozmiar(szerokosc, wysokosc);
	else
		{
		szerokosc = 0;
		wysokosc = 0;
		}
	if (cewki)
		{
		int temp_x, temp_y;
		cewki->podaj_rozmiar(temp_x, temp_y);
		if (temp_y>wysokosc)
			wysokosc = temp_y;
		}
	}

int rung::dzialaj(int wejscie)
	{
	int wyjscie;
	if (elementy)
		wyjscie = elementy->dzialaj(wejscie);
	else
		wyjscie = wejscie;
	if (cewki)
		cewki->dzialaj(wyjscie);
	return wyjscie;
	}

void rung::narysuj(HDC kontekst, int, int x, int y)
	{
	if (elementy)
		{
		elementy->narysuj(kontekst, RYSUJ_NAZWE|RYSUJ_ADRES, x, y);
		int szerokosc, wysokosc;
		elementy->podaj_rozmiar(szerokosc, wysokosc);
		MoveToEx(kontekst, akt_program_LD->mapuj_x(szerokosc+x)-20, akt_program_LD->mapuj_y(y)+Y_WYJSCIA, NULL);
		LineTo(kontekst, akt_program_LD->mapuj_x(akt_program_LD->x_cewek()+x), akt_program_LD->mapuj_y(y)+Y_WYJSCIA);
		}
   else
   	{
      MoveToEx(kontekst, akt_program_LD->mapuj_x(0), akt_program_LD->mapuj_y(y)+Y_WYJSCIA, NULL);
		LineTo(kontekst, akt_program_LD->mapuj_x(akt_program_LD->x_cewek()), akt_program_LD->mapuj_y(y)+Y_WYJSCIA);
      }
	if (cewki)
   	{
		cewki->narysuj(kontekst, RYSUJ_NAZWE|RYSUJ_ADRES, akt_program_LD->x_cewek(), y);
		MoveToEx(kontekst, akt_program_LD->mapuj_x(akt_program_LD->x_cewek()+1)-20, akt_program_LD->mapuj_y(y)+Y_WYJSCIA, NULL);
		LineTo(kontekst, akt_program_LD->mapuj_x(akt_program_LD->x_cewek()+1), akt_program_LD->mapuj_y(y)+Y_WYJSCIA);
      }
   else
   	{
      MoveToEx(kontekst, akt_program_LD->mapuj_x(akt_program_LD->x_cewek()), akt_program_LD->mapuj_y(y)+Y_WYJSCIA, NULL);
		LineTo(kontekst, akt_program_LD->mapuj_x(akt_program_LD->x_cewek()+1), akt_program_LD->mapuj_y(y)+Y_WYJSCIA);
      }
	}

void rung::dodaj_hotspot(int x, int y)
	{
   if (elementy)
   	elementy->dodaj_hotspot(x, y);
   if (cewki)
	   cewki->dodaj_hotspot(akt_program_LD->x_cewek(), y);
   }

ZDARZENIE rung::edytuj(int x, int y, ZDARZENIE zdarzenie, element * &edytowany)
	{
	int temp_x1, temp_y1, temp_x2, temp_y2;
	if (elementy)
		elementy->podaj_rozmiar(temp_x1, temp_y1);
	else
		{
		temp_x1 = 0;
		temp_y1 = 0;
		}
	if (cewki)
		cewki->podaj_rozmiar(temp_x2, temp_y2);
	else
		{
		temp_x2 = 0;
		temp_y2 = 0;
		}
	if ((x<temp_x1)&&(y<temp_y1))
		{
		switch (elementy->edytuj(x, y, zdarzenie, edytowany))
			{
			case NIC_NIE_ROB:
				return NIC_NIE_ROB;
			case SKASUJ_MNIE:
				delete elementy;
				elementy = NULL;
				return NIC_NIE_ROB;
			case ZASTAP_MNIE:
				delete elementy;
				elementy = edytowany;
				return NIC_NIE_ROB;
			case ZASTAP_MNIE_I_NIE_KASUJ:
				elementy = edytowany;
				return NIC_NIE_ROB;
			}
		return NIC_NIE_ROB;
		}
	if ((x<temp_x2+akt_program_LD->x_cewek())&&(x>=akt_program_LD->x_cewek())&&(y<temp_y2))
		{
		switch (cewki->edytuj(x-akt_program_LD->x_cewek(), y, zdarzenie, edytowany))
			{
			case NIC_NIE_ROB:
				return NIC_NIE_ROB;
			case SKASUJ_MNIE:
				delete cewki;
				cewki = NULL;
				return NIC_NIE_ROB;
			case ZASTAP_MNIE:
				delete cewki;
				cewki = edytowany;
				return NIC_NIE_ROB;
			case ZASTAP_MNIE_I_NIE_KASUJ:
				cewki = edytowany;
				return NIC_NIE_ROB;
			}
		return NIC_NIE_ROB;
		}
   if ((elementy)&&(!cewki)&&(x==akt_program_LD->x_cewek()))
   	switch (zdarzenie)
      	{
         case DODAJ_SZEREGOWO:
         case DODAJ_ROWNOLEGLE:
         	cewki = edytowany;
            return NIC_NIE_ROB;
         default:
         	return NIC_NIE_ROB;
         }
   if ((!elementy)&&(cewki)&&(x>=0)&&(x<akt_program_LD->x_cewek()))
   	switch (zdarzenie)
      	{
         case DODAJ_SZEREGOWO:
         case DODAJ_ROWNOLEGLE:
         	elementy = edytowany;
            return NIC_NIE_ROB;
         default:
         	return NIC_NIE_ROB;
         }
	return NIC_NIE_ROB;
	}

int rung::sa_elementy(void)
	{
   if (elementy)
   	return TRUE;
   return FALSE;
   }

int rung::sa_cewki(void)
	{
   if (cewki)
   	return TRUE;
   return FALSE;
   }

void rung::zapisz(FILE * plik)
	{
   int stala;
   if (elementy)
   	{
      stala = 1;
      fwrite(&stala, sizeof(stala), 1, plik);
      elementy->zapisz(plik);
      }
   else
   	{
      stala = 0;
      fwrite(&stala, sizeof(stala), 1, plik);
      }
   if (cewki)
   	{
      stala = 1;
      fwrite(&stala, sizeof(stala), 1, plik);
      cewki->zapisz(plik);
      }
   else
   	{
      stala = 0;
      fwrite(&stala, sizeof(stala), 1, plik);
      }
   }

rung::rung(FILE * plik)
	{
	int stala;
   fread(&stala, sizeof(stala), 1, plik);
   if (stala)
		elementy = akt_narzedzia->rozpoznaj_i_wczytaj(plik);
   else
   	elementy = NULL;
   fread(&stala, sizeof(stala), 1, plik);
   if (stala)
		cewki = akt_narzedzia->rozpoznaj_i_wczytaj(plik);
   else
   	cewki = NULL;
   }

