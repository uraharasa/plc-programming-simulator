#include "polaczenia.h"
#include "okno_glowne.h"

element::element(void)
{
}

wstring element::podaj_nazwe(void)
{
	return nazwa;
}

element_zwykly::element_zwykly(): adres_bazowy(NULL), wejscia(NULL), wyjscia(NULL), il_wejsc(0), il_wyjsc(0)
{
}

element_zwykly::~element_zwykly()
{
	if (adres_bazowy)
		delete adres_bazowy;
	if (il_wejsc)
	{
		pamiec * * akt = wejscia;
		while (il_wejsc)
		{
			il_wejsc--;
			delete *(akt+il_wejsc);
		}
		delete wejscia;
	}
	if (il_wyjsc)
	{
		pamiec * * akt = wyjscia;
		while (il_wyjsc)
		{
			il_wyjsc--;
			delete *(akt+il_wyjsc);
		}
		delete wyjscia;
	}
}

void element_zwykly::dodaj_hotspot(int x, int y)
{
	int szer, wys;
	podaj_rozmiar(szer, wys);
	akt_program_LD->hotspot.dodaj(x, y, szer, wys, this);
}

ZDARZENIE element_zwykly::edytuj(int , int , ZDARZENIE zdarzenie, element * &edytowany)
{
	switch (zdarzenie)
	{
	case SKASUJ_GO:
		return SKASUJ_MNIE;
	case DODAJ_SZEREGOWO:
		edytowany = new polaczenie_szeregowe(this, edytowany);
		return ZASTAP_MNIE_I_NIE_KASUJ;
	case DODAJ_ROWNOLEGLE:
		edytowany = new polaczenie_rownolegle(this, edytowany);
		return ZASTAP_MNIE_I_NIE_KASUJ;
	}
	return NIC_NIE_ROB;
}

void element_zwykly::zapisz(FILE * plik)
{
	int stala;
	fwrite(nazwa.c_str(), 2, nazwa.length()+1, plik);
	if (adres_bazowy)
	{
		stala = 1;
		fwrite(&stala, sizeof(stala), 1, plik);
		adres_bazowy->zapisz(plik);
	}
	else
	{
		stala = 0;
		fwrite(&stala, sizeof(stala), 1, plik);
	}
	fwrite(&il_wejsc, sizeof(il_wejsc), 1, plik);
	for (int i=0; i<il_wejsc; i++)
		(*(wejscia + i))->zapisz(plik);
	fwrite(&il_wyjsc, sizeof(il_wejsc), 1, plik);
	for (int i=0; i<il_wyjsc; i++)
		(*(wyjscia + i))->zapisz(plik);
}

element_zwykly::element_zwykly(FILE * plik)
{
	int stala;
	fread(&stala, sizeof(stala), 1, plik);
	if (stala)
		adres_bazowy = new pamiec(plik);
	else
		adres_bazowy = NULL;
	fread(&il_wejsc, sizeof(il_wejsc), 1, plik);
	if (il_wejsc)
	{
		wejscia = new pamiec *[il_wejsc];
		for (int i = 0; i<il_wejsc; i++)
			*(wejscia + i) = new pamiec(plik);
	}
	else
		wejscia = NULL;
	fread(&il_wyjsc, sizeof(il_wyjsc), 1, plik);
	if (il_wyjsc)
	{
		wyjscia = new pamiec *[il_wyjsc];
		for (int i = 0; i<il_wyjsc; i++)
			*(wyjscia + i) = new pamiec(plik);
	}
	else
		wyjscia = NULL;
}

