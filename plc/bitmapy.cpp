#include "bitmapy.h"
#include <fstream>

using namespace std;

bitmapa::bitmapa(char * nazwa_pliku)
	{
   char nazwa[256];
   strcpy(nazwa, nazwa_pliku);
   strcat(nazwa, ".bmp");
   mapa = NULL;
   maska = NULL;
   szer_mapy = 0;
   wys_mapy = 0;
   ifstream plik(nazwa, ios::in | ios::binary);
   BITMAPFILEHEADER naglowek_pliku_bmp;
   plik.read((char *)&naglowek_pliku_bmp, sizeof(BITMAPFILEHEADER));
   long rozmiar_bmp = naglowek_pliku_bmp.bfSize - sizeof(BITMAPFILEHEADER);
   char * mapa_DIB = new char[rozmiar_bmp];
   plik.read(mapa_DIB, rozmiar_bmp);
   LPBITMAPINFOHEADER bmih = (LPBITMAPINFOHEADER) mapa_DIB;
   szer_mapy = bmih->biWidth;
   wys_mapy = bmih->biHeight;
   LPSTR dane = (LPSTR) mapa_DIB + sizeof(BITMAPINFOHEADER);
   HDC kontekst = GetDC(NULL);
   mapa = CreateDIBitmap(kontekst, bmih, CBM_INIT, dane, (LPBITMAPINFO)bmih, DIB_RGB_COLORS);
   ReleaseDC(NULL, kontekst);
   delete [] mapa_DIB;
   strcpy(nazwa, nazwa_pliku);
   strcat(nazwa, "_m.bmp");
   ifstream plik2(nazwa, ios::in | ios::binary);
   if (!plik2)
   	return;
   plik2.read((char *)&naglowek_pliku_bmp, sizeof(BITMAPFILEHEADER));
   rozmiar_bmp = naglowek_pliku_bmp.bfSize - sizeof(BITMAPFILEHEADER);
   mapa_DIB = new char[rozmiar_bmp];
   plik2.read(mapa_DIB, rozmiar_bmp);
   bmih = (LPBITMAPINFOHEADER) mapa_DIB;
	dane = (LPSTR) mapa_DIB + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*2;
   kontekst = GetDC(NULL);
   LPLOGPALETTE plog = (LPLOGPALETTE) new unsigned char[sizeof(LOGPALETTE) + sizeof(PALETTEENTRY)];
   plog->palVersion=0x300;
   plog->palNumEntries = 2;
	plog->palPalEntry[0].peRed = 0;
	plog->palPalEntry[0].peGreen = 0;
	plog->palPalEntry[0].peBlue = 0;
	plog->palPalEntry[0].peFlags = 0;
	plog->palPalEntry[1].peRed = 255;
	plog->palPalEntry[1].peGreen = 255;
	plog->palPalEntry[1].peBlue = 255;
	plog->palPalEntry[1].peFlags = 0;
   HPALETTE paleta = CreatePalette(plog);
   delete plog;
   HPALETTE poprzednia = SelectPalette(kontekst, paleta, FALSE);
   RealizePalette(kontekst);
	maska = CreateDIBitmap(kontekst, bmih, CBM_INIT, dane, (LPBITMAPINFO)bmih, DIB_RGB_COLORS);
   SelectPalette(kontekst, poprzednia, FALSE);
   DeleteObject(paleta);
   ReleaseDC(NULL, kontekst);
   delete [] mapa_DIB;
   }

bitmapa::~bitmapa(void)
	{
   DeleteObject(mapa);
   if (maska)
   	DeleteObject(maska);
   }

void bitmapa::wyswietl(HDC kontekst, int x, int y, int szer, int wys, int pocz_x, int pocz_y)
	{
   if (szer == -1)
   	szer = szer_mapy;
   if (wys == -1)
   	wys = wys_mapy;
   HDC kontekst_mapy = CreateCompatibleDC(kontekst);
   SelectObject(kontekst_mapy, mapa);
   if (!maska)
	   BitBlt(kontekst, x, y, szer, wys, kontekst_mapy, pocz_x, pocz_y, SRCCOPY);
   else
   	{
	   SelectObject(kontekst_mapy, maska);
	   BitBlt(kontekst, x, y, szer, wys, kontekst_mapy, pocz_x, pocz_y, SRCAND);
	   SelectObject(kontekst_mapy, mapa);
	   BitBlt(kontekst, x, y, szer, wys, kontekst_mapy, pocz_x, pocz_y, SRCPAINT);
      }
   DeleteDC(kontekst_mapy);
   }

