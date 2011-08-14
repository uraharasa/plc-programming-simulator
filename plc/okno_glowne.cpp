#include <windows.h>
#include <commctrl.h>
#include "program_LD.h"
#include "narzedzia.h"
#include "lekcja1.h"
#include "lekcja2.h"
#include "lekcja3.h"
#include "lekcja4.h"
#include "lekcja5.h"
#include "resource.h"
#include "help.h"
#include "about.h"

#define WM_PYTANIE (WM_USER+1)

HINSTANCE instancja;
program_LD * akt_program_LD = NULL;
narzedzia * akt_narzedzia = NULL;
lekcja * akt_lekcja = NULL;
HWND OknoGlowne;
HWND OknoNarzedzi;
int wysokosc_toolbara;
int praca_krokowa;
int praca_dziala;

LRESULT CALLBACK ProcOknaGlownego(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ProcOknaLD(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ProcOknaNarzedzi(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ProcOknaLekcji(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ProcStart(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI TimerProc(LPVOID);
void zrob_krok(void);
void dostepne_menu(HWND okno);

int WINAPI WinMain(HINSTANCE zad, HINSTANCE, LPSTR, int tryb_okna)
	{
   instancja = zad;
   InitCommonControls();
	WNDCLASS klasa_okna;
   klasa_okna.style = 0;
   klasa_okna.cbClsExtra = 0;
   klasa_okna.cbWndExtra = 0;
   klasa_okna.hCursor = LoadCursor(NULL, IDC_ARROW);
   klasa_okna.hInstance = instancja;
   klasa_okna.lpszClassName = L"OknoGlowne";
   klasa_okna.lpfnWndProc = ProcOknaGlownego;
   klasa_okna.lpszMenuName = MAKEINTRESOURCE(IDM_MENU_GLOWNE);
   klasa_okna.hbrBackground = CreateSolidBrush(0x7f0000);
   klasa_okna.hIcon = LoadIcon(instancja, MAKEINTRESOURCE(IDI_ICON1));
   RegisterClass(&klasa_okna);

   klasa_okna.style = CS_DBLCLKS;
   klasa_okna.cbClsExtra = 0;
   klasa_okna.cbWndExtra = 0;
   klasa_okna.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND));
   klasa_okna.hInstance = instancja;
   klasa_okna.lpszClassName = L"OknoLD";
   klasa_okna.lpfnWndProc = ProcOknaLD;
   klasa_okna.lpszMenuName = NULL;
   klasa_okna.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
   klasa_okna.hIcon = NULL;
   RegisterClass(&klasa_okna);

   klasa_okna.style = 0;
   klasa_okna.cbClsExtra = 0;
   klasa_okna.cbWndExtra = 0;
   klasa_okna.hCursor = LoadCursor(NULL, IDC_ARROW);
   klasa_okna.hInstance = instancja;
   klasa_okna.lpszClassName = L"OknoNarzedzi";
   klasa_okna.lpfnWndProc = ProcOknaNarzedzi;
   klasa_okna.lpszMenuName = NULL;
   klasa_okna.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
   klasa_okna.hIcon = NULL;
   RegisterClass(&klasa_okna);

   klasa_okna.style = 0;
   klasa_okna.cbClsExtra = 0;
   klasa_okna.cbWndExtra = 0;
   klasa_okna.hCursor = LoadCursor(NULL, IDC_ARROW);
   klasa_okna.hInstance = instancja;
   klasa_okna.lpszClassName = L"OknoLekcji";
   klasa_okna.lpfnWndProc = ProcOknaLekcji;
   klasa_okna.lpszMenuName = NULL;
   klasa_okna.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
   klasa_okna.hIcon = NULL;
   RegisterClass(&klasa_okna);

	OknoGlowne = CreateWindow(L"OknoGlowne", L"Program dydaktyczny do nauki programowania sterowników PLC", WS_OVERLAPPEDWINDOW,
   	CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
      NULL, NULL, instancja, NULL);
   OknoNarzedzi = CreateWindow(L"OknoNarzedzi", L"Elementy", WS_CAPTION|WS_CHILD|WS_CLIPSIBLINGS,
   	0, 0, 50, 50,
      OknoGlowne, NULL, instancja, NULL);

	ShowWindow(OknoGlowne, SW_MAXIMIZE);
   SendMessage(OknoGlowne, WM_PYTANIE, 0, 0);

   MSG komunikat;
   while (GetMessage(&komunikat, NULL, 0, 0))
   	{
      TranslateMessage(&komunikat);
      DispatchMessage(&komunikat);
      }
   return komunikat.wParam;
   }

LRESULT CALLBACK ProcOknaGlownego(HWND okno, UINT komunikat, WPARAM wParam, LPARAM lParam)
	{
   switch (komunikat)
   	{
      case WM_CREATE:
      	{
         TBBUTTON przyciski[11];
         memset(przyciski, 0, sizeof(przyciski));
         przyciski[0].fsStyle = TBSTYLE_SEP;
         przyciski[1].iBitmap = 5;
         przyciski[1].idCommand = CM_ODCZYT;
         przyciski[1].fsState = 0;
         przyciski[1].fsStyle = TBSTYLE_BUTTON;
         przyciski[2].iBitmap = 6;
         przyciski[2].idCommand = CM_ZAPIS;
         przyciski[2].fsStyle = TBSTYLE_BUTTON;
         przyciski[2].fsState = 0;
         przyciski[3].iBitmap = 7;
         przyciski[3].idCommand = CM_WYDRUKUJ;
         przyciski[3].fsState = 0;
         przyciski[3].fsStyle = TBSTYLE_BUTTON;
         przyciski[4].fsStyle = TBSTYLE_SEP;
         przyciski[5].iBitmap = 0;
         przyciski[5].idCommand = CM_PRACASTART;
         przyciski[5].fsState = 0;
         przyciski[5].fsStyle = TBSTYLE_CHECKGROUP;
         przyciski[6].iBitmap = 1;
         przyciski[6].idCommand = CM_PRACAPAUZA;
         przyciski[6].fsState = TBSTATE_CHECKED;
         przyciski[6].fsStyle = TBSTYLE_CHECKGROUP;
         przyciski[7].iBitmap = 2;
         przyciski[7].idCommand = CM_PRACARESTART;
         przyciski[7].fsState = 0;
         przyciski[7].fsStyle = TBSTYLE_BUTTON;
         przyciski[8].iBitmap = 3;
         przyciski[8].idCommand = CM_PRACAKROKOWA;
         przyciski[8].fsState = 0;
         przyciski[8].fsStyle = TBSTYLE_CHECK;
         przyciski[9].fsStyle = TBSTYLE_SEP;
         przyciski[10].iBitmap = 4;
         przyciski[10].idCommand = CM_USTAWOKNA;
         przyciski[10].fsState = TBSTATE_ENABLED;
         przyciski[10].fsStyle = TBSTYLE_BUTTON;
         HWND tool = CreateToolbarEx(okno, WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS, IDC_TOOLBAR, 8, instancja, IDB_TOOLBAR, przyciski, 11, 0, 0, 16, 16, sizeof(TBBUTTON));
         RECT ob;
         GetWindowRect(tool, &ob);
         wysokosc_toolbara = ob.bottom-ob.top;
		   HMENU menu = GetMenu(okno);
		   EnableMenuItem(menu, CM_PRACASTART, MF_BYCOMMAND|MF_GRAYED);
		   EnableMenuItem(menu, CM_PRACAPAUZA, MF_BYCOMMAND|MF_GRAYED);
		   EnableMenuItem(menu, CM_PRACARESTART, MF_BYCOMMAND|MF_GRAYED);
		   EnableMenuItem(menu, CM_PRACAKROKOWA, MF_BYCOMMAND|MF_GRAYED);
		   EnableMenuItem(menu, CM_ODCZYT, MF_BYCOMMAND|MF_GRAYED);
		   EnableMenuItem(menu, CM_ZAPIS, MF_BYCOMMAND|MF_GRAYED);
		   EnableMenuItem(menu, CM_WYDRUKUJ, MF_BYCOMMAND|MF_GRAYED);
		   EnableMenuItem(menu, CM_POMOCLEKCJA, MF_BYCOMMAND|MF_GRAYED);
         praca_krokowa = FALSE;
         praca_dziala = FALSE;
         DWORD watek_id;
			HANDLE watek = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TimerProc, 0, 0, &watek_id);
			SetThreadPriority(watek, THREAD_PRIORITY_HIGHEST);
         HDC kont = GetDC(okno);
         int szerokosc = GetDeviceCaps(kont, HORZRES);
         int wysokosc = GetDeviceCaps(kont, VERTRES);
         int glebokosc = GetDeviceCaps(kont, BITSPIXEL);
         ReleaseDC(okno, kont);
      	if ((glebokosc <= 8) || (szerokosc < 800) || (wysokosc < 600))
         	MessageBox(okno, L"Do wygodnej pracy z programem zalecana jest rozdzielczoœæ co najmniej 800x600 przy 65 tysi¹cach kolorów.", L"Zmiana parametrów obrazu", MB_OK|MB_ICONINFORMATION);
      	break;
         }
      case WM_PYTANIE:
//			CreateDialog(instancja, MAKEINTRESOURCE(IDD_START), okno, (DLGPROC)ProcStart);
			DialogBox(instancja, MAKEINTRESOURCE(IDD_START), okno, (DLGPROC)ProcStart);
         break;
      case WM_SIZE:
      	{
         SendDlgItemMessage(okno, IDC_TOOLBAR, WM_SIZE, wParam, lParam);
         break;
         }
      case WM_CLOSE:
      	if (praca_dziala)
         	MessageBox(okno, L"Nie mo¿na zakoñczyæ programu, gdy pracuje symulacja. Musisz j¹ wpierw zatrzymaæ.", L"Symulacja aktywna!", MB_OK);
         else
         	DestroyWindow(okno);
      	break;
      case WM_DESTROY:
      	PostQuitMessage(0);
         break;
      case WM_DISPLAYCHANGE:
      	if ((wParam <= 8) || (LOWORD(lParam) < 800) || (HIWORD(lParam) < 600))
         	MessageBox(okno, L"Do wygodnej pracy z programem zalecana jest rozdzielczoœæ co najmniej 800x600 przy 65 tysi¹cach kolorów.", L"Zmiana parametrów obrazu", MB_OK|MB_ICONINFORMATION);
      	break;
      case WM_COMMAND:
      	switch (LOWORD(wParam))
         	{
            case CM_ABOUT:
            	DialogBox(instancja, MAKEINTRESOURCE(IDD_ABOUT), okno, (DLGPROC)proc_okna_about);
            	break;
            case CM_POMOCLEKCJA:
            	if (akt_lekcja)
               	pomoc.wyswietl(akt_lekcja->podaj_nazwe());
            	break;
            case CM_WYDRUKUJ:
            	if (akt_program_LD)
               	akt_program_LD->wydrukuj();
            	break;
            case CM_USTAWOKNA:
            	if (akt_lekcja)
               	akt_lekcja->ustal_rozmiar_okna();
            	break;
            case CM_LEKCJA1:
					if (akt_lekcja)
               	delete akt_lekcja;
               akt_lekcja = new lekcja1;
               akt_lekcja->ustal_rozmiar_okna();
            	break;
            case CM_LEKCJA2:
					if (akt_lekcja)
               	delete akt_lekcja;
               akt_lekcja = new lekcja2;
               akt_lekcja->ustal_rozmiar_okna();
            	break;
            case CM_LEKCJA3:
					if (akt_lekcja)
               	delete akt_lekcja;
               akt_lekcja = new lekcja3;
               akt_lekcja->ustal_rozmiar_okna();
            	break;
            case CM_LEKCJA4:
					if (akt_lekcja)
               	delete akt_lekcja;
               akt_lekcja = new lekcja4;
               akt_lekcja->ustal_rozmiar_okna();
            	break;
            case CM_LEKCJA5:
					if (akt_lekcja)
               	delete akt_lekcja;
               akt_lekcja = new lekcja5;
               akt_lekcja->ustal_rozmiar_okna();
            	break;
            case CM_ODCZYT:
            	{
               if (akt_lekcja)
               	{
                  wchar_t nazwa[256];
                  nazwa[0] = '\0';
                  OPENFILENAME strukt;
                  ZeroMemory((void *)&strukt, sizeof(OPENFILENAME));
                  strukt.lStructSize = sizeof(OPENFILENAME);
                  strukt.hwndOwner = okno;
                  strukt.lpstrFilter = L"Programy LD (*.ld)\0*.ld\0Wszystkie pliki (*.*)\0*.*\0\0";
                  strukt.lpstrCustomFilter = NULL;
                  strukt.nFilterIndex = 1;
						strukt.lpstrFile = nazwa;
                  strukt.nMaxFile = 256;
                  strukt.lpstrFileTitle = NULL;
                  strukt.lpstrInitialDir = NULL;
                  strukt.lpstrTitle = L"Wczytaj program LD:";
                  strukt.Flags = OFN_HIDEREADONLY|OFN_NOCHANGEDIR;
                  strukt.lpstrDefExt = L"ld";
                  if (GetOpenFileName(&strukt))
                  	{
                     FILE * plik;
                     plik = _wfopen(strukt.lpstrFile, L"rb");
                     if (plik)
                     	akt_program_LD->wczytaj(plik);
                     fclose(plik);
                     }
                  }
               break;
               }
            case CM_ZAPIS:
            	{
               if (akt_lekcja)
               	{
                  wchar_t nazwa[256];
                  nazwa[0] = '\0';
                  OPENFILENAME strukt;
                  ZeroMemory((void *)&strukt, sizeof(strukt));
                  strukt.lStructSize = sizeof(OPENFILENAME);
                  strukt.hwndOwner = okno;
                  strukt.hInstance = instancja;
                  strukt.lpstrFilter = L"Programy LD (*.ld)\0*.ld\0Wszystkie pliki (*.*)\0*.*\0";
                  strukt.lpstrCustomFilter = NULL;
                  strukt.nFilterIndex = 1;
						strukt.lpstrFile = nazwa;
                  strukt.nMaxFile = 256;
                  strukt.lpstrFileTitle = NULL;
                  strukt.lpstrInitialDir = NULL;
                  strukt.lpstrTitle = L"Zapisz program LD:";
                  strukt.Flags = OFN_HIDEREADONLY|OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT|OFN_EXPLORER;
                  strukt.lpstrDefExt = L"ld";
                  if (GetSaveFileName(&strukt))
                  	{
                     FILE * plik;
                     plik = _wfopen(strukt.lpstrFile, L"wb");
                     if (plik)
                     	akt_program_LD->zapisz(plik);
                     fclose(plik);
                     }
                  }
               break;
               }
            case CM_KONIEC:
            	if (akt_lekcja)
               	delete akt_lekcja;
               DestroyWindow(okno);
            	break;
            case CM_PRACARESTART:
            	{
               if (akt_lekcja)
               	akt_lekcja->zresetuj();
               break;
               }
            case CM_PRACASTART:
            	{
               SendDlgItemMessage(okno, IDC_TOOLBAR, TB_CHECKBUTTON, CM_PRACASTART, MAKELONG(TRUE, 0));
               praca_dziala = TRUE;
               if (praca_krokowa)
               	{
                  zrob_krok();
                  SendDlgItemMessage(okno, IDC_TOOLBAR, TB_CHECKBUTTON, CM_PRACAPAUZA, MAKELONG(TRUE, 0));
                  praca_dziala = FALSE;
                  }
               dostepne_menu(okno);
               break;
               }
            case CM_PRACAPAUZA:
            	{
               SendDlgItemMessage(okno, IDC_TOOLBAR, TB_CHECKBUTTON, CM_PRACAPAUZA, MAKELONG(TRUE, 0));
               praca_dziala = FALSE;
               dostepne_menu(okno);
               break;
               }
            case CM_PRACAKROKOWA:
            	{
               praca_krokowa = !praca_krokowa;
               if (praca_krokowa)
               	{
                  CheckMenuItem(GetMenu(okno), CM_PRACAKROKOWA, MF_BYCOMMAND|MF_CHECKED);
                  SendDlgItemMessage(okno, IDC_TOOLBAR, TB_CHECKBUTTON, CM_PRACAKROKOWA, MAKELONG(TRUE, 0));
						if (praca_dziala)
                  	{
                     praca_dziala = FALSE;
                     SendDlgItemMessage(okno, IDC_TOOLBAR, TB_CHECKBUTTON, CM_PRACAPAUZA, MAKELONG(TRUE, 0));
                     }
                  }
               else
               	{
               	CheckMenuItem(GetMenu(okno), CM_PRACAKROKOWA, MF_BYCOMMAND|MF_UNCHECKED);
                  SendDlgItemMessage(okno, IDC_TOOLBAR, TB_CHECKBUTTON, CM_PRACAKROKOWA, MAKELONG(FALSE, 0));
                  }
               dostepne_menu(okno);
               break;
               }
            }
      	break;
      default:
		   return DefWindowProc(okno, komunikat, wParam, lParam);
      }
   return 0;
   }

LRESULT CALLBACK ProcOknaLD(HWND okno, UINT komunikat, WPARAM wParam, LPARAM lParam)
	{
   switch (komunikat)
   	{
      case WM_CREATE:
      	akt_program_LD = new program_LD(okno);
         break;
      case WM_DESTROY:
      	delete akt_program_LD;
         break;
      default:
		   return akt_program_LD->obsluz_komunikat(okno, komunikat, wParam, lParam);
      }
   return 0;
   }

LRESULT CALLBACK ProcOknaNarzedzi(HWND okno, UINT komunikat, WPARAM wParam, LPARAM lParam)
	{
   switch (komunikat)
   	{
      case WM_CREATE:
      	akt_narzedzia = new narzedzia(okno);
         break;
      case WM_DESTROY:
      	delete akt_narzedzia;
         break;
      default:
	   	return akt_narzedzia->obsluz_komunikat(okno, komunikat, wParam, lParam);
      }
   return 0;
   }

LRESULT CALLBACK ProcOknaNarzedziKlient(HWND okno, UINT komunikat, WPARAM wParam, LPARAM lParam)
	{
   return akt_narzedzia->obsluz_komunikat_klienta(okno, komunikat, wParam, lParam);
   }

DWORD WINAPI TimerProc(LPVOID)
	{
   DWORD stary_czas = timeGetTime();
   DWORD nowy_czas;
   while (1)
   	{
      nowy_czas = timeGetTime();
      if (nowy_czas-stary_czas<9)
	      Sleep(9-(nowy_czas-stary_czas));
      do
      	nowy_czas = timeGetTime();
         while (nowy_czas-stary_czas<10);
      stary_czas = nowy_czas;
	   if ((!praca_krokowa)&&(praca_dziala))
			zrob_krok();
      };
   }

void zrob_krok(void)
	{
   if (akt_lekcja)
   	akt_lekcja->dzialaj();
   if (akt_program_LD)
   	akt_program_LD->dzialaj();
   }

void dostepne_menu(HWND okno)
	{
   UINT tryb;
   if (praca_dziala)
   	tryb = MF_BYCOMMAND|MF_GRAYED;
   else
   	tryb = MF_BYCOMMAND|MF_ENABLED;
   HMENU menu = GetMenu(okno);
   EnableMenuItem(menu, CM_LEKCJA1, tryb);
   EnableMenuItem(menu, CM_LEKCJA2, tryb);
   EnableMenuItem(menu, CM_LEKCJA3, tryb);
   EnableMenuItem(menu, CM_LEKCJA4, tryb);
   EnableMenuItem(menu, CM_LEKCJA5, tryb);
   EnableMenuItem(menu, CM_KONIEC, tryb);
   EnableMenuItem(menu, CM_ODCZYT, tryb);
   EnableMenuItem(menu, CM_ZAPIS, tryb);
   EnableMenuItem(menu, CM_WYDRUKUJ, tryb);
   SendDlgItemMessage(okno, IDC_TOOLBAR, TB_ENABLEBUTTON, CM_ODCZYT, MAKELONG(!praca_dziala, 0));
   SendDlgItemMessage(okno, IDC_TOOLBAR, TB_ENABLEBUTTON, CM_ZAPIS, MAKELONG(!praca_dziala, 0));
   SendDlgItemMessage(okno, IDC_TOOLBAR, TB_ENABLEBUTTON, CM_WYDRUKUJ, MAKELONG(!praca_dziala, 0));
   }

LRESULT CALLBACK ProcStart(HWND okno, UINT komunikat, WPARAM wParam, LPARAM lParam)
	{
   switch (komunikat)
   	{
      case WM_INITDIALOG:
      	CheckDlgButton(okno, IDC_OPCJA1, BST_CHECKED);
      	break;
      case WM_COMMAND:
      	switch (LOWORD(wParam))
         	{
            case IDOK:
            	if (IsDlgButtonChecked(okno, IDC_OPCJA1) == BST_CHECKED)
               	{
                  SendMessage(GetParent(okno), WM_COMMAND, MAKELONG(CM_LEKCJA1, 0), 0);
                  SendMessage(GetParent(okno), WM_COMMAND, MAKELONG(CM_POMOCLEKCJA, 0), 0);
                  }
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

