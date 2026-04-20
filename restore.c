#include <windows.h>
#include "common.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\CatWallpaper", 0, KEY_READ | KEY_WRITE, &hKey) == ERROR_SUCCESS) {
        char backupPath[MAX_PATH];
        DWORD size = MAX_PATH;
        
        if (RegQueryValueExA(hKey, "Backup", NULL, NULL, (LPBYTE)backupPath, &size) == ERROR_SUCCESS) {
            SetWall(backupPath);
            RegDeleteValueA(hKey, "Backup");
        }
        RegCloseKey(hKey);
    }
    return 0;
}
