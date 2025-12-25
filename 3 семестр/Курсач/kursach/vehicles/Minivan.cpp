#include "Minivan.h"
#include "../core/List.h"
#include <sstream>
#include <stdexcept>

// Конструктор по умолчанию
Minivan::Minivan()
    : TaxiVehicle(), hourlyPrice(200.0), hasClimateControl(false), hasSeatHeating(false),
      hasSeatMassage(false), hasNavigation(false), hasCruiseControl(false),
      hasSteeringWheelHeating(false), hasLeatherSeats(false), hasPremiumAudio(false),
      hasChildSeats(true) {
    vehicleType = VehicleType::MINIVAN;             // Установить тип транспортного средства
    luggageCapacity = 500;                          // Установить значение по умолчанию для объема багажника
}

// Конструктор с параметрами
Minivan::Minivan(const std::string& brand, const std::string& model, int year,
                 const std::string& licensePlate, int mileage, VehicleStatus status,
                 int seats, const std::string& category, int luggageCapacity, double hourlyPrice,
                 bool hasClimateControl, bool hasSeatHeating, bool hasSeatMassage,
                 bool hasNavigation, bool hasCruiseControl, bool hasSteeringWheelHeating,
                 bool hasLeatherSeats, bool hasPremiumAudio, bool hasChildSeats)
    : TaxiVehicle(brand, model, year, licensePlate, mileage, status,
                  VehicleType::MINIVAN, seats, category, luggageCapacity),
      hourlyPrice(hourlyPrice), hasClimateControl(hasClimateControl),
      hasSeatHeating(hasSeatHeating), hasSeatMassage(hasSeatMassage),
      hasNavigation(hasNavigation), hasCruiseControl(hasCruiseControl),
      hasSteeringWheelHeating(hasSteeringWheelHeating), hasLeatherSeats(hasLeatherSeats),
      hasPremiumAudio(hasPremiumAudio), hasChildSeats(hasChildSeats) {
    if (hourlyPrice < 0) {                         // Проверка корректности почасовой стоимости
        throw std::invalid_argument("Hourly price cannot be negative");
    }
}

double Minivan::getHourlyPrice() const {
    return hourlyPrice;
}

bool Minivan::getHasChildSeats() const {
    return hasChildSeats;
}

void Minivan::setHourlyPrice(double price) {
    if (price < 0) {
        throw std::invalid_argument("Hourly price cannot be negative");
    }
    hourlyPrice = price;
}

void Minivan::setHasChildSeats(bool has) {
    hasChildSeats = has;
}

bool Minivan::getHasClimateControl() const {
    return hasClimateControl;
}

bool Minivan::getHasSeatHeating() const {
    return hasSeatHeating;
}

bool Minivan::getHasSeatMassage() const {
    return hasSeatMassage;
}

bool Minivan::getHasNavigation() const {
    return hasNavigation;
}

bool Minivan::getHasCruiseControl() const {
    return hasCruiseControl;
}

bool Minivan::getHasSteeringWheelHeating() const {
    return hasSteeringWheelHeating;
}

bool Minivan::getHasLeatherSeats() const {
    return hasLeatherSeats;
}

bool Minivan::getHasPremiumAudio() const {
    return hasPremiumAudio;
}

void Minivan::setHasClimateControl(bool has) {
    hasClimateControl = has;
}

void Minivan::setHasSeatHeating(bool has) {
    hasSeatHeating = has;
}

void Minivan::setHasSeatMassage(bool has) {
    hasSeatMassage = has;
}

void Minivan::setHasNavigation(bool has) {
    hasNavigation = has;
}

void Minivan::setHasCruiseControl(bool has) {
    hasCruiseControl = has;
}

void Minivan::setHasSteeringWheelHeating(bool has) {
    hasSteeringWheelHeating = has;
}

void Minivan::setHasLeatherSeats(bool has) {
    hasLeatherSeats = has;
}

void Minivan::setHasPremiumAudio(bool has) {
    hasPremiumAudio = has;
}

// Получить тип транспортного средства
std::string Minivan::getType() const {
    return "Minivan";                               // Вернуть строку с типом
}

// Создать копию объекта
Vehicle* Minivan::clone() const {
    return new Minivan(*this);                      // Создать новый объект через конструктор копирования
}

// Преобразовать объект в строку для отображения
std::string Minivan::toString() const {
    std::ostringstream oss;
    oss << TaxiVehicle::toString() << ", Цена за час: " << hourlyPrice << " руб/час";
    if (hasClimateControl) oss << ", Климат-контроль";
    if (hasSeatHeating) oss << ", Подогрев сидений";
    if (hasSeatMassage) oss << ", Массаж сидений";
    if (hasNavigation) oss << ", Навигация";
    if (hasCruiseControl) oss << ", Круиз-контроль";
    if (hasSteeringWheelHeating) oss << ", Подогрев руля";
    if (hasLeatherSeats) oss << ", Кожаные сиденья";
    if (hasPremiumAudio) oss << ", Премиум аудио";
    if (hasChildSeats) oss << ", Детские кресла";
    return oss.str();
}

// Преобразовать объект в строку для сохранения в файл
std::string Minivan::toFileString() const {
    std::ostringstream oss;
    oss << TaxiVehicle::toFileString() << "|" << hourlyPrice << "|"
        << (hasClimateControl ? 1 : 0) << "|" << (hasSeatHeating ? 1 : 0) << "|"
        << (hasSeatMassage ? 1 : 0) << "|" << (hasNavigation ? 1 : 0) << "|"
        << (hasCruiseControl ? 1 : 0) << "|" << (hasSteeringWheelHeating ? 1 : 0) << "|"
        << (hasLeatherSeats ? 1 : 0) << "|" << (hasPremiumAudio ? 1 : 0) << "|"
        << (hasChildSeats ? 1 : 0);
    return oss.str();
}

// Восстановить объект из строки файла
void Minivan::fromFileString(const std::string& data) {
    TaxiVehicle::fromFileString(data);              // Вызвать метод базового класса
    std::istringstream iss(data);                   // Создать поток из строки данных
    std::string token;                              // Текущий токен при разборе
    List<std::string> tokens;                       // Список всех токенов
    
    while (std::getline(iss, token, '|')) {         // Разделить строку по символу '|'
        tokens.push_back(token);
    }
    
    if (tokens.size() >= 21) {
        // Новый формат со всеми опциями
        auto it = tokens.begin();
        for (int i = 0; i < 11 && it != tokens.end(); ++i, ++it) {}
        if (it != tokens.end()) hourlyPrice = std::stod(*it++);
        if (it != tokens.end()) hasClimateControl = std::stoi(*it++) != 0;
        if (it != tokens.end()) hasSeatHeating = std::stoi(*it++) != 0;
        if (it != tokens.end()) hasSeatMassage = std::stoi(*it++) != 0;
        if (it != tokens.end()) hasNavigation = std::stoi(*it++) != 0;
        if (it != tokens.end()) hasCruiseControl = std::stoi(*it++) != 0;
        if (it != tokens.end()) hasSteeringWheelHeating = std::stoi(*it++) != 0;
        if (it != tokens.end()) hasLeatherSeats = std::stoi(*it++) != 0;
        if (it != tokens.end()) hasPremiumAudio = std::stoi(*it++) != 0;
        if (it != tokens.end()) hasChildSeats = std::stoi(*it) != 0;
    } else if (tokens.size() >= 13) {
        // Старый формат - только почасовая стоимость и детские кресла
        auto it = tokens.begin();
        for (int i = 0; i < 11 && it != tokens.end(); ++i, ++it) {}
        if (it != tokens.end()) {
            hourlyPrice = std::stod(*it++);
            if (it != tokens.end()) hasChildSeats = std::stoi(*it) != 0;
        }
        // Остальные опции по умолчанию false
    }
}

