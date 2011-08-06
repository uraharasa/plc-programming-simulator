#ifndef bitmapy_h_included
#define bitmapy_h_included

#include <windows.h>

class bitmapa
	{
   private:
   	int szer_mapy;
      int wys_mapy;
      HBITMAP mapa;
      HBITMAP maska;
   public:
   	bitmapa(char * nazwa_pliku);
      ~bitmapa(void);
      void wyswietl(HDC kontekst, int x, int y, int szer = -1, int wys = -1, int pocz_x = 0, int pocz_y = 0);
   };

#endif