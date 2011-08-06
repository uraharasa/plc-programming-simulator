#ifndef rung_h_included
#define rung_h_included

#include "element.h"

class rung : public element
	{
	private:
		element * elementy;
		element * cewki;
	public:
		rung * nastepny;
		rung(element *, element *);
      rung(FILE * plik);
		~rung(void);
      int sa_elementy(void);
      int sa_cewki(void);
		void podaj_rozmiar(int & szerokosc, int & wysokosc, int tryb = 0);
		int dzialaj(int wejscie);
		void narysuj(HDC kontekst, int tryb, int x, int y);
      void dodaj_hotspot(int x, int y);
		ZDARZENIE edytuj(int x, int y, ZDARZENIE zdarzenie, element * &edytowany);
      void zapisz(FILE * plik);
	};

#endif