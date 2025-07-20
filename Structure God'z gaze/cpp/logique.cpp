#include "main.h"
#include <windows.h>
#include <shlobj.h>
#include <string>
#include <fstream>

void CreerDossier(const std::wstring& nomDossier) {
    std::wstring cheminBase;

    if (!app.cheminDossier.empty()) {
        cheminBase = app.cheminDossier;
    } else {
        // Récupérer le chemin du Bureau
        wchar_t bureau[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_DESKTOPDIRECTORY, nullptr, 0, bureau))) {
            cheminBase = bureau;
        } else {
            cheminBase = L".";
        }
    }

    std::wstring cheminComplet = cheminBase + L"\\" + nomDossier;

    // Créer le dossier s'il n'existe pas
    CreateDirectoryW(cheminComplet.c_str(), nullptr);

    // Créer un fichier txt avec un résumé (placeholder)
    std::wstring fichierRes = cheminComplet + L"\\resultats.txt";

    std::wofstream fichier(fichierRes, std::ios::out | std::ios::trunc);
    if (fichier.is_open()) {
        fichier << L"Résultats pour : " << nomDossier << L"\n\n";
        fichier << L"Snapchat : trouvé\nInstagram : non trouvé\nFacebook : non trouvé\nGitHub : trouvé\n";
        fichier.close();
    }
}

void EffectuerRecherchePseudo(const std::wstring& pseudo) {
    CreerDossier(pseudo);
}

void EffectuerRechercheIP(const std::wstring& ip) {
    CreerDossier(ip);
}

void EffectuerRechercheEmail(const std::wstring& email) {
    CreerDossier(email);
}