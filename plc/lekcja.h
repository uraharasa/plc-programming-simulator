#ifndef lekcja_h_included
#define lekcja_h_included

#include <windows.h>
#include "pamiec.h"
#include <string>
using namespace std;

class lekcja
{
private:
	HWND okno;
	HWND okno_LD;
protected:
	pamiec * wejscia_I;
	pamiec * wyjscia_Q;
	pamiec * wejscia_AI;
	pamiec * wyjscia_AQ;
	wstring nazwa;
public:
	lekcja();
	virtual ~lekcja();
	wstring podaj_nazwe();
	void ustal_rozmiar_okna(void);
	virtual BOOL click(int x, int y) =0;
	virtual void dzialaj(void);
	virtual void zresetuj(void);
	virtual void narysuj(HDC kontekst) =0;
	virtual void podaj_rozmiar_okna(int & szerokosc, int & wysokosc) =0;
};

#endif