#ifndef PAGE_PSEUDO_H
#define PAGE_PSEUDO_H

#include <windows.h>
#include <string>

class AppState;

class PagePseudo {
public:
    PagePseudo(AppState* state);
    void draw(HWND hwnd, HDC hdc, RECT& clientRect);
    void onSearch(const std::wstring& pseudo);

private:
    AppState* appState;
};

#endif