#include <windows.h>
#include <commctrl.h>
#include "pamiec.h"
#include "okno_glowne.h"
#include "resource.h"

#define ILE_CYFR 4

BOOL CALLBACK ProcPamieci(HWND okno, UINT komunikat, WPARAM wParam, LPARAM lParam);

int * pamiec::I = NULL;
int * pamiec::Q = NULL;
int * pamiec::R = NULL;
int * pamiec::M = NULL;
int * pamiec::AI = NULL;
int * pamiec::AQ = NULL;
int pamiec::il_I = 0;
int pamiec::il_Q = 0;
int pamiec::il_R = 0;
int pamiec::il_M = 0;
int pamiec::il_AI = 0;
int pamiec::il_AQ = 0;
opis_komorki * pamiec::lista_opisow = NULL;
opis_komorki * pamiec::koniec_listy = NULL;

pamiec::pamiec(wstring nazwa, int dozwolone, int szerokosc)
{
	nazwa_komorki = nazwa;
	dozwolone_typy = dozwolone;
	zajetosc_pamieci = szerokosc;
	valid = FALSE;
}

pamiec::pamiec(typy_pamieci typ, int adres, int szerokosc)
{
	valid = TRUE;
	zajetosc_pamieci = szerokosc;
	adres_pamieci = adres;
	typ_pamieci = typ;
}

pamiec::~pamiec()
{
}

void pamiec::nowe_parametry_sterownika(int nowe_I, int nowe_Q, int nowe_R, int nowe_M, int nowe_AI, int nowe_AQ)
{
	if (I)
		delete I;
	I = new int[nowe_I];
	il_I = nowe_I;
	if (Q)
		delete Q;
	Q = new int[nowe_Q];
	il_Q = nowe_Q;
	if (R)
		delete R;
	R = new int[nowe_R];
	il_R = nowe_R;
	if (M)
		delete M;
	M = new int[nowe_M];
	il_M = nowe_M;
	if (AI)
		delete AI;
	AI = new int[nowe_AI];
	il_AI = nowe_AI;
	if (AQ)
		delete AQ;
	AQ = new int[nowe_AQ];
	il_AQ = nowe_AQ;
	wyczysc_pamiec();
	usun_opisy();
}

void pamiec::wyczysc_pamiec(void)
{
	for (int i=0; i<il_I; i++)
		I[i] = 0;
	for (int i=0; i<il_Q; i++)
		Q[i] = 0;
	for (int i=0; i<il_R; i++)
		R[i] = 0;
	for (int i=0; i<il_M; i++)
		M[i] = 0;
	for (int i=0; i<il_AI; i++)
		AI[i] = 0;
	for (int i=0; i<il_AQ; i++)
		AQ[i] = 0;
}

void pamiec::wybierz_pamiec(int * &komorka, int adres)
{
	if (valid)
	{
		switch (typ_pamieci)
		{
		case typ_I:
			komorka = I + adres_pamieci + adres;
			break;
		case typ_Q:
			komorka = Q + adres_pamieci + adres;
			break;
		case typ_R:
			komorka = R + adres_pamieci + adres;
			break;
		case typ_M:
			komorka = M + adres_pamieci + adres;
			break;
		case typ_AI:
			komorka = AI + adres_pamieci + adres;
			break;
		case typ_AQ:
			komorka = AQ + adres_pamieci + adres;
			break;
		}
	}
	else
		komorka = NULL;
}

void pamiec::zapisz_pamiec(int wartosc, int adres)
{
	int * komorka;
	wybierz_pamiec(komorka, adres);
	if (komorka)
		*komorka = wartosc;
}

int pamiec::odczytaj_pamiec(int adres)
{
	int * komorka;
	if (typ_pamieci != typ_CONST)
	{
		wybierz_pamiec(komorka, adres);
		if (komorka)
			return *komorka;
	}
	else
		return adres_pamieci;
	return 0;
}

wstring pamiec::podpisz_nazwa(void)
{
	return nazwa_komorki;
}

void pamiec::narysuj_adres(HDC kontekst, int x, int y, int align)
{
	SetTextAlign(kontekst, align);
	wstring napis = podpisz_adres();
	COLORREF kolor = GetTextColor(kontekst);
	if (napis[0] == '?')
		SetTextColor(kontekst, KOLOR_ADRES_ZLY);
	else
		SetTextColor(kontekst, KOLOR_ADRES_DOBRY);
	TextOut(kontekst, x, y, napis.c_str(), napis.length());
	SetTextColor(kontekst, kolor);
}

void pamiec::narysuj_nazwe(HDC kontekst, int x, int y, int align)
{
	SetTextAlign(kontekst, align);
	wstring napis = podpisz_nazwa();
	TextOut(kontekst, x, y, napis.c_str(), napis.length());
}

wstring pamiec::podpisz_adres(void)
{
	if (valid)
	{
		wstring znaleziony;
		if ((znaleziony = poszukaj_opisu(typ_pamieci, adres_pamieci)).length() > 0)
		{
			return znaleziony;
		}
		wstring nowy;
		switch (typ_pamieci)
		{
		case typ_I:
			nowy += L"%I";
			break;
		case typ_Q:
			nowy += L"%Q";
			break;
		case typ_R:
			nowy += L"%R";
			break;
		case typ_M:
			nowy += L"%M";
			break;
		case typ_AI:
			nowy += L"%AI";
			break;
		case typ_AQ:
			nowy += L"%AQ";
			break;
		case typ_CONST:
			nowy += L"CST ";
			if (adres_pamieci>0)
				nowy += L"+";
			break;
		}
		int ad = adres_pamieci;
		if (ad<0)
		{
			nowy += L"-";
			ad = -ad;
		}
		wstring liczba;
		for (int i = 0; i<ILE_CYFR; i++)
		{
			liczba += (ad % 10) + 0x30;
			ad /=10;
		}
		for (int i = 0; i<ILE_CYFR; i++)
		{
			nowy += liczba[ILE_CYFR - i - 1];
		}
		return nowy;
	}
	else
	{
		return L"????";
	}
}


int adres_pamieci;
int zajetosc_pamieci;
typy_pamieci typ_pamieci;
int dozwolone_typy;
int valid;
int il_I, il_Q, il_R, il_M, il_AI, il_AQ;
void zmien_parametry_pamieci(HWND okno, pamiec * aktualna)
{
	adres_pamieci = aktualna->adres_pamieci;
	zajetosc_pamieci = aktualna->zajetosc_pamieci;
	typ_pamieci = aktualna->typ_pamieci;
	dozwolone_typy = aktualna->dozwolone_typy;
	il_I = pamiec::il_I - zajetosc_pamieci;
	il_Q = pamiec::il_Q - zajetosc_pamieci;
	il_R = pamiec::il_R - zajetosc_pamieci;
	il_M = pamiec::il_M - zajetosc_pamieci;
	il_AI = pamiec::il_AI - zajetosc_pamieci;
	il_AQ = pamiec::il_AQ - zajetosc_pamieci;
	if (il_I<0)
		dozwolone_typy &= ~MOZNA_I;
	if (il_Q<0)
		dozwolone_typy &= ~MOZNA_Q;
	if (il_R<0)
		dozwolone_typy &= ~MOZNA_R;
	if (il_M<0)
		dozwolone_typy &= ~MOZNA_M;
	if (il_AI<0)
		dozwolone_typy &= ~MOZNA_AI;
	if (il_AQ<0)
		dozwolone_typy &= ~MOZNA_AQ;
	valid = aktualna->valid;
	if (DialogBox(instancja, MAKEINTRESOURCE(IDD_PAMIEC), okno, (DLGPROC) ProcPamieci))
	{
		aktualna->adres_pamieci = adres_pamieci;
		aktualna->typ_pamieci = typ_pamieci;
		aktualna->valid = TRUE;
	}
}

BOOL CALLBACK ProcPamieci(HWND okno, UINT komunikat, WPARAM wParam, LPARAM lParam)
{
	static int oszukanstwo = FALSE;
	switch (komunikat)
	{
	case WM_INITDIALOG:
		{
			if (!(dozwolone_typy&MOZNA_I))
				EnableWindow(GetDlgItem(okno, IDC_RADIO_I), FALSE);
			if (!(dozwolone_typy&MOZNA_Q))
				EnableWindow(GetDlgItem(okno, IDC_RADIO_Q), FALSE);
			if (!(dozwolone_typy&MOZNA_R))
				EnableWindow(GetDlgItem(okno, IDC_RADIO_R), FALSE);
			if (!(dozwolone_typy&MOZNA_M))
				EnableWindow(GetDlgItem(okno, IDC_RADIO_M), FALSE);
			if (!(dozwolone_typy&MOZNA_AI))
				EnableWindow(GetDlgItem(okno, IDC_RADIO_AI), FALSE);
			if (!(dozwolone_typy&MOZNA_AQ))
				EnableWindow(GetDlgItem(okno, IDC_RADIO_AQ), FALSE);
			if (!(dozwolone_typy&MOZNA_CONST))
				EnableWindow(GetDlgItem(okno, IDC_RADIO_CONST), FALSE);
			if (!valid)
			{
				adres_pamieci = 0;
				if (dozwolone_typy&MOZNA_I)
					SendDlgItemMessage(okno, IDC_RADIO_I, BM_CLICK, 0, 0);
				else
					if (dozwolone_typy&MOZNA_Q)
						SendDlgItemMessage(okno, IDC_RADIO_Q, BM_CLICK, 0, 0);
					else
						if (dozwolone_typy&MOZNA_R)
							SendDlgItemMessage(okno, IDC_RADIO_R, BM_CLICK, 0, 0);
						else
							if (dozwolone_typy&MOZNA_M)
								SendDlgItemMessage(okno, IDC_RADIO_M, BM_CLICK, 0, 0);
							else
								if (dozwolone_typy&MOZNA_AI)
									SendDlgItemMessage(okno, IDC_RADIO_AI, BM_CLICK, 0, 0);
								else
									if (dozwolone_typy&MOZNA_AQ)
										SendDlgItemMessage(okno, IDC_RADIO_AQ, BM_CLICK, 0, 0);
									else
										if (dozwolone_typy&MOZNA_CONST)
											SendDlgItemMessage(okno, IDC_RADIO_CONST, BM_CLICK, 0, 0);
										else
										{
											EnableWindow(GetDlgItem(okno, IDC_ADRES), FALSE);
											ShowWindow(GetDlgItem(okno, IDC_TEXT), SW_HIDE);
										}
			}
			else
			{
				switch (typ_pamieci)
				{
				case typ_I:
					SendDlgItemMessage(okno, IDC_RADIO_I, BM_CLICK, 0, 0);
					break;
				case typ_Q:
					SendDlgItemMessage(okno, IDC_RADIO_Q, BM_CLICK, 0, 0);
					break;
				case typ_R:
					SendDlgItemMessage(okno, IDC_RADIO_R, BM_CLICK, 0, 0);
					break;
				case typ_M:
					SendDlgItemMessage(okno, IDC_RADIO_M, BM_CLICK, 0, 0);
					break;
				case typ_AI:
					SendDlgItemMessage(okno, IDC_RADIO_AI, BM_CLICK, 0, 0);
					break;
				case typ_AQ:
					SendDlgItemMessage(okno, IDC_RADIO_AQ, BM_CLICK, 0, 0);
					break;
				case typ_CONST:
					SendDlgItemMessage(okno, IDC_RADIO_CONST, BM_CLICK, 0, 0);
					break;
				}
				SendDlgItemMessage(okno, IDC_MSCTLS_UPDOWN1, UDM_SETPOS, 0, MAKELONG(adres_pamieci, 0));
			}
			SendDlgItemMessage(okno, IDC_PREDEFINIOWANE, CB_INSERTSTRING, 0, (LPARAM)L"W³asne ustawienie");
			opis_komorki * akt = pamiec::lista_opisow;
			int i = 1;
			int q = 1;
			while (akt)
			{
				if ((akt->typ) & dozwolone_typy)
				{
					SendDlgItemMessage(okno, IDC_PREDEFINIOWANE, CB_INSERTSTRING, i, (LPARAM) akt->opis.c_str());
					SendDlgItemMessage(okno, IDC_PREDEFINIOWANE, CB_SETITEMDATA, i, q);
					i++;
				}
				q++;
				akt = akt->nastepny;
			}
			SendDlgItemMessage(okno, IDC_PREDEFINIOWANE, CB_SETCURSEL, 0, 0);
			break;
		}
	case WM_CLOSE:
		EndDialog(okno, FALSE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			{
				if (IsWindowEnabled(GetDlgItem(okno, IDC_ADRES)))
				{
					valid = TRUE;
					adres_pamieci = (signed short)SendDlgItemMessage(okno, IDC_MSCTLS_UPDOWN1, UDM_GETPOS, 0, 0);
				}
				else
				{
					valid = FALSE;
				}
				EndDialog(okno, TRUE);
				break;
			}
		case IDCANCEL:
			EndDialog(okno, FALSE);
			break;
		case IDC_RADIO_I:
			SetDlgItemText(okno, IDC_TEXT, L"Wybierz numer wejœcia :");
			SendDlgItemMessage(okno, IDC_MSCTLS_UPDOWN1, UDM_SETRANGE, 0, MAKELONG(il_I, 0));
			typ_pamieci = typ_I;
			if (!oszukanstwo)
				SendDlgItemMessage(okno, IDC_PREDEFINIOWANE, CB_SETCURSEL, 0, 0);
			SetDlgItemText(okno, IDC_ADRES, L"0");
			break;
		case IDC_RADIO_Q:
			SetDlgItemText(okno, IDC_TEXT, L"Wybierz numer wyjœcia :");
			SendDlgItemMessage(okno, IDC_MSCTLS_UPDOWN1, UDM_SETRANGE, 0, MAKELONG(il_Q, 0));
			typ_pamieci = typ_Q;
			if (!oszukanstwo)
				SendDlgItemMessage(okno, IDC_PREDEFINIOWANE, CB_SETCURSEL, 0, 0);
			SetDlgItemText(okno, IDC_ADRES, L"0");
			break;
		case IDC_RADIO_R:
			SetDlgItemText(okno, IDC_TEXT, L"Wybierz adres komórki :");
			SendDlgItemMessage(okno, IDC_MSCTLS_UPDOWN1, UDM_SETRANGE, 0, MAKELONG(il_R, 0));
			typ_pamieci = typ_R;
			if (!oszukanstwo)
				SendDlgItemMessage(okno, IDC_PREDEFINIOWANE, CB_SETCURSEL, 0, 0);
			SetDlgItemText(okno, IDC_ADRES, L"0");
			break;
		case IDC_RADIO_M:
			SetDlgItemText(okno, IDC_TEXT, L"Wybierz adres komórki :");
			SendDlgItemMessage(okno, IDC_MSCTLS_UPDOWN1, UDM_SETRANGE, 0, MAKELONG(il_M, 0));
			typ_pamieci = typ_M;
			if (!oszukanstwo)
				SendDlgItemMessage(okno, IDC_PREDEFINIOWANE, CB_SETCURSEL, 0, 0);
			SetDlgItemText(okno, IDC_ADRES, L"0");
			break;
		case IDC_RADIO_AI:
			SetDlgItemText(okno, IDC_TEXT, L"Wybierz numer wejœcia :");
			SendDlgItemMessage(okno, IDC_MSCTLS_UPDOWN1, UDM_SETRANGE, 0, MAKELONG(il_AI, 0));
			typ_pamieci = typ_AI;
			if (!oszukanstwo)
				SendDlgItemMessage(okno, IDC_PREDEFINIOWANE, CB_SETCURSEL, 0, 0);
			SetDlgItemText(okno, IDC_ADRES, L"0");
			break;
		case IDC_RADIO_AQ:
			SetDlgItemText(okno, IDC_TEXT, L"Wybierz numer wyjœcia :");
			SendDlgItemMessage(okno, IDC_MSCTLS_UPDOWN1, UDM_SETRANGE, 0, MAKELONG(il_AQ, 0));
			typ_pamieci = typ_AQ;
			if (!oszukanstwo)
				SendDlgItemMessage(okno, IDC_PREDEFINIOWANE, CB_SETCURSEL, 0, 0);
			SetDlgItemText(okno, IDC_ADRES, L"0");
			break;
		case IDC_RADIO_CONST:
			SetDlgItemText(okno, IDC_TEXT, L"Podaj sta³¹ :");
			SendDlgItemMessage(okno, IDC_MSCTLS_UPDOWN1, UDM_SETRANGE, 0, MAKELONG(9999, -9999));
			typ_pamieci = typ_CONST;
			if (!oszukanstwo)
				SendDlgItemMessage(okno, IDC_PREDEFINIOWANE, CB_SETCURSEL, 0, 0);
			SetDlgItemText(okno, IDC_ADRES, L"0");
			break;
		case IDC_ADRES:
			if (HIWORD(wParam) == EN_CHANGE)
			{
				if (!oszukanstwo)
					SendDlgItemMessage(okno, IDC_PREDEFINIOWANE, CB_SETCURSEL, 0, 0);
				oszukanstwo = FALSE;
			}
			break;
		case IDC_PREDEFINIOWANE:
			{
				if (HIWORD(wParam) == CBN_SELCHANGE)
				{
					int wybr = SendDlgItemMessage(okno, IDC_PREDEFINIOWANE, CB_GETCURSEL, 0, 0);
					if (wybr)
					{
						int wybrany = SendDlgItemMessage(okno, IDC_PREDEFINIOWANE, CB_GETITEMDATA, wybr, 0);
						opis_komorki * akt;
						int i;
						for (akt = pamiec::lista_opisow, i=1; i<wybrany; i++, akt = akt->nastepny);
						oszukanstwo = TRUE;
						switch (akt->typ)
						{
						case typ_I:
							SendDlgItemMessage(okno, IDC_RADIO_I, BM_CLICK, 0, 0);
							break;
						case typ_Q:
							SendDlgItemMessage(okno, IDC_RADIO_Q, BM_CLICK, 0, 0);
							break;
						case typ_R:
							SendDlgItemMessage(okno, IDC_RADIO_R, BM_CLICK, 0, 0);
							break;
						case typ_M:
							SendDlgItemMessage(okno, IDC_RADIO_M, BM_CLICK, 0, 0);
							break;
						case typ_AI:
							SendDlgItemMessage(okno, IDC_RADIO_AI, BM_CLICK, 0, 0);
							break;
						case typ_AQ:
							SendDlgItemMessage(okno, IDC_RADIO_AQ, BM_CLICK, 0, 0);
							break;
						case typ_CONST:
							SendDlgItemMessage(okno, IDC_RADIO_CONST, BM_CLICK, 0, 0);
							break;
						}
						oszukanstwo = TRUE;
						SetDlgItemInt(okno, IDC_ADRES, akt->adres, TRUE);
					}
				}
				break;
			}
		default:
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

void pamiec::dodaj_opis(typy_pamieci typ, int adres, wstring opis)
{
	if (!koniec_listy)
	{
		lista_opisow = new opis_komorki;
		koniec_listy = lista_opisow;
	}
	else
	{
		koniec_listy->nastepny = new opis_komorki;
		koniec_listy = koniec_listy->nastepny;
	}
	koniec_listy->nastepny = NULL;
	koniec_listy->typ = typ;
	koniec_listy->adres = adres;
	koniec_listy->opis = opis;
}

wstring pamiec::poszukaj_opisu(typy_pamieci typ, int adres)
{
	opis_komorki * akt = lista_opisow;
	while (akt)
	{
		if ((akt->typ == typ)&&(akt->adres==adres))
			return akt->opis;
		akt = akt->nastepny;
	}
	return L"";
}

void pamiec::usun_opisy(void)
{
	opis_komorki * akt = lista_opisow;
	while (akt)
	{
		opis_komorki * nast = akt->nastepny;
		delete akt;
		akt = nast;
	}
	lista_opisow = NULL;
	koniec_listy = NULL;
}

void pamiec::zapisz(FILE * plik)
{
	fwrite(&adres_pamieci, sizeof(adres_pamieci), 1, plik);
	fwrite(&zajetosc_pamieci, sizeof(zajetosc_pamieci), 1, plik);
	fwrite(&typ_pamieci, sizeof(typ_pamieci), 1, plik);
	fwrite(&dozwolone_typy, sizeof(dozwolone_typy), 1, plik);
	fwrite(&valid, sizeof(valid), 1, plik);
	fwrite(nazwa_komorki.c_str(), 2, nazwa_komorki.length()+1, plik);
}

pamiec::pamiec(FILE * plik)
{
	fread(&adres_pamieci, sizeof(adres_pamieci), 1, plik);
	fread(&zajetosc_pamieci, sizeof(zajetosc_pamieci), 1, plik);
	fread(&typ_pamieci, sizeof(typ_pamieci), 1, plik);
	fread(&dozwolone_typy, sizeof(dozwolone_typy), 1, plik);
	fread(&valid, sizeof(valid), 1, plik);
	wchar_t bufor[256];
	int i=0;
	do
	{
		wchar_t letter = fgetc(plik) | (fgetc(plik) << 8);
		bufor[i] = letter;
		i++;
	} while (bufor[i-1]);
	nazwa_komorki = bufor;
}

