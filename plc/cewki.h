#ifndef cewki_h_included
#define cewki_h_included

#include "element.h"

class cewka : public element_zwykly
	{
   public:
   	cewka(void);
      cewka(FILE * plik);
      void podaj_rozmiar(int & szerokosc, int & wysokosc, int tryb = 0);
      virtual element * sklonuj(FILE * plik = NULL) = 0;
      virtual int dzialaj(int wejscie) = 0;
      virtual void narysuj(HDC kontekst, int tryb, int x, int y) = 0;
   };

class cewka_zwierna : public cewka
	{
   public:
   	cewka_zwierna(void);
   	cewka_zwierna(FILE * plik);
   	element * sklonuj(FILE * plik = NULL);
      int dzialaj(int wejscie);
      void narysuj(HDC kontekst, int tryb, int x, int y);
   };

class cewka_rozwierna : public cewka
	{
   public:
   	cewka_rozwierna(void);
   	cewka_rozwierna(FILE * plik);
   	element * sklonuj(FILE * plik = NULL);
      int dzialaj(int wejscie);
      void narysuj(HDC kontekst, int tryb, int x, int y);
   };

class cewka_zbocze_narastajace : public cewka
	{
   private:
   	int stan_poprzedni;
   public:
   	cewka_zbocze_narastajace(void);
   	cewka_zbocze_narastajace(FILE * plik);
   	element * sklonuj(FILE * plik = NULL);
      int dzialaj(int wejscie);
      void narysuj(HDC kontekst, int tryb, int x, int y);
   };

class cewka_zbocze_opadajace : public cewka
	{
   private:
   	int stan_poprzedni;
   public:
   	cewka_zbocze_opadajace(void);
   	cewka_zbocze_opadajace(FILE * plik);
   	element * sklonuj(FILE * plik = NULL);
      int dzialaj(int wejscie);
      void narysuj(HDC kontekst, int tryb, int x, int y);
   };

class cewka_S : public cewka
	{
   public:
   	cewka_S(void);
   	cewka_S(FILE * plik);
   	element * sklonuj(FILE * plik = NULL);
      int dzialaj(int wejscie);
      void narysuj(HDC kontekst, int tryb, int x, int y);
   };

class cewka_R : public cewka
	{
   public:
   	cewka_R(void);
   	cewka_R(FILE * plik);
   	element * sklonuj(FILE * plik = NULL);
      int dzialaj(int wejscie);
      void narysuj(HDC kontekst, int tryb, int x, int y);
   };

#endif
