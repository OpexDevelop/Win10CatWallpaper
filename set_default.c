#include <windows.h>
#include <string.h>
#include "common.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    char path[MAX_PATH];
    
    // Получаем полный путь к нашему запущенному .exe
    if (GetModuleFileNameA(NULL, path, MAX_PATH) == 0) {
        return 1;
    }

    // Ищем последний обратный слэш, чтобы отрезать имя экзешника и получить папку
    char* lastSlash = strrchr(path, '\\');
    if (lastSlash != NULL) {
        *(lastSlash + 1) = '\0'; // Оставляем слеш и обрываем строку
    }

    // Приклеиваем имя картинки, которую будем ставить
    strcat(path, "default.jpg");

    // Проверяем, существует ли файл физически (чтобы не поставить "черный экран")
    HANDLE hFile = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        CloseHandle(hFile);
        
        // Вызываем функцию установки обоев из твоего common.h
        SetWall(path);
    } else {
        // Если файла нет, выдаем ошибку, чтобы было понятно, в чем дело
        MessageBoxA(NULL, "Файл 'default.jpg' не найден!\nПоложите его в ту же папку, где находится программа.", "Ошибка", MB_OK | MB_ICONERROR);
    }

    return 0;
}
