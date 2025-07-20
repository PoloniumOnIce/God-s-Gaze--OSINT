#ifndef STYLE_H
#define STYLE_H

#include <windows.h>

namespace Style {
    enum class Theme {
        Sombre,
        Clair
    };

    struct StyleConfig {
        COLORREF backgroundColor;
        COLORREF buttonColor;
        COLORREF buttonBorderColor;
        COLORREF buttonTextColor;
        COLORREF titleTextColor;
        COLORREF errorTextColor;
        COLORREF byPoloniumColor;
        HFONT titleFont;
        HFONT buttonFont;
        HFONT smallFont;
    };

    void Initialize(Theme theme);
    const StyleConfig& GetCurrent();
    void Cleanup();
}

#endif