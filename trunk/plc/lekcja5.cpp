#include "lekcja5.h"

void lekcja5::zresetuj()
	{
   polozenie_windy = 0;
   polozenie_drzwi[0] = 0;
   polozenie_drzwi[1] = 0;
   polozenie_drzwi[2] = 0;
   polozenie_drzwi[3] = 0;
   polozenie_drzwi[4] = 0;
   wcisniete_przyciski[0] = FALSE;
   wcisniete_przyciski[1] = FALSE;
   wcisniete_przyciski[2] = FALSE;
   wcisniete_przyciski[3] = FALSE;
   wcisniete_przyciski[4] = FALSE;
   lekcja::zresetuj();
   }

BOOL lekcja5::click(int x, int y)
	{
   if ((x>=300) && (x<340))
   	{
      if ((y>=60)&&(y<100))
      	wcisniete_przyciski[4] = TRUE;
      if ((y>=100)&&(y<140))
      	wcisniete_przyciski[3] = TRUE;
      if ((y>=140)&&(y<180))
      	wcisniete_przyciski[2] = TRUE;
      if ((y>=180)&&(y<220))
      	wcisniete_przyciski[1] = TRUE;
      if ((y>=220)&&(y<260))
      	wcisniete_przyciski[0] = TRUE;
      }
   return FALSE;
   }

lekcja5::lekcja5() : winda(L"lekcja5\\winda"),
							drzwi(L"lekcja5\\drzwi"),
							pietro(L"lekcja5\\pietro"),
							parter(L"lekcja5\\parter"),
							pietro_1(L"lekcja5\\pietro_1"),
							pietro_2(L"lekcja5\\pietro_2"),
							pietro_3(L"lekcja5\\pietro_3"),
							pietro_4(L"lekcja5\\pietro_4"),
							button_p(L"lekcja5\\button_p"),
							button_1(L"lekcja5\\button_1"),
							button_2(L"lekcja5\\button_2"),
							button_3(L"lekcja5\\button_3"),
							button_4(L"lekcja5\\button_4")
	{
   nazwa = L"lekcja5";
   pamiec::nowe_parametry_sterownika(5, 12, 200, 200, 1, 0);
   wejscia_I = new pamiec(typ_I, 0, 5);
   wejscia_AI = new pamiec(typ_AI, 0, 1);
   wyjscia_Q = new pamiec(typ_Q, 0, 12);
   pamiec::dodaj_opis(typ_I, 0, L"PRZYC_P");
   pamiec::dodaj_opis(typ_I, 1, L"PRZYC_1");
   pamiec::dodaj_opis(typ_I, 2, L"PRZYC_2");
   pamiec::dodaj_opis(typ_I, 3, L"PRZYC_3");
   pamiec::dodaj_opis(typ_I, 4, L"PRZYC_4");
   pamiec::dodaj_opis(typ_AI, 0, L"CZUJ_WYS");
   pamiec::dodaj_opis(typ_Q, 0, L"SWIAT£O_P");
   pamiec::dodaj_opis(typ_Q, 1, L"SWIAT£O_1");
   pamiec::dodaj_opis(typ_Q, 2, L"SWIAT£O_2");
   pamiec::dodaj_opis(typ_Q, 3, L"SWIAT£O_3");
   pamiec::dodaj_opis(typ_Q, 4, L"SWIAT£O_4");
   pamiec::dodaj_opis(typ_Q, 5, L"DRZWI_P");
   pamiec::dodaj_opis(typ_Q, 6, L"DRZWI_1");
   pamiec::dodaj_opis(typ_Q, 7, L"DRZWI_2");
   pamiec::dodaj_opis(typ_Q, 8, L"DRZWI_3");
   pamiec::dodaj_opis(typ_Q, 9, L"DRZWI_4");
   pamiec::dodaj_opis(typ_Q, 10, L"WIND_RUCH");
   pamiec::dodaj_opis(typ_Q, 11, L"WIND_KIER");
   zresetuj();
   }

lekcja5::~lekcja5()
	{
   pamiec::nowe_parametry_sterownika(0, 0, 0, 0, 0, 0);
   }

void lekcja5::podaj_rozmiar_okna(int & szerokosc, int & wysokosc)
	{
   szerokosc = 340;
   wysokosc = 320;
   }

void lekcja5::dzialaj()
	{
	for (int i=0; i<5; i++)
   	{
      if (wcisniete_przyciski[i])
      	wejscia_I->zapisz_pamiec(1, i);
      else
      	wejscia_I->zapisz_pamiec(0, i);
      wcisniete_przyciski[i] = FALSE;
      }
   if (wyjscia_Q->odczytaj_pamiec(10))
   	if (wyjscia_Q->odczytaj_pamiec(11))
		   polozenie_windy++;
      else
		   polozenie_windy--;
   if (polozenie_windy > 1280)
   	polozenie_windy = 1280;
   if (polozenie_windy < 0)
   	polozenie_windy = 0;
   for (int i=0; i<5; i++)
   	{
      if (wyjscia_Q->odczytaj_pamiec(5+i))
	      polozenie_drzwi[i] += 1;
      else
      	polozenie_drzwi[i] -= 1;
      if (polozenie_drzwi[i] > 64)
      	polozenie_drzwi[i] = 64;
      if (polozenie_drzwi[i] < 0)
      	polozenie_drzwi[i] = 0;
      }
  	wejscia_AI->zapisz_pamiec(polozenie_windy, 0);
   lekcja::dzialaj();
   }

void lekcja5::narysuj(HDC kontekst)
	{
   winda.wyswietl(kontekst, 0, 0);
   int ktore_drzwi = polozenie_windy/320;
   drzwi.wyswietl(kontekst, 89-polozenie_drzwi[ktore_drzwi], polozenie_windy%320 + 114);
   drzwi.wyswietl(kontekst, 154+polozenie_drzwi[ktore_drzwi], polozenie_windy%320 + 114);
   if (ktore_drzwi+1 < 5)
   	{
	   drzwi.wyswietl(kontekst, 89-polozenie_drzwi[ktore_drzwi+1], polozenie_windy%320 + 114 - 320);
	   drzwi.wyswietl(kontekst, 154+polozenie_drzwi[ktore_drzwi+1], polozenie_windy%320 + 114 - 320);
      }
   pietro.wyswietl(kontekst, 0, polozenie_windy%320);
   pietro.wyswietl(kontekst, 0, polozenie_windy%320 - 320);
   parter.wyswietl(kontekst, 40, polozenie_windy + 170 - 320*0);
   pietro_1.wyswietl(kontekst, 40, polozenie_windy + 170 - 320*1);
   pietro_2.wyswietl(kontekst, 40, polozenie_windy + 170 - 320*2);
   pietro_3.wyswietl(kontekst, 40, polozenie_windy + 170 - 320*3);
   pietro_4.wyswietl(kontekst, 40, polozenie_windy + 170 - 320*4);
   if (wyjscia_Q->odczytaj_pamiec(0))
   	button_p.wyswietl(kontekst, 300, 220);
   if (wyjscia_Q->odczytaj_pamiec(1))
   	button_1.wyswietl(kontekst, 300, 180);
   if (wyjscia_Q->odczytaj_pamiec(2))
   	button_2.wyswietl(kontekst, 300, 140);
   if (wyjscia_Q->odczytaj_pamiec(3))
   	button_3.wyswietl(kontekst, 300, 100);
   if (wyjscia_Q->odczytaj_pamiec(4))
   	button_4.wyswietl(kontekst, 300, 60);
   }

