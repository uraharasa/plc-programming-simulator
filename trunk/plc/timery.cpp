#include "timery.h"

timer_ONDTR::timer_ONDTR()
	{
   nazwa = L"timer_ONDTR";
   nazwa_bloku = L"ONDTR";
   adres_bazowy = new pamiec(L"", MOZNA_R, 3);
   il_wejsc = 2;
   wejscia = new pamiec *[2];
   *wejscia = new pamiec(L"R", MOZNA_I|MOZNA_R|MOZNA_M);
   *(wejscia+1) = new pamiec(L"PV", MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_CONST);
   }

timer_ONDTR::timer_ONDTR(FILE * plik): blok_funkcyjny(plik)
	{
   nazwa = L"timer_ONDTR";
   }

int timer_ONDTR::dzialaj(int wejscie)
	{
   if (wejscie)
   	{
      adres_bazowy->zapisz_pamiec((*(wejscia+1))->odczytaj_pamiec(),1);
      adres_bazowy->zapisz_pamiec(adres_bazowy->odczytaj_pamiec(0)+1, 0);
      }
   if ((*(wejscia))->odczytaj_pamiec())
   	adres_bazowy->zapisz_pamiec(0, 0);
   if (adres_bazowy->odczytaj_pamiec(0) >= adres_bazowy->odczytaj_pamiec(1))
   	return TRUE;
   else
   	return FALSE;
   }

element * timer_ONDTR::sklonuj(FILE * plik)
	{
   if (plik)
	   return new timer_ONDTR(plik);
   else
	   return new timer_ONDTR;
   }

timer_OFDT::timer_OFDT()
	{
   nazwa = L"timer_OFDT";
   nazwa_bloku = L"OFDT";
   adres_bazowy = new pamiec(L"", MOZNA_R, 3);
   il_wejsc = 1;
   wejscia = new pamiec *;
   *wejscia = new pamiec(L"PV", MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_CONST);
   }

timer_OFDT::timer_OFDT(FILE * plik): blok_funkcyjny(plik)
	{
   nazwa = L"timer_OFDT";
   }

int timer_OFDT::dzialaj(int wejscie)
	{
   if (wejscie)
   	{
      adres_bazowy->zapisz_pamiec(0, 0);
      adres_bazowy->zapisz_pamiec((*wejscia)->odczytaj_pamiec(), 1);
      return TRUE;
      }
   else
   	{
      adres_bazowy->zapisz_pamiec(adres_bazowy->odczytaj_pamiec(0)+1, 0);
      adres_bazowy->zapisz_pamiec((*wejscia)->odczytaj_pamiec(), 1);
      if (adres_bazowy->odczytaj_pamiec(0) >= adres_bazowy->odczytaj_pamiec(1))
      	return FALSE;
      else
      	return TRUE;
      }
   }

element * timer_OFDT::sklonuj(FILE * plik)
	{
   if (plik)
	   return new timer_OFDT(plik);
   else
	   return new timer_OFDT;
   }

timer_TMR::timer_TMR()
	{
   nazwa = L"timer_TMR";
   nazwa_bloku = L"TMR";
   adres_bazowy = new pamiec(L"", MOZNA_R, 3);
   il_wejsc = 1;
   wejscia = new pamiec *;
   *wejscia = new pamiec(L"PV", MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_CONST);
   }

timer_TMR::timer_TMR(FILE * plik): blok_funkcyjny(plik)
	{
   nazwa = L"timer_TMR";
   }

int timer_TMR::dzialaj(int wejscie)
	{
   if (wejscie)
   	{
      adres_bazowy->zapisz_pamiec(adres_bazowy->odczytaj_pamiec(0)+1, 0);
      adres_bazowy->zapisz_pamiec((*wejscia)->odczytaj_pamiec(), 1);
      if (adres_bazowy->odczytaj_pamiec(0) >= adres_bazowy->odczytaj_pamiec(1))
      	return TRUE;
      else
      	return FALSE;
      }
   else
   	{
      adres_bazowy->zapisz_pamiec(0, 0);
      return FALSE;
      }
   }

element * timer_TMR::sklonuj(FILE * plik)
	{
   if (plik)
	   return new timer_TMR(plik);
   else
	   return new timer_TMR;
   }
