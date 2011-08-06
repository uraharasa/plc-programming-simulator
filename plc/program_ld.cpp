#include "program_LD.h"
#include "okno_glowne.h"
#include "zmiana_parametrow.h"
#include "resource.h"
#include "help.h"

int autoscroll;
POINTS poprzednie_wspolrzedne;

program_LD::program_LD(HWND okno_programu_LD)
	{
	lista_rungow = NULL;
	poprawnosc_wymiarow = FALSE;
   okno = okno_programu_LD;
   dragging = FALSE;
	}

program_LD::~program_LD(void)
	{
	rung * aktualny, * nastepny;
	aktualny = lista_rungow;
	while (aktualny)
		{
		nastepny = aktualny->nastepny;
		delete aktualny;
		aktualny = nastepny;
		}
	}

void program_LD::narysuj(void)
	{
   PAINTSTRUCT rysowanie;
   HDC kontekst = BeginPaint(okno, &rysowanie);
	RECT obszar;
   GetClientRect(okno, &obszar);
   MoveToEx(kontekst, mapuj_x(0), 0, NULL);
   LineTo(kontekst, mapuj_x(0), obszar.bottom);
   MoveToEx(kontekst, mapuj_x(x_cewek()+1), 0, NULL);
   LineTo(kontekst, mapuj_x(x_cewek()+1), obszar.bottom);
   HFONT stara_czcionka = (HFONT)GetCurrentObject(kontekst, OBJ_FONT);
   SelectObject(kontekst, GetStockObject(DEFAULT_GUI_FONT));
   HPEN pioro = CreatePen(PS_DOT, 1, 0xff7f7f);
   HPEN stare_pioro = (HPEN)GetCurrentObject(kontekst, OBJ_PEN);
   SelectObject(kontekst, pioro);
   MoveToEx(kontekst, mapuj_x(x_cewek()), mapuj_y(0), NULL);
   LineTo(kontekst, mapuj_x(x_cewek()), obszar.bottom);
   SelectObject(kontekst, stare_pioro);
   DeleteObject(pioro);
	int akt_y = 0;
	int szerokosc, wysokosc;
	rung * aktualny = lista_rungow;
	while (aktualny)
		{
		aktualny->narysuj(kontekst, 0, 0, akt_y);
		aktualny->podaj_rozmiar(szerokosc, wysokosc);
		akt_y += wysokosc;
		aktualny = aktualny->nastepny;
		}
   SelectObject(kontekst, stara_czcionka);
   EndPaint(okno, &rysowanie);
	}

void program_LD::odswiez_hotspots(void)
	{
   hotspot.wyczysc();
   rung * akt = lista_rungow;
   int akt_y = 0;
   while (akt)
   	{
      int szer, wys;
      akt->podaj_rozmiar(szer, wys);
      akt->dodaj_hotspot(0, akt_y);
      akt_y += wys;
      akt = akt->nastepny;
      }
   }

int program_LD::mapuj_x(int x)
	{
   if (dragging)
   	return dragging_wspolrzedne.x;
   else
		return x*SZEROKOSC_ELEMENTU+MARGINES_LEWY-scroll_x;
	}

int program_LD::mapuj_y(int y)
	{
   if (dragging)
   	return dragging_wspolrzedne.y;
   else
		return y*WYSOKOSC_ELEMENTU-scroll_y;
	}

int program_LD::remapuj_x(int x)
	{
   return x-MARGINES_LEWY+scroll_x;
   }

int program_LD::remapuj_y(int y)
	{
   return y+scroll_y;
   }

int program_LD::x_cewek(void)
	{
	if (!poprawnosc_wymiarow)
		{
		poprawnosc_wymiarow = TRUE;
      popraw_wymiary();
		}
	return wartosc_x_cewek;
	}

int program_LD::podaj_szerokosc(void)
	{
   if (!poprawnosc_wymiarow)
   	{
      poprawnosc_wymiarow = TRUE;
      popraw_wymiary();
      }
   return szerokosc_programu;
   }

int program_LD::podaj_wysokosc(void)
	{
   if (!poprawnosc_wymiarow)
   	{
      poprawnosc_wymiarow = TRUE;
      popraw_wymiary();
      }
   return wysokosc_programu;
   }

void program_LD::popraw_wymiary(void)
	{
	wartosc_x_cewek = 1;
   wysokosc_programu = 0;
	rung * aktualny = lista_rungow;
	while (aktualny)
		{
		int szerokosc, wysokosc;
		aktualny->podaj_rozmiar(szerokosc, wysokosc);
      wysokosc_programu += wysokosc;
		if (szerokosc>wartosc_x_cewek)
			wartosc_x_cewek = szerokosc;
		aktualny = aktualny->nastepny;
      }
   szerokosc_programu = wartosc_x_cewek+1;
   }

LRESULT CALLBACK program_LD::obsluz_komunikat(HWND okno, UINT komunikat, WPARAM wParam, LPARAM lParam)
	{
   switch (komunikat)
   	{
      case WM_PAINT:
			narysuj();
      	break;
      case WM_SIZE:
      	ustaw_scrollbary();
      	break;
      case WM_LBUTTONDOWN:
      	BringWindowToTop(okno);
         SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEALL)));
         autoscroll = TRUE;
         poprzednie_wspolrzedne = MAKEPOINTS(lParam);
         SetCapture(okno);
      	break;
      case WM_HSCROLL:
      	{
         int pos = scroll_x;
         switch (LOWORD(wParam))
         	{
            case SB_LINELEFT:
            	pos -= 1;
               break;
            case SB_LINERIGHT:
            	pos += 1;
               break;
            case SB_PAGELEFT:
            	pos -= page_x;
               break;
            case SB_PAGERIGHT:
            	pos += page_x;
               break;
            case SB_THUMBPOSITION:
            	pos = HIWORD(wParam);
               break;
            case SB_LEFT:
            	pos = 0;
               break;
            case SB_RIGHT:
            	pos = max_x;
               break;
            case SB_THUMBTRACK:
            	pos = HIWORD(wParam);
               break;
            }
         if (pos<0)
         	pos = 0;
         if (pos>max_x-page_x)
           	pos = max_x-page_x;
         if (pos!=scroll_x)
         	{
	         SetScrollPos(okno, SB_HORZ, pos, TRUE);
            RECT obszar;
            GetClientRect(okno, &obszar);
            ScrollWindowEx(okno, scroll_x-pos, 0, NULL, &obszar, NULL, NULL, SW_ERASE|SW_INVALIDATE);
	         scroll_x = pos;
            }
         break;
         }
      case WM_VSCROLL:
      	{
         int pos = scroll_y;
         switch (LOWORD(wParam))
         	{
            case SB_LINEUP:
            	pos -= 1;
               break;
            case SB_LINEDOWN:
            	pos += 1;
               break;
            case SB_PAGEUP:
            	pos -= page_y;
               break;
            case SB_PAGEDOWN:
            	pos += page_y;
               break;
            case SB_THUMBPOSITION:
            	pos = HIWORD(wParam);
               break;
            case SB_TOP:
            	pos = 0;
               break;
            case SB_BOTTOM:
            	pos = max_y;
               break;
            case SB_THUMBTRACK:
            	pos = HIWORD(wParam);
               break;
            }
         if (pos<0)
         	pos = 0;
         if (pos>max_y-page_y)
           	pos = max_y-page_y;
         if (pos!=scroll_y)
         	{
	         SetScrollPos(okno, SB_VERT, pos, TRUE);
            RECT obszar;
            GetClientRect(okno, &obszar);
            ScrollWindowEx(okno, 0, scroll_y-pos, NULL, &obszar, NULL, NULL, SW_ERASE|SW_INVALIDATE);
	         scroll_y = pos;
            }
         break;
         }
      case WM_LBUTTONUP:
      	{
         if (dragging)
         	{
            if (!pierwszy_DRAG)
            	{
	            HDC kontekst_ekranu = GetDC(okno);
	            SetROP2(kontekst_ekranu, R2_NOTXORPEN);
	            nowy_element->narysuj(kontekst_ekranu, 0, 0, 0);
               narysuj_kreski(okno, dragging_wspolrzedne.x, dragging_wspolrzedne.y);
	            ReleaseDC(NULL, kontekst_ekranu);
               }
            dragging = FALSE;
            ReleaseCapture();
				int drop_x, drop_y;
            drop_x = remapuj_x(LOWORD(lParam));
            drop_y = remapuj_y(HIWORD(lParam));
            RECT obszar;
            GetClientRect(okno, &obszar);
            if ((LOWORD(lParam)<obszar.right)&&(LOWORD(lParam)>=0)&&(HIWORD(lParam)<obszar.bottom)&&(HIWORD(lParam)>=0))
            	{
               element_zwykly * cel;
               ZDARZENIE zdarzenie;
               if (znajdz_cel_drag_and_drop(drop_x, drop_y, cel, zdarzenie))
               	{
                  switch (zdarzenie)
                  	{
                     case DODAJ_RUNG_ELEMENT:
                     	{
                        rung * akt = lista_rungow;
                        rung * * wskaz = &lista_rungow;
                        int akt_y = 0;
                        while (akt)
                        	{
                           int szer, wys;
                           akt -> podaj_rozmiar(szer, wys);
                           if (drop_y==akt_y)
                              break;
                           akt_y += wys;
                           wskaz = &(akt->nastepny);
                           akt = akt->nastepny;
                           }
                        *wskaz = new rung(nowy_element, NULL);
                        (*wskaz)->nastepny = akt;
                     	break;
                        }
                     case DODAJ_RUNG_CEWKA:
                     	{
                        rung * akt = lista_rungow;
                        rung * * wskaz = &lista_rungow;
                        int akt_y = 0;
                        while (akt)
                        	{
                           int szer, wys;
                           akt -> podaj_rozmiar(szer, wys);
                           if (drop_y==akt_y)
                              break;
                           akt_y += wys;
                           wskaz = &(akt->nastepny);
                           akt = akt->nastepny;
                           }
                        *wskaz = new rung(NULL, nowy_element);
                        (*wskaz)->nastepny = akt;
                     	break;
                        }
                     case DODAJ_SZEREGOWO:
                     	{
                        rung * akt = lista_rungow;
                        int akt_y = 0;
                        while (akt)
                        	{
                           int szer, wys;
                           akt->podaj_rozmiar(szer, wys);
                           if ((drop_y>=akt_y)&&(drop_y<akt_y+wys))
                           	{
                              akt->edytuj(drop_x, drop_y-akt_y, DODAJ_SZEREGOWO, nowy_element);
                              break;
                              }
                           akt = akt->nastepny;
                           akt_y += wys;
                           }
                        break;
                        }
                     case DODAJ_ROWNOLEGLE:
                     	{
                        rung * akt = lista_rungow;
                        int akt_y = 0;
                        while (akt)
                        	{
                           int szer, wys;
                           akt->podaj_rozmiar(szer, wys);
                           if ((drop_y>=akt_y)&&(drop_y<akt_y+wys))
                           	{
                              akt->edytuj(drop_x, drop_y-akt_y, DODAJ_ROWNOLEGLE, nowy_element);
                              break;
                              }
                           akt = akt->nastepny;
                           akt_y += wys;
                           }
                        break;
                        }
                     case DODAJ_DO_ELEMENTOW:
                     case DODAJ_DO_CEWEK:
                     	{
                        rung * akt = lista_rungow;
                        int akt_y = 0;
                        while (akt)
                        	{
                           int szer, wys;
                           akt->podaj_rozmiar(szer, wys);
                           if ((drop_y>=akt_y)&&(drop_y<akt_y+wys))
                           	{
                              akt->edytuj(drop_x, drop_y-akt_y, DODAJ_SZEREGOWO, nowy_element);
                              break;
                              }
                           akt = akt->nastepny;
                           akt_y += wys;
                           }
                        break;
                        }
                     }
						poprawnosc_wymiarow = FALSE;
                  ustaw_scrollbary();
                  odswiez_hotspots();
                  InvalidateRect(okno, NULL, TRUE);
                  }
               else
               	delete nowy_element;
               }
            else
	            delete nowy_element;
            }
         else
         	if (autoscroll)
            	{
            	autoscroll = FALSE;
               ReleaseCapture();
               }
         break;
         }
      case WM_LBUTTONDBLCLK:
      	{
			int drop_x, drop_y;
         drop_x = remapuj_x(LOWORD(lParam))/SZEROKOSC_ELEMENTU;
         drop_y = remapuj_y(HIWORD(lParam))/WYSOKOSC_ELEMENTU;
         RECT traf;
         element_zwykly * wsk;
         if (hotspot.sprawdz(drop_x, drop_y, &traf, &wsk)&&(!praca_dziala))
         	{
            zmien_parametry_elementu(okno, wsk);
            InvalidateRect(okno, NULL, TRUE);
            }
         else
         	{
            autoscroll = TRUE;
         	poprzednie_wspolrzedne = MAKEPOINTS(lParam);
            SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEALL)));
            SetCapture(okno);
            }
         break;
         }
      case WM_MOUSEMOVE:
      	{
         if (dragging)
         	{
            HDC kontekst_ekranu = GetDC(okno);
            SetROP2(kontekst_ekranu, R2_NOTXORPEN);
            if (pierwszy_DRAG)
            	pierwszy_DRAG = FALSE;
            else
            	{
					nowy_element->narysuj(kontekst_ekranu, 0, 0, 0);
               narysuj_kreski(okno, dragging_wspolrzedne.x, dragging_wspolrzedne.y);
               }
            dragging_wspolrzedne.x = LOWORD(lParam);
            dragging_wspolrzedne.y = HIWORD(lParam);
				nowy_element->narysuj(kontekst_ekranu, 0, 0, 0);
            //ClientToScreen(okno, &dragging_wspolrzedne);
            narysuj_kreski(okno, dragging_wspolrzedne.x, dragging_wspolrzedne.y);
            ReleaseDC(okno, kontekst_ekranu);
            }
         else
         	if (autoscroll)
            	{
               POINTS nowe_wspolrzedne;
		         nowe_wspolrzedne = MAKEPOINTS(lParam);
               int roznica_x = poprzednie_wspolrzedne.x - nowe_wspolrzedne.x;
               int roznica_y = poprzednie_wspolrzedne.y - nowe_wspolrzedne.y;
               przesun_scrollbary(roznica_x, roznica_y);
               poprzednie_wspolrzedne = nowe_wspolrzedne;
               }
         break;
         }
      case WM_RBUTTONUP:
      	{
			int drop_x, drop_y;
         drop_x = remapuj_x(LOWORD(lParam))/SZEROKOSC_ELEMENTU;
         drop_y = remapuj_y(HIWORD(lParam))/WYSOKOSC_ELEMENTU;
         POINT punkt;
         punkt.x = LOWORD(lParam);
         punkt.y = HIWORD(lParam);
         ClientToScreen(okno, &punkt);
         RECT traf;
         element_zwykly * wsk;
         if (hotspot.sprawdz(drop_x, drop_y, &traf, &wsk))
         	{
            HMENU uchwyt = GetSubMenu(LoadMenu(instancja, MAKEINTRESOURCE(IDM_MENUEDYCJA)), 0);
            if (praca_dziala)
            	{
               EnableMenuItem(uchwyt, CM_WLASCIWOSCI, MF_BYCOMMAND|MF_GRAYED);
               EnableMenuItem(uchwyt, CM_USUN, MF_BYCOMMAND|MF_GRAYED);
               }
            switch (TrackPopupMenu(uchwyt, TPM_LEFTALIGN|TPM_TOPALIGN|TPM_NONOTIFY|TPM_RETURNCMD, punkt.x, punkt.y, 0, okno, NULL))
            	{
               case CM_WLASCIWOSCI:
                  zmien_parametry_elementu(okno, wsk);
                  InvalidateRect(okno, NULL, TRUE);
                  break;
               case CM_POMOC:
               	{
                  pomoc.wyswietl(wsk->podaj_nazwe());
                  break;
                  }
               case CM_USUN:
               	{
                  rung * akt = lista_rungow;
                  int akt_y = 0;
                  while (akt)
                  	{
                     int szer, wys;
                     akt->podaj_rozmiar(szer, wys);
                     if ((drop_y>=akt_y)&&(drop_y<akt_y+wys))
                     	{
                        element * cos;
                        akt->edytuj(drop_x, drop_y-akt_y, SKASUJ_GO, cos);
                        sprawdz_rungi();
								poprawnosc_wymiarow = FALSE;
		                  ustaw_scrollbary();
		                  odswiez_hotspots();
		                  InvalidateRect(okno, NULL, TRUE);
                        break;
                        }
                     akt_y += wys;
                     akt = akt->nastepny;
                     }
                  break;
                  }
               }
            DestroyMenu(uchwyt);
            }
         break;
         }
      case WM_CAPTURECHANGED:
      	{
         if (dragging)
         	{
            if (!pierwszy_DRAG)
            	{
	            HDC kontekst_ekranu = GetDC(okno);
	            SetROP2(kontekst_ekranu, R2_NOTXORPEN);
	            nowy_element->narysuj(kontekst_ekranu, 0, 0, 0);
               narysuj_kreski(okno, dragging_wspolrzedne.x, dragging_wspolrzedne.y);
	            ReleaseDC(NULL, kontekst_ekranu);
               }
            dragging = FALSE;
            delete nowy_element;
            }
         else
         	if (autoscroll)
            	{
               autoscroll = FALSE;
               }
         break;
         }
      default:
		   return DefWindowProc(okno, komunikat, wParam, lParam);
      }
   return 0;
   }

int program_LD::znajdz_cel_drag_and_drop(int & drop_x, int & drop_y, element_zwykly * & cel, ZDARZENIE & co_zrobic)
	{
   if ((drop_y>=0)&&(drop_y<podaj_wysokosc()*WYSOKOSC_ELEMENTU))
	   if ((drop_x>-MARGINES_LEWY)&&(drop_x<0))
	   	{
         if (!dragging_cewka)
         	{
	         rung * akt = lista_rungow;
            int akt_y = 0;
            int szer, wys;
            while (akt)
            	{
	            akt->podaj_rozmiar(szer, wys);
               if ((drop_y>=akt_y*WYSOKOSC_ELEMENTU)&&(drop_y<(akt_y+wys)*WYSOKOSC_ELEMENTU))
               	{
                  drop_x = 0;
                  drop_y = akt_y;
						co_zrobic = DODAJ_RUNG_ELEMENT;
                  return TRUE;
                  }
               akt_y += wys;
               akt = akt->nastepny;
               }
            return FALSE;
            }
         else
         	return FALSE;
	      }
	   else
		   if ((drop_x>=0)&&(drop_x<x_cewek()*SZEROKOSC_ELEMENTU))
	      	{
            if (!dragging_cewka)
            	{
               RECT obszar;
               if (hotspot.sprawdz(drop_x/SZEROKOSC_ELEMENTU, drop_y/WYSOKOSC_ELEMENTU, &obszar, &cel))
               	{
                  if ((drop_x-obszar.left*SZEROKOSC_ELEMENTU)<(obszar.right-obszar.left)*(SZEROKOSC_ELEMENTU/2))
	                  co_zrobic = DODAJ_ROWNOLEGLE;
                  else
                  	co_zrobic = DODAJ_SZEREGOWO;
                  drop_x = obszar.left;
                  drop_y = obszar.top;
               	return TRUE;
                  }
               else
               	{
			         rung * akt = lista_rungow;
		            int akt_y = 0;
		            int szer, wys;
		            while (akt)
		            	{
			            akt->podaj_rozmiar(szer, wys);
		               if ((drop_y>=akt_y*WYSOKOSC_ELEMENTU)&&(drop_y<(akt_y+wys)*WYSOKOSC_ELEMENTU))
		               	{
                        if (!(akt->sa_elementy()))
                        	{
			                  drop_x = 0;
			                  drop_y = akt_y;
									co_zrobic = DODAJ_DO_ELEMENTOW;
			                  return TRUE;
                           }
                        else
                        	return FALSE;
		                  }
		               akt_y += wys;
		               akt = akt->nastepny;
		               }
		            return FALSE;
                  }
               }
            else
	            return FALSE;
	         }
	      else
	      	if ((drop_x>=x_cewek()*SZEROKOSC_ELEMENTU)&&(drop_x<(x_cewek()+1)*SZEROKOSC_ELEMENTU))
	         	{
	            if (dragging_cewka)
	            	{
	               RECT obszar;
	               if (hotspot.sprawdz(drop_x/SZEROKOSC_ELEMENTU, drop_y/WYSOKOSC_ELEMENTU, &obszar, &cel))
	               	{
                  	co_zrobic = DODAJ_ROWNOLEGLE;
	                  drop_x = obszar.left;
	                  drop_y = obszar.top;
	               	return TRUE;
	                  }
	               else
	               	{
				         rung * akt = lista_rungow;
			            int akt_y = 0;
			            int szer, wys;
			            while (akt)
			            	{
				            akt->podaj_rozmiar(szer, wys);
			               if ((drop_y>=akt_y*WYSOKOSC_ELEMENTU)&&(drop_y<(akt_y+wys)*WYSOKOSC_ELEMENTU))
			               	{
	                        if (!(akt->sa_cewki()))
	                        	{
				                  drop_x = x_cewek();
				                  drop_y = akt_y;
										co_zrobic = DODAJ_DO_CEWEK;
				                  return TRUE;
	                           }
	                        else
	                        	return FALSE;
			                  }
			               akt_y += wys;
			               akt = akt->nastepny;
			               }
			            return FALSE;
	                  }
                  }
	            else
		            return FALSE;
	            }
            else
            	{
               return FALSE;
               }
	else
		if (drop_x<x_cewek()*SZEROKOSC_ELEMENTU)
      	{
         if (!dragging_cewka)
         	{
	         drop_x = 0;
	         drop_y = podaj_wysokosc();
	         co_zrobic = DODAJ_RUNG_ELEMENT;
            return TRUE;
            }
         else
	         return FALSE;
         }
      else
      	{
         if (dragging_cewka)
         	{
	         drop_x = x_cewek();
	         drop_y = podaj_wysokosc();
	         co_zrobic = DODAJ_RUNG_CEWKA;
            return TRUE;
            }
         else
	         return FALSE;
         }
   }

void program_LD::ustaw_scrollbary(void)
	{
   RECT obszar;
   GetClientRect(okno, &obszar);
   SCROLLINFO info;
   info.cbSize = sizeof(info);
   info.fMask = SIF_PAGE|SIF_RANGE;
   info.nPage = page_x = obszar.right;
   info.nMin = 0;
   info.nMax = max_x = podaj_szerokosc()*SZEROKOSC_ELEMENTU+MARGINES_LEWY*2;
   SetScrollInfo(okno, SB_HORZ, &info, TRUE);
   info.cbSize = sizeof(info);
   info.fMask = SIF_PAGE|SIF_RANGE;
   info.nPage = page_y = obszar.bottom;
   info.nMin = 0;
   info.nMax = max_y = podaj_wysokosc()*WYSOKOSC_ELEMENTU+MARGINES_DOLNY;
   SetScrollInfo(okno, SB_VERT, &info, TRUE);
   int poz_x = GetScrollPos(okno, SB_HORZ);
   int poz_y = GetScrollPos(okno, SB_VERT);
   if ((poz_x!=scroll_x)||(poz_y!=scroll_y))
   	{
      scroll_x = poz_x;
      scroll_y = poz_y;
      InvalidateRect(okno, NULL, TRUE);
      }
   }

void program_LD::przesun_scrollbary(int deltax, int deltay)
	{
   int nscroll_x = scroll_x+deltax;
   int nscroll_y = scroll_y+deltay;
   if (nscroll_x < 0)
   	nscroll_x = 0;
   if (nscroll_x > max_x -page_x)
   	nscroll_x = max_x - page_x;
   if (nscroll_y < 0)
   	nscroll_y = 0;
   if (nscroll_y > max_y -page_y)
   	nscroll_y = max_y - page_y;

   SetScrollPos(okno, SB_HORZ, nscroll_x, TRUE);
   SetScrollPos(okno, SB_VERT, nscroll_y, TRUE);
   nscroll_x = GetScrollPos(okno, SB_HORZ);
   nscroll_y = GetScrollPos(okno, SB_VERT);
	if ((nscroll_x!=scroll_x)||(nscroll_y!=scroll_y))
   	{
      RECT obszar;
      GetClientRect(okno, &obszar);
      ScrollWindowEx(okno, scroll_x-nscroll_x, scroll_y-nscroll_y, NULL, &obszar, NULL, NULL, SW_ERASE|SW_INVALIDATE);
      scroll_x = nscroll_x;
      scroll_y = nscroll_y;
      }
   }

void program_LD::narysuj_kreski(HWND okno, int drop_x, int drop_y)
	{
   HDC kontekst = GetDC(okno);
   SetROP2(kontekst, R2_NOTXORPEN);
   POINT zapas;
   zapas.x = drop_x;
   zapas.y = drop_y;
   POINT punkt;
   punkt.x = drop_x;
   punkt.y = drop_y;
   //ScreenToClient(okno, &punkt);
   RECT obszar;
   GetClientRect(okno, &obszar);
   if ((punkt.x>=obszar.left)&&(punkt.x<obszar.right)&&(punkt.y>=obszar.top)&&(punkt.y<obszar.bottom))
   	{
	   drop_x = remapuj_x(punkt.x);
	   drop_y = remapuj_y(punkt.y);
      element_zwykly * cel;
      ZDARZENIE co_zrobic;
      if (znajdz_cel_drag_and_drop(drop_x, drop_y, cel, co_zrobic))
      	{
         int stary_drag = dragging;
         dragging = FALSE;
         punkt.x = mapuj_x(drop_x);
         punkt.y = mapuj_y(drop_y);
         dragging = stary_drag;
         //ScreenToClient(okno, &zapas);
         switch (co_zrobic)
         	{
            case DODAJ_SZEREGOWO:
            	{
               int szer1, wys1, szer2, wys2;
               nowy_element->podaj_rozmiar(szer1, wys1);
               cel->podaj_rozmiar(szer2, wys2);
               MoveToEx(kontekst, zapas.x, zapas.y+Y_WYJSCIA, NULL);
               LineTo(kontekst, punkt.x+szer2*SZEROKOSC_ELEMENTU-20, punkt.y+Y_WYJSCIA);
               LineTo(kontekst, punkt.x+szer2*SZEROKOSC_ELEMENTU-10, punkt.y+Y_WYJSCIA);
               LineTo(kontekst, zapas.x+szer1*SZEROKOSC_ELEMENTU-20, zapas.y+Y_WYJSCIA);
            	break;
               }
            case DODAJ_ROWNOLEGLE:
					{
               int szer1, wys1, szer2, wys2;
               nowy_element->podaj_rozmiar(szer1, wys1);
               cel->podaj_rozmiar(szer2, wys2);
               MoveToEx(kontekst, punkt.x, punkt.y+Y_WYJSCIA, NULL);
               LineTo(kontekst, zapas.x, zapas.y+Y_WYJSCIA);
               MoveToEx(kontekst, punkt.x+szer2*SZEROKOSC_ELEMENTU-20, punkt.y+Y_WYJSCIA, NULL);
               LineTo(kontekst, zapas.x+szer1*SZEROKOSC_ELEMENTU-20, zapas.y+Y_WYJSCIA);
            	break;
               }
            case DODAJ_RUNG_ELEMENT:
            	{
               int szer, wys;
               nowy_element->podaj_rozmiar(szer, wys);
               MoveToEx(kontekst, zapas.x, zapas.y+Y_WYJSCIA, NULL);
               LineTo(kontekst, punkt.x, punkt.y+Y_WYJSCIA);
               MoveToEx(kontekst, punkt.x+x_cewek()*SZEROKOSC_ELEMENTU, punkt.y+Y_WYJSCIA, NULL);
               LineTo(kontekst, zapas.x+szer*SZEROKOSC_ELEMENTU-20, zapas.y+Y_WYJSCIA);
               break;
               }
            case DODAJ_DO_ELEMENTOW:
            	{
               int szer, wys;
               nowy_element->podaj_rozmiar(szer, wys);
               MoveToEx(kontekst, zapas.x, zapas.y+Y_WYJSCIA, NULL);
               LineTo(kontekst, punkt.x, punkt.y+Y_WYJSCIA);
               LineTo(kontekst, punkt.x+x_cewek()*SZEROKOSC_ELEMENTU, punkt.y+Y_WYJSCIA);
               LineTo(kontekst, zapas.x+szer*SZEROKOSC_ELEMENTU-20, zapas.y+Y_WYJSCIA);
            	break;
               }
            case DODAJ_RUNG_CEWKA:
            	{
               int szer, wys;
               nowy_element->podaj_rozmiar(szer, wys);
               MoveToEx(kontekst, zapas.x, zapas.y+Y_WYJSCIA, NULL);
               LineTo(kontekst, punkt.x, punkt.y+Y_WYJSCIA);
               MoveToEx(kontekst, punkt.x+SZEROKOSC_ELEMENTU, punkt.y+Y_WYJSCIA, NULL);
               LineTo(kontekst, zapas.x+szer*SZEROKOSC_ELEMENTU-20, zapas.y+Y_WYJSCIA);
            	break;
               }
            case DODAJ_DO_CEWEK:
            	{
               int szer, wys;
               nowy_element->podaj_rozmiar(szer, wys);
               MoveToEx(kontekst, zapas.x, zapas.y+Y_WYJSCIA, NULL);
               LineTo(kontekst, punkt.x, punkt.y+Y_WYJSCIA);
               LineTo(kontekst, punkt.x+SZEROKOSC_ELEMENTU, punkt.y+Y_WYJSCIA);
               LineTo(kontekst, zapas.x+szer*SZEROKOSC_ELEMENTU-20, zapas.y+Y_WYJSCIA);
            	break;
               }
            }
         }
      }
	ReleaseDC(okno, kontekst);
   }

void program_LD::rozpocznij_DRAGDROP(element * nowy, int czy_cewka)
	{
   dragging_cewka = czy_cewka;
	dragging = TRUE;
   pierwszy_DRAG = TRUE;
	nowy_element = nowy;
   SetCapture(okno);
   SetCursor(LoadCursor(instancja, MAKEINTRESOURCE(IDC_DRAGDROP)));
   }

void program_LD::sprawdz_rungi(void)
	{
	rung * akt = lista_rungow;
   rung * * wskaz = &lista_rungow;
   while (akt)
		{
      if ((!akt->sa_elementy())&&(!akt->sa_cewki()))
      	{
         *wskaz = akt->nastepny;
         delete akt;
         akt = *wskaz;
         }
      else
      	{
         wskaz = &(akt->nastepny);
         akt = akt->nastepny;
         }
      }
   }

void program_LD::dzialaj(void)
	{
   rung * akt = lista_rungow;
   while (akt)
   	{
      akt->dzialaj(1);
      akt = akt->nastepny;
      }
   }

void program_LD::wydrukuj()
	{
	PRINTDLG dialog;
	dialog.lStructSize = sizeof(PRINTDLG);
	dialog.hDevMode = (HANDLE) NULL;
	dialog.hDevNames = (HANDLE) NULL;
	dialog.Flags = PD_RETURNDC;
	dialog.hwndOwner = okno;
	dialog.hDC = (HDC) NULL;
	dialog.nFromPage = 1;
	dialog.nToPage = 1;
	dialog.nMinPage = 1;
	dialog.nMaxPage = 1;
	dialog.nCopies = 1;
	dialog.hInstance = (HINSTANCE) NULL;
	dialog.lCustData = 0L;
	dialog.lpfnPrintHook = (LPPRINTHOOKPROC) NULL;
	dialog.lpfnSetupHook = (LPSETUPHOOKPROC) NULL;
	dialog.lpPrintTemplateName = (LPSTR) NULL;
	dialog.lpSetupTemplateName = (LPSTR)  NULL;
	dialog.hPrintTemplate = (HANDLE) NULL;
	dialog.hSetupTemplate = (HANDLE) NULL;
   if (!PrintDlg(&dialog))
		return;
   HDC kontekst = dialog.hDC;
   DOCINFO dok;
   dok.cbSize = sizeof(DOCINFO);
   dok.lpszDocName = "Program LD";
   dok.lpszOutput = NULL;
   dok.lpszDatatype = NULL;
   dok.fwType = 0;
   StartDoc(kontekst, &dok);
   StartPage(kontekst);

   HFONT stara_czcionka = (HFONT)GetCurrentObject(kontekst, OBJ_FONT);
   SelectObject(kontekst, GetStockObject(DEFAULT_GUI_FONT));
   int sscroll_x = scroll_x;
   int sscroll_y = scroll_y;
   scroll_x = 0;
   scroll_y = 0;
	int akt_y = 0;
	int szerokosc, wysokosc;
	rung * aktualny = lista_rungow;
	while (aktualny)
		{
		aktualny->narysuj(kontekst, 0, 0, akt_y);
		aktualny->podaj_rozmiar(szerokosc, wysokosc);
		akt_y += wysokosc;
		aktualny = aktualny->nastepny;
		}
   scroll_x = sscroll_x;
   scroll_y = sscroll_y;
   SelectObject(kontekst, stara_czcionka);

   EndPage(kontekst);
   EndDoc(kontekst);
   }

void program_LD::zapisz(FILE * plik)
	{
	int ilosc_rungow = 0;
   rung * akt = lista_rungow;
   while (akt)
   	{
      ilosc_rungow++;
      akt = akt->nastepny;
      }
   fwrite(&ilosc_rungow, sizeof(ilosc_rungow), 1, plik);
   akt = lista_rungow;
   while (akt)
   	{
      akt->zapisz(plik);
      akt = akt->nastepny;
      }
   }

void program_LD::wczytaj(FILE * plik)
	{
	rung * aktualny, * nastepny;
	aktualny = lista_rungow;
	while (aktualny)
		{
		nastepny = aktualny->nastepny;
		delete aktualny;
		aktualny = nastepny;
		}
   int ilosc_rungow;
   fread(&ilosc_rungow, sizeof(ilosc_rungow), 1, plik);
   rung * * akt = &lista_rungow;
   for (int i=0; i<ilosc_rungow; i++)
   	{
		*akt = new rung(plik);
      akt = &((*akt)->nastepny);
      }
   *akt = NULL;
	poprawnosc_wymiarow = FALSE;
   ustaw_scrollbary();
   odswiez_hotspots();
   InvalidateRect(okno, NULL, TRUE);
   }

