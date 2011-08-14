#ifndef pamiec_h_included
#define pamiec_h_included

#include <windows.h>
#include <stdio.h>
#include <string>
using namespace std;

#define MOZNA_CONST	0x0001
#define MOZNA_I		0x0002
#define MOZNA_Q		0x0004
#define MOZNA_R		0x0008
#define MOZNA_M		0x0010
#define MOZNA_AI		0x0020
#define MOZNA_AQ		0x0040

#define KOLOR_ADRES_DOBRY	0x000000
#define KOLOR_ADRES_ZLY		0x0000ff

typedef enum
	{
   typ_CONST = 1,
   typ_I = 2,
   typ_Q = 4,
   typ_R = 8,
   typ_M = 16,
   typ_AI = 32,
   typ_AQ = 64
   } typy_pamieci;

struct opis_komorki
	{
   wstring opis;
   typy_pamieci typ;
   int adres;
   opis_komorki * nastepny;
   };

class pamiec
	{
   private:
   	static int * I;
      static int * Q;
      static int * R;
      static int * M;
      static int * AI;
      static int * AQ;
      static int il_I;
      static int il_Q;
      static int il_R;
      static int il_M;
      static int il_AI;
      static int il_AQ;
      int adres_pamieci;
      int zajetosc_pamieci;
      typy_pamieci typ_pamieci;
      int dozwolone_typy;
      int valid;
      wstring nazwa_komorki;
      void wybierz_pamiec(int * &komorka, int adres);
      static void usun_opisy(void);
      static wstring poszukaj_opisu(typy_pamieci typ, int adres);
   public:
      static opis_komorki * lista_opisow;
      static opis_komorki * koniec_listy;
   	pamiec(wstring nazwa, int dozwolone, int szerokosc = 1);
      pamiec(typy_pamieci typ, int adres, int szerokosc);
      pamiec(FILE * plik);
      ~pamiec();
		static void nowe_parametry_sterownika(int nowe_I, int nowe_Q, int nowe_R, int nowe_M, int nowe_AI, int nowe_AQ);
      static void wyczysc_pamiec(void);
      void zapisz_pamiec(int wartosc, int adres = 0);
      int odczytaj_pamiec(int adres = 0);
      wstring podpisz_nazwa(void);
      void narysuj_nazwe(HDC kontekst, int x, int y, int align);
      wstring podpisz_adres(void);
      void narysuj_adres(HDC kontekst, int x, int y, int align);
      static void dodaj_opis(typy_pamieci typ, int adres, wstring opis);
      friend void zmien_parametry_pamieci(HWND okno, pamiec * aktualna);
      void zapisz(FILE * plik);
   };

void zmien_parametry_pamieci(HWND okno, pamiec * aktualna);

#endif