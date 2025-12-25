#include "TaxiParkException.h"

// Конструктор исключения с параметрами
TaxiParkException::TaxiParkException(ExceptionType t, const std::string& msg)
    : type(t), message(msg) {                      // Инициализировать тип и сообщение об ошибке
}

// Получить тип исключения
ExceptionType TaxiParkException::getType() const {
    return type;                                    // Вернуть тип исключения
}

// Получить сообщение об ошибке (переопределение метода базового класса)
const char* TaxiParkException::what() const noexcept {
    return message.c_str();                         // Вернуть C-строку с сообщением об ошибке
}

// Получить строковое представление типа исключения
std::string TaxiParkException::getTypeString() const {
    switch (type) {                                 // Определить тип исключения
        case ExceptionType::FILE_ERROR:
            return "FILE_ERROR";                    // Ошибка работы с файлом
        case ExceptionType::INVALID_INPUT:
            return "INVALID_INPUT";                 // Некорректный ввод данных
        case ExceptionType::NOT_FOUND:
            return "NOT_FOUND";                     // Объект не найден
        case ExceptionType::DUPLICATE_ENTRY:
            return "DUPLICATE_ENTRY";               // Дублирование записи
        case ExceptionType::INVALID_OPERATION:
            return "INVALID_OPERATION";             // Некорректная операция
        case ExceptionType::DATA_CORRUPTION:
            return "DATA_CORRUPTION";               // Повреждение данных
        default:
            return "UNKNOWN";                       // Неизвестный тип
    }
}

