#include "TaxiVehicle.h"
#include "../core/List.h"
#include <sstream>
#include <stdexcept>

// Конструктор по умолчанию
TaxiVehicle::TaxiVehicle()
    : Vehicle(), vehicleType(VehicleType::ECONOMY), seats(4), category("Standard"), luggageCapacity(300) {
}

// Конструктор с параметрами
TaxiVehicle::TaxiVehicle(const std::string& brand, const std::string& model, int year,
                         const std::string& licensePlate, int mileage, VehicleStatus status,
                         VehicleType vehicleType, int seats, const std::string& category, int luggageCapacity)
    : Vehicle(brand, model, year, licensePlate, mileage, status),
      vehicleType(vehicleType), seats(seats), category(category), luggageCapacity(luggageCapacity) {
    if (seats < 1 || seats > 20) {             // Проверка корректности количества мест
        throw std::invalid_argument("Invalid number of seats");
    }
    if (luggageCapacity < 0) {                 // Проверка корректности объема багажника
        throw std::invalid_argument("Luggage capacity cannot be negative");
    }
}

// Получить тип транспортного средства
VehicleType TaxiVehicle::getVehicleType() const {
    return vehicleType;
}

// Получить количество мест
int TaxiVehicle::getSeats() const {
    return seats;
}

// Получить категорию
std::string TaxiVehicle::getCategory() const {
    return category;
}

// Получить объем багажника
int TaxiVehicle::getLuggageCapacity() const {
    return luggageCapacity;
}

// Получить строковое представление типа транспортного средства
std::string TaxiVehicle::getVehicleTypeString() const {
    switch (vehicleType) {
        case VehicleType::ECONOMY:
            return "Эконом";
        case VehicleType::COMFORT:
            return "Комфорт";
        case VehicleType::BUSINESS:
            return "Бизнес";
        case VehicleType::MINIVAN:
            return "Минивэн";
        default:
            return "Неизвестно";
    }
}

// Установить тип транспортного средства
void TaxiVehicle::setVehicleType(VehicleType vehicleType) {
    this->vehicleType = vehicleType;
}

// Установить количество мест
void TaxiVehicle::setSeats(int seats) {
    if (seats < 1 || seats > 20) {             // Проверка корректности количества мест
        throw std::invalid_argument("Invalid number of seats");
    }
    this->seats = seats;
}

// Установить категорию
void TaxiVehicle::setCategory(const std::string& category) {
    this->category = category;
}

// Установить объем багажника
void TaxiVehicle::setLuggageCapacity(int capacity) {
    if (capacity < 0) {                        // Проверка корректности объема багажника
        throw std::invalid_argument("Luggage capacity cannot be negative");
    }
    this->luggageCapacity = capacity;
}

// Переопределить метод преобразования в строку для отображения
std::string TaxiVehicle::toString() const {
    std::ostringstream oss;
    oss << Vehicle::toString() << ", Тип: " << getVehicleTypeString()
        << ", Мест: " << seats << ", Категория: " << category
        << ", Объем багажа: " << luggageCapacity << " л";
    return oss.str();
}

// Переопределить метод преобразования в строку для сохранения в файл
std::string TaxiVehicle::toFileString() const {
    std::ostringstream oss;
    oss << Vehicle::toFileString() << "|" << static_cast<int>(vehicleType)
        << "|" << seats << "|" << category << "|" << luggageCapacity;
    return oss.str();
}

// Переопределить метод восстановления объекта из строки файла
void TaxiVehicle::fromFileString(const std::string& data) {
    Vehicle::fromFileString(data);             // Вызвать метод базового класса
    std::istringstream iss(data);              // Создать поток из строки данных
    std::string token;                         // Текущий токен при разборе
    List<std::string> tokens;                  // Список всех токенов
    
    while (std::getline(iss, token, '|')) {    // Разделить строку по символу '|'
        tokens.push_back(token);
    }
    
    if (tokens.size() >= 11) {                 // Новый формат с объемом багажника
        auto it = tokens.begin();
        for (int i = 0; i < 7 && it != tokens.end(); ++i, ++it) {}  // Пропустить поля базового класса
        if (it != tokens.end()) {
            vehicleType = static_cast<VehicleType>(std::stoi(*it++));  // Получить тип
            if (it != tokens.end()) seats = std::stoi(*it++);          // Получить количество мест
            if (it != tokens.end()) category = *it++;                  // Получить категорию
            if (it != tokens.end()) luggageCapacity = std::stoi(*it);  // Получить объем багажника
        }
    } else if (tokens.size() >= 10) {
        // Обратная совместимость - старый формат без объема багажника
        auto it = tokens.begin();
        for (int i = 0; i < 7 && it != tokens.end(); ++i, ++it) {}  // Пропустить поля базового класса
        if (it != tokens.end()) {
            vehicleType = static_cast<VehicleType>(std::stoi(*it++));  // Получить тип
            if (it != tokens.end()) seats = std::stoi(*it++);          // Получить количество мест
            if (it != tokens.end()) category = *it;                    // Получить категорию
            luggageCapacity = 300;              // Значение по умолчанию
        }
    }
}

