#include "include/functions.h"
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

/// @brief Порт для связи
constexpr int PORT = 12345;

//-------------------------------------------------------------------------------------------------

// Функция для отправки файла на сервер
void sendFile(const std::string& filePath) {
    // Создание сокета
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Ошибка создания сокета\n";
        return;
    }

    // Настройка адреса сервера
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Адрес сервера (localhost)
    serverAddr.sin_port = htons(PORT);

    // Подключение к серверу
    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0) {
        std::cerr << "Ошибка подключения к серверу\n";
        close(clientSocket);
        return;
    }

    std::ifstream inputFile(filePath, std::ios::binary);

    // Проверка успешности открытия файла
    if (!inputFile.is_open()) {
        std::cerr << "Ошибка открытия файла для чтения\n";
        close(clientSocket);
        return;
    }

    std::cout << "Начало передачи файла...\n";

    char buffer[BUFFER_SIZE];
    while (!inputFile.eof()) {
        inputFile.read(buffer, sizeof(buffer));
        std::streamsize bytesRead = inputFile.gcount();

        // Отправка данных на сервер
        if (write(clientSocket, buffer, bytesRead) < 0) {
            std::cerr << "Ошибка передачи данных\n";
            break;
        }
    }

    inputFile.close();
    close(clientSocket);
    std::cout << "Файл успешно передан\n";
}
