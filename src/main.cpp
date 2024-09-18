#include "include/functions.h"
#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {
    // Проверка аргументов командной строки
    if (argc != 3 || std::strcmp(argv[1], "-c") != 0) {
        std::cerr << "Неверные параметры запуска. Используйте '-c' и путь к файлу для запуска клиента.\n";
        return 1;
    }

    // Отправка файла
    sendFile(argv[2]);
    return 0;
}
