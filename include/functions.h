#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

/// @brief Размер буфера для передачи данных
constexpr int BUFFER_SIZE = 1024;

/// @brief Функция для отправки файла на сервер
void sendFile(const std::string& filePath);

#endif // FUNCTIONS_H
