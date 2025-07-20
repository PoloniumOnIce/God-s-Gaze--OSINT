#include "PageAccueil.h"
#include "RessourceManager.h"
#include "AppState.h"

PageAccueil::PageAccueil(AppState* state) : appState(state) {}

void PageAccueil::draw(HWND hwnd, HDC hdc, RECT& clientRect) {
    SetBkMode(hdc, TRANSPARENT);

    HFONT bannerFont = RessourceManager::getFont(32, true);
    HFONT prevFont = (HFONT)SelectObject(hdc, bannerFont);
    SetTextColor(hdc, RGB(178, 34, 34)); // Rouge sang

    std::wstring banner = appState->getLocalizedString(L"banner");
    SIZE textSize;
    GetTextExtentPoint32(hdc, banner.c_str(), banner.length(), &textSize);
    int centerX = (clientRect.right - textSize.cx) / 2;
    int centerY = (clientRect.bottom) / 3;

    TextOut(hdc, centerX, centerY, banner.c_str(), banner.length());

    SelectObject(hdc, prevFont);
    DeleteObject(bannerFont);

    // Affichage de l’erreur si besoin
    if (!appState->isInternetAvailable()) {
        std::wstring msg = appState->getLocalizedString(L"no_internet_error");
        SetTextColor(hdc, RGB(178, 34, 34));
        TextOut(hdc, 10, clientRect.bottom - 20, msg.c_str(), msg.length());
    }

    // Affichage signature "By Polønium"
    std::wstring signature = L"By Polønium";
    GetTextExtentPoint32(hdc, signature.c_str(), signature.length(), &textSize);
    TextOut(hdc, clientRect.right - textSize.cx - 10, 10, signature.c_str(), signature.length());
}