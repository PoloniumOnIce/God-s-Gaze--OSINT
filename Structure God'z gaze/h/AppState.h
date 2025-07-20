#ifndef APPSTATE_H
#define APPSTATE_H

#include <string>

enum class Theme {
    Sombre,
    Clair
};

enum class Langue {
    Francais,
    Anglais
};

struct AppState {
    Theme theme = Theme::Sombre;
    Langue langue = Langue::Francais;
    bool internetActif = true;
    std::string cheminSauvegarde = ""; // Par défaut : bureau
};

#endif // APPSTATE_H