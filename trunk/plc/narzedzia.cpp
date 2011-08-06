#include "narzedzia.h"
#include "polaczenia.h"
#include "styki.h"
#include "cewki.h"
#include "liczniki.h"
#include "timery.h"
#include "arytmetyka.h"
#include "relacje.h"
#include "okno_glowne.h"
#include "resource.h"
#include "help.h"
#include <commctrl.h>


narzedzia::narzedzia(HWND okno_narzedziowe)
	{
   akt_kategoria = 0;
   okno = okno_narzedziowe;
   zbior_narzedzi[0].nazwa_kategorii = "Styki";
   zbior_narzedzi[1].nazwa_kategorii = "Cewki";
   kategoria_cewek = 1;
   zbior_narzedzi[2].nazwa_kategorii = "Liczniki";
   zbior_narzedzi[3].nazwa_kategorii = "Timery";
   zbior_narzedzi[4].nazwa_kategorii = "Arytmetyka";
   zbior_narzedzi[5].nazwa_kategorii = "Relacje";
   for (int i=0; i<ILOSC_KATEGORII; i++)
      {
      zbior_narzedzi[i].pierwsze_narzedzie = NULL;
      }
   dodaj_narzedzie(0, new styk_zwierny);
   dodaj_narzedzie(0, new styk_rozwierny);
   dodaj_narzedzie(1, new cewka_zwierna);
   dodaj_narzedzie(1, new cewka_rozwierna);
   dodaj_narzedzie(1, new cewka_zbocze_narastajace);
   dodaj_narzedzie(1, new cewka_zbocze_opadajace);
   dodaj_narzedzie(1, new cewka_S);
   dodaj_narzedzie(1, new cewka_R);
   dodaj_narzedzie(2, new licznik_UPCTR);
   dodaj_narzedzie(2, new licznik_DNCTR);
   dodaj_narzedzie(3, new timer_ONDTR);
   dodaj_narzedzie(3, new timer_OFDT);
   dodaj_narzedzie(3, new timer_TMR);
   dodaj_narzedzie(4, new math_add);
   dodaj_narzedzie(4, new math_sub);
   dodaj_narzedzie(4, new math_mul);
   dodaj_narzedzie(4, new math_div);
   dodaj_narzedzie(4, new math_mod);
   dodaj_narzedzie(4, new math_sqrt);
	dodaj_narzedzie(5, new relacja_rowny);
	dodaj_narzedzie(5, new relacja_nierowny);
	dodaj_narzedzie(5, new relacja_wiekszy);
	dodaj_narzedzie(5, new relacja_wiekszyrowny);
	dodaj_narzedzie(5, new relacja_mniejszy);
	dodaj_narzedzie(5, new relacja_mniejszyrowny);
	dodaj_narzedzie(5, new relacja_zakres);
   RECT obszar;
   GetClientRect(okno, &obszar);
   zakladki = CreateWindow(WC_TABCONTROL, "", WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE,
		0, 0, obszar.right, obszar.bottom, okno, NULL, instancja, NULL);
   for (int i=0; i<ILOSC_KATEGORII; i++)
   	{
      TC_ITEM zak;
      zak.mask = TCIF_TEXT;
      zak.pszText = zbior_narzedzi[i].nazwa_kategorii;
      TabCtrl_InsertItem(zakladki, i, &zak);
      }
   int max_szerokosc = 0;
   int max_wysokosc = 0;
	for (int i=0; i<ILOSC_KATEGORII; i++)
   	{
		jedno_narzedzie * aktualne = zbior_narzedzi[i].pierwsze_narzedzie;
      int szerokosc = 0;
      int wysokosc = 0;
		while (aktualne)
      	{
         int szer, wys;
         aktualne->narzedzie->podaj_rozmiar(szer, wys, WERSJA_MINI);
         szerokosc += szer;
         if (wys>wysokosc)
         	wysokosc = wys;
         aktualne = aktualne->nastepne;
         }
		if (szerokosc>max_szerokosc)
      	max_szerokosc = szerokosc;
      if (wysokosc>max_wysokosc)
      	max_wysokosc = wysokosc;
      }
   obszar.left = obszar.top = 0;
   obszar.right = max_szerokosc*SZEROKOSC_ELEMENTU;
   obszar.bottom = max_wysokosc*WYSOKOSC_ELEMENTU;
	TabCtrl_AdjustRect(zakladki, TRUE, &obszar);
   RECT obszar2 = obszar;
   AdjustWindowRect(&obszar2, STYL_OKNA_NARZEDZIOWEGO, FALSE);
   MoveWindow(okno, 0, 20, obszar2.right-obszar2.left, obszar2.bottom-obszar2.top, TRUE);
   MoveWindow(zakladki, 0, 0, obszar.right-obszar.left, obszar.bottom-obszar.top, TRUE);
	obszar.right -= obszar.left;
   obszar.bottom -= obszar.top;
   obszar.left = 0;
   obszar.top = 0;
   TabCtrl_AdjustRect(zakladki, FALSE, &obszar);
   WNDCLASS klasa_klienta;
   klasa_klienta.style = 0;
   klasa_klienta.hInstance = instancja;
   klasa_klienta.lpszClassName = "klient";
   klasa_klienta.lpfnWndProc = ProcOknaNarzedziKlient;
   klasa_klienta.hIcon = NULL;
   klasa_klienta.hCursor = LoadCursor(NULL, IDC_ARROW);
   klasa_klienta.lpszMenuName = NULL;
   klasa_klienta.cbClsExtra = 0;
   klasa_klienta.cbWndExtra = 0;
   klasa_klienta.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
   RegisterClass(&klasa_klienta);
   klient = CreateWindow("klient", "", WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE,
   	obszar.left, obszar.top, obszar.right-obszar.left, obszar.bottom-obszar.top,
      okno, 0, instancja, NULL);
	BringWindowToTop(klient);
   }

narzedzia::~narzedzia(void)
	{
	for (int i=0; i<ILOSC_KATEGORII; i++)
   	{
      jedno_narzedzie * aktualne = zbior_narzedzi[i].pierwsze_narzedzie;
      while (aktualne)
      	{
         jedno_narzedzie * nastepne = aktualne->nastepne;
         delete aktualne->narzedzie;
         delete aktualne;
         aktualne = nastepne;
         }
      }
   }

LRESULT CALLBACK narzedzia::obsluz_komunikat(HWND okno, UINT komunikat,WPARAM wParam, LPARAM lParam)
	{
   switch (komunikat)
   	{
      case WM_NOTIFY:
      	{
         LPNMHDR lpnmhdr = (LPNMHDR) lParam;
         switch (lpnmhdr->code)
         	{
            case TCN_SELCHANGE:
            	akt_kategoria = TabCtrl_GetCurSel(zakladki);
               InvalidateRect(klient, NULL, TRUE);
            	break;
            }
      	break;
         }
      default:
      	return DefWindowProc(okno, komunikat, wParam, lParam);
      }
  	return 0;
   }

LRESULT CALLBACK narzedzia::obsluz_komunikat_klienta(HWND okno, UINT komunikat,WPARAM wParam, LPARAM lParam)
	{
   switch (komunikat)
   	{
      case WM_PAINT:
			{
         int temp_x = akt_program_LD->scroll_x;
         int temp_y = akt_program_LD->scroll_y;
         akt_program_LD->scroll_x = 0;
         akt_program_LD->scroll_y = 0;
         PAINTSTRUCT strukturka;
         HDC kontekst = BeginPaint(okno, &strukturka);
         HFONT stara_czcionka = (HFONT)GetCurrentObject(kontekst, OBJ_FONT);
         SelectObject(kontekst, GetStockObject(DEFAULT_GUI_FONT));
         int akt_x = 0;
         jedno_narzedzie * akt_narzedzie = zbior_narzedzi[akt_kategoria].pierwsze_narzedzie;
         while (akt_narzedzie)
         	{
				akt_narzedzie->narzedzie->narysuj(kontekst, RYSUJ_NAZWE|WERSJA_MINI, akt_x, 0);
            int szerokosc, wysokosc;
            akt_narzedzie->narzedzie->podaj_rozmiar(szerokosc, wysokosc, WERSJA_MINI);
            akt_x += szerokosc;
            akt_narzedzie = akt_narzedzie->nastepne;
            }
         SelectObject(kontekst, stara_czcionka);
         EndPaint(okno, &strukturka);
         akt_program_LD->scroll_x = temp_x;
         akt_program_LD->scroll_y = temp_y;
      	break;
         }
      case WM_LBUTTONDOWN:
      	{
         if (!praca_dziala)
         	{
				int szukany_x = LOWORD(lParam)/SZEROKOSC_ELEMENTU;
				int szukany_y = HIWORD(lParam)/WYSOKOSC_ELEMENTU;
	         int cur_x = 0;
				jedno_narzedzie * akt = zbior_narzedzi[akt_kategoria].pierwsze_narzedzie;
	         while (akt)
	         	{
	            int szer, wys;
					akt->narzedzie->podaj_rozmiar(szer, wys, WERSJA_MINI);
	            if ((szukany_x>=cur_x)&&(szukany_x<cur_x+szer)&&(szukany_y<wys))
	            	break;
	            cur_x += szer;
	            akt = akt->nastepne;
	            }
	         if (akt)
	         	akt_program_LD->rozpocznij_DRAGDROP(akt->narzedzie->sklonuj(), akt_kategoria==kategoria_cewek);
            }
         break;
         }
      case WM_RBUTTONUP:
      	{
         POINT punkt;
         punkt.x = LOWORD(lParam);
         punkt.y = HIWORD(lParam);
         ClientToScreen(okno, &punkt);
			int szukany_x = LOWORD(lParam)/SZEROKOSC_ELEMENTU;
			int szukany_y = HIWORD(lParam)/WYSOKOSC_ELEMENTU;
         int cur_x = 0;
			jedno_narzedzie * akt = zbior_narzedzi[akt_kategoria].pierwsze_narzedzie;
         while (akt)
         	{
            int szer, wys;
				akt->narzedzie->podaj_rozmiar(szer, wys, WERSJA_MINI);
            if ((szukany_x>=cur_x)&&(szukany_x<cur_x+szer)&&(szukany_y<wys))
            	break;
            cur_x += szer;
            akt = akt->nastepne;
            }
         if (akt)
         	switch (TrackPopupMenu(GetSubMenu(LoadMenu(instancja, MAKEINTRESOURCE(IDM_MENUNARZEDZIE)), 0), TPM_LEFTALIGN|TPM_TOPALIGN|TPM_NONOTIFY|TPM_RETURNCMD, punkt.x, punkt.y, 0, okno, NULL))
            	{
               case CM_POMOC:
                  pomoc.wyswietl(akt->narzedzie->podaj_nazwe());
               	break;
               }
      	break;
         }
      default:
		   return DefWindowProc(okno, komunikat, wParam, lParam);
      }
   return 0;
	}

void narzedzia::dodaj_narzedzie(int kategoria, element_zwykly * nowe_narzedzie)
	{
   jedno_narzedzie * akt;
   if (akt = zbior_narzedzi[kategoria].pierwsze_narzedzie)
   	{
		while (akt->nastepne)
         akt = akt->nastepne;
      akt->nastepne = new jedno_narzedzie;
      akt = akt->nastepne;
      }
   else
      akt = zbior_narzedzi[kategoria].pierwsze_narzedzie = new jedno_narzedzie;
   akt->narzedzie = nowe_narzedzie;
   akt->nastepne = NULL;
   }

element * narzedzia::rozpoznaj_i_wczytaj(FILE * plik)
	{
   char bufor[256];
   int i = 0;
   do
   	{
      bufor[i] = fgetc(plik);
      i++;
      } while (bufor[i-1]);
	if (strcmp(bufor, "polaczenie_szeregowe") == 0)
   	return new polaczenie_szeregowe(plik);
	if (strcmp(bufor, "polaczenie_rownolegle") == 0)
   	return new polaczenie_rownolegle(plik);
   for (int i=0; i<ILOSC_KATEGORII; i++)
   	{
		jedno_narzedzie * akt = zbior_narzedzi[i].pierwsze_narzedzie;
      while (akt)
      	{
         if (strcmp((akt->narzedzie)->podaj_nazwe(), bufor) == 0)
         	return (akt->narzedzie)->sklonuj(plik);
         akt = akt->nastepne;
         }
      }
   return NULL;
   }

