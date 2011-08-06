#ifndef timery_h_included
#define timery_h_included

#include "bloki_funkcyjne.h"

class timer_ONDTR : public blok_funkcyjny
	{
   public:
   	timer_ONDTR();
   	timer_ONDTR(FILE * plik);
		int dzialaj(int wejscie);
      element * sklonuj(FILE * plik = NULL);
   };

class timer_TMR : public blok_funkcyjny
	{
   public:
   	timer_TMR();
   	timer_TMR(FILE * plik);
		int dzialaj(int wejscie);
      element * sklonuj(FILE * plik = NULL);
   };

class timer_OFDT : public blok_funkcyjny
	{
   public:
   	timer_OFDT();
   	timer_OFDT(FILE * plik);
      int dzialaj(int wejscie);
      element * sklonuj(FILE * plik = NULL);
   };

#endif
