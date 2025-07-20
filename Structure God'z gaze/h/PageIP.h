#ifndef PAGE_IP_H
#define PAGE_IP_H

#include <windows.h>
#include <string>

class AppState;

class PageIP {
public:
    PageIP(AppState* state);
    void draw(HWND hwnd, HDC hdc, RECT& clientRect);
    void onSearch(const std::wstring& ip);

private:
    AppState* appState;
};

#endif