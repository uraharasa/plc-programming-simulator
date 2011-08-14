#ifndef lekcja2_h_included
#define lekcja2_h_included

#include "lekcja.h"
#include "bitmapy.h"

class lekcja2 : public lekcja
{
private:
	bitmapa zawor_zamkniety;
	bitmapa zawor_otwarty;
	bitmapa doplyw_otwarty;
	bitmapa doplyw_zamkniety;
	bitmapa odplyw_otwarty;
	bitmapa odplyw_zamkniety;
	bitmapa przycisk_napelnij;
	bitmapa przycisk_oproznij;
	bitmapa przycisk_wymiana_on;
	bitmapa przycisk_wymiana_off;
	int poziom_wody;
	int ulamki;
	int doplyw;
	int odplyw;
	int rozlana;
	int wymiana;
	int napelnij;
	int oproznij;
public:
	lekcja2();
	~lekcja2();
	BOOL click(int x, int y);
	void dzialaj();
	void zresetuj();
	void narysuj(HDC kontekst);
	void podaj_rozmiar_okna(int & szerokosc, int & wysokosc);
};

#endif