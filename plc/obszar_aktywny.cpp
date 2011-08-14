#include "obszar_aktywny.h"

obszar_aktywny::obszar_aktywny(void)
{
	pierwszy = NULL;
};

obszar_aktywny::~obszar_aktywny(void)
{
	wyczysc();
};

void obszar_aktywny::dodaj(int x, int y, int szer, int wys, element_zwykly * elemencik)
{
	jeden_prostokat * * aktualny = &pierwszy;
	while (*aktualny)
		aktualny = &((*aktualny)->nastepny);
	*aktualny = new jeden_prostokat;
	(*aktualny)->obszar.left = x;
	(*aktualny)->obszar.top = y;
	(*aktualny)->obszar.right = x+szer;
	(*aktualny)->obszar.bottom = y+wys;
	(*aktualny)->nastepny = NULL;
	(*aktualny)->komponent = elemencik;
}

void obszar_aktywny::wyczysc(void)
{
	jeden_prostokat * aktualny, * nastepny;
	for (aktualny = pierwszy; aktualny; aktualny = nastepny)
	{
		nastepny = aktualny->nastepny;
		delete aktualny;
	}
	pierwszy = NULL;
}

int obszar_aktywny::sprawdz(int x, int y, RECT * obszar, element_zwykly * * elemencik)
{
	jeden_prostokat * aktualny = pierwszy;
	while (aktualny)
	{
		if ((aktualny->obszar.left<=x)&&(aktualny->obszar.right>x)&&(aktualny->obszar.top<=y)&&(aktualny->obszar.bottom>y))
		{
			*obszar = aktualny->obszar;
			if (elemencik)
				*elemencik = aktualny->komponent;
			return TRUE;
		}
		aktualny = aktualny->nastepny;
	}
	return FALSE;
}
