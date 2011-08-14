#include "about.h"
#include "bitmapy.h"

bitmapa about(L"about");
int aktualne_przesuniecie;
const int rozmiar_y = 649;
UINT timer;

BOOL CALLBACK proc_okna_about(HWND okno, UINT komunikat, WPARAM wParam, LPARAM lParam)
	{
	switch (komunikat)
   	{
      case WM_INITDIALOG:
      	aktualne_przesuniecie = 0;
         timer = SetTimer(okno, 100, 10, NULL);
      	break;
      case WM_PAINT:
      	{
         PAINTSTRUCT info;
         HDC kontekst = BeginPaint(okno, &info);
      	about.wyswietl(kontekst, 30, 40, -1, 100, 0, aktualne_przesuniecie);
         if (aktualne_przesuniecie + 100 > rozmiar_y)
         	about.wyswietl(kontekst, 30, 40+rozmiar_y-aktualne_przesuniecie, -1, 100-rozmiar_y+aktualne_przesuniecie); 
         EndPaint(okno, &info);
         break;
         }
      case WM_TIMER:
      	aktualne_przesuniecie += 1;
         if (aktualne_przesuniecie >= rozmiar_y)
         	aktualne_przesuniecie = 0;
         InvalidateRect(okno, NULL, FALSE);
         break;
      case WM_COMMAND:
      	switch (LOWORD(wParam))
         	{
            case IDOK:
            	KillTimer(okno, timer);
            	EndDialog(okno, TRUE);
               break;
            default:
            	return FALSE;
            }
         break;
		default:
      	return FALSE;
      }
   return TRUE;
   }