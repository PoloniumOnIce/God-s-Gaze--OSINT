#include "main.h"
#include <commctrl.h>
#include <shlobj.h>
#include <fstream>
#include <wininet.h>

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "wininet.lib")

AppState app;

void VerifierConnexionInternet() {
    DWORD dwFlags;
    app.connected = InternetGetConnectedState(&dwFlags, 0);
}

void AppliquerTheme() {
    COLORREF fond = (app.theme == THEME_SOMBRE) ? RGB(45, 45, 45) : RGB(255, 255, 255);
    SendMessage(app.hWnd, WM_CTLCOLORDLG, 0, (LPARAM)fond);
    InvalidateRect(app.hWnd, NULL, TRUE);
}

void AppliquerLangue() {
    // À implémenter plus tard pour changer les textes
}

void SupprimerElementsPage(HWND hWnd) {
    EnumChildWindows(hWnd, [](HWND hwnd, LPARAM) -> BOOL {
        DestroyWindow(hwnd);
        return TRUE;
    }, 0);
}

void AfficherLabelErreur(HWND hWnd, const std::wstring& message) {
    if (app.labelErreur) DestroyWindow(app.labelErreur);

    app.labelErreur = CreateWindowW(L"STATIC", message.c_str(),
        WS_CHILD | WS_VISIBLE,
        10, 450, 700, 25,
        hWnd, nullptr, nullptr, nullptr);

    SetWindowLongPtr(app.labelErreur, GWLP_ID, 9000);
    SetTextColor((HDC)GetDC(app.labelErreur), RGB(178, 34, 34));
}

void AfficherTitre(HWND hWnd, const std::wstring& texte) {
    if (app.labelTitre) DestroyWindow(app.labelTitre);

    app.labelTitre = CreateWindowW(L"STATIC", texte.c_str(),
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        200, 20, 400, 30,
        hWnd, nullptr, nullptr, nullptr);

    SetWindowLongPtr(app.labelTitre, GWLP_ID, 8000);
}

void AjouterBoutonRetour(HWND hWnd) {
    app.boutonRetour = CreateWindowW(L"BUTTON", L"←",
        WS_CHILD | WS_VISIBLE,
        10, 10, 50, 30,
        hWnd, (HMENU)1000, nullptr, nullptr);
}

void AfficherZoneSaisieEtBouton(HWND hWnd, int boutonID) {
    app.zoneSaisie = CreateWindowW(L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        200, 150, 400, 30,
        hWnd, nullptr, nullptr, nullptr);

    app.boutonRecherche = CreateWindowW(L"BUTTON", L"Rechercher",
        WS_CHILD | WS_VISIBLE,
        300, 200, 200, 40,
        hWnd, (HMENU)boutonID, nullptr, nullptr);
}

void ChangerDePage(Page nouvellePage) {
    SupprimerElementsPage(app.hWnd);
    app.pageActuelle = nouvellePage;

    switch (nouvellePage) {
        case PAGE_ACCUEIL:
            AfficherAccueil(app.hWnd);
            break;
        case PAGE_PSEUDO:
            AfficherPagePseudo(app.hWnd);
            break;
        case PAGE_IP:
            AfficherPageIP(app.hWnd);
            break;
        case PAGE_EMAIL:
            AfficherPageEmail(app.hWnd);
            break;
        case PAGE_IMAGE:
            AfficherPageImage(app.hWnd);
            break;
        case PAGE_PARAMETRES:
            AfficherParametres(app.hWnd);
            break;
    }
}

void AfficherAccueil(HWND hWnd) {
    VerifierConnexionInternet();

    // Bannière ASCII au centre vertical
    CreateWindowW(L"STATIC", L"   _____           _     _____                   \n  / ____|         | |   / ____|                  \n | |  __  ___  ___| |_ | |  __  __ _ _ __ ___   \n | | |_ |/ _ \\/ __| __|| | |_ |/ _` | '_ ` _ \\  \n | |__| |  __/\\__ \\ |_ | |__| | (_| | | | | | | \n  \\_____|\\___||___/\\__(_)_____|\\__,_|_| |_| |_| \n",
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        0, 200, 800, 120, hWnd, nullptr, nullptr, nullptr);

    // Boutons du menu principal
    CreateWindowW(L"BUTTON", L"Pseudo", WS_CHILD | WS_VISIBLE, 300, 350, 200, 40, hWnd, (HMENU)2001, nullptr, nullptr);
    CreateWindowW(L"BUTTON", L"IP", WS_CHILD | WS_VISIBLE, 300, 400, 200, 40, hWnd, (HMENU)2002, nullptr, nullptr);
    CreateWindowW(L"BUTTON", L"Email", WS_CHILD | WS_VISIBLE, 300, 450, 200, 40, hWnd, (HMENU)2003, nullptr, nullptr);
    CreateWindowW(L"BUTTON", L"Image", WS_CHILD | WS_VISIBLE | (app.connected ? 0 : WS_DISABLED), 300, 500, 200, 40, hWnd, (HMENU)2004, nullptr, nullptr);
    CreateWindowW(L"BUTTON", L"Paramètres", WS_CHILD | WS_VISIBLE, 300, 550, 200, 40, hWnd, (HMENU)2005, nullptr, nullptr);

    if (!app.connected) {
        AfficherLabelErreur(hWnd, L"Il est nécessaire de bénéficier d’une connexion à internet pour pouvoir utiliser cette fonction");
    }
}

void AfficherPagePseudo(HWND hWnd) {
    AjouterBoutonRetour(hWnd);
    AfficherTitre(hWnd, L"Recherche par pseudo");
    AfficherZoneSaisieEtBouton(hWnd, 3001);
}

void AfficherPageIP(HWND hWnd) {
    AjouterBoutonRetour(hWnd);
    AfficherTitre(hWnd, L"Recherche par IP");
    AfficherZoneSaisieEtBouton(hWnd, 3002);
}

void AfficherPageEmail(HWND hWnd) {
    AjouterBoutonRetour(hWnd);
    AfficherTitre(hWnd, L"Recherche par Email");
    AfficherZoneSaisieEtBouton(hWnd, 3003);
}

void AfficherParametres(HWND hWnd) {
    AjouterBoutonRetour(hWnd);
    AfficherTitre(hWnd, L"Paramètres");

    CreateWindowW(L"BUTTON", L"Thème : Sombre/Clair", WS_CHILD | WS_VISIBLE, 300, 200, 200, 40, hWnd, (HMENU)4001, nullptr, nullptr);
    CreateWindowW(L"BUTTON", L"Langue : FR/EN", WS_CHILD | WS_VISIBLE, 300, 250, 200, 40, hWnd, (HMENU)4002, nullptr, nullptr);
    CreateWindowW(L"BUTTON", L"Réinitialiser", WS_CHILD | WS_VISIBLE, 300, 300, 200, 40, hWnd, (HMENU)4003, nullptr, nullptr);
}

void AfficherPageImage(HWND hWnd) {
    AjouterBoutonRetour(hWnd);
    AfficherTitre(hWnd, L"Recherche par image");

    app.boutonImageFichier = CreateWindowW(L"BUTTON", L"Déposer image(s)", WS_CHILD | WS_VISIBLE,
        220, 200, 160, 40, hWnd, (HMENU)5001, nullptr, nullptr);

    app.boutonImageLink = CreateWindowW(L"BUTTON", L"Coller lien(s)", WS_CHILD | WS_VISIBLE,
        420, 200, 160, 40, hWnd, (HMENU)5002, nullptr, nullptr);
}

void ReinitialiserParametres() {
    app.theme = THEME_SOMBRE;
    app.langue = LANGUE_FR;
    app.cheminDossier = L"";
    AppliquerTheme();
    AppliquerLangue();
    ChangerDePage(PAGE_ACCUEIL);
}