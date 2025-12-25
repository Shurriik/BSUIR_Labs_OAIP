#ifndef TAXIPARKEXCEPTION_H
#define TAXIPARKEXCEPTION_H

#include <string>
#include <exception>

// Перечисление типов исключений
enum class ExceptionType {
    FILE_ERROR,                                 // Ошибка работы с файлом
    INVALID_INPUT,                              // Некорректный ввод данных
    NOT_FOUND,                                  // Объект не найден
    DUPLICATE_ENTRY,                            // Дублирование записи
    INVALID_OPERATION,                          // Некорректная операция
    DATA_CORRUPTION                             // Повреждение данных
};

// Класс исключения для системы управления таксопарком
class TaxiParkException : public std::exception {
private:
    ExceptionType type;                         // Тип исключения
    std::string message;                        // Сообщение об ошибке

public:
    TaxiParkException(ExceptionType t, const std::string& msg);  // Конструктор с параметрами
    virtual ~TaxiParkException() noexcept = default;  // Виртуальный деструктор
    
    ExceptionType getType() const;               // Получить тип исключения
    const char* what() const noexcept override; // Получить сообщение об ошибке (переопределение метода базового класса)
    std::string getTypeString() const;          // Получить строковое представление типа исключения
};

#endif // TAXIPARKEXCEPTION_H

