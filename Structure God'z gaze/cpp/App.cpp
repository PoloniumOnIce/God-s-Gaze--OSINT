#include "App.h"
#include <wininet.h>
#include <shlobj.h>
#include <fstream>

#pragma comment(lib, "wininet.lib")

HWND hMainWindow = nullptr;
HINSTANCE hInst = nullptr;
Page currentPage = PAGE_HOME;
AppSettings settings;

void SwitchPage(Page newPage) {
    currentPage = newPage;
    InvalidateRect(hMainWindow, NULL, TRUE);
}

void ApplyTheme(HWND hwnd) {
    // Set dark or light theme colors (example: background color)
    HBRUSH brush = CreateSolidBrush(settings.theme == THEME_DARK ? RGB(45, 45, 45) : RGB(255, 255, 255));
    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)brush);
}

void DrawBanner(HDC hdc, RECT clientRect) {
    const wchar_t* banner =
        L" ▄████  ▒█████  ▓█████▄      ██████             ▄████  ▄▄▄      ▒███████▒▓█████ \n"
        L" ██▒ ▀█▒▒██▒  ██▒▒██▀ ██▌   ▒██    ▒           ██▒ ▀█▒▒████▄    ▒ ▒ ▒ ▄▀░▓█   ▀ \n"
        L"▒██░▄▄▄░▒██░  ██▒░██   █▌   ▓██▄             ▒██░▄▄▄░▒██  ▀█▄  ░ ▒ ▄▀▒░ ▒███   \n"
        L"░▓█  ██▓▒██   ██░░▓█▄   ▌     ▒   ██▒          ░▓█  ██▓░██▄▄▄▄██   ▄▀▒   ░▒▓█  ▄ \n"
        L"░▒▓███▀▒░ ████▓▒░░▒████▓    ▒██████▒▒          ░▒▓███▀▒ ▓█   ▓██▒▒███████▒░▒████▒\n"
        L" ░▒   ▒ ░ ▒░▒░▒░  ▒▒▓  ▒    ▒ ▒▓▒ ▒ ░           ░▒   ▒  ▒▒   ▓▒█░░▒▒ ▓░▒░▒░░ ▒░ ░\n"
        L"  ░   ░   ░ ▒ ▒░  ░ ▒  ▒    ░ ░▒  ░ ░            ░   ░   ▒   ▒▒ ░░░▒ ▒ ░ ▒ ░ ░  ░\n"
        L"░ ░   ░ ░ ░ ░ ▒   ░ ░  ░    ░  ░  ░            ░ ░   ░   ░   ▒   ░ ░ ░ ░ ░   ░   \n";

    SetTextColor(hdc, RGB(178, 34, 34)); // Red
    SetBkMode(hdc, TRANSPARENT);

    SIZE textSize;
    GetTextExtentPoint32(hdc, banner, lstrlenW(banner), &textSize);
    int width = clientRect.right - clientRect.left;
    int height = clientRect.bottom - clientRect.top;

    int yStart = height / 3; // Vertical center (middle third)
    TextOutW(hdc, (width - textSize.cx) / 2, yStart, banner, lstrlenW(banner));
}

void CheckInternetConnection() {
    DWORD dwFlags;
    settings.internetAvailable = InternetGetConnectedState(&dwFlags, 0);
}

std::wstring GetTranslatedText(const std::wstring& key) {
    if (settings.language == LANG_FR) {
        if (key == L"search") return L"Rechercher";
        if (key == L"back") return L"Retour";
        if (key == L"settings") return L"Paramètres";
        if (key == L"theme") return L"Thème";
        if (key == L"language") return L"Langue";
        if (key == L"reset") return L"Réinitialiser";
        if (key == L"internet_error") return L"Il est nécessaire de bénéficier d’une connexion à internet pour pouvoir utiliser cette fonction";
        if (key == L"created") return L"Dossier créé dans le Bureau";
    } else {
        if (key == L"search") return L"Search";
        if (key == L"back") return L"Back";
        if (key == L"settings") return L"Settings";
        if (key == L"theme") return L"Theme";
        if (key == L"language") return L"Language";
        if (key == L"reset") return L"Reset";
        if (key == L"internet_error") return L"An Internet connection is required to use this function.";
        if (key == L"created") return L"Folder created on Desktop";
    }
    return key;
}

std::wstring GetSaveFolder() {
    if (!settings.savePath.empty()) return settings.savePath;

    wchar_t* desktopPath = nullptr;
    SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &desktopPath);
    std::wstring path(desktopPath);
    CoTaskMemFree(desktopPath);
    return path;
}

void SaveTextToFile(const std::wstring& folderName, const std::wstring& content) {
    std::wstring baseFolder = GetSaveFolder();
    std::wstring fullFolderPath = baseFolder + L"\\" + folderName;

    CreateDirectory(fullFolderPath.c_str(), NULL);

    std::wstring filePath = fullFolderPath + L"\\" + folderName + L".txt";
    std::wofstream out(filePath);
    if (out.is_open()) {
        out << content;
        out.close();
    }
}