#ifndef lekcja5_h_included
#define lekcja5_h_included

#include "lekcja.h"
#include "bitmapy.h"

class lekcja5 : public lekcja
{
private:
	bitmapa winda;
	bitmapa drzwi;
	bitmapa pietro;
	bitmapa parter;
	bitmapa pietro_1;
	bitmapa pietro_2;
	bitmapa pietro_3;
	bitmapa pietro_4;
	bitmapa button_p;
	bitmapa button_1;
	bitmapa button_2;
	bitmapa button_3;
	bitmapa button_4;
	int polozenie_windy;
	int polozenie_drzwi[5];
	int wcisniete_przyciski[5];
public:
	lekcja5();
	~lekcja5();
	BOOL click(int x, int y);
	void dzialaj();
	void zresetuj();
	void narysuj(HDC kontekst);
	void podaj_rozmiar_okna(int & szerokosc, int & wysokosc);
};

#endif