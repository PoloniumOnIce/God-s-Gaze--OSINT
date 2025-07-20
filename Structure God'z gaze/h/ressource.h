#ifndef RESOURCE_H
#define RESOURCE_H

#include <windows.h>

bool LoadResources(HINSTANCE hInst);
void FreeResources();

HICON GetWifiIconOn();
HICON GetWifiIconOff();

#endif // RESOURCE_H