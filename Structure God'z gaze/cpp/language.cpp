#include "language.h"

Langue Language::currentLangue = Langue::FRANCAIS;

std::map<std::string, std::string> Language::textesFR = {
    {"accueil", "Accueil"},
    {"pseudo", "Pseudo"},
    {"ip", "Adresse IP"},
    {"email", "Email"},
    {"image", "Image"},
    {"parametres", "Paramètres"},
    {"recherche", "Rechercher"},
    {"retour", "Retour"},
    {"aucun_resultat", "Aucun résultat trouvé"},
    {"dossier_cree", "Dossier créé dans le Bureau"},
    {"besoin_internet", "Connexion internet requise pour cette fonction"},
    {"theme_sombre", "Thème sombre"},
    {"theme_clair", "Thème clair"},
    {"langue", "Langue"},
    {"reset", "Réinitialiser"},
    {"sauvegarde_chemin", "Chemin de sauvegarde personnalisé"}
};

std::map<std::string, std::string> Language::textesEN = {
    {"accueil", "Home"},
    {"pseudo", "Username"},
    {"ip", "IP Address"},
    {"email", "Email"},
    {"image", "Image"},
    {"parametres", "Settings"},
    {"recherche", "Search"},
    {"retour", "Back"},
    {"aucun_resultat", "No result found"},
    {"dossier_cree", "Folder created on Desktop"},
    {"besoin_internet", "Internet connection required for this function"},
    {"theme_sombre", "Dark Theme"},
    {"theme_clair", "Light Theme"},
    {"langue", "Language"},
    {"reset", "Reset"},
    {"sauvegarde_chemin", "Custom save path"}
};

void Language::setLangue(Langue langue) {
    currentLangue = langue;
}

Langue Language::getLangue() {
    return currentLangue;
}

std::string Language::get(const std::string& key) {
    if (currentLangue == Langue::FRANCAIS) {
        return textesFR[key];
    } else {
        return textesEN[key];
    }
}