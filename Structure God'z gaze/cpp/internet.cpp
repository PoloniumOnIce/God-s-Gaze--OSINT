#include "internet.h"
#include <windows.h>
#include <wininet.h>

#pragma comment(lib, "wininet.lib")

bool Internet::isConnected() {
    return InternetCheckConnectionA("http://www.google.com", FLAG_ICC_FORCE_CONNECTION, 0);
}