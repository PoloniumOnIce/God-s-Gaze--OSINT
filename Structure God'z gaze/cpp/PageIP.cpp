#include "PageIP.h"
#include "AppState.h"
#include "RessourceManager.h"
#include "RechercheManager.h"

PageIP::PageIP(AppState* state) : appState(state) {}

void PageIP::onSearch(const std::wstring& ip) {
    std::wstring result = RechercheManager::rechercherIP(ip);
    std::wstring chemin = appState->sauvegarderResultat(ip, result);
    appState->setLastSearchResultPath(chemin);
}

void PageIP::draw(HWND hwnd, HDC hdc, RECT& clientRect) {
    SetBkMode(hdc, TRANSPARENT);
    HFONT font = RessourceManager::getFont(22);
    HFONT oldFont = (HFONT)SelectObject(hdc, font);
    SetTextColor(hdc, RGB(178, 34, 34));

    std::wstring titre = appState->getLocalizedString(L"ip_title");
    SIZE textSize;
    GetTextExtentPoint32(hdc, titre.c_str(), titre.length(), &textSize);
    int centerX = (clientRect.right - textSize.cx) / 2;

    TextOut(hdc, centerX, 20, titre.c_str(), titre.length());

    SelectObject(hdc, oldFont);
    DeleteObject(font);

    // Affichage message succès
    if (!appState->getLastSearchResultPath().empty()) {
        std::wstring msg = appState->getLocalizedString(L"folder_created");
        msg += appState->getLastSearchResultPath();
        SetTextColor(hdc, RGB(178, 34, 34));
        TextOut(hdc, 10, clientRect.bottom - 20, msg.c_str(), msg.length());
    }
}