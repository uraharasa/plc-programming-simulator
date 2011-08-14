#include "cewki.h"
#include "okno_glowne.h"

cewka::cewka(void)
	{
   adres_bazowy = new pamiec(L"", MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AQ);
   }

cewka::cewka(FILE * plik): element_zwykly(plik)
	{
   }

void cewka::podaj_rozmiar(int & szerokosc, int & wysokosc, int tryb)
	{
   szerokosc = wysokosc = 1;
   }

cewka_zwierna::cewka_zwierna(void)
	{
   nazwa = L"cewka_zwierna";
   }

cewka_zwierna::cewka_zwierna(FILE * plik): cewka(plik)
	{
   nazwa = L"cewka_zwierna";
   }

element * cewka_zwierna::sklonuj(FILE * plik)
	{
   if (plik)
	   return new cewka_zwierna(plik);
   else
	   return new cewka_zwierna;
   }

int cewka_zwierna::dzialaj(int wejscie)
	{
	adres_bazowy->zapisz_pamiec(wejscie);
   return wejscie;
   }

void cewka_zwierna::narysuj(HDC kontekst, int tryb, int x, int y)
	{
	int x_pocz = akt_program_LD->mapuj_x(x);
	int y_pocz = akt_program_LD->mapuj_y(y);
   MoveToEx(kontekst, x_pocz, y_pocz+Y_WYJSCIA, NULL);
   LineTo(kontekst, x_pocz+20, y_pocz+Y_WYJSCIA);
   MoveToEx(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA-10, NULL);
   LineTo(kontekst, x_pocz+20, y_pocz+Y_WYJSCIA-5);
   LineTo(kontekst, x_pocz+20, y_pocz+Y_WYJSCIA+5);
   LineTo(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA+10);
   MoveToEx(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA-10, NULL);
   LineTo(kontekst, x_pocz+40, y_pocz+Y_WYJSCIA-5);
   LineTo(kontekst, x_pocz+40, y_pocz+Y_WYJSCIA+5);
   LineTo(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA+10);
   MoveToEx(kontekst, x_pocz+40, y_pocz+Y_WYJSCIA, NULL);
   LineTo(kontekst, x_pocz+60, y_pocz+Y_WYJSCIA);
   if (tryb&RYSUJ_ADRES)
      adres_bazowy->narysuj_adres(kontekst, x_pocz+30, y_pocz, TA_CENTER|TA_TOP|TA_NOUPDATECP);
   }

cewka_rozwierna::cewka_rozwierna(void)
	{
   nazwa = L"cewka_rozwierna";
   }

cewka_rozwierna::cewka_rozwierna(FILE * plik): cewka(plik)
	{
   nazwa = L"cewka_rozwierna";
   }

element * cewka_rozwierna::sklonuj(FILE * plik)
	{
   if (plik)
	   return new cewka_rozwierna(plik);
   else
	   return new cewka_rozwierna;
   }

int cewka_rozwierna::dzialaj(int wejscie)
	{
	adres_bazowy->zapisz_pamiec(!wejscie);
   return wejscie;
   }

void cewka_rozwierna::narysuj(HDC kontekst, int tryb, int x, int y)
	{
	int x_pocz = akt_program_LD->mapuj_x(x);
	int y_pocz = akt_program_LD->mapuj_y(y);
   MoveToEx(kontekst, x_pocz, y_pocz+Y_WYJSCIA, NULL);
   LineTo(kontekst, x_pocz+20, y_pocz+Y_WYJSCIA);
   MoveToEx(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA-10, NULL);
   LineTo(kontekst, x_pocz+20, y_pocz+Y_WYJSCIA-5);
   LineTo(kontekst, x_pocz+20, y_pocz+Y_WYJSCIA+5);
   LineTo(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA+10);
   LineTo(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA-10);
   LineTo(kontekst, x_pocz+40, y_pocz+Y_WYJSCIA-5);
   LineTo(kontekst, x_pocz+40, y_pocz+Y_WYJSCIA+5);
   LineTo(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA+10);
   MoveToEx(kontekst, x_pocz+40, y_pocz+Y_WYJSCIA, NULL);
   LineTo(kontekst, x_pocz+60, y_pocz+Y_WYJSCIA);
   if (tryb&RYSUJ_ADRES)
      adres_bazowy->narysuj_adres(kontekst, x_pocz+30, y_pocz, TA_CENTER|TA_TOP|TA_NOUPDATECP);
   }

cewka_zbocze_narastajace::cewka_zbocze_narastajace(void)
	{
   nazwa = L"cewka_zbocze_narastajace";
   stan_poprzedni = 0;
   }

cewka_zbocze_narastajace::cewka_zbocze_narastajace(FILE * plik): cewka(plik)
	{
   nazwa = L"cewka_zbocze_narastajace";
   stan_poprzedni = 0;
   }

element * cewka_zbocze_narastajace::sklonuj(FILE * plik)
	{
   if (plik)
	   return new cewka_zbocze_narastajace(plik);
   else
	   return new cewka_zbocze_narastajace;
   }

int cewka_zbocze_narastajace::dzialaj(int wejscie)
	{
   if ((wejscie)&&(!stan_poprzedni))
		adres_bazowy->zapisz_pamiec(1);
   else
		adres_bazowy->zapisz_pamiec(0);
   stan_poprzedni = wejscie;
   return wejscie;
   }

void cewka_zbocze_narastajace::narysuj(HDC kontekst, int tryb, int x, int y)
	{
	int x_pocz = akt_program_LD->mapuj_x(x);
	int y_pocz = akt_program_LD->mapuj_y(y);
   MoveToEx(kontekst, x_pocz, y_pocz+Y_WYJSCIA, NULL);
   LineTo(kontekst, x_pocz+20, y_pocz+Y_WYJSCIA);
   MoveToEx(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA-10, NULL);
   LineTo(kontekst, x_pocz+20, y_pocz+Y_WYJSCIA-5);
   LineTo(kontekst, x_pocz+20, y_pocz+Y_WYJSCIA+5);
   LineTo(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA+10);
   MoveToEx(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA-10, NULL);
   LineTo(kontekst, x_pocz+40, y_pocz+Y_WYJSCIA-5);
   LineTo(kontekst, x_pocz+40, y_pocz+Y_WYJSCIA+5);
   LineTo(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA+10);
   MoveToEx(kontekst, x_pocz+30, y_pocz+Y_WYJSCIA+10, NULL);
   LineTo(kontekst, x_pocz+30, y_pocz+Y_WYJSCIA-10);
   MoveToEx(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA, NULL);
   LineTo(kontekst, x_pocz+30, y_pocz+Y_WYJSCIA-10);
   LineTo(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA);
   MoveToEx(kontekst, x_pocz+40, y_pocz+Y_WYJSCIA, NULL);
   LineTo(kontekst, x_pocz+60, y_pocz+Y_WYJSCIA);
   if (tryb&RYSUJ_ADRES)
      adres_bazowy->narysuj_adres(kontekst, x_pocz+30, y_pocz, TA_CENTER|TA_TOP|TA_NOUPDATECP);
   }

cewka_zbocze_opadajace::cewka_zbocze_opadajace(void)
	{
   nazwa = L"cewka_zbocze_opadajace";
   stan_poprzedni = 0;
   }

cewka_zbocze_opadajace::cewka_zbocze_opadajace(FILE * plik): cewka(plik)
	{
   nazwa = L"cewka_zbocze_opadajace";
   stan_poprzedni = 0;
   }

element * cewka_zbocze_opadajace::sklonuj(FILE * plik)
	{
   if (plik)
	   return new cewka_zbocze_opadajace(plik);
   else
	   return new cewka_zbocze_opadajace;
   }

int cewka_zbocze_opadajace::dzialaj(int wejscie)
	{
   if ((!wejscie)&&(stan_poprzedni))
		adres_bazowy->zapisz_pamiec(1);
   else
		adres_bazowy->zapisz_pamiec(0);
   stan_poprzedni = wejscie;
   return wejscie;
   }

void cewka_zbocze_opadajace::narysuj(HDC kontekst, int tryb, int x, int y)
	{
	int x_pocz = akt_program_LD->mapuj_x(x);
	int y_pocz = akt_program_LD->mapuj_y(y);
   MoveToEx(kontekst, x_pocz, y_pocz+Y_WYJSCIA, NULL);
   LineTo(kontekst, x_pocz+20, y_pocz+Y_WYJSCIA);
   MoveToEx(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA-10, NULL);
   LineTo(kontekst, x_pocz+20, y_pocz+Y_WYJSCIA-5);
   LineTo(kontekst, x_pocz+20, y_pocz+Y_WYJSCIA+5);
   LineTo(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA+10);
   MoveToEx(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA-10, NULL);
   LineTo(kontekst, x_pocz+40, y_pocz+Y_WYJSCIA-5);
   LineTo(kontekst, x_pocz+40, y_pocz+Y_WYJSCIA+5);
   LineTo(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA+10);
   MoveToEx(kontekst, x_pocz+30, y_pocz+Y_WYJSCIA+10, NULL);
   LineTo(kontekst, x_pocz+30, y_pocz+Y_WYJSCIA-10);
   MoveToEx(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA, NULL);
   LineTo(kontekst, x_pocz+30, y_pocz+Y_WYJSCIA+10);
   LineTo(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA);
   MoveToEx(kontekst, x_pocz+40, y_pocz+Y_WYJSCIA, NULL);
   LineTo(kontekst, x_pocz+60, y_pocz+Y_WYJSCIA);
   if (tryb&RYSUJ_ADRES)
      adres_bazowy->narysuj_adres(kontekst, x_pocz+30, y_pocz, TA_CENTER|TA_TOP|TA_NOUPDATECP);
   }

cewka_S::cewka_S(void)
	{
   nazwa = L"cewka_S";
   }

cewka_S::cewka_S(FILE * plik): cewka(plik)
	{
   nazwa = L"cewka_S";
   }

element * cewka_S::sklonuj(FILE * plik)
	{
   if (plik)
	   return new cewka_S(plik);
   else
	   return new cewka_S;
   }

int cewka_S::dzialaj(int wejscie)
	{
   if (wejscie)
		adres_bazowy->zapisz_pamiec(1);
   return wejscie;
   }

void cewka_S::narysuj(HDC kontekst, int tryb, int x, int y)
	{
	int x_pocz = akt_program_LD->mapuj_x(x);
	int y_pocz = akt_program_LD->mapuj_y(y);
   MoveToEx(kontekst, x_pocz, y_pocz+Y_WYJSCIA, NULL);
   LineTo(kontekst, x_pocz+20, y_pocz+Y_WYJSCIA);
   MoveToEx(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA-10, NULL);
   LineTo(kontekst, x_pocz+20, y_pocz+Y_WYJSCIA-5);
   LineTo(kontekst, x_pocz+20, y_pocz+Y_WYJSCIA+5);
   LineTo(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA+10);
   MoveToEx(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA-10, NULL);
   LineTo(kontekst, x_pocz+40, y_pocz+Y_WYJSCIA-5);
   LineTo(kontekst, x_pocz+40, y_pocz+Y_WYJSCIA+5);
   LineTo(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA+10);
   MoveToEx(kontekst, x_pocz+40, y_pocz+Y_WYJSCIA, NULL);
   LineTo(kontekst, x_pocz+60, y_pocz+Y_WYJSCIA);
   if (tryb&RYSUJ_NAZWE)
   	{
      SetTextAlign(kontekst, TA_TOP|TA_CENTER|TA_NOUPDATECP);
      TextOut(kontekst, x_pocz+30, y_pocz+Y_WYJSCIA-7, L"S", 1);
      }
   if (tryb&RYSUJ_ADRES)
      adres_bazowy->narysuj_adres(kontekst, x_pocz+30, y_pocz, TA_CENTER|TA_TOP|TA_NOUPDATECP);
   }

cewka_R::cewka_R(void)
	{
   nazwa = L"cewka_R";
   }

cewka_R::cewka_R(FILE * plik): cewka(plik)
	{
   nazwa = L"cewka_R";
   }

element * cewka_R::sklonuj(FILE * plik)
	{
   if (plik)
	   return new cewka_R(plik);
   else
	   return new cewka_R;
   }

int cewka_R::dzialaj(int wejscie)
	{
   if (wejscie)
		adres_bazowy->zapisz_pamiec(0);
   return wejscie;
   }

void cewka_R::narysuj(HDC kontekst, int tryb, int x, int y)
	{
	int x_pocz = akt_program_LD->mapuj_x(x);
	int y_pocz = akt_program_LD->mapuj_y(y);
   MoveToEx(kontekst, x_pocz, y_pocz+Y_WYJSCIA, NULL);
   LineTo(kontekst, x_pocz+20, y_pocz+Y_WYJSCIA);
   MoveToEx(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA-10, NULL);
   LineTo(kontekst, x_pocz+20, y_pocz+Y_WYJSCIA-5);
   LineTo(kontekst, x_pocz+20, y_pocz+Y_WYJSCIA+5);
   LineTo(kontekst, x_pocz+25, y_pocz+Y_WYJSCIA+10);
   MoveToEx(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA-10, NULL);
   LineTo(kontekst, x_pocz+40, y_pocz+Y_WYJSCIA-5);
   LineTo(kontekst, x_pocz+40, y_pocz+Y_WYJSCIA+5);
   LineTo(kontekst, x_pocz+35, y_pocz+Y_WYJSCIA+10);
   MoveToEx(kontekst, x_pocz+40, y_pocz+Y_WYJSCIA, NULL);
   LineTo(kontekst, x_pocz+60, y_pocz+Y_WYJSCIA);
   if (tryb&RYSUJ_NAZWE)
   	{
      SetTextAlign(kontekst, TA_TOP|TA_CENTER|TA_NOUPDATECP);
      TextOut(kontekst, x_pocz+30, y_pocz+Y_WYJSCIA-7, L"R", 1);
      }
   if (tryb&RYSUJ_ADRES)
      adres_bazowy->narysuj_adres(kontekst, x_pocz+30, y_pocz, TA_CENTER|TA_TOP|TA_NOUPDATECP);
   }

