#ifndef lekcja1_h_included
#define lekcja1_h_included

#include "lekcja.h"
#include "bitmapy.h"

class lekcja1 : public lekcja
{
private:
	bitmapa wiatrak1;
	bitmapa wiatrak2;
	bitmapa wiatrak3;
	bitmapa wiatrak4;
	bitmapa czerwona_zgasz;
	bitmapa czerwona_zapal;
	bitmapa zolta_zgasz;
	bitmapa zolta_zapal;
	bitmapa pushbutton;
	bitmapa switch_on;
	bitmapa switch_off;
	bitmapa poten_podst;
	bitmapa poten_galka;
	bitmapa tlo;
	float kat_obrotu;
	int switch1;
	int switch2;
	int button1;
	int button2;
	int poten1;
	int poten2;
public:
	lekcja1();
	~lekcja1();
	BOOL click(int x, int y);
	void dzialaj(void);
	void zresetuj(void);
	void narysuj(HDC kontekst);
	void podaj_rozmiar_okna(int & szerokosc, int & wysokosc);
};

#endif