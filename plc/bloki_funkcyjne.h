#ifndef bloki_funkcyjne_h_included
#define bloki_funkcyjne_h_included

#include "element.h"
#include <string>
using namespace std;

class blok_funkcyjny : public element_zwykly
	{
   protected:
	   wstring nazwa_bloku;
   public:
   	blok_funkcyjny();
   	blok_funkcyjny(FILE * plik);
      ~blok_funkcyjny();
	   void podaj_rozmiar(int & szerokosc, int & wysokosc, int tryb = 0);
		virtual int dzialaj(int wejscie) = 0;
	   void narysuj(HDC kontekst, int tryb, int x, int y);
	   virtual element * sklonuj(FILE * plik = NULL) =0;
      virtual void zapisz(FILE * plik);
   };

#endif