#ifndef styki_h_included
#define styki_h_included

#include "element.h"
#include "pamiec.h"

class styk : public element_zwykly
	{
	public:
   	styk();
      styk(FILE * plik);
		void podaj_rozmiar(int & szerokosc, int & wysokosc, int tryb = 0);
      virtual element * sklonuj(FILE * plik = NULL) =0;
		virtual int dzialaj(int wejscie) =0;
		virtual void narysuj(HDC kontekst, int tryb, int x, int y) =0;
   };

class styk_zwierny : public styk
	{
	public:
   	styk_zwierny(void);
   	styk_zwierny(FILE * plik);
   	element * sklonuj(FILE * plik = NULL);
		int dzialaj(int wejscie);
		void narysuj(HDC kontekst, int tryb, int x, int y);
   };

class styk_rozwierny : public styk
	{
	public:
   	styk_rozwierny(void);
   	styk_rozwierny(FILE * plik);
   	element * sklonuj(FILE * plik = NULL);
		int dzialaj(int wejscie);
		void narysuj(HDC kontekst, int tryb, int x, int y);
   };


#endif