#include "lekcja1.h"
#include "pamiec.h"
#include "bitmapy.h"

const int wys_zarow = 20;
const int wys_panelu = 80;

void lekcja1::dzialaj(void)
{
	if (button1)
	{
		wejscia_I->zapisz_pamiec(1, 2);
		button1 = FALSE;
	}
	else
		wejscia_I->zapisz_pamiec(0, 2);
	if (button2)
	{
		wejscia_I->zapisz_pamiec(1, 3);
		button2 = FALSE;
	}
	else
		wejscia_I->zapisz_pamiec(0, 3);
	if (switch1)
		wejscia_I->zapisz_pamiec(1, 0);
	else
		wejscia_I->zapisz_pamiec(0, 0);
	if (switch2)
		wejscia_I->zapisz_pamiec(1, 1);
	else
		wejscia_I->zapisz_pamiec(0, 1);
	wejscia_AI->zapisz_pamiec(poten1, 0);
	wejscia_AI->zapisz_pamiec((float)poten2*2.5 + 50 + rand() * 10 / RAND_MAX, 1);
	float predkosc = wyjscia_AQ->odczytaj_pamiec(0);
	predkosc -= predkosc*((float)rand() * 100 /(float)1000 / RAND_MAX);
	if (predkosc < 0)
		predkosc = 0;
	if (predkosc > 1000)
		predkosc = 1000;
	kat_obrotu += predkosc/10;
	wejscia_I->zapisz_pamiec(0, 4);
	while (kat_obrotu >= 256)
	{
		kat_obrotu -= 256;
		wejscia_I->zapisz_pamiec(1, 4);
	}
	lekcja::dzialaj();
}

void lekcja1::zresetuj(void)
{
	srand(123);
	kat_obrotu = 0;
	switch1 = FALSE;
	switch2 = FALSE;
	button1 = FALSE;
	button2 = FALSE;
	poten1 = 0;
	poten2 = 0;
	lekcja::zresetuj();
}

BOOL lekcja1::click(int x, int y)
{
	if ((x>=2) && (x<2+35) && (y>=wys_panelu+12) && (y<wys_panelu+12+48))
	{
		switch1 = !switch1;
		return TRUE;
	}
	if ((x>=42) && (x<42+35) && (y>=wys_panelu+12) && (y<wys_panelu+12+48))
	{
		switch2 = !switch2;
		return TRUE;
	}
	if ((x>=84) && (x<84+32) && (y>=wys_panelu+20) && (y<wys_panelu+20+32))
	{
		button1 = TRUE;
		return FALSE;
	}
	if ((x>=124) && (x<124+32) && (y>=wys_panelu+20) && (y<wys_panelu+20+32))
	{
		button2 = TRUE;
		return FALSE;
	}
	if ((x>=164) && (x<164+31) && (y>=wys_panelu) && (y<wys_panelu+71))
	{
		poten1 = 45-(y - wys_panelu - 8 - 5);
		if (poten1 < 0)
			poten1 = 0;
		if (poten1 > 45)
			poten1 = 45;
		return TRUE;
	}
	if ((x>=204) && (x<204+31) && (y>=wys_panelu) && (y<wys_panelu+71))
	{
		poten2 = 45-(y - wys_panelu - 8 - 5);
		if (poten2 < 0)
			poten2 = 0;
		if (poten2 > 45)
			poten2 = 45;
		return TRUE;
	}
	return FALSE;
}

void lekcja1::narysuj(HDC kontekst)
{
	tlo.wyswietl(kontekst, 0, 0);
	if (wyjscia_Q->odczytaj_pamiec(0))
		zolta_zapal.wyswietl(kontekst, 2, wys_zarow);
	else
		zolta_zgasz.wyswietl(kontekst, 3, wys_zarow);
	if (wyjscia_Q->odczytaj_pamiec(1))
		czerwona_zapal.wyswietl(kontekst, 42, wys_zarow);
	else
		czerwona_zgasz.wyswietl(kontekst, 42, wys_zarow);
	if (wyjscia_Q->odczytaj_pamiec(2))
		zolta_zapal.wyswietl(kontekst, 82, wys_zarow);
	else
		zolta_zgasz.wyswietl(kontekst, 83, wys_zarow);
	if (wyjscia_Q->odczytaj_pamiec(3))
		czerwona_zapal.wyswietl(kontekst, 122, wys_zarow);
	else
		czerwona_zgasz.wyswietl(kontekst, 122, wys_zarow);
	switch ((int)kat_obrotu/64)
	{
	case 0:
		wiatrak1.wyswietl(kontekst, 184, wys_zarow);
		break;
	case 1:
		wiatrak2.wyswietl(kontekst, 184, wys_zarow);
		break;
	case 2:
		wiatrak3.wyswietl(kontekst, 184, wys_zarow);
		break;
	case 3:
		wiatrak4.wyswietl(kontekst, 184, wys_zarow);
		break;
	}
	if (switch1)
		switch_on.wyswietl(kontekst, 2, wys_panelu+12);
	else
		switch_off.wyswietl(kontekst, 2, wys_panelu+12);
	if (switch2)
		switch_on.wyswietl(kontekst, 42, wys_panelu+12);
	else
		switch_off.wyswietl(kontekst, 42, wys_panelu+12);
	pushbutton.wyswietl(kontekst, 84, wys_panelu+20);
	pushbutton.wyswietl(kontekst, 124, wys_panelu+20);
	poten_podst.wyswietl(kontekst, 164, wys_panelu);
	poten_galka.wyswietl(kontekst, 174, wys_panelu+8+45-poten1);
	poten_podst.wyswietl(kontekst, 204, wys_panelu);
	poten_galka.wyswietl(kontekst, 214, wys_panelu+8+45-poten2);
}

lekcja1::lekcja1() : wiatrak1(L"lekcja1\\wiatrak1"),
	wiatrak2(L"lekcja1\\wiatrak2"),
	wiatrak3(L"lekcja1\\wiatrak3"),
	wiatrak4(L"lekcja1\\wiatrak4"),
	czerwona_zgasz(L"lekcja1\\czerw_zgasz"),
	czerwona_zapal(L"lekcja1\\czerw_zapal"),
	zolta_zgasz(L"lekcja1\\zolta_zgasz"),
	zolta_zapal(L"lekcja1\\zolta_zapal"),
	pushbutton(L"lekcja1\\pushbutton"),
	switch_on(L"lekcja1\\switch_on"),
	switch_off(L"lekcja1\\switch_off"),
	poten_podst(L"lekcja1\\poten_podst"),
	poten_galka(L"lekcja1\\poten_galka"),
	tlo(L"lekcja1\\tlo")
{
	nazwa = L"lekcja1";
	pamiec::nowe_parametry_sterownika(5,4,100,100,2,1);
	wejscia_I = new pamiec(typ_I, 0, 5);
	wyjscia_Q = new pamiec(typ_Q, 0, 4);
	wejscia_AI = new pamiec(typ_AI, 0, 2);
	wyjscia_AQ = new pamiec(typ_AQ, 0, 1);
	pamiec::dodaj_opis(typ_Q, 0, L"¯Ó£TA_1");
	pamiec::dodaj_opis(typ_Q, 1, L"CZERW_1");
	pamiec::dodaj_opis(typ_Q, 2, L"¯Ó£TA_2");
	pamiec::dodaj_opis(typ_Q, 3, L"CZERW_2");
	pamiec::dodaj_opis(typ_I, 0, L"BISTAB_1");
	pamiec::dodaj_opis(typ_I, 1, L"BISTAB_2");
	pamiec::dodaj_opis(typ_I, 2, L"ASTAB_1");
	pamiec::dodaj_opis(typ_I, 3, L"ASTAB_2");
	pamiec::dodaj_opis(typ_I, 4, L"CZUJNIK");
	pamiec::dodaj_opis(typ_AI, 0, L"POTEN_1");
	pamiec::dodaj_opis(typ_AI, 1, L"POTEN_2");
	pamiec::dodaj_opis(typ_AQ, 0, L"WIATRAK");
	zresetuj();
}

lekcja1::~lekcja1()
{
	pamiec::nowe_parametry_sterownika(0, 0, 0, 0, 0, 0);
}

void lekcja1::podaj_rozmiar_okna(int & szerokosc, int & wysokosc)
{
	szerokosc = 240;
	wysokosc = 160;
}
