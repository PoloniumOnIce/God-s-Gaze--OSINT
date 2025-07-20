#include "PageImage.h"
#include "AppState.h"
#include "RessourceManager.h"
#include "RechercheManager.h"

PageImage::PageImage(AppState* state) : appState(state), imageLoaded(false), fromURL(false) {}

void PageImage::onImageDropped(const std::wstring& path) {
    imagePath = path;
    imageLoaded = true;
    fromURL = false;
}

void PageImage::onImageLinkPasted(const std::wstring& url) {
    imagePath = url;
    imageLoaded = true;
    fromURL = true;
}

void PageImage::removeImage() {
    imagePath.clear();
    imageLoaded = false;
}

void PageImage::draw(HWND hwnd, HDC hdc, RECT& clientRect) {
    SetBkMode(hdc, TRANSPARENT);
    HFONT font = RessourceManager::getFont(22);
    HFONT oldFont = (HFONT)SelectObject(hdc, font);
    SetTextColor(hdc, RGB(178, 34, 34));

    std::wstring titre = appState->getLocalizedString(L"image_title");
    SIZE textSize;
    GetTextExtentPoint32(hdc, titre.c_str(), titre.length(), &textSize);
    int centerX = (clientRect.right - textSize.cx) / 2;

    TextOut(hdc, centerX, 20, titre.c_str(), titre.length());

    SelectObject(hdc, oldFont);
    DeleteObject(font);

    // Message ou aperçu image
    if (imageLoaded) {
        std::wstring msg = fromURL
            ? appState->getLocalizedString(L"url_loaded")
            : appState->getLocalizedString(L"image_loaded");

        SetTextColor(hdc, RGB(178, 34, 34));
        TextOut(hdc, 10, clientRect.bottom - 40, msg.c_str(), msg.length());

        std::wstring croix = L"[X]";
        TextOut(hdc, clientRect.right - 30, clientRect.bottom - 40, croix.c_str(), croix.length());
    }

    if (!appState->hasInternet()) {
        std::wstring error = appState->getLocalizedString(L"internet_required");
        SetTextColor(hdc, RGB(178, 34, 34));
        TextOut(hdc, 10, clientRect.bottom - 20, error.c_str(), error.length());
    }
}