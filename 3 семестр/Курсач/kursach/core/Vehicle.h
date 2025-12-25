#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

// Перечисление статусов транспортного средства
enum class VehicleStatus {
    ON_LINE,                                   // Транспортное средство на линии
    IN_PARK,                                   // Транспортное средство в парке
    IN_REPAIR                                  // Транспортное средство в ремонте
};

// Базовый абстрактный класс транспортного средства
class Vehicle {
protected:
    int id;                                    // Уникальный идентификатор транспортного средства
    std::string brand;                         // Марка автомобиля
    std::string model;                         // Модель автомобиля
    int year;                                  // Год выпуска
    std::string licensePlate;                  // Государственный номерной знак
    int mileage;                               // Пробег в километрах
    VehicleStatus status;                       // Текущий статус транспортного средства

    static int nextId;                         // Статическая переменная для генерации следующего идентификатора

public:
    Vehicle();                                 // Конструктор по умолчанию
    Vehicle(const std::string& brand, const std::string& model, int year,
            const std::string& licensePlate, int mileage, VehicleStatus status);  // Конструктор с параметрами
    virtual ~Vehicle() = default;               // Виртуальный деструктор

    // Методы получения значений (геттеры)
    int getId() const;                         // Получить идентификатор транспортного средства
    std::string getBrand() const;              // Получить марку автомобиля
    std::string getModel() const;               // Получить модель автомобиля
    int getYear() const;                       // Получить год выпуска
    std::string getLicensePlate() const;        // Получить номерной знак
    int getMileage() const;                    // Получить пробег
    VehicleStatus getStatus() const;            // Получить статус транспортного средства
    std::string getStatusString() const;        // Получить строковое представление статуса

    // Методы установки значений (сеттеры)
    void setId(int id);                        // Установить идентификатор
    void setBrand(const std::string& brand);   // Установить марку
    void setModel(const std::string& model);   // Установить модель
    void setYear(int year);                    // Установить год выпуска
    void setLicensePlate(const std::string& licensePlate);  // Установить номерной знак
    void setMileage(int mileage);              // Установить пробег
    void setStatus(VehicleStatus status);      // Установить статус

    // Основные методы
    virtual bool needsMaintenance() const;      // Проверить необходимость технического обслуживания
    virtual std::string toString() const;      // Преобразовать объект в строку для отображения
    virtual std::string toFileString() const;  // Преобразовать объект в строку для сохранения в файл
    virtual void fromFileString(const std::string& data);  // Восстановить объект из строки файла

    // Виртуальные методы для полиморфного поведения
    virtual std::string getType() const = 0;   // Получить тип транспортного средства (чисто виртуальный)
    virtual Vehicle* clone() const = 0;        // Создать копию объекта (чисто виртуальный)
};

#endif 

