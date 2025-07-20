#pragma once

#include <windows.h>
#include <string>

enum Page {
    PAGE_HOME,
    PAGE_PSEUDO,
    PAGE_EMAIL,
    PAGE_IP,
    PAGE_IMAGE,
    PAGE_SETTINGS
};

enum Theme {
    THEME_DARK,
    THEME_LIGHT
};

enum Language {
    LANG_FR,
    LANG_EN
};

struct AppSettings {
    Theme theme = THEME_DARK;
    Language language = LANG_FR;
    bool internetAvailable = true;
    std::wstring savePath = L"";
};

extern HWND hMainWindow;
extern HINSTANCE hInst;
extern Page currentPage;
extern AppSettings settings;

void SwitchPage(Page newPage);
void UpdateLayout();
void ApplyTheme(HWND hwnd);
void DrawBanner(HDC hdc, RECT clientRect);
void CheckInternetConnection();
std::wstring GetTranslatedText(const std::wstring& key);
std::wstring GetSaveFolder();
void SaveTextToFile(const std::wstring& folderName, const std::wstring& content);