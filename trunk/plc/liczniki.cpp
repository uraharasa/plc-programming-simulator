#include "liczniki.h"

licznik_UPCTR::licznik_UPCTR()
	{
   nazwa = "licznik_UPCTR";
   nazwa_bloku = new char[strlen("UPCTR")+1];
   strcpy(nazwa_bloku, "UPCTR");
   adres_bazowy = new pamiec("", MOZNA_R, 3);
   il_wejsc = 2;
   wejscia = new pamiec *[2];
   *wejscia = new pamiec("R", MOZNA_I|MOZNA_R|MOZNA_M);
   *(wejscia+1) = new pamiec("PV", MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_CONST);
   }

licznik_UPCTR::licznik_UPCTR(FILE * plik): blok_funkcyjny(plik)
	{
   nazwa = "licznik_UPCTR";
   }

int licznik_UPCTR::dzialaj(int wejscie)
	{
   if ((wejscie)&&(!((adres_bazowy->odczytaj_pamiec(2))&0x2000)))
      adres_bazowy->zapisz_pamiec(adres_bazowy->odczytaj_pamiec(0)+1, 0);
	if ((*wejscia)->odczytaj_pamiec())
   	adres_bazowy->zapisz_pamiec(0, 0);
   adres_bazowy->zapisz_pamiec((*(wejscia+1))->odczytaj_pamiec(), 1);
	if (wejscie)
   	adres_bazowy->zapisz_pamiec(adres_bazowy->odczytaj_pamiec(2)|0x2000,2);
   else
   	adres_bazowy->zapisz_pamiec(adres_bazowy->odczytaj_pamiec(2)&0xdfff,2);
   if (adres_bazowy->odczytaj_pamiec(0) >= adres_bazowy->odczytaj_pamiec(1))
   	return TRUE;
   else
   	return FALSE;
   }

element * licznik_UPCTR::sklonuj(FILE * plik)
	{
   if (plik)
	   return new licznik_UPCTR(plik);
   else
	   return new licznik_UPCTR;
   }

licznik_DNCTR::licznik_DNCTR()
	{
   nazwa = "licznik_DNCTR";
   nazwa_bloku = new char[strlen("DNCTR")+1];
   strcpy(nazwa_bloku, "DNCTR");
   adres_bazowy = new pamiec("", MOZNA_R, 3);
   il_wejsc = 2;
   wejscia = new pamiec *[2];
   *wejscia = new pamiec("R", MOZNA_I|MOZNA_R|MOZNA_M);
   *(wejscia+1) = new pamiec("PV", MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_CONST);
   }

licznik_DNCTR::licznik_DNCTR(FILE * plik): blok_funkcyjny(plik)
	{
   nazwa = "licznik_DNCTR";
   }

int licznik_DNCTR::dzialaj(int wejscie)
	{
   if ((wejscie)&&(!((adres_bazowy->odczytaj_pamiec(2))&0x2000)))
      adres_bazowy->zapisz_pamiec(adres_bazowy->odczytaj_pamiec(0)-1, 0);
   adres_bazowy->zapisz_pamiec((*(wejscia+1))->odczytaj_pamiec(), 1);
	if ((*wejscia)->odczytaj_pamiec())
   	adres_bazowy->zapisz_pamiec(adres_bazowy->odczytaj_pamiec(1), 0);
	if (wejscie)
   	adres_bazowy->zapisz_pamiec(adres_bazowy->odczytaj_pamiec(2)|0x2000,2);
   else
   	adres_bazowy->zapisz_pamiec(adres_bazowy->odczytaj_pamiec(2)&0xdfff,2);
   if (adres_bazowy->odczytaj_pamiec(0) <= 0)
   	return TRUE;
   else
   	return FALSE;
   }

element * licznik_DNCTR::sklonuj(FILE * plik)
	{
   if (plik)
	   return new licznik_DNCTR(plik);
   else
	   return new licznik_DNCTR;
   }

