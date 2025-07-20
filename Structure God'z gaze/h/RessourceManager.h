#ifndef RESSOURCE_MANAGER_H
#define RESSOURCE_MANAGER_H

#include <windows.h>
#include <unordered_map>
#include <string>

class RessourceManager {
public:
    static HICON GetIcon(const std::string& name);
    static void LoadIcons();

private:
    static std::unordered_map<std::string, HICON> icons;
};

#endif