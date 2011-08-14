#include "zmiana_parametrow.h"
#include "okno_glowne.h"
#include "resource.h"

BOOL CALLBACK ProceduraDialogu(HWND okno, UINT komunikat, WPARAM wParam, LPARAM lParam);

element_zwykly * edytowany;
HDC kontekst_pamieci;
HBITMAP bitmapa;
RECT bitmapa_wymiary;
int szerokosc_dialogu;
int wysokosc_dialogu;
const int szerokosc_przycisku = 80;
const int wysokosc_przycisku = 25;
pamiec * adres_bazowy;
pamiec * * wejscia;
pamiec * * wyjscia;
int il_wejsc;
int il_wyjsc;
pamiec * * adresy;
int ilosc_przyciskow;
HFONT czcionka_dialogu = 0;

void zmien_parametry_elementu(HWND okno, element_zwykly * aktualny)
{
	if (czcionka_dialogu == 0)
	{
		NONCLIENTMETRICS metrics;
		metrics.cbSize = sizeof(NONCLIENTMETRICS);
		BOOL result = SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &metrics, 0);
		czcionka_dialogu = CreateFontIndirect(&metrics.lfCaptionFont);
	}

	edytowany = aktualny;
	adres_bazowy = edytowany->adres_bazowy;
	wejscia = edytowany->wejscia;
	wyjscia = edytowany->wyjscia;
	il_wejsc = edytowany->il_wejsc;
	il_wyjsc = edytowany->il_wyjsc;
	ilosc_przyciskow = 0;
	if (adres_bazowy)
		ilosc_przyciskow++;
	ilosc_przyciskow += il_wejsc + il_wyjsc;
	adresy = new pamiec * [ilosc_przyciskow];
	DialogBox(instancja, MAKEINTRESOURCE(IDD_PARAMETRY), okno, (DLGPROC) ProceduraDialogu);
	delete adresy;
}

BOOL CALLBACK ProceduraDialogu(HWND okno, UINT komunikat, WPARAM wParam, LPARAM lParam)
{
	static HFONT stara_czcionka;
	switch (komunikat)
	{
	case WM_INITDIALOG:
		{
			int szer, wys;
			edytowany->podaj_rozmiar(szer, wys);
			bitmapa_wymiary.left = bitmapa_wymiary.top = 0;
			bitmapa_wymiary.right = szer*SZEROKOSC_ELEMENTU;
			bitmapa_wymiary.bottom = wys*WYSOKOSC_ELEMENTU;
			HDC kontekst = GetDC(okno);
			kontekst_pamieci = CreateCompatibleDC(kontekst);
			stara_czcionka = (HFONT)GetCurrentObject(kontekst_pamieci, OBJ_FONT);
			SelectObject(kontekst_pamieci, GetStockObject(DEFAULT_GUI_FONT));
			bitmapa = CreateCompatibleBitmap(kontekst, bitmapa_wymiary.right, bitmapa_wymiary.bottom);
			SelectObject(kontekst_pamieci, bitmapa);
			SelectObject(kontekst_pamieci, GetStockObject(BLACK_PEN));
			int back_x = akt_program_LD->scroll_x;
			int back_y = akt_program_LD->scroll_y;
			akt_program_LD->scroll_x = 0;
			akt_program_LD->scroll_y = 0;
			FillRect(kontekst_pamieci, &bitmapa_wymiary, (HBRUSH)GetStockObject(WHITE_BRUSH));
			edytowany->narysuj(kontekst_pamieci, RYSUJ_ADRES|RYSUJ_NAZWE, 0, 0);
			akt_program_LD->scroll_x = back_x;
			akt_program_LD->scroll_y = back_y;

			szerokosc_dialogu = bitmapa_wymiary.right+20;
			wysokosc_dialogu = bitmapa_wymiary.bottom+20;

			int akt_wys = wysokosc_dialogu;
			int i=0;
			if (adres_bazowy)
			{
				*(adresy+i) = adres_bazowy;
				SIZE rozmiar;
				GetTextExtentPoint32(kontekst, L"Adres bazowy", 12, &rozmiar);
				if (rozmiar.cx+szerokosc_przycisku+30>szerokosc_dialogu)
					szerokosc_dialogu = rozmiar.cx+szerokosc_przycisku+30;
				HWND etykieta = CreateWindow(L"STATIC", L"Adres bazowy", WS_CHILD|WS_VISIBLE, 10, wysokosc_dialogu+(wysokosc_przycisku-rozmiar.cy)/2, rozmiar.cx, rozmiar.cy, okno, NULL, instancja, NULL);
				SendMessage(etykieta, WM_SETFONT, (WPARAM)czcionka_dialogu, FALSE);
				wysokosc_dialogu += wysokosc_przycisku+10;
				i++;
			}
			if (il_wejsc)
			{
				int o = 0;
				do
				{
					*(adresy+i) = *(wejscia+o);
					SIZE rozmiar;
					wstring napis = L"Wejœcie ";
					wstring napis2 = (*(adresy+i))->podpisz_nazwa();
					wstring pelen = napis + napis2;
					GetTextExtentPoint32(kontekst, pelen.c_str(), pelen.length(), &rozmiar);
					if (rozmiar.cx+szerokosc_przycisku+30>szerokosc_dialogu)
						szerokosc_dialogu = rozmiar.cx+szerokosc_przycisku+30;
					HWND etykieta = CreateWindow(L"STATIC", pelen.c_str(), WS_CHILD|WS_VISIBLE, 10, wysokosc_dialogu+(wysokosc_przycisku-rozmiar.cy)/2, rozmiar.cx, rozmiar.cy, okno, NULL, instancja, NULL);
					SendMessage(etykieta, WM_SETFONT, (WPARAM)czcionka_dialogu, FALSE);
					wysokosc_dialogu += wysokosc_przycisku+10;
					o++;
					i++;
				} while (o<il_wejsc);
			}
			if (il_wyjsc)
			{
				int o = 0;
				do
				{
					*(adresy+i) = *(wyjscia+o);
					SIZE rozmiar;
					wstring napis = L"Wyjœcie ";
					wstring napis2 = (*(adresy+i))->podpisz_nazwa();
					wstring pelen = napis + napis2;
					GetTextExtentPoint32(kontekst, pelen.c_str(), pelen.length(), &rozmiar);
					if (rozmiar.cx+szerokosc_przycisku+30>szerokosc_dialogu)
						szerokosc_dialogu = rozmiar.cx+szerokosc_przycisku+30;
					HWND etykieta = CreateWindow(L"STATIC", pelen.c_str(), WS_CHILD|WS_VISIBLE, 10, wysokosc_dialogu+(wysokosc_przycisku-rozmiar.cy)/2, rozmiar.cx, rozmiar.cy, okno, NULL, instancja, NULL);
					SendMessage(etykieta, WM_SETFONT, (WPARAM)czcionka_dialogu, FALSE);
					wysokosc_dialogu += wysokosc_przycisku+10;
					o++;
					i++;
				} while (o<il_wyjsc);
			}
			ReleaseDC(okno, kontekst);
			for (int i=0; i<ilosc_przyciskow; i++)
			{
				HWND przycisk = CreateWindow(L"BUTTON", L"Zmieñ", BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE, szerokosc_dialogu-szerokosc_przycisku-10, akt_wys+(wysokosc_przycisku+10)*i, szerokosc_przycisku, wysokosc_przycisku, okno, (HMENU)(0x100+i), instancja, NULL);
				SendMessage(przycisk, WM_SETFONT, (WPARAM)czcionka_dialogu, FALSE);
			}

			MoveWindow(GetDlgItem(okno, IDOK), (szerokosc_dialogu-szerokosc_przycisku)/2, wysokosc_dialogu+10, szerokosc_przycisku, wysokosc_przycisku, FALSE);
			wysokosc_dialogu += wysokosc_przycisku + 20;
			RECT obszar;
			GetWindowRect(okno, &obszar);
			obszar.right = obszar.left + szerokosc_dialogu;
			obszar.bottom = obszar.top + wysokosc_dialogu;
			AdjustWindowRect(&obszar, WS_POPUP|WS_CAPTION, FALSE);
			MoveWindow(okno, obszar.left, obszar.top, obszar.right-obszar.left, obszar.bottom-obszar.top, TRUE);
			break;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT info;
			HDC kontekst = BeginPaint(okno, &info);
			BitBlt(kontekst, (szerokosc_dialogu-bitmapa_wymiary.right)/2, 10, bitmapa_wymiary.right, bitmapa_wymiary.bottom, kontekst_pamieci, 0, 0, SRCCOPY);
			EndPaint(okno, &info);
			break;
		}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			SelectObject(kontekst_pamieci, stara_czcionka);
			DeleteObject(bitmapa);
			DeleteDC(kontekst_pamieci);
			EndDialog(okno, TRUE);
			break;
		default:
			zmien_parametry_pamieci(okno, *(adresy+(LOWORD(wParam)-0x100)));
			int back_x = akt_program_LD->scroll_x;
			int back_y = akt_program_LD->scroll_y;
			akt_program_LD->scroll_x = 0;
			akt_program_LD->scroll_y = 0;
			FillRect(kontekst_pamieci, &bitmapa_wymiary, (HBRUSH)GetStockObject(WHITE_BRUSH));
			edytowany->narysuj(kontekst_pamieci, RYSUJ_ADRES|RYSUJ_NAZWE, 0, 0);
			akt_program_LD->scroll_x = back_x;
			akt_program_LD->scroll_y = back_y;
			InvalidateRect(okno, NULL, FALSE);
			break;
		}
		break;
	case WM_CLOSE:
		SelectObject(kontekst_pamieci, stara_czcionka);
		DeleteObject(bitmapa);
		DeleteDC(kontekst_pamieci);
		EndDialog(okno, TRUE);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}