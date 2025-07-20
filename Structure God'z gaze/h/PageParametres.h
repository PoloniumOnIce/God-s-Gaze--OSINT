#ifndef PAGE_PARAMETRES_H
#define PAGE_PARAMETRES_H

#include <windows.h>
#include <string>

class AppState;

class PageParametres {
public:
    PageParametres(AppState* state);

    void draw(HWND hwnd, HDC hdc, RECT& clientRect);

private:
    AppState* appState;
};

#endif