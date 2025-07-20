#pragma once
#include <windows.h>

// Couleurs thèmes
extern COLORREF g_clrBackgroundDark;
extern COLORREF g_clrButtonDark;
extern COLORREF g_clrTextRed;

// Fonctions d'interface
void InitInterface(HWND hwnd);
void CreateMainButtons(HWND hwnd);
void ShowPageAccueil(HWND hwnd);
void ShowPagePseudo(HWND hwnd);
void ShowPageIP(HWND hwnd);
void ShowPageEmail(HWND hwnd);
void ShowPageImage(HWND hwnd);
void ShowPageParametres(HWND hwnd);
void ShowPageParametresAvances(HWND hwnd);

void UpdateTheme(bool darkTheme);
void UpdateLanguage(bool french);

bool CheckInternetConnection();
void UpdateInternetIcon(HWND hwnd);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);