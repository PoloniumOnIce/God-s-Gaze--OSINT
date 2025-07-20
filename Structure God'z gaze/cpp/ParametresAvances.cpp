#include "ParametresAvances.h"
#include <windows.h>
#include <string>

static HWND hWndPage = NULL;
static HWND hEditChemin = NULL;
static HWND hBtnRetour = NULL;
static HWND hStaticTitre = NULL;
static HWND hStaticMessage = NULL;

static std::wstring cheminSauvegarde = L""; // par défaut vide = bureau
static bool langFR = true; // par défaut français

// Pour centrer horizontalement une fenêtre dans son parent
static void CenterChildWindow(HWND hwndChild, HWND hwndParent, int width, int height) {
    RECT rcParent;
    GetClientRect(hwndParent, &rcParent);
    int x = (rcParent.right - width) / 2;
    int y = (rcParent.bottom - height) / 3; // en haut, 1/3 hauteur
    SetWindowPos(hwndChild, NULL, x, y, width, height, SWP_NOZORDER | SWP_NOACTIVATE);
}

// Affiche ou masque la page
void ShowParametresAvancesPage(HWND hwndParent) {
    if (hWndPage == NULL) {
        hWndPage = CreateWindowEx(0, L"STATIC", NULL,
            WS_CHILD | WS_VISIBLE,
            0, 0, 0, 0,
            hwndParent, NULL, NULL, NULL);

        // Titre en rouge centré
        hStaticTitre = CreateWindowEx(0, L"STATIC", langFR ? L"Paramètres avancés" : L"Advanced Settings",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            0, 0, 300, 30,
            hWndPage, NULL, NULL, NULL);
        SendMessage(hStaticTitre, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
        SetTextColor((HDC)GetDC(hStaticTitre), RGB(178, 34, 34)); // rouge sang

        // Zone de saisie pour chemin
        hEditChemin = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", cheminSauvegarde.c_str(),
            WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
            0, 0, 300, 25,
            hWndPage, NULL, NULL, NULL);
        SendMessage(hEditChemin, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

        // Bouton retour
        hBtnRetour = CreateWindowEx(0, L"BUTTON", langFR ? L"Retour" : L"Back",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            0, 0, 100, 30,
            hWndPage, (HMENU)1001, NULL, NULL);
        SendMessage(hBtnRetour, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

        // Message petit en bas
        hStaticMessage = CreateWindowEx(0, L"STATIC", L"",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            0, 0, 300, 20,
            hWndPage, NULL, NULL, NULL);
        SendMessage(hStaticMessage, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

        // Couleur texte rouge pour titre et message
        HDC hdcTitre = GetDC(hStaticTitre);
        SetTextColor(hdcTitre, RGB(178, 34, 34));
        ReleaseDC(hStaticTitre, hdcTitre);

        HDC hdcMsg = GetDC(hStaticMessage);
        SetTextColor(hdcMsg, RGB(178, 34, 34));
        ReleaseDC(hStaticMessage, hdcMsg);
    }

    RECT rcParent;
    GetClientRect(hwndParent, &rcParent);

    MoveWindow(hWndPage, 0, 0, rcParent.right, rcParent.bottom, TRUE);

    // Positionnement éléments
    SetWindowPos(hStaticTitre, NULL, (rcParent.right - 300) / 2, 10, 300, 30, SWP_NOZORDER);
    SetWindowPos(hEditChemin, NULL, (rcParent.right - 300) / 2, 50, 300, 25, SWP_NOZORDER);
    SetWindowPos(hBtnRetour, NULL, 10, 10, 100, 30, SWP_NOZORDER);
    SetWindowPos(hStaticMessage, NULL, (rcParent.right - 300) / 2, rcParent.bottom - 40, 300, 20, SWP_NOZORDER);

    ShowWindow(hWndPage, SW_SHOW);
}

void HideParametresAvancesPage() {
    if (hWndPage) {
        ShowWindow(hWndPage, SW_HIDE);
    }
}

void ResetParametresAvances() {
    cheminSauvegarde = L"";
    if (hEditChemin) {
        SetWindowText(hEditChemin, cheminSauvegarde.c_str());
    }
    if (hStaticMessage) {
        SetWindowText(hStaticMessage, L"");
    }
}

void SetParametresAvancesLangFR() {
    langFR = true;
    if (hBtnRetour) SetWindowText(hBtnRetour, L"Retour");
    if (hStaticTitre) SetWindowText(hStaticTitre, L"Paramètres avancés");
}

void SetParametresAvancesLangEN() {
    langFR = false;
    if (hBtnRetour) SetWindowText(hBtnRetour, L"Back");
    if (hStaticTitre) SetWindowText(hStaticTitre, L"Advanced Settings");
}