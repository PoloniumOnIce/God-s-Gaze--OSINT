#ifndef UI_H
#define UI_H

#include <windows.h>

namespace UI {
    void drawCenteredText(HDC hdc, RECT rect, const std::wstring& text, COLORREF color, int fontSize = 20);
    void drawButton(HDC hdc, RECT rect, const std::wstring& label, bool hovered = false);
}

#endif