#ifndef PAGE_IMAGE_H
#define PAGE_IMAGE_H

#include <windows.h>
#include <string>

class AppState;

class PageImage {
public:
    PageImage(AppState* state);

    void draw(HWND hwnd, HDC hdc, RECT& clientRect);
    void onImageDropped(const std::wstring& path);
    void onImageLinkPasted(const std::wstring& url);
    void removeImage();

private:
    AppState* appState;
    std::wstring imagePath;
    bool imageLoaded;
    bool fromURL;
};

#endif