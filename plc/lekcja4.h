#ifndef lekcja4_h_included
#define lekcja4_h_included

#include "lekcja.h"
#include "bitmapy.h"

class lekcja4 : public lekcja
	{
   private:
   	bitmapa tlo;
      bitmapa lampka_zielona;
      bitmapa lampka_czerwona;
      bitmapa ubrania1;
      bitmapa ubrania2;
      bitmapa ubrania3;
      bitmapa ubrania4;
      bitmapa ubrania5;
      bitmapa ubrania6;
      bitmapa ubrania7;
      bitmapa ubrania8;
      bitmapa ubrania9;
      bitmapa ubrania10;
      bitmapa ubrania11;
      bitmapa ubrania12;
      bitmapa woda;
      float kat_obrotu;
      int predkosc_obrotowa;
      float poziom_wody;
      int nastaw_temperatury;
      int przycisk;
      int spalona_grzalka;
      float temperatura_wody;
      float wskazanie_temperatury_wody;
   public:
   	lekcja4();
      ~lekcja4();
      BOOL click(int x, int y);
      void dzialaj();
      void zresetuj();
      void narysuj(HDC kontekst);
      void podaj_rozmiar_okna(int & szerokosc, int & wysokosc);
   };

#endif