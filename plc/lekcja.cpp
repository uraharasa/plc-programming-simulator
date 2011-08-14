#include "lekcja.h"
#include "okno_glowne.h"
#include "resource.h"
#include <commctrl.h>

lekcja::lekcja()
	{
	okno_LD = CreateWindow(L"OknoLD", L"Program LD", WS_CAPTION|WS_CHILD|WS_CLIPSIBLINGS|WS_HSCROLL|WS_VSCROLL|WS_THICKFRAME|WS_VISIBLE|WS_MAXIMIZEBOX,
		0, 50, 200, 200,
      OknoGlowne, NULL, instancja, NULL);
   ShowWindow(OknoNarzedzi, SW_SHOW);
   okno = CreateWindow(L"OknoLekcji", L"Uk³ad wykonawczy", WS_CAPTION|WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE,
   	0, 50, 200, 200,
      OknoGlowne, NULL, instancja, NULL);
   SendDlgItemMessage(OknoGlowne, IDC_TOOLBAR, TB_ENABLEBUTTON, CM_PRACASTART, MAKELONG(TRUE, 0));
   SendDlgItemMessage(OknoGlowne, IDC_TOOLBAR, TB_ENABLEBUTTON, CM_PRACAPAUZA, MAKELONG(TRUE, 0));
   SendDlgItemMessage(OknoGlowne, IDC_TOOLBAR, TB_ENABLEBUTTON, CM_PRACARESTART, MAKELONG(TRUE, 0));
   SendDlgItemMessage(OknoGlowne, IDC_TOOLBAR, TB_ENABLEBUTTON, CM_PRACAKROKOWA, MAKELONG(TRUE, 0));
   SendDlgItemMessage(OknoGlowne, IDC_TOOLBAR, TB_ENABLEBUTTON, CM_ODCZYT, MAKELONG(TRUE, 0));
   SendDlgItemMessage(OknoGlowne, IDC_TOOLBAR, TB_ENABLEBUTTON, CM_ZAPIS, MAKELONG(TRUE, 0));
   SendDlgItemMessage(OknoGlowne, IDC_TOOLBAR, TB_ENABLEBUTTON, CM_WYDRUKUJ, MAKELONG(TRUE, 0));
   HMENU menu = GetMenu(OknoGlowne);
   EnableMenuItem(menu, CM_PRACASTART, MF_BYCOMMAND|MF_ENABLED);
   EnableMenuItem(menu, CM_PRACAPAUZA, MF_BYCOMMAND|MF_ENABLED);
   EnableMenuItem(menu, CM_PRACARESTART, MF_BYCOMMAND|MF_ENABLED);
   EnableMenuItem(menu, CM_PRACAKROKOWA, MF_BYCOMMAND|MF_ENABLED);
   EnableMenuItem(menu, CM_ODCZYT, MF_BYCOMMAND|MF_ENABLED);
   EnableMenuItem(menu, CM_ZAPIS, MF_BYCOMMAND|MF_ENABLED);
   EnableMenuItem(menu, CM_WYDRUKUJ, MF_BYCOMMAND|MF_ENABLED);
   EnableMenuItem(menu, CM_POMOCLEKCJA, MF_BYCOMMAND|MF_ENABLED);
   wejscia_I = NULL;
   wyjscia_Q = NULL;
   wejscia_AI = NULL;
   wyjscia_AQ = NULL;
   }

wstring lekcja::podaj_nazwe()
	{
   return nazwa;
   }

void lekcja::ustal_rozmiar_okna(void)
	{
   int szer, wys;
   podaj_rozmiar_okna(szer, wys);
   RECT obszar;
   obszar.left = obszar.top = 0;
   obszar.right = szer;
   obszar.bottom = wys;
   AdjustWindowRect(&obszar, WS_CAPTION|WS_CHILD, FALSE);
   MoveWindow(okno, 0, wysokosc_toolbara, obszar.right-obszar.left, obszar.bottom-obszar.top, TRUE);
   RECT klient;
   GetClientRect(OknoGlowne, &klient);
   RECT narzedzia;
   GetWindowRect(OknoNarzedzi, &narzedzia);
   MoveWindow(OknoNarzedzi, klient.right-(narzedzia.right-narzedzia.left), wysokosc_toolbara, narzedzia.right-narzedzia.left, narzedzia.bottom-narzedzia.top, TRUE);
   int y_pocz = max(obszar.bottom-obszar.top, narzedzia.bottom-narzedzia.top)+wysokosc_toolbara;
   MoveWindow(okno_LD, 0, y_pocz, klient.right, klient.bottom-y_pocz, TRUE);
   }

void lekcja::dzialaj(void)
	{
   InvalidateRect(okno, NULL, FALSE);
   }

void lekcja::zresetuj(void)
	{
   pamiec::wyczysc_pamiec();
   InvalidateRect(okno, NULL, FALSE);
   }

lekcja::~lekcja()
	{
   DestroyWindow(okno);
   ShowWindow(OknoNarzedzi, SW_HIDE);
   DestroyWindow(okno_LD);
   if (wejscia_I)
   	delete wejscia_I;
   if (wyjscia_Q)
   	delete wyjscia_Q;
   if (wejscia_AI)
   	delete wejscia_AI;
   if (wyjscia_AQ)
   	delete wyjscia_AQ;
   SendDlgItemMessage(OknoGlowne, IDC_TOOLBAR, TB_ENABLEBUTTON, CM_PRACASTART, MAKELONG(FALSE, 0));
   SendDlgItemMessage(OknoGlowne, IDC_TOOLBAR, TB_ENABLEBUTTON, CM_PRACAPAUZA, MAKELONG(FALSE, 0));
   SendDlgItemMessage(OknoGlowne, IDC_TOOLBAR, TB_ENABLEBUTTON, CM_PRACARESTART, MAKELONG(FALSE, 0));
   SendDlgItemMessage(OknoGlowne, IDC_TOOLBAR, TB_ENABLEBUTTON, CM_PRACAKROKOWA, MAKELONG(FALSE, 0));
   SendDlgItemMessage(OknoGlowne, IDC_TOOLBAR, TB_ENABLEBUTTON, CM_ODCZYT, MAKELONG(FALSE, 0));
   SendDlgItemMessage(OknoGlowne, IDC_TOOLBAR, TB_ENABLEBUTTON, CM_ZAPIS, MAKELONG(FALSE, 0));
   SendDlgItemMessage(OknoGlowne, IDC_TOOLBAR, TB_ENABLEBUTTON, CM_WYDRUKUJ, MAKELONG(FALSE, 0));
   HMENU menu = GetMenu(OknoGlowne);
   EnableMenuItem(menu, CM_PRACASTART, MF_BYCOMMAND|MF_GRAYED);
   EnableMenuItem(menu, CM_PRACAPAUZA, MF_BYCOMMAND|MF_GRAYED);
   EnableMenuItem(menu, CM_PRACARESTART, MF_BYCOMMAND|MF_GRAYED);
   EnableMenuItem(menu, CM_PRACAKROKOWA, MF_BYCOMMAND|MF_GRAYED);
   EnableMenuItem(menu, CM_ODCZYT, MF_BYCOMMAND|MF_GRAYED);
   EnableMenuItem(menu, CM_ZAPIS, MF_BYCOMMAND|MF_GRAYED);
   EnableMenuItem(menu, CM_WYDRUKUJ, MF_BYCOMMAND|MF_GRAYED);
   EnableMenuItem(menu, CM_POMOCLEKCJA, MF_BYCOMMAND|MF_GRAYED);
   }

LRESULT CALLBACK ProcOknaLekcji(HWND okno, UINT komunikat, WPARAM wParam, LPARAM lParam)
	{
   if (akt_lekcja)
		{
	   switch (komunikat)
	   	{
         case WM_LBUTTONDOWN:
         	{
            if (akt_lekcja->click(LOWORD(lParam), HIWORD(lParam)))
            	InvalidateRect(okno, NULL, FALSE);
            break;
            }
         case WM_PAINT:
         	{
            int szer, wys;
            akt_lekcja->podaj_rozmiar_okna(szer, wys);
            PAINTSTRUCT strukt;
            HDC kontekst = BeginPaint(okno, &strukt);
            HDC kontekst_bitmapy = CreateCompatibleDC(kontekst);
            HBITMAP bitmapa = CreateCompatibleBitmap(kontekst, szer, wys);
            SelectObject(kontekst_bitmapy, bitmapa);
            akt_lekcja->narysuj(kontekst_bitmapy);
            BitBlt(kontekst, 0, 0, szer, wys, kontekst_bitmapy, 0, 0, SRCCOPY);
            DeleteDC(kontekst_bitmapy);
            DeleteObject(bitmapa);
            EndPaint(okno, &strukt);
            break;
            }
	      default:
	      	return DefWindowProc(okno, komunikat, wParam, lParam);
	      }
      return 0;
	   }
   else
   	return DefWindowProc(okno, komunikat, wParam, lParam);
   }
