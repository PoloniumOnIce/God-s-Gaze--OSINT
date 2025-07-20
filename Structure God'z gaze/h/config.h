#ifndef CONFIG_H
#define CONFIG_H

#include <string>

enum class Theme
{
    Sombre,
    Clair
};

enum class Langue
{
    FR,
    EN
};

struct Configuration
{
    Theme themeActuel = Theme::Sombre;
    Langue langueActuelle = Langue::FR;
    std::string cheminSauvegarde = ""; // Bureau par défaut (défini dynamiquement au démarrage)
    bool internetDisponible = false;
    bool imageChargee = false;
};

extern Configuration CONFIG;

#endif // CONFIG_H