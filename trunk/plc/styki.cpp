#include "styki.h"
#include "okno_glowne.h"

styk::styk()
	{
   adres_bazowy = new pamiec("", MOZNA_I|MOZNA_M|MOZNA_R|MOZNA_Q);
   }

styk::styk(FILE * plik): element_zwykly(plik)
	{
   }

void styk::podaj_rozmiar(int & szerokosc, int & wysokosc, int tryb)
	{
   szerokosc = 1;
   wysokosc = 1;
   }

styk_zwierny::styk_zwierny(void)
	{
   nazwa = "styk_zwierny";
   }

styk_zwierny::styk_zwierny(FILE * plik): styk(plik)
	{
   nazwa = "styk_zwierny";
   }

int styk_zwierny::dzialaj(int wejscie)
	{
   if (adres_bazowy->odczytaj_pamiec())
   	return wejscie;
   else
   	return 0;
   }

void styk_zwierny::narysuj(HDC kontekst, int tryb, int x, int y)
	{
   int x_pocz = akt_program_LD->mapuj_x(x);
   int y_pocz = akt_program_LD->mapuj_y(y);
   MoveToEx(kontekst, x_pocz, y_pocz+Y_WYJSCIA, NULL);
   LineTo(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA);
   MoveToEx(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA-10, NULL);
   LineTo(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA+10);
   MoveToEx(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA-10, NULL);
   LineTo(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA+10);
   MoveToEx(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA, NULL);
   LineTo(kontekst, x_pocz+60, y_pocz+Y_WYJSCIA);
	if (tryb&RYSUJ_ADRES)
      adres_bazowy->narysuj_adres(kontekst, x_pocz+30, y_pocz, TA_CENTER|TA_TOP|TA_NOUPDATECP);
   }

element * styk_zwierny::sklonuj(FILE * plik)
	{
   if (plik)
	   return new styk_zwierny(plik);
   else
	   return new styk_zwierny;
   }

styk_rozwierny::styk_rozwierny(void)
	{
   nazwa = "styk_rozwierny";
   }

styk_rozwierny::styk_rozwierny(FILE * plik): styk(plik)
	{
   nazwa = "styk_rozwierny";
   }

int styk_rozwierny::dzialaj(int wejscie)
	{
   if (adres_bazowy->odczytaj_pamiec())
   	return 0;
   else
   	return wejscie;
   }

void styk_rozwierny::narysuj(HDC kontekst, int tryb, int x, int y)
	{
   int x_pocz = akt_program_LD->mapuj_x(x);
   int y_pocz = akt_program_LD->mapuj_y(y);
   MoveToEx(kontekst, x_pocz, y_pocz+Y_WYJSCIA, NULL);
   LineTo(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA);
   MoveToEx(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA-10, NULL);
   LineTo(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA+10);
   LineTo(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA-10);
   LineTo(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA+10);
   MoveToEx(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA, NULL);
   LineTo(kontekst, x_pocz+60, y_pocz+Y_WYJSCIA);
	if (tryb&RYSUJ_ADRES)
      adres_bazowy->narysuj_adres(kontekst, x_pocz+30, y_pocz, TA_CENTER|TA_TOP|TA_NOUPDATECP);
   }

element * styk_rozwierny::sklonuj(FILE * plik)
	{
   if (plik)
	   return new styk_rozwierny(plik);
   else
	   return new styk_rozwierny;
   }
