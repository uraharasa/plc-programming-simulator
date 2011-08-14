#ifndef arytmetyka_h_included
#define arytmetyka_h_included

#include "bloki_funkcyjne.h"

class math_add : public blok_funkcyjny
{
public:
	math_add();
	math_add(FILE * plik);
	int dzialaj(int wejscie);
	element * sklonuj(FILE * plik = NULL);
};

class math_sub : public blok_funkcyjny
{
public:
	math_sub();
	math_sub(FILE * plik);
	int dzialaj(int wejscie);
	element * sklonuj(FILE * plik = NULL);
};

class math_mul : public blok_funkcyjny
{
public:
	math_mul();
	math_mul(FILE * plik);
	int dzialaj(int wejscie);
	element * sklonuj(FILE * plik = NULL);
};

class math_div : public blok_funkcyjny
{
public:
	math_div();
	math_div(FILE * plik);
	int dzialaj(int wejscie);
	element * sklonuj(FILE * plik = NULL);
};

class math_mod : public blok_funkcyjny
{
public:
	math_mod();
	math_mod(FILE * plik);
	int dzialaj(int wejscie);
	element * sklonuj(FILE * plik = NULL);
};

class math_sqrt : public blok_funkcyjny
{
public:
	math_sqrt();
	math_sqrt(FILE * plik);
	int dzialaj(int wejscie);
	element * sklonuj(FILE * plik = NULL);
};

#endif