#ifndef lekcja3_h_included
#define lekcja3_h_included

#include "lekcja.h"
#include "bitmapy.h"

#define MAX_ILOSC_BUTELEK 10

struct butelka
{
	int x;
	int zawartosc;
	int ma_kapselek;
};

class lekcja3 : public lekcja
{
private:
	bitmapa tlo;
	bitmapa nalewacz;
	bitmapa kapslownik;
	bitmapa tlok;
	bitmapa kapsel;
	bitmapa tasma;
	bitmapa kolko1;
	bitmapa kolko2;
	bitmapa kolko3;
	bitmapa kolko4;
	bitmapa butelka_pusta;
	bitmapa butelka_pelna;
	int faza_tasmy;
	int polozenie_nalewacza;
	int polozenie_kapslownika;
	int polozenie_tloku;
	int kapsel_przy_tloku;
	butelka butelki[MAX_ILOSC_BUTELEK];
	int ilosc_butelek;
public:
	lekcja3();
	~lekcja3();
	BOOL click(int x, int y);
	void dzialaj();
	void zresetuj();
	void narysuj(HDC kontekst);
	void podaj_rozmiar_okna(int & szerokosc, int & wysokosc);
};

#endif