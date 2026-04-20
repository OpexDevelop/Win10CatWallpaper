#ifndef COMMON_H
#define COMMON_H

#include <windows.h>
#include <string.h>

void BackupWallpaper() {
    HKEY hKey;
    char currentPath[MAX_PATH];
    
    if (!SystemParametersInfoA(SPI_GETDESKWALLPAPER, MAX_PATH, currentPath, 0)) return;

    if (RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\CatWallpaper", 0, NULL, 0, KEY_READ | KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
        DWORD type;
        char checkPath[MAX_PATH];
        DWORD size = MAX_PATH;
        
        if (RegQueryValueExA(hKey, "Backup", NULL, &type, (LPBYTE)checkPath, &size) != ERROR_SUCCESS) {
            RegSetValueExA(hKey, "Backup", 0, REG_SZ, (const BYTE*)currentPath, strlen(currentPath) + 1);
        }
        RegCloseKey(hKey);
    }
}

void SetWall(const char* path) {
    HKEY hKey;
    if(RegOpenKeyExA(HKEY_CURRENT_USER, "Control Panel\\Desktop", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        RegSetValueExA(hKey, "WallpaperStyle", 0, REG_SZ, (const BYTE*)"10", 3);
        RegSetValueExA(hKey, "TileWallpaper", 0, REG_SZ, (const BYTE*)"0", 2);
        RegCloseKey(hKey);
    }
    SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (void*)path, SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);
}

#endif
