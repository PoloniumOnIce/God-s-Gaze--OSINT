#include <windows.h>
#include <commctrl.h>
#include "internet.h"
#include "ui.h"
#include "config.h"
#include "language.h"
#include "style.h"

// Identifiants des pages
enum class Page { Accueil, Pseudo, IP, Email, Image, Parametres };
static Page currentPage = Page::Accueil;

HINSTANCE g_hInst;
HWND g_hWnd;

// Prototypes
void SwitchPage(Page p);
Page  GetPageFromTab(int idx);
int   GetTabFromPage(Page p);

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    g_hInst = hInstance;
    InitCommonControls();

    WNDCLASSEX wc = { sizeof(wc) };
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProcMain;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(GetColor_Background());
    wc.lpszClassName = "GodsGazeMain";

    if (!RegisterClassEx(&wc)) return 0;
    g_hWnd = CreateWindowEx(0, wc.lpszClassName, L"God's Gaze - By Polønium",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 900, 600,
        nullptr, nullptr, hInstance, nullptr);
    if (!g_hWnd) return 0;

    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);
    // Vérifie l'Internet dès le début
    Config::isOnline = Internet::Check();
    UI::Init(g_hWnd);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}

// Changement de page
void SwitchPage(Page p) {
    if (p == currentPage) return;
    currentPage = p;
    UI::SwitchTab(GetTabFromPage(p));
}

// Conversion entre Tab index et Page
int GetTabFromPage(Page p) {
    switch (p) {
        case Page::Accueil: return 0;
        case Page::Parametres: return 1;
        case Page::Pseudo: return 2;
        case Page::IP: return 3;
        case Page::Email: return 4;
        case Page::Image: return 5;
    }
    return 0;
}
Page GetPageFromTab(int idx) {
    static Page map[] = {
        Page::Accueil, Page::Parametres,
        Page::Pseudo, Page::IP,
        Page::Email, Page::Image
    };
    return (idx >= 0 && idx < _countof(map)) ? map[idx] : Page::Accueil;
}

// Gestionnaire principal
LRESULT CALLBACK WndProcMain(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_SIZE:
        UI::OnResize();
        break;
    case WM_NOTIFY:
        if (lParam && ((LPNMHDR)lParam)->hwndFrom == UI::GetTabHandle() &&
            ((LPNMHDR)lParam)->code == TCN_SELCHANGE) {
            int idx = UI::GetTabHandleCurSel();
            SwitchPage(GetPageFromTab(idx));
        }
        break;
    case WM_COMMAND:
        UI::HandleCommand(LOWORD(wParam));
        break;
    case WM_PAINT:
        UI::OnPaint();
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}