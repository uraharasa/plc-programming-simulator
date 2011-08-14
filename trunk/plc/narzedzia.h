#ifndef narzedzia_h_included
#define narzedzia_h_included

#include "element.h"
#include <string>
using namespace std;

#define ILOSC_KATEGORII	6
#define STYL_OKNA_NARZEDZIOWEGO	(WS_CAPTION|WS_CHILD|WS_CLIPSIBLINGS)

class jedno_narzedzie
	{
   public:
   	element_zwykly * narzedzie;
      jedno_narzedzie * nastepne;
   };

class jedna_kategoria
	{
   public:
   	jedno_narzedzie * pierwsze_narzedzie;
      wstring nazwa_kategorii;
   };

class narzedzia
	{
   private:
   	HWND okno;
      HWND zakladki;
      HWND klient;
		jedna_kategoria zbior_narzedzi[ILOSC_KATEGORII];
      int kategoria_cewek;
      void narysuj(void);
      void dodaj_narzedzie(int kategoria, element_zwykly * nowe_narzedzie);
   public:
   	int akt_kategoria;
   	narzedzia(HWND okno_narzedziowe);
      LRESULT CALLBACK obsluz_komunikat(HWND, UINT, WPARAM, LPARAM);
      LRESULT CALLBACK obsluz_komunikat_klienta(HWND, UINT, WPARAM, LPARAM);
      ~narzedzia(void);
      element * rozpoznaj_i_wczytaj(FILE * plik);
   };

#endif
