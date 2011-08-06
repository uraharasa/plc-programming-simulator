#ifndef polaczenia_h_included
#define polaczenia_h_included

#include "element.h"

class polaczenie_szeregowe : public element
	{
	private:
   	int kasowany;
		element * pierwszy;
		element * drugi;
	public:
		polaczenie_szeregowe(element * jeden, element * dwa);
      polaczenie_szeregowe(FILE * plik);
      ~polaczenie_szeregowe();
		void podaj_rozmiar(int & szerokosc, int & wysokosc, int tryb = 0);
		int dzialaj(int wejscie);
		void narysuj(HDC kontekst, int tryb, int x, int y);
      void dodaj_hotspot(int x, int y);
		ZDARZENIE edytuj(int x, int y, ZDARZENIE zdarzenie, element * &edytowany);
      void zapisz(FILE * plik);
	};

class polaczenie_rownolegle : public element
	{
	private:
   	int kasowany;
		element * pierwszy;
		element * drugi;
	public:
		polaczenie_rownolegle(element * jeden, element * dwa);
      polaczenie_rownolegle(FILE * plik);
      ~polaczenie_rownolegle();
		void podaj_rozmiar(int & szerokosc, int & wysokosc, int tryb = 0);
		int dzialaj(int wejscie);
		void narysuj(HDC kontekst, int tryb, int x, int y);
      void dodaj_hotspot(int x, int y);
		ZDARZENIE edytuj(int x, int y, ZDARZENIE zdarzenie, element * &edytowany);
      void zapisz(FILE * plik);
	};

#endif