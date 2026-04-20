#include <windows.h>
#include <urlmon.h>
#include "common.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    BackupWallpaper();

    char tempPath[MAX_PATH];
    GetTempPathA(MAX_PATH, tempPath);
    strcat(tempPath, "online_cat_bg.jpg");

    HRESULT hr = URLDownloadToFileA(NULL, "https://cataas.com/cat", tempPath, 0, NULL);
    
    if (hr == S_OK) {
        SetWall(tempPath);
    }

    return 0;
}
