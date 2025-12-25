#include "Vehicle.h"
#include "List.h"
#include <sstream>
#include <stdexcept>

int Vehicle::nextId = 1;                       // Инициализация статической переменной для генерации идентификаторов

// Конструктор по умолчанию
Vehicle::Vehicle()
    : id(nextId++), brand(""), model(""), year(2020),
      licensePlate(""), mileage(0), status(VehicleStatus::IN_PARK) {
}

// Конструктор с параметрами
Vehicle::Vehicle(const std::string& brand, const std::string& model, int year,
                 const std::string& licensePlate, int mileage, VehicleStatus status)
    : id(nextId++), brand(brand), model(model), year(year),
      licensePlate(licensePlate), mileage(mileage), status(status) {
    if (year < 1900 || year > 2100) {          // Проверка корректности года выпуска
        throw std::invalid_argument("Invalid year");
    }
    if (mileage < 0) {                         // Проверка корректности пробега
        throw std::invalid_argument("Mileage cannot be negative");
    }
}

// Получить идентификатор транспортного средства
int Vehicle::getId() const {
    return id;
}

// Получить марку автомобиля
std::string Vehicle::getBrand() const {
    return brand;
}

// Получить модель автомобиля
std::string Vehicle::getModel() const {
    return model;
}

// Получить год выпуска
int Vehicle::getYear() const {
    return year;
}

// Получить номерной знак
std::string Vehicle::getLicensePlate() const {
    return licensePlate;
}

// Получить пробег
int Vehicle::getMileage() const {
    return mileage;
}

// Получить статус транспортного средства
VehicleStatus Vehicle::getStatus() const {
    return status;
}

// Получить строковое представление статуса
std::string Vehicle::getStatusString() const {
    switch (status) {
        case VehicleStatus::ON_LINE:
            return "На линии";
        case VehicleStatus::IN_PARK:
            return "В парке";
        case VehicleStatus::IN_REPAIR:
            return "В ремонте";
        default:
            return "Неизвестно";
    }
}

// Установить идентификатор
void Vehicle::setId(int id) {
    this->id = id;
}

// Установить марку
void Vehicle::setBrand(const std::string& brand) {
    this->brand = brand;
}

// Установить модель
void Vehicle::setModel(const std::string& model) {
    this->model = model;
}

// Установить год выпуска
void Vehicle::setYear(int year) {
    if (year < 1900 || year > 2100) {          // Проверка корректности года
        throw std::invalid_argument("Invalid year");
    }
    this->year = year;
}

// Установить номерной знак
void Vehicle::setLicensePlate(const std::string& licensePlate) {
    this->licensePlate = licensePlate;
}

// Установить пробег
void Vehicle::setMileage(int mileage) {
    if (mileage < 0) {                         // Проверка корректности пробега
        throw std::invalid_argument("Mileage cannot be negative");
    }
    this->mileage = mileage;
}

// Установить статус
void Vehicle::setStatus(VehicleStatus status) {
    this->status = status;
}

// Проверить необходимость технического обслуживания
bool Vehicle::needsMaintenance() const {
    // ТО требуется каждые 10000 км
    return mileage % 10000 >= 9000;
}

// Преобразовать объект в строку для отображения
std::string Vehicle::toString() const {
    std::ostringstream oss;
    oss << "ID: " << id << ", " << brand << " " << model
        << " (" << year << "), " << licensePlate
        << ", Пробег: " << mileage << " км, Статус: " << getStatusString();
    return oss.str();
}

// Преобразовать объект в строку для сохранения в файл
std::string Vehicle::toFileString() const {
    std::ostringstream oss;
    oss << id << "|" << brand << "|" << model << "|" << year << "|"
        << licensePlate << "|" << mileage << "|" << static_cast<int>(status);
    return oss.str();
}

// Восстановить объект из строки файла
void Vehicle::fromFileString(const std::string& data) {
    std::istringstream iss(data);              // Создать поток из строки данных
    std::string token;                         // Текущий токен при разборе
    List<std::string> tokens;                  // Список всех токенов
    
    while (std::getline(iss, token, '|')) {    // Разделить строку по символу '|'
        tokens.push_back(token);
    }
    
    if (tokens.size() >= 7) {                  // Проверка наличия всех необходимых полей
        auto it = tokens.begin();
        if (it != tokens.end()) {
            id = std::stoi(*it++);             // Преобразовать идентификатор
            if (id >= nextId) {                // Обновить счетчик идентификаторов
                nextId = id + 1;
            }
            if (it != tokens.end()) brand = *it++;      // Получить марку
            if (it != tokens.end()) model = *it++;      // Получить модель
            if (it != tokens.end()) year = std::stoi(*it++);  // Получить год
            if (it != tokens.end()) licensePlate = *it++;      // Получить номерной знак
            if (it != tokens.end()) mileage = std::stoi(*it++);  // Получить пробег
            if (it != tokens.end()) status = static_cast<VehicleStatus>(std::stoi(*it));  // Получить статус
        }
    }
}

