#include <windows.h>
#include <urlmon.h>
#include <wininet.h>
#include "common.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    BackupWallpaper();

    char tempPath[MAX_PATH];
    GetTempPathA(MAX_PATH, tempPath);
    strcat(tempPath, "online_cat_bg.jpg");

    // 1. Меняем источник. cataas.com часто блокирует запросы.
    // loremflickr выдает отличные картинки котов в Full HD и не банит скрипты.
    const char* url = "https://loremflickr.com/1920/1080/cat";

    // 2. Очищаем кэш IE. URLDownloadToFile любит кэшировать ошибки "намертво".
    DeleteUrlCacheEntryA(url);

    // Функция синхронная, но loremflickr отвечает быстро.
    HRESULT hr = URLDownloadToFileA(NULL, url, tempPath, 0, NULL);
    
    if (hr == S_OK) {
        // 3. Убедимся, что скачалась реальная картинка, а не HTML-страница с ошибкой
        HANDLE hFile = CreateFileA(tempPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile != INVALID_HANDLE_VALUE) {
            DWORD size = GetFileSize(hFile, NULL);
            CloseHandle(hFile);
            
            // Если размер файла больше 5 КБ, это с вероятностью 99% картинка
            if (size > 5000) {
                SetWall(tempPath);
            }
        }
    }

    return 0;
}
