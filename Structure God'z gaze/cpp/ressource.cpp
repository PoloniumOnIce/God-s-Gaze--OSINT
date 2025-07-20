#include <windows.h>
#include "resource.h"

// Variables globales statiques pour stocker les handles des icônes
static HICON hIconWifiOn = NULL;
static HICON hIconWifiOff = NULL;

// Charger toutes les ressources
bool LoadResources(HINSTANCE hInst)
{
    // Charger l'icône wifi ON
    hIconWifiOn = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_WIFI_ON), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
    if (!hIconWifiOn) return false;

    // Charger l'icône wifi OFF (barré)
    hIconWifiOff = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_WIFI_OFF), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
    if (!hIconWifiOff)
    {
        if (hIconWifiOn)
        {
            DestroyIcon(hIconWifiOn);
            hIconWifiOn = NULL;
        }
        return false;
    }

    return true;
}

// Libérer toutes les ressources (appeler avant fermeture)
void FreeResources()
{
    if (hIconWifiOn)
    {
        DestroyIcon(hIconWifiOn);
        hIconWifiOn = NULL;
    }
    if (hIconWifiOff)
    {
        DestroyIcon(hIconWifiOff);
        hIconWifiOff = NULL;
    }
}

// Obtenir l'icône wifi ON
HICON GetWifiIconOn()
{
    return hIconWifiOn;
}

// Obtenir l'icône wifi OFF
HICON GetWifiIconOff()
{
    return hIconWifiOff;
}