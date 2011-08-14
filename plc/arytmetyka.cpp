#include <math.h>
#include "arytmetyka.h"

math_add::math_add()
{
	nazwa = L"math_add";
	nazwa_bloku = L"ADD";
	il_wejsc = 2;
	wejscia = new pamiec *[2];
	*wejscia = new pamiec(L"I1", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
	*(wejscia+1) = new pamiec(L"I2", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
	il_wyjsc = 1;
	wyjscia = new pamiec *[1];
	*wyjscia = new pamiec(L"Q", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ);
}

math_add::math_add(FILE * plik): blok_funkcyjny(plik)
{
	nazwa = L"math_add";
}

int math_add::dzialaj(int wejscie)
{
	if (wejscie)
	{
		int i1 = (*wejscia)->odczytaj_pamiec();
		int i2 = (*(wejscia+1))->odczytaj_pamiec();
		int q = i1 + i2;
		if ((q<-32768) || (q>32767))
		{
			(*wyjscia)->zapisz_pamiec(q);
			return 0;
		}
		else
		{
			(*wyjscia)->zapisz_pamiec(q);
			return 1;
		}
	}
	else
		return 0;
}

element * math_add::sklonuj(FILE * plik)
{
	if (plik)
		return new math_add(plik);
	else
		return new math_add;
}

math_sub::math_sub()
{
	nazwa = L"math_sub";
	nazwa_bloku = L"SUB";
	il_wejsc = 2;
	wejscia = new pamiec *[2];
	*wejscia = new pamiec(L"I1", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
	*(wejscia+1) = new pamiec(L"I2", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
	il_wyjsc = 1;
	wyjscia = new pamiec *[1];
	*wyjscia = new pamiec(L"Q", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ);
}

math_sub::math_sub(FILE * plik): blok_funkcyjny(plik)
{
	nazwa = L"math_sub";
}

int math_sub::dzialaj(int wejscie)
{
	if (wejscie)
	{
		int i1 = (*wejscia)->odczytaj_pamiec();
		int i2 = (*(wejscia+1))->odczytaj_pamiec();
		int q = i1 - i2;
		if ((q<-32768) || (q>32767))
		{
			(*wyjscia)->zapisz_pamiec(q);
			return 0;
		}
		else
		{
			(*wyjscia)->zapisz_pamiec(q);
			return 1;
		}
	}
	else
		return 0;
}

element * math_sub::sklonuj(FILE * plik)
{
	if (plik)
		return new math_sub(plik);
	else
		return new math_sub;
}

math_mul::math_mul()
{
	nazwa = L"math_mul";
	nazwa_bloku = L"MUL";
	il_wejsc = 2;
	wejscia = new pamiec *[2];
	*wejscia = new pamiec(L"I1", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
	*(wejscia+1) = new pamiec(L"I2", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
	il_wyjsc = 1;
	wyjscia = new pamiec *[1];
	*wyjscia = new pamiec(L"Q", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ);
}

math_mul::math_mul(FILE * plik): blok_funkcyjny(plik)
{
	nazwa = L"math_mul";
}

int math_mul::dzialaj(int wejscie)
{
	if (wejscie)
	{
		int i1 = (*wejscia)->odczytaj_pamiec();
		int i2 = (*(wejscia+1))->odczytaj_pamiec();
		int q = i1 * i2;
		if ((q<-32768) || (q>32767))
		{
			(*wyjscia)->zapisz_pamiec(q);
			return 0;
		}
		else
		{
			(*wyjscia)->zapisz_pamiec(q);
			return 1;
		}
	}
	else
		return 0;
}

element * math_mul::sklonuj(FILE * plik)
{
	if (plik)
		return new math_mul(plik);
	else
		return new math_mul;
}

math_div::math_div()
{
	nazwa = L"math_div";
	nazwa_bloku = L"DIV";
	il_wejsc = 2;
	wejscia = new pamiec *[2];
	*wejscia = new pamiec(L"I1", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
	*(wejscia+1) = new pamiec(L"I2", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
	il_wyjsc = 1;
	wyjscia = new pamiec *[1];
	*wyjscia = new pamiec(L"Q", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ);
}

math_div::math_div(FILE * plik): blok_funkcyjny(plik)
{
	nazwa = L"math_div";
}

int math_div::dzialaj(int wejscie)
{
	if (wejscie)
	{
		int i1 = (*wejscia)->odczytaj_pamiec();
		int i2 = (*(wejscia+1))->odczytaj_pamiec();
		if (i2 != 0)
		{
			int q = i1 / i2;
			if ((q<-32768) || (q>32767))
			{
				(*wyjscia)->zapisz_pamiec(q);
				return 0;
			}
			else
			{
				(*wyjscia)->zapisz_pamiec(q);
				return 1;
			}
		}
		else
			return 0;
	}
	else
		return 0;
}

element * math_div::sklonuj(FILE * plik)
{
	if (plik)
		return new math_div(plik);
	else
		return new math_div;
}

math_mod::math_mod()
{
	nazwa = L"math_mod";
	nazwa_bloku = L"MOD";
	il_wejsc = 2;
	wejscia = new pamiec *[2];
	*wejscia = new pamiec(L"I1", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
	*(wejscia+1) = new pamiec(L"I2", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
	il_wyjsc = 1;
	wyjscia = new pamiec *[1];
	*wyjscia = new pamiec(L"Q", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ);
}

math_mod::math_mod(FILE * plik): blok_funkcyjny(plik)
{
	nazwa = L"math_mod";
}

int math_mod::dzialaj(int wejscie)
{
	if (wejscie)
	{
		int i1 = (*wejscia)->odczytaj_pamiec();
		int i2 = (*(wejscia+1))->odczytaj_pamiec();
		if (i2 != 0)
		{
			int q = i1 % i2;
			if ((q<-32768) || (q>32767))
			{
				(*wyjscia)->zapisz_pamiec(q);
				return 0;
			}
			else
			{
				(*wyjscia)->zapisz_pamiec(q);
				return 1;
			}
		}
		else
			return 0;
	}
	else
		return 0;
}

element * math_mod::sklonuj(FILE * plik)
{
	if (plik)
		return new math_mod(plik);
	else
		return new math_mod;
}

math_sqrt::math_sqrt()
{
	nazwa = L"math_sqrt";
	nazwa_bloku = L"SQRT";
	il_wejsc = 1;
	wejscia = new pamiec *[1];
	*wejscia = new pamiec(L"IN", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
	il_wyjsc = 1;
	wyjscia = new pamiec *[1];
	*wyjscia = new pamiec(L"Q", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ);
}

math_sqrt::math_sqrt(FILE * plik): blok_funkcyjny(plik)
{
	nazwa = L"math_sqrt";
}

int math_sqrt::dzialaj(int wejscie)
{
	if (wejscie)
	{
		int i = (*wejscia)->odczytaj_pamiec();
		if (i >= 0)
		{
			int q = sqrt((double)i);
			if ((q<-32768) || (q>32767))
			{
				(*wyjscia)->zapisz_pamiec(q);
				return 0;
			}
			else
			{
				(*wyjscia)->zapisz_pamiec(q);
				return 1;
			}
		}
		else
			return 0;
	}
	else
		return 0;
}

element * math_sqrt::sklonuj(FILE * plik)
{
	if (plik)
		return new math_sqrt(plik);
	else
		return new math_sqrt;
}

