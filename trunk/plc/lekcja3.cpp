#include "lekcja3.h"

void lekcja3::zresetuj()
{
	faza_tasmy = 0;
	polozenie_nalewacza = 0;
	polozenie_kapslownika = 0;
	polozenie_tloku = 0;
	kapsel_przy_tloku = 1;
	ilosc_butelek = 0;
	lekcja::zresetuj();
}

BOOL lekcja3::click(int x, int y)
{
	return FALSE;
}

lekcja3::lekcja3() : tasma(L"lekcja3\\tasma"), kolko1(L"lekcja3\\kolko1"),
	kolko2(L"lekcja3\\kolko2"), kolko3(L"lekcja3\\kolko3"),
	kolko4(L"lekcja3\\kolko4"), butelka_pusta(L"lekcja3\\butelka_pusta"),
	butelka_pelna(L"lekcja3\\butelka_pelna"), tlo(L"lekcja3\\tlo"),
	nalewacz(L"lekcja3\\nalewacz"),
	kapslownik(L"lekcja3\\kapslownik"), tlok(L"lekcja3\\tlok"),
	kapsel(L"lekcja3\\kapsel")
{
	nazwa = L"lekcja3";
	pamiec::nowe_parametry_sterownika(2, 5, 100, 100, 0, 0);
	wejscia_I = new pamiec(typ_I, 0, 2);
	wyjscia_Q = new pamiec(typ_Q, 0, 5);
	pamiec::dodaj_opis(typ_Q, 0, L"TAŒMA");
	pamiec::dodaj_opis(typ_Q, 1, L"DOP£YW");
	pamiec::dodaj_opis(typ_Q, 2, L"LEJEK");
	pamiec::dodaj_opis(typ_Q, 3, L"KAPSEL");
	pamiec::dodaj_opis(typ_Q, 4, L"T£OK");
	pamiec::dodaj_opis(typ_I, 0, L"PRZY_DOP");
	pamiec::dodaj_opis(typ_I, 1, L"PRZY_KAP"); 
	zresetuj();
}

lekcja3::~lekcja3()
{
	pamiec::nowe_parametry_sterownika(0, 0, 0, 0, 0, 0);
}

void lekcja3::podaj_rozmiar_okna(int & szerokosc, int & wysokosc)
{
	szerokosc = 320;
	wysokosc = 200;
}

void lekcja3::dzialaj()
{
	int czy_tasma = wyjscia_Q->odczytaj_pamiec(0);
	int czy_doplyw = wyjscia_Q->odczytaj_pamiec(1);
	int czy_lejek = wyjscia_Q->odczytaj_pamiec(2);
	int czy_kapslownik = wyjscia_Q->odczytaj_pamiec(3);
	int czy_tlok = wyjscia_Q->odczytaj_pamiec(4);
	if (czy_tasma)
	{
		faza_tasmy++;
		faza_tasmy %= 64;
		if (!(faza_tasmy%4))
		{
			for (int i=0; i<ilosc_butelek; i++)
				butelki[i].x++;
			if ((ilosc_butelek)&&(butelki[0].x == 320))
			{
				for (int i=0; i<ilosc_butelek-1; i++)
					butelki[i] = butelki[i+1];
				ilosc_butelek--;
			}
		}
	}
	if (czy_lejek)
	{
		polozenie_nalewacza++;
		if (polozenie_nalewacza > 40)
			polozenie_nalewacza = 40;
	}
	else
	{
		polozenie_nalewacza--;
		if (polozenie_nalewacza < 0)
			polozenie_nalewacza = 0;
	}
	if (czy_kapslownik)
	{
		polozenie_kapslownika++;
		if (polozenie_kapslownika > 16)
			polozenie_kapslownika = 16;
	}
	else
	{
		polozenie_kapslownika--;
		if (polozenie_kapslownika < 0)
			polozenie_kapslownika = 0;
	}
	if (czy_tlok)
	{
		polozenie_tloku++;
		if (polozenie_tloku > 58)
			polozenie_tloku = 58;
	}
	else
	{
		polozenie_tloku--;
		if (polozenie_tloku < 0)
		{
			polozenie_tloku = 0;
			kapsel_przy_tloku = 1;
		}
	}
	if ((!ilosc_butelek)||((butelki[ilosc_butelek-1].x>30)&&(ilosc_butelek<MAX_ILOSC_BUTELEK)))
	{
		butelki[ilosc_butelek].x = -13;
		butelki[ilosc_butelek].zawartosc = 0;
		butelki[ilosc_butelek].ma_kapselek = 0;
		ilosc_butelek++;
	}
	int jest_pod_doplywem = 0;
	for (int i=0; i<ilosc_butelek; i++)
		if (butelki[i].x == 113)
		{
			jest_pod_doplywem = 1;
			if ((polozenie_nalewacza == 40)&&(czy_doplyw))
				butelki[i].zawartosc++;
		}
		wejscia_I->zapisz_pamiec(jest_pod_doplywem, 0);
		int jest_pod_kapslem = 0;
		for (int i=0; i<ilosc_butelek; i++)
		{
			if (butelki[i].x == 201)
			{
				jest_pod_kapslem = 1;
				if (kapsel_przy_tloku && (polozenie_kapslownika == 16) && (polozenie_tloku == 58))
				{
					butelki[i].ma_kapselek = 1;
					kapsel_przy_tloku = 0;
				}
			}
		}
		wejscia_I->zapisz_pamiec(jest_pod_kapslem, 1);
		lekcja::dzialaj();
}

void lekcja3::narysuj(HDC kontekst)
{
	const int wysokosc_tasmy = 150;
	const int wysokosc_zbiornika = 20;
	const int wysokosc_kapslownika = 20;
	const int x_zbiornika = 40;
	const int x_kapslownika = 199;
	RECT obszar;
	obszar.top = obszar.left = 0;
	int szer, wys;
	podaj_rozmiar_okna(szer, wys);
	obszar.right = szer;
	obszar.bottom = wys;
	tlo.wyswietl(kontekst, 0, 0);
	int faza = faza_tasmy;
	for (int i=-1; i<obszar.right/16; i++)
		tasma.wyswietl(kontekst, i*16+faza/4, wysokosc_tasmy);
	bitmapa * kolko;
	switch ((faza/16)%4)
	{
	case 0:
		kolko = &kolko1;
		break;
	case 1:
		kolko = &kolko2;
		break;
	case 2:
		kolko = &kolko3;
		break;
	case 3:
		kolko = &kolko4;
		break;
	}
	for (int i=0; i<obszar.right/32; i++)
		kolko->wyswietl(kontekst, i*32+5, wysokosc_tasmy+30);
	for (int i=0; i<ilosc_butelek; i++)
	{
		butelka_pusta.wyswietl(kontekst, butelki[i].x, wysokosc_tasmy-20, -1, 38-butelki[i].zawartosc, 0, 0);
		butelka_pelna.wyswietl(kontekst, butelki[i].x, wysokosc_tasmy-20+38-butelki[i].zawartosc, -1, butelki[i].zawartosc, 0, 38-butelki[i].zawartosc);
		if (butelki[i].ma_kapselek)
			kapsel.wyswietl(kontekst, butelki[i].x+3, wysokosc_tasmy-20);
	}
	nalewacz.wyswietl(kontekst, x_zbiornika+58, wysokosc_zbiornika+55+polozenie_nalewacza);
	HBRUSH pedzel = CreateSolidBrush(0x5b92ef);
	obszar.top = wysokosc_zbiornika+47;
	obszar.left = x_zbiornika+77;
	obszar.right = x_zbiornika+82;
	obszar.bottom = polozenie_nalewacza+57+wysokosc_zbiornika;
	FillRect(kontekst, &obszar, pedzel);
	DeleteObject(pedzel);
	tlok.wyswietl(kontekst, x_kapslownika+5, wysokosc_kapslownika+polozenie_kapslownika+polozenie_tloku);
	if (kapsel_przy_tloku)
		kapsel.wyswietl(kontekst, x_kapslownika+5, wysokosc_kapslownika+polozenie_kapslownika+polozenie_tloku+36);
	kapslownik.wyswietl(kontekst, x_kapslownika-15, wysokosc_kapslownika+polozenie_kapslownika);
}

