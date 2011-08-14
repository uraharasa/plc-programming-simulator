#include "lekcja4.h"
#include "pamiec.h"

const float temperatura_wody_doplywu = 16; // oC
const float cieplo_wlasciwe = 4190; // [J/(kg * K)]
const float masa_piksla = 1; // [kg]
const float moc_grzalki = 1000; // [W]

void lekcja4::zresetuj()
	{
   kat_obrotu = 0;
   poziom_wody = 0;
   nastaw_temperatury = 0;
   predkosc_obrotowa = 0;
   wskazanie_temperatury_wody = temperatura_wody = temperatura_wody_doplywu;
   przycisk = FALSE;
   spalona_grzalka = FALSE;
   lekcja::zresetuj();
   }

BOOL lekcja4::click(int x, int y)
	{
   if ((x >= 51) && (x < 150) && (y >= 16) && (y < 25))
   	{
      nastaw_temperatury = x-51;
      return TRUE;
      }
   if ((x>=10) && (y>=10) && (x<=30) && (y<=30))
   	przycisk = TRUE;
   return FALSE;
   }

lekcja4::lekcja4() : tlo(L"lekcja4\\tlo"),
							lampka_czerwona(L"lekcja4\\lampka_czerwona"),
							lampka_zielona(L"lekcja4\\lampka_zielona"),
                     ubrania1(L"lekcja4\\ubrania1"),
                     ubrania2(L"lekcja4\\ubrania2"),
                     ubrania3(L"lekcja4\\ubrania3"),
                     ubrania4(L"lekcja4\\ubrania4"),
                     ubrania5(L"lekcja4\\ubrania5"),
                     ubrania6(L"lekcja4\\ubrania6"),
                     ubrania7(L"lekcja4\\ubrania7"),
                     ubrania8(L"lekcja4\\ubrania8"),
                     ubrania9(L"lekcja4\\ubrania9"),
                     ubrania10(L"lekcja4\\ubrania10"),
                     ubrania11(L"lekcja4\\ubrania11"),
                     ubrania12(L"lekcja4\\ubrania12"),
                     woda(L"lekcja4\\woda")
	{
   nazwa = L"lekcja4";
   pamiec::nowe_parametry_sterownika(1, 5, 100, 100, 3, 0);
   wejscia_I = new pamiec(typ_I, 0, 1);
   wejscia_AI = new pamiec(typ_AI, 0, 3);
   wyjscia_Q = new pamiec(typ_Q, 0, 5);
   pamiec::dodaj_opis(typ_I, 0, L"PRANIE");
   pamiec::dodaj_opis(typ_AI, 0, L"POZIOM");
   pamiec::dodaj_opis(typ_AI, 1, L"CZUJ_TEMP");
   pamiec::dodaj_opis(typ_AI, 2, L"NAST_TEMP");
   pamiec::dodaj_opis(typ_Q, 0, L"BÊBEN");
   pamiec::dodaj_opis(typ_Q, 1, L"KIER_BÊB");
   pamiec::dodaj_opis(typ_Q, 2, L"GRZA£KA");
   pamiec::dodaj_opis(typ_Q, 3, L"DOP£YW");
   pamiec::dodaj_opis(typ_Q, 4, L"ODP£YW");
   zresetuj();
   }

lekcja4::~lekcja4()
	{
   pamiec::nowe_parametry_sterownika(0, 0, 0, 0, 0, 0);
   }

void lekcja4::podaj_rozmiar_okna(int & szerokosc, int & wysokosc)
	{
   szerokosc = 200;
   wysokosc = 240;
   }

void lekcja4::dzialaj()
	{
   if (!spalona_grzalka)
   	{
	   if (przycisk)
	   	{
	   	wejscia_I->zapisz_pamiec(1, 0);
	      przycisk = FALSE;
	      }
	   else
	   	wejscia_I->zapisz_pamiec(0, 0);
	   kat_obrotu += (float)predkosc_obrotowa / 10.0;
	   while (kat_obrotu >= 360)
	   	kat_obrotu -= 360;
	   while (kat_obrotu < 0)
	   	kat_obrotu += 360;
		if (wyjscia_Q->odczytaj_pamiec(0))
	   	if (wyjscia_Q->odczytaj_pamiec(1))
	      	predkosc_obrotowa += 3;
	      else
	      	predkosc_obrotowa -= 3;
	   else
	   	if (predkosc_obrotowa > 0)
	      	predkosc_obrotowa -= 1;
	      else
	      	if (predkosc_obrotowa < 0)
		      	predkosc_obrotowa += 1;
	   if (predkosc_obrotowa > 100)
	   	predkosc_obrotowa = 100;
	   if (predkosc_obrotowa < -100)
	   	predkosc_obrotowa = -100;
	   if (wyjscia_Q->odczytaj_pamiec(3))
	   	{
	      temperatura_wody = (temperatura_wody*(poziom_wody/10)+0.1*temperatura_wody_doplywu)/((poziom_wody/10)+0.1);
	      poziom_wody += 1;
	      }
	   if (wyjscia_Q->odczytaj_pamiec(4))
	   	poziom_wody -= 2;
	   if (poziom_wody < 0)
	   	poziom_wody = 0;
	   if (poziom_wody > 500)
	   	poziom_wody = 500;
	   if (wyjscia_Q->odczytaj_pamiec(2))
	   	if (poziom_wody > 0.1)
		   	temperatura_wody += moc_grzalki / ((poziom_wody/10) * masa_piksla * cieplo_wlasciwe);
	      else
	      	spalona_grzalka = TRUE;
	   wskazanie_temperatury_wody += (temperatura_wody-wskazanie_temperatury_wody)*0.01;
      if (wskazanie_temperatury_wody > 90)
      	wskazanie_temperatury_wody = 90;
      if (wskazanie_temperatury_wody < 10)
      	wskazanie_temperatury_wody = 10;
      if (temperatura_wody > 100)
      	spalona_grzalka = TRUE;
      wejscia_AI->zapisz_pamiec(wskazanie_temperatury_wody, 1);
      wejscia_AI->zapisz_pamiec(poziom_wody, 0);
      wejscia_AI->zapisz_pamiec(nastaw_temperatury, 2);
      }
   lekcja::dzialaj();
   }

void lekcja4::narysuj(HDC kontekst)
	{
   tlo.wyswietl(kontekst, 0, 0);
   switch ((int)(kat_obrotu / 30))
   	{
      case 0:
      	ubrania1.wyswietl(kontekst, 55, 116);
         break;
      case 1:
      	ubrania2.wyswietl(kontekst, 55, 116);
         break;
      case 2:
      	ubrania3.wyswietl(kontekst, 55, 116);
         break;
      case 3:
      	ubrania4.wyswietl(kontekst, 55, 116);
         break;
      case 4:
      	ubrania5.wyswietl(kontekst, 55, 116);
         break;
      case 5:
      	ubrania6.wyswietl(kontekst, 55, 116);
         break;
      case 6:
      	ubrania7.wyswietl(kontekst, 55, 116);
         break;
      case 7:
      	ubrania8.wyswietl(kontekst, 55, 116);
         break;
      case 8:
      	ubrania9.wyswietl(kontekst, 55, 116);
         break;
      case 9:
      	ubrania10.wyswietl(kontekst, 55, 116);
         break;
      case 10:
      	ubrania11.wyswietl(kontekst, 55, 116);
         break;
      case 11:
      	ubrania12.wyswietl(kontekst, 55, 116);
         break;
      }
   if (wyjscia_Q->odczytaj_pamiec(2))
   	lampka_czerwona.wyswietl(kontekst, 25, 55);
   else
   	lampka_zielona.wyswietl(kontekst, 25, 55);
   if (wyjscia_Q->odczytaj_pamiec(3))
   	lampka_czerwona.wyswietl(kontekst, 135, 72);
   else
   	lampka_zielona.wyswietl(kontekst, 135, 72);
   if (wyjscia_Q->odczytaj_pamiec(4))
   	lampka_czerwona.wyswietl(kontekst, 135, 192);
   else
   	lampka_zielona.wyswietl(kontekst, 135, 192);
   int poziom = poziom_wody/10;
   woda.wyswietl(kontekst, 55, 116+50-poziom, 50, poziom, 0, 50-poziom);
   RECT obszar;
   obszar.left = 51+nastaw_temperatury;
   obszar.right = obszar.left + 2;
   obszar.top = 16;
   obszar.bottom = 25;
   HBRUSH pedzel = CreateSolidBrush(0xff);
   FillRect(kontekst, &obszar, pedzel);
   obszar.left = 20;
   obszar.right = 25;
   obszar.top = 100 + 80 - wskazanie_temperatury_wody + 10;
   obszar.bottom = 180;
   FillRect(kontekst, &obszar, pedzel);
   DeleteObject(pedzel);
   if (spalona_grzalka)
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
      TextOut(kontekst, 20, 180, L"Spali³eœ grza³kê !!!", wcslen(L"Spali³eœ grza³kê !!!"));
      DeleteObject(SelectObject(kontekst, stara));
      }
   }
