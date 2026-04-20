#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "common.h"
#include "cat_images.h" 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    if (cats_count == 0) return 0; 

    BackupWallpaper(); 

    srand((unsigned int)time(NULL));
    int r = rand() % cats_count; 

    char tempPath[MAX_PATH];
    GetTempPathA(MAX_PATH, tempPath);
    strcat(tempPath, "local_cat_bg.jpg");

    FILE *f = fopen(tempPath, "wb");
    if (f) {
        fwrite(cats[r].data, 1, cats[r].len, f);
        fclose(f);
        SetWall(tempPath);
    }

    return 0;
}
