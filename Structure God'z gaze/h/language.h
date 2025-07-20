#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <string>
#include <map>

enum class Langue {
    FRANCAIS,
    ANGLAIS
};

class Language {
public:
    static void setLangue(Langue langue);
    static Langue getLangue();
    static std::string get(const std::string& key);

private:
    static Langue currentLangue;
    static std::map<std::string, std::string> textesFR;
    static std::map<std::string, std::string> textesEN;
};

#endif