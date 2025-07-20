#include "RessourceManager.h"
#include "resource.h"

std::unordered_map<std::string, HICON> RessourceManager::icons;

void RessourceManager::LoadIcons() {
    icons["wifi_on"]  = (HICON)LoadImage(NULL, L"resrc\\wifi_on.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
    icons["wifi_off"] = (HICON)LoadImage(NULL, L"resrc\\wifi_off.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
}

HICON RessourceManager::GetIcon(const std::string& name) {
    auto it = icons.find(name);
    if (it != icons.end()) {
        return it->second;
    }
    return nullptr;
}