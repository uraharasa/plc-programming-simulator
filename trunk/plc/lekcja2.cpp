#include "lekcja2.h"
#include "pamiec.h"

void lekcja2::zresetuj()
{
	poziom_wody = 0;
	rozlana = FALSE;
	ulamki = 0;
	doplyw = FALSE;
	odplyw = FALSE;
	wymiana = FALSE;
	napelnij = FALSE;
	oproznij = FALSE;
	lekcja::zresetuj();
}

BOOL lekcja2::click(int x, int y)
{
	if ((x>=160)&&(x<210))
	{
		if (y < 50)
			napelnij = TRUE;
		if ((y>=50)&&(y<100))
			oproznij = TRUE;
		if ((y>=100)&&(y<150))
		{
			wymiana = !wymiana;
			return TRUE;
		}
	}
	return FALSE;
}

lekcja2::lekcja2() : doplyw_zamkniety(L"lekcja2\\basen"), doplyw_otwarty(L"lekcja2\\basen_doplyw"), odplyw_otwarty(L"lekcja2\\basen_z_woda_otwarty"), odplyw_zamkniety(L"lekcja2\\basen_z_woda_zamkniety"),
	zawor_zamkniety(L"lekcja2\\zawor_zamkniety"), zawor_otwarty(L"lekcja2\\zawor_otwarty"), przycisk_napelnij(L"lekcja2\\button_napelnij"), przycisk_oproznij(L"lekcja2\\button_oproznij"),
	przycisk_wymiana_on(L"lekcja2\\button_wymiana_on"), przycisk_wymiana_off(L"lekcja2\\button_wymiana_off")
{
	nazwa = L"lekcja2";
	pamiec::nowe_parametry_sterownika(5, 2, 100, 100, 0, 0);
	wejscia_I = new pamiec(typ_I, 0, 5);
	wyjscia_Q = new pamiec(typ_Q, 0, 2);
	pamiec::dodaj_opis(typ_I, 0, L"CZUJ_GÓRA");
	pamiec::dodaj_opis(typ_I, 1, L"CZUJ_DÓ£");
	pamiec::dodaj_opis(typ_I, 2, L"NAPE£NIJ");
	pamiec::dodaj_opis(typ_I, 3, L"OPRÓ¯NIJ");
	pamiec::dodaj_opis(typ_I, 4, L"WYMIANA");
	pamiec::dodaj_opis(typ_Q, 0, L"DOP£YW");
	pamiec::dodaj_opis(typ_Q, 1, L"ODP£YW");
	zresetuj();
}

lekcja2::~lekcja2()
{
	pamiec::nowe_parametry_sterownika(0, 0,0, 0, 0, 0);
}

void lekcja2::podaj_rozmiar_okna(int & szerokosc, int & wysokosc)
{
	szerokosc = 210;
	wysokosc = 160;
}

void lekcja2::dzialaj()
{
	if (!rozlana)
	{
		if (napelnij)
			wejscia_I->zapisz_pamiec(TRUE, 2);
		else
			wejscia_I->zapisz_pamiec(FALSE, 2);
		napelnij = FALSE;
		if (oproznij)
			wejscia_I->zapisz_pamiec(TRUE, 3);
		else
			wejscia_I->zapisz_pamiec(FALSE, 3);
		oproznij = FALSE;
		wejscia_I->zapisz_pamiec(wymiana, 4);
		doplyw = wyjscia_Q->odczytaj_pamiec(0);
		odplyw = wyjscia_Q->odczytaj_pamiec(1);
		if (doplyw)
		{
			ulamki++;
			if (ulamki >= 10)
			{
				poziom_wody++;
				ulamki = 0;
			}
		}
		if (poziom_wody > 100)
			rozlana = TRUE;
		if (odplyw&&(poziom_wody>0))
		{
			ulamki --;
			if (ulamki < 0)
			{
				poziom_wody--;
				ulamki = 9;
			}
		}
		if (poziom_wody > 92)
			wejscia_I->zapisz_pamiec(TRUE, 0);
		else
			wejscia_I->zapisz_pamiec(FALSE, 0);
		if (poziom_wody > 22)
			wejscia_I->zapisz_pamiec(TRUE, 1);
		else
			wejscia_I->zapisz_pamiec(FALSE, 1);
	}
	lekcja::dzialaj();
}

void lekcja2::narysuj(HDC kontekst)
{
	RECT obszar;
	obszar.top = obszar.left = 0;
	int x, y;
	podaj_rozmiar_okna(x, y);
	obszar.right = x;
	obszar.bottom = y;
	FillRect(kontekst, &obszar, (HBRUSH)GetStockObject(WHITE_BRUSH));
	przycisk_napelnij.wyswietl(kontekst, 160, 0);
	przycisk_oproznij.wyswietl(kontekst, 160, 50);
	if (wymiana)
		przycisk_wymiana_on.wyswietl(kontekst, 160, 100);
	else
		przycisk_wymiana_off.wyswietl(kontekst, 160, 100);
	doplyw_otwarty.wyswietl(kontekst, 0, 0, -1, 25);
	if (doplyw)
		doplyw_otwarty.wyswietl(kontekst, 0, 25, -1, 25+100-poziom_wody, 0, 25);
	else
		doplyw_zamkniety.wyswietl(kontekst, 0, 25, -1, 25+100-poziom_wody, 0, 25);
	if (poziom_wody > 0)
	{
		if (odplyw)
			odplyw_otwarty.wyswietl(kontekst, 0, 50+100-poziom_wody, -1, poziom_wody + 10, 0, 50+100-poziom_wody);
		else
			odplyw_zamkniety.wyswietl(kontekst, 0, 50+100-poziom_wody, -1, poziom_wody + 10, 0, 50+100-poziom_wody);
	}
	else
		odplyw_zamkniety.wyswietl(kontekst, 0, 150, -1, 10, 0, 150);
	if (doplyw)
		zawor_otwarty.wyswietl(kontekst, 21, 21);
	else
		zawor_zamkniety.wyswietl(kontekst, 21, 21);
	if (odplyw)
		zawor_otwarty.wyswietl(kontekst, 121, 101);
	else
		zawor_zamkniety.wyswietl(kontekst, 121, 101);
	if (rozlana)
	{
		LOGFONT lf;
		memset(&lf, 0, sizeof(LOGFONT));
		lf.lfHeight = 29;
		lf.lfWeight = FW_NORMAL;
		lf.lfCharSet = DEFAULT_CHARSET;
		wcscpy(lf.lfFaceName, L"Arial CE");
		lf.lfEscapement = lf.lfOrientation = 450;
		HFONT stara = (HFONT)SelectObject(kontekst, CreateFontIndirect(&lf));
		SetBkMode(kontekst, TRANSPARENT);
		SetTextColor(kontekst, 0xff);
		TextOut(kontekst, 0, 140, L"Rozla³eœ wodê !!!", wcslen(L"Rozla³eœ wodê !!!"));
		DeleteObject(SelectObject(kontekst, stara));
	}
}

