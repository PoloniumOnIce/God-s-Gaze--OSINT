#include "style.h"

namespace Style {
    static StyleConfig currentStyle;
    static HFONT CreateFontHelper(int size, bool bold = false) {
        return CreateFontW(size, 0, 0, 0, bold ? FW_BOLD : FW_NORMAL,
                           FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                           OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                           DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                           L"Segoe UI");
    }

    void Initialize(Theme theme) {
        if (theme == Theme::Sombre) {
            currentStyle.backgroundColor    = RGB(45, 45, 45);
            currentStyle.buttonColor        = RGB(20, 20, 20);
            currentStyle.buttonBorderColor  = RGB(180, 180, 180);
            currentStyle.buttonTextColor    = RGB(178, 34, 34); // rouge sang
            currentStyle.titleTextColor     = RGB(178, 34, 34);
            currentStyle.errorTextColor     = RGB(255, 0, 0);
            currentStyle.byPoloniumColor    = RGB(180, 180, 180);
        } else {
            currentStyle.backgroundColor    = RGB(255, 255, 255);
            currentStyle.buttonColor        = RGB(240, 240, 240);
            currentStyle.buttonBorderColor  = RGB(80, 80, 80);
            currentStyle.buttonTextColor    = RGB(178, 34, 34);
            currentStyle.titleTextColor     = RGB(178, 34, 34);
            currentStyle.errorTextColor     = RGB(255, 0, 0);
            currentStyle.byPoloniumColor    = RGB(50, 50, 50);
        }

        currentStyle.titleFont  = CreateFontHelper(28, true);
        currentStyle.buttonFont = CreateFontHelper(16);
        currentStyle.smallFont  = CreateFontHelper(12);
    }

    const StyleConfig& GetCurrent() {
        return currentStyle;
    }

    void Cleanup() {
        DeleteObject(currentStyle.titleFont);
        DeleteObject(currentStyle.buttonFont);
        DeleteObject(currentStyle.smallFont);
    }
}