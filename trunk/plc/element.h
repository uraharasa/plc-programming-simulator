#ifndef element_h_included
#define element_h_included

#include <windows.h>
#include <stdio.h>
#include "pamiec.h"
#include <string>
using namespace std;

#define SZEROKOSC_ELEMENTU		80
#define WYSOKOSC_ELEMENTU		60
#define Y_WYJSCIA					40
#define MARGINES_LEWY			10
#define MARGINES_DOLNY			(WYSOKOSC_ELEMENTU)

#define RYSUJ_ADRES		0x0001
#define RYSUJ_NAZWE		0x0002
#define WERSJA_MINI		0x0004

enum ZDARZENIE
{
	//zdarzenia generowane przez uzytkownika, obslugiwane przez klase
	//"element_zwykly"

	//uzytkownik chce skasowac element o wspolrzednych x, y
	SKASUJ_GO,
	//uzytkownik chce dodac element polaczony szeregowo z elementem o
	//wspolrzednych x, y, wskaznik do nowego znajduje sie w "edytowany"
	DODAJ_SZEREGOWO,
	//uzytkownik chce dodac element polaczony rownolegle z elementem o
	//wspolrzednych x, y, wskaznik do nowego znajduje sie w "edytowany"
	DODAJ_ROWNOLEGLE,

	//zdarzenia generowane przez elementy, obslugiwane przez klasy
	//"polaczenie_szeregowe" i "polaczenie_rownolegle"

	//zdarzenie zostalo obsluzone i nic wiecej nie trzeba zrobic
	NIC_NIE_ROB,
	//zdarzenie zostalo obsluzone i element ktory je obsluzyl ma zostac
	//skasowany przez klase nadrzedna
	SKASUJ_MNIE,
	//zdarzenie zostalo obsluzone i element ktory je obsluzyl ma zostac
	//skasowany i zastapiony przez "edytowany"
	ZASTAP_MNIE,
	//zdarzenie zostalo obsluzone i element ktory je obsluzyl ma zostac
	//zastapiony przez "edytowany", ale nie ma zostac skasowany
	ZASTAP_MNIE_I_NIE_KASUJ,

	DODAJ_RUNG_ELEMENT,
	DODAJ_RUNG_CEWKA,
	DODAJ_DO_ELEMENTOW,
	DODAJ_DO_CEWEK
};

class element
{
protected:
	wstring nazwa;
public:
	element();
	wstring podaj_nazwe(void);
	virtual void podaj_rozmiar(int & szerokosc, int & wysokosc, int tryb = 0) =0;
	virtual int dzialaj(int wejscie) =0;
	virtual void narysuj(HDC kontekst, int tryb, int x, int y) =0;
	virtual void dodaj_hotspot(int x, int y) =0;
	virtual ZDARZENIE edytuj(int x, int y, ZDARZENIE zdarzenie, element * &edytowany) =0;
	virtual void zapisz(FILE * plik) = 0;
	virtual ~element() {};
};

class element_zwykly : public element
{
protected:
	pamiec * adres_bazowy;
	pamiec * * wejscia;
	int il_wejsc;
	pamiec * * wyjscia;
	int il_wyjsc;
public:
	element_zwykly();
	element_zwykly(FILE * plik);
	~element_zwykly();
	virtual void podaj_rozmiar(int & szerokosc, int & wysokosc, int tryb = 0) =0;
	virtual int dzialaj(int wejscie) =0;
	virtual void narysuj(HDC kontekst, int tryb, int x, int y) =0;
	virtual element * sklonuj(FILE * plik = NULL) =0;
	virtual void zapisz(FILE * plik);
	void dodaj_hotspot(int x, int y);
	ZDARZENIE edytuj(int x, int y, ZDARZENIE zdarzenie, element * &edytowany);
	friend void zmien_parametry_elementu(HWND okno, element_zwykly * aktualny);
};

#endif