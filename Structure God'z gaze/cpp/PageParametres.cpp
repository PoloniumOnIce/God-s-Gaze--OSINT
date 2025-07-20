#include "PageParametres.h"
#include "AppState.h"
#include "RessourceManager.h"

PageParametres::PageParametres(AppState* state) : appState(state) {}

void PageParametres::draw(HWND hwnd, HDC hdc, RECT& clientRect) {
    SetBkMode(hdc, TRANSPARENT);
    HFONT font = RessourceManager::getFont(20);
    HFONT oldFont = (HFONT)SelectObject(hdc, font);
    SetTextColor(hdc, RGB(178, 34, 34));

    std::wstring titre = appState->getLocalizedString(L"settings_title");
    SIZE textSize;
    GetTextExtentPoint32(hdc, titre.c_str(), titre.length(), &textSize);
    int centerX = (clientRect.right - textSize.cx) / 2;

    TextOut(hdc, centerX, 20, titre.c_str(), titre.length());

    SelectObject(hdc, oldFont);
    DeleteObject(font);

    // Les boutons sont dessinés via la gestion classique des boutons Windows (créés ailleurs)
    // Ici, on peut dessiner le chemin de dossier personnalisé s’il y a lieu

    std::wstring dossier = appState->getStoragePath();
    std::wstring message = appState->getLocalizedString(L"storage_path_msg") + dossier;

    HFONT fontSmall = RessourceManager::getFont(14);
    HFONT oldSmallFont = (HFONT)SelectObject(hdc, fontSmall);
    SetTextColor(hdc, RGB(178, 34, 34));
    TextOut(hdc, 10, clientRect.bottom - 30, message.c_str(), message.length());
    SelectObject(hdc, oldSmallFont);
    DeleteObject(fontSmall);
}