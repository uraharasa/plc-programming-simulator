#ifndef okno_glowne_h_included
#define okno_glowne_h_included

#include <windows.h>
#include "program_LD.h"
#include "narzedzia.h"
#include "lekcja.h"

extern program_LD * akt_program_LD;
extern HINSTANCE instancja;
extern narzedzia * akt_narzedzia;
extern lekcja * akt_lekcja;
extern HWND OknoNarzedzi;
extern HWND OknoGlowne;
extern LRESULT CALLBACK ProcOknaNarzedziKlient(HWND, UINT, WPARAM, LPARAM);
extern int wysokosc_toolbara;
extern int praca_dziala;
extern int praca_krokowa;

#endif