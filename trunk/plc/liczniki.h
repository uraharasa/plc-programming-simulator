#ifndef liczniki_h_included
#define liczniki_h_included

#include "bloki_funkcyjne.h"

class licznik_UPCTR : public blok_funkcyjny
	{
   public:
   	licznik_UPCTR();
   	licznik_UPCTR(FILE * plik);
      int dzialaj(int wejscie);
      element * sklonuj(FILE * plik = NULL);
   };

class licznik_DNCTR : public blok_funkcyjny
	{
   public:
   	licznik_DNCTR();
   	licznik_DNCTR(FILE * plik);
      int dzialaj(int wejscie);
      element * sklonuj(FILE * plik = NULL);
   };

#endif