#ifndef PAGE_ACCUEIL_H
#define PAGE_ACCUEIL_H

#include <windows.h>
#include <string>

class AppState;

class PageAccueil {
public:
    PageAccueil(AppState* state);
    void draw(HWND hwnd, HDC hdc, RECT& clientRect);

private:
    AppState* appState;
};

#endif