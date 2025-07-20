#ifndef PAGE_EMAIL_H
#define PAGE_EMAIL_H

#include <windows.h>
#include <string>

class AppState;

class PageEmail {
public:
    PageEmail(AppState* state);
    void draw(HWND hwnd, HDC hdc, RECT& clientRect);
    void onSearch(const std::wstring& email);

private:
    AppState* appState;
};

#endif