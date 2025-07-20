#ifndef MAIN_H
#define MAIN_H

#include <windows.h>
#include <string>
#include <vector>

// Constantes pour les identifiants des boutons/pages
enum Page {
    PAGE_ACCUEIL,
    PAGE_PSEUDO,
    PAGE_IP,
    PAGE_EMAIL,
    PAGE_IMAGE,
    PAGE_PARAMETRES,
};

enum Theme {
    THEME_SOMBRE,
    THEME_CLAIR
};

enum Langue {
    LANGUE_FR,
    LANGUE_EN
};

// Structure globale pour l'état de l'application
struct AppState {
    HWND hWnd;
    HWND zoneSaisie;
    HWND boutonRecherche;
    HWND boutonRetour;
    HWND boutonImageLink;
    HWND boutonImageFichier;
    HWND boutonImageFace;
    HWND boutonImageReverse;
    HWND labelTitre;
    HWND labelErreur;
    HFONT font;
    Page pageActuelle = PAGE_ACCUEIL;
    Theme theme = THEME_SOMBRE;
    Langue langue = LANGUE_FR;
    bool imageLinkMode = false;
    bool imageLoaded = false;
    bool connected = true;
    std::wstring cheminDossier = L"";
};

extern AppState app;

// Fonctions principales
void ChangerDePage(Page nouvellePage);
void AppliquerTheme();
void AppliquerLangue();
void VerifierConnexionInternet();
void AfficherAccueil(HWND hWnd);
void AfficherPagePseudo(HWND hWnd);
void AfficherPageIP(HWND hWnd);
void AfficherPageEmail(HWND hWnd);
void AfficherPageImage(HWND hWnd);
void AfficherParametres(HWND hWnd);
void AfficherTitre(HWND hWnd, const std::wstring& texte);
void AfficherLabelErreur(HWND hWnd, const std::wstring& message);
void SupprimerElementsPage(HWND hWnd);
void ReinitialiserParametres();

#endif