#ifndef TAXIVEHICLE_H
#define TAXIVEHICLE_H

#include "../core/Vehicle.h"
#include <string>

// Перечисление типов такси-транспортных средств
enum class VehicleType {
    ECONOMY,                                   // Эконом-класс
    COMFORT,                                   // Комфорт-класс
    BUSINESS,                                  // Бизнес-класс
    MINIVAN                                    // Минивэн
};

// Класс такси-транспортного средства, наследуется от Vehicle
class TaxiVehicle : public Vehicle {
protected:
    VehicleType vehicleType;                   // Тип транспортного средства
    int seats;                                 // Количество мест
    std::string category;                      // Категория транспортного средства
    int luggageCapacity;                       // Объем багажника в литрах

public:
    TaxiVehicle();                             // Конструктор по умолчанию
    TaxiVehicle(const std::string& brand, const std::string& model, int year,
                const std::string& licensePlate, int mileage, VehicleStatus status,
                VehicleType vehicleType, int seats, const std::string& category, int luggageCapacity);  // Конструктор с параметрами
    virtual ~TaxiVehicle() = default;          // Виртуальный деструктор

    VehicleType getVehicleType() const;        // Получить тип транспортного средства
    int getSeats() const;                     // Получить количество мест
    std::string getCategory() const;           // Получить категорию
    int getLuggageCapacity() const;            // Получить объем багажника
    std::string getVehicleTypeString() const;  // Получить строковое представление типа

    void setVehicleType(VehicleType vehicleType);  // Установить тип транспортного средства
    void setSeats(int seats);                  // Установить количество мест
    void setCategory(const std::string& category);  // Установить категорию
    void setLuggageCapacity(int capacity);     // Установить объем багажника

    std::string toString() const override;     // Переопределить метод преобразования в строку
    std::string toFileString() const override; // Переопределить метод преобразования для файла
    void fromFileString(const std::string& data) override;  // Переопределить метод восстановления из файла
};

#endif // TAXIVEHICLE_H

