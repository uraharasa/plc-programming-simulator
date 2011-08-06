#include "relacje.h"

relacja_rowny::relacja_rowny()
	{
	nazwa = "relacja_rowny";
   nazwa_bloku = new char[strlen("EQ")+1];
   strcpy(nazwa_bloku, "EQ");
   il_wejsc = 2;
   wejscia = new pamiec *[2];
   *wejscia = new pamiec("I1", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
   *(wejscia+1) = new pamiec("I2", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
   }

relacja_rowny::relacja_rowny(FILE * plik): blok_funkcyjny(plik)
	{
	nazwa = "relacja_rowny";
   }

int relacja_rowny::dzialaj(int wejscie)
	{
   if (wejscie)
   	{
      if ((*wejscia)->odczytaj_pamiec() == (*(wejscia+1))->odczytaj_pamiec())
      	return 1;
      else
      	return 0;
      }
   else
   	return 0;
   }

element * relacja_rowny::sklonuj(FILE * plik)
	{
   if (plik)
   	return new relacja_rowny(plik);
   else
	   return new relacja_rowny;
   }

relacja_nierowny::relacja_nierowny()
	{
	nazwa = "relacja_nierowny";
   nazwa_bloku = new char[strlen("NE")+1];
   strcpy(nazwa_bloku, "NE");
   il_wejsc = 2;
   wejscia = new pamiec *[2];
   *wejscia = new pamiec("I1", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
   *(wejscia+1) = new pamiec("I2", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
   }

relacja_nierowny::relacja_nierowny(FILE * plik): blok_funkcyjny(plik)
	{
	nazwa = "relacja_nierowny";
   }

int relacja_nierowny::dzialaj(int wejscie)
	{
   if (wejscie)
   	{
      if ((*wejscia)->odczytaj_pamiec() != (*(wejscia+1))->odczytaj_pamiec())
      	return 1;
      else
      	return 0;
      }
   else
   	return 0;
   }

element * relacja_nierowny::sklonuj(FILE * plik)
	{
   if (plik)
	   return new relacja_nierowny(plik);
   else
	   return new relacja_nierowny;
   }

relacja_wiekszy::relacja_wiekszy()
	{
	nazwa = "relacja_wiekszy";
   nazwa_bloku = new char[strlen("GT")+1];
   strcpy(nazwa_bloku, "GT");
   il_wejsc = 2;
   wejscia = new pamiec *[2];
   *wejscia = new pamiec("I1", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
   *(wejscia+1) = new pamiec("I2", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
   }

relacja_wiekszy::relacja_wiekszy(FILE * plik): blok_funkcyjny(plik)
	{
	nazwa = "relacja_wiekszy";
   }

int relacja_wiekszy::dzialaj(int wejscie)
	{
   if (wejscie)
   	{
      if ((*wejscia)->odczytaj_pamiec() > (*(wejscia+1))->odczytaj_pamiec())
      	return 1;
      else
      	return 0;
      }
   else
   	return 0;
   }

element * relacja_wiekszy::sklonuj(FILE * plik)
	{
   if (plik)
	   return new relacja_wiekszy(plik);
   else
	   return new relacja_wiekszy;
   }

relacja_wiekszyrowny::relacja_wiekszyrowny()
	{
	nazwa = "relacja_wiekszyrowny";
   nazwa_bloku = new char[strlen("GE")+1];
   strcpy(nazwa_bloku, "GE");
   il_wejsc = 2;
   wejscia = new pamiec *[2];
   *wejscia = new pamiec("I1", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
   *(wejscia+1) = new pamiec("I2", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
   }

relacja_wiekszyrowny::relacja_wiekszyrowny(FILE * plik): blok_funkcyjny(plik)
	{
	nazwa = "relacja_wiekszyrowny";
   }

int relacja_wiekszyrowny::dzialaj(int wejscie)
	{
   if (wejscie)
   	{
      if ((*wejscia)->odczytaj_pamiec() >= (*(wejscia+1))->odczytaj_pamiec())
      	return 1;
      else
      	return 0;
      }
   else
   	return 0;
   }

element * relacja_wiekszyrowny::sklonuj(FILE * plik)
	{
   if (plik)
	   return new relacja_wiekszyrowny(plik);
	else
	   return new relacja_wiekszyrowny;
   }

relacja_mniejszy::relacja_mniejszy()
	{
	nazwa = "relacja_mniejszy";
   nazwa_bloku = new char[strlen("LT")+1];
   strcpy(nazwa_bloku, "LT");
   il_wejsc = 2;
   wejscia = new pamiec *[2];
   *wejscia = new pamiec("I1", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
   *(wejscia+1) = new pamiec("I2", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
   }

relacja_mniejszy::relacja_mniejszy(FILE * plik): blok_funkcyjny(plik)
	{
	nazwa = "relacja_mniejszy";
   }

int relacja_mniejszy::dzialaj(int wejscie)
	{
   if (wejscie)
   	{
      if ((*wejscia)->odczytaj_pamiec() < (*(wejscia+1))->odczytaj_pamiec())
      	return 1;
      else
      	return 0;
      }
   else
   	return 0;
   }

element * relacja_mniejszy::sklonuj(FILE * plik)
	{
   if (plik)
	   return new relacja_mniejszy(plik);
   else
	   return new relacja_mniejszy;
   }

relacja_mniejszyrowny::relacja_mniejszyrowny()
	{
	nazwa = "relacja_mniejszyrowny";
   nazwa_bloku = new char[strlen("LE")+1];
   strcpy(nazwa_bloku, "LE");
   il_wejsc = 2;
   wejscia = new pamiec *[2];
   *wejscia = new pamiec("I1", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
   *(wejscia+1) = new pamiec("I2", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
   }

relacja_mniejszyrowny::relacja_mniejszyrowny(FILE * plik): blok_funkcyjny(plik)
	{
	nazwa = "relacja_mniejszyrowny";
   }

int relacja_mniejszyrowny::dzialaj(int wejscie)
	{
   if (wejscie)
   	{
      if ((*wejscia)->odczytaj_pamiec() <= (*(wejscia+1))->odczytaj_pamiec())
      	return 1;
      else
      	return 0;
      }
   else
   	return 0;
   }

element * relacja_mniejszyrowny::sklonuj(FILE * plik)
	{
   if (plik)
	   return new relacja_mniejszyrowny(plik);
   else
	   return new relacja_mniejszyrowny;
   }

relacja_zakres::relacja_zakres()
	{
	nazwa = "relacja_zakres";
   nazwa_bloku = new char[strlen("RANGE")+1];
   strcpy(nazwa_bloku, "RANGE");
   il_wejsc = 3;
   wejscia = new pamiec *[3];
   *wejscia = new pamiec("L1", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
   *(wejscia+1) = new pamiec("L2", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
   *(wejscia+2) = new pamiec("IN", MOZNA_I|MOZNA_Q|MOZNA_R|MOZNA_M|MOZNA_AI|MOZNA_AQ|MOZNA_CONST);
   }

relacja_zakres::relacja_zakres(FILE * plik): blok_funkcyjny(plik)
	{
	nazwa = "relacja_zakres";
   }

int relacja_zakres::dzialaj(int wejscie)
	{
   if (wejscie)
   	{
      int prog1 = (*wejscia)->odczytaj_pamiec();
      int prog2 = (*(wejscia+1))->odczytaj_pamiec();
      int x = (*(wejscia+2))->odczytaj_pamiec();
      if (prog1 > prog2)
      	{
         int temp = prog2;
         prog2 = prog1;
         prog1 = temp;
         }
      if ((x >= prog1)&&(x <= prog2))
      	return 1;
      else
      	return 0;
      }
   else
   	return 0;
   }

element * relacja_zakres::sklonuj(FILE * plik)
	{
   if (plik)
	   return new relacja_zakres(plik);
   else
	   return new relacja_zakres;
   }

