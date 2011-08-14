#ifndef obszar_aktywny_h_included
#define obszar_aktywny_h_included

#include "element.h"

struct jeden_prostokat
{
	RECT obszar;
	element_zwykly * komponent;
	jeden_prostokat * nastepny;
};

class obszar_aktywny
{
private:
	jeden_prostokat * pierwszy;
public:
	obszar_aktywny(void);
	~obszar_aktywny(void);
	void dodaj(int x, int y, int szer, int wys, element_zwykly * elemencik);
	int sprawdz(int x, int y, RECT * obszar, element_zwykly * * elemencik = NULL);
	void wyczysc(void);
};

#endif