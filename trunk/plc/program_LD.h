#ifndef program_LD_h_included
#define program_LD_h_included

#include "rung.h"
#include "obszar_aktywny.h"

class program_LD
{
private:
	rung * lista_rungow;
	int dragging;
	int dragging_cewka;
	POINT dragging_wspolrzedne;
	int pierwszy_DRAG;
	element * nowy_element;
	int wartosc_x_cewek;
	int szerokosc_programu;
	int wysokosc_programu;
	int page_x;
	int max_x;
	int page_y;
	int max_y;
	int poprawnosc_wymiarow;
	void popraw_wymiary(void);
	int podaj_szerokosc(void);
	int podaj_wysokosc(void);
	void narysuj(void);
	void ustaw_scrollbary(void);
	void przesun_scrollbary(int deltax, int deltay);
	int remapuj_x(int);
	int remapuj_y(int);
	void odswiez_hotspots(void);
	int znajdz_cel_drag_and_drop(int & drop_x, int & drop_y, element_zwykly * &cel, ZDARZENIE &co_zrobic);
	void narysuj_kreski(HWND okno, int drop_x, int drop_y);
	void sprawdz_rungi(void);
public:
	int scroll_x;
	int scroll_y;
	obszar_aktywny hotspot;
	HWND okno;
	program_LD(HWND okno_programu_LD);
	~program_LD(void);
	int mapuj_x(int);
	int mapuj_y(int);
	int x_cewek(void);
	void dzialaj(void);
	void wydrukuj(void);
	void rozpocznij_DRAGDROP(element * nowy, int czy_cewka);
	LRESULT CALLBACK obsluz_komunikat(HWND okno, UINT komunikat, WPARAM wParam, LPARAM lParam);
	void wczytaj(FILE * plik);
	void zapisz(FILE * plik);
};

#endif