#include "okno_glowne.h"
#include "bloki_funkcyjne.h"

blok_funkcyjny::blok_funkcyjny() : nazwa_bloku(L"")
	{
   }

blok_funkcyjny::blok_funkcyjny(FILE * plik): element_zwykly(plik)
	{
   }

blok_funkcyjny::~blok_funkcyjny()
	{
   }

void blok_funkcyjny::podaj_rozmiar(int & szerokosc, int & wysokosc, int tryb)
	{
	szerokosc = 1;
   if (!(tryb&WERSJA_MINI))
   	{
	   if (il_wejsc)
	   	szerokosc++;
	   if (il_wyjsc)
	   	szerokosc++;
      }
   wysokosc = 1;
   if ((il_wejsc+1)/2+1>wysokosc)
   	wysokosc = (il_wejsc+1)/2+1;
   if ((il_wyjsc+1)/2+1>wysokosc)
   	wysokosc = (il_wyjsc+1)/2+1;
   }

void blok_funkcyjny::narysuj(HDC kontekst, int tryb, int x, int y)
	{
   int x_pocz = akt_program_LD->mapuj_x(x);
   int y_pocz = akt_program_LD->mapuj_y(y);
   int szer, wys;
   podaj_rozmiar(szer, wys);
   int x_bloku = x_pocz;
   if (il_wejsc&&(!(tryb&WERSJA_MINI)))
   	x_bloku += SZEROKOSC_ELEMENTU;
   RECT obszar;
   obszar.left = x_bloku;
   obszar.top = y_pocz+25;
   obszar.right = x_bloku + SZEROKOSC_ELEMENTU - 35;
   obszar.bottom = y_pocz + WYSOKOSC_ELEMENTU*wys-5;
	MoveToEx(kontekst, obszar.left, obszar.top, NULL);
   LineTo(kontekst, obszar.right, obszar.top);
   LineTo(kontekst, obszar.right, obszar.bottom);
   LineTo(kontekst, obszar.left, obszar.bottom);
   LineTo(kontekst, obszar.left, obszar.top);
   if (!(tryb&WERSJA_MINI))
   	{
	   MoveToEx(kontekst, obszar.right, y_pocz+Y_WYJSCIA, NULL);
	   LineTo(kontekst, x_pocz+szer*SZEROKOSC_ELEMENTU-20, y_pocz+Y_WYJSCIA);
      }
	else
   	{
	   MoveToEx(kontekst, obszar.right, y_pocz+Y_WYJSCIA, NULL);
	   LineTo(kontekst, obszar.right+5, y_pocz+Y_WYJSCIA);
      }
   if ((tryb&RYSUJ_NAZWE)&&(nazwa_bloku.length() > 0))
   	{
      SetTextAlign(kontekst, TA_CENTER|TA_TOP|TA_NOUPDATECP);
	  TextOut(kontekst, x_bloku+23, y_pocz + 30, nazwa_bloku.c_str(), nazwa_bloku.length());
      }
   if ((tryb&RYSUJ_ADRES)&&(adres_bazowy))
      adres_bazowy->narysuj_adres(kontekst, x_bloku+23, y_pocz, TA_CENTER|TA_TOP|TA_NOUPDATECP);
   if (il_wejsc)
   	{
      if (!(tryb&WERSJA_MINI))
      	{
	      MoveToEx(kontekst, x_pocz, y_pocz+Y_WYJSCIA, NULL);
	      LineTo(kontekst, x_pocz+SZEROKOSC_ELEMENTU, y_pocz+Y_WYJSCIA);
         }
      else
      	{
	      MoveToEx(kontekst, x_pocz-5, y_pocz+Y_WYJSCIA, NULL);
	      LineTo(kontekst, x_pocz, y_pocz+Y_WYJSCIA);
         }
      for (int i = 1; i<=il_wejsc; i++)
      	{
         if (tryb&RYSUJ_NAZWE)
            (*(wejscia+i-1))->narysuj_nazwe(kontekst, x_bloku+5, y_pocz+WYSOKOSC_ELEMENTU*i/2+Y_WYJSCIA-7, TA_LEFT|TA_TOP|TA_NOUPDATECP);
         if (tryb&RYSUJ_ADRES)
            (*(wejscia+i-1))->narysuj_adres(kontekst, x_bloku-10, y_pocz+WYSOKOSC_ELEMENTU*i/2+Y_WYJSCIA-7, TA_RIGHT|TA_TOP|TA_NOUPDATECP);
         MoveToEx(kontekst, x_bloku-5, y_pocz+WYSOKOSC_ELEMENTU*i/2+Y_WYJSCIA, NULL);
         LineTo(kontekst, x_bloku, y_pocz+WYSOKOSC_ELEMENTU*i/2+Y_WYJSCIA);
         }
      }
   for (int i = 1; i<=il_wyjsc; i++)
	  	{
      if (tryb&RYSUJ_NAZWE)
         (*(wyjscia+i-1))->narysuj_nazwe(kontekst, x_bloku+SZEROKOSC_ELEMENTU-40, y_pocz+WYSOKOSC_ELEMENTU*i/2+Y_WYJSCIA-7, TA_RIGHT|TA_TOP|TA_NOUPDATECP);
      if (tryb&RYSUJ_ADRES)
         (*(wyjscia+i-1))->narysuj_adres(kontekst, x_bloku+SZEROKOSC_ELEMENTU-25, y_pocz+WYSOKOSC_ELEMENTU*i/2+Y_WYJSCIA-7, TA_LEFT|TA_TOP|TA_NOUPDATECP);
      MoveToEx(kontekst, x_bloku+SZEROKOSC_ELEMENTU-30, y_pocz+WYSOKOSC_ELEMENTU*i/2+Y_WYJSCIA, NULL);
      LineTo(kontekst, x_bloku+SZEROKOSC_ELEMENTU-35, y_pocz+WYSOKOSC_ELEMENTU*i/2+Y_WYJSCIA);
      }
   }

void blok_funkcyjny::zapisz(FILE * plik)
	{
   element_zwykly::zapisz(plik);
   }

