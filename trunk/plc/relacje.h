#ifndef relacje_h_included
#define relacje_h_included

#include "bloki_funkcyjne.h"

class relacja_rowny : public blok_funkcyjny
	{
   public:
   	relacja_rowny();
   	relacja_rowny(FILE * plik);
      int dzialaj(int wejscie);
      element * sklonuj(FILE * plik = NULL);
   };

class relacja_nierowny : public blok_funkcyjny
	{
   public:
   	relacja_nierowny();
   	relacja_nierowny(FILE * plik);
      int dzialaj(int wejscie);
      element * sklonuj(FILE * plik = NULL);
   };

class relacja_wiekszy : public blok_funkcyjny
	{
   public:
   	relacja_wiekszy();
   	relacja_wiekszy(FILE * plik);
      int dzialaj(int wejscie);
      element * sklonuj(FILE * plik = NULL);
   };

class relacja_wiekszyrowny : public blok_funkcyjny
	{
   public:
   	relacja_wiekszyrowny();
   	relacja_wiekszyrowny(FILE * plik);
      int dzialaj(int wejscie);
      element * sklonuj(FILE * plik = NULL);
   };

class relacja_mniejszy : public blok_funkcyjny
	{
   public:
   	relacja_mniejszy();
   	relacja_mniejszy(FILE * plik);
      int dzialaj(int wejscie);
      element * sklonuj(FILE * plik = NULL);
   };

class relacja_mniejszyrowny : public blok_funkcyjny
	{
   public:
   	relacja_mniejszyrowny();
   	relacja_mniejszyrowny(FILE * plik);
      int dzialaj(int wejscie);
      element * sklonuj(FILE * plik = NULL);
   };

class relacja_zakres : public blok_funkcyjny
	{
   public:
   	relacja_zakres();
   	relacja_zakres(FILE * plik);
      int dzialaj(int wejscie);
      element * sklonuj(FILE * plik = NULL);
   };

#endif