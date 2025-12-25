#include "BusinessCar.h"
#include "../core/List.h"
#include <sstream>
#include <stdexcept>

// Конструктор по умолчанию
BusinessCar::BusinessCar()
    : TaxiVehicle(), hourlyPrice(250.0), hasClimateControl(false), hasSeatHeating(false),
      hasSeatMassage(false), hasNavigation(false), hasCruiseControl(false),
      hasSteeringWheelHeating(false), hasLeatherSeats(true), hasPremiumAudio(true),
      hasChildSeats(false) {
    vehicleType = VehicleType::BUSINESS;            // Установить тип транспортного средства
}

// Конструктор с параметрами
BusinessCar::BusinessCar(const std::string& brand, const std::string& model, int year,
                         const std::string& licensePlate, int mileage, VehicleStatus status,
                         int seats, const std::string& category, int luggageCapacity, double hourlyPrice,
                         bool hasClimateControl, bool hasSeatHeating, bool hasSeatMassage,
                         bool hasNavigation, bool hasCruiseControl, bool hasSteeringWheelHeating,
                         bool hasLeatherSeats, bool hasPremiumAudio, bool hasChildSeats)
    : TaxiVehicle(brand, model, year, licensePlate, mileage, status,
                  VehicleType::BUSINESS, seats, category, luggageCapacity),
      hourlyPrice(hourlyPrice), hasClimateControl(hasClimateControl),
      hasSeatHeating(hasSeatHeating), hasSeatMassage(hasSeatMassage),
      hasNavigation(hasNavigation), hasCruiseControl(hasCruiseControl),
      hasSteeringWheelHeating(hasSteeringWheelHeating), hasLeatherSeats(hasLeatherSeats),
      hasPremiumAudio(hasPremiumAudio), hasChildSeats(hasChildSeats) {
    if (hourlyPrice < 0) {                         // Проверка корректности почасовой стоимости
        throw std::invalid_argument("Hourly price cannot be negative");
    }
}

double BusinessCar::getHourlyPrice() const {
    return hourlyPrice;
}

bool BusinessCar::getHasLeatherSeats() const {
    return hasLeatherSeats;
}

bool BusinessCar::getHasPremiumAudio() const {
    return hasPremiumAudio;
}

void BusinessCar::setHourlyPrice(double price) {
    if (price < 0) {
        throw std::invalid_argument("Hourly price cannot be negative");
    }
    hourlyPrice = price;
}

void BusinessCar::setHasLeatherSeats(bool has) {
    hasLeatherSeats = has;
}

void BusinessCar::setHasPremiumAudio(bool has) {
    hasPremiumAudio = has;
}

bool BusinessCar::getHasClimateControl() const {
    return hasClimateControl;
}

bool BusinessCar::getHasSeatHeating() const {
    return hasSeatHeating;
}

bool BusinessCar::getHasSeatMassage() const {
    return hasSeatMassage;
}

bool BusinessCar::getHasNavigation() const {
    return hasNavigation;
}

bool BusinessCar::getHasCruiseControl() const {
    return hasCruiseControl;
}

bool BusinessCar::getHasSteeringWheelHeating() const {
    return hasSteeringWheelHeating;
}

bool BusinessCar::getHasChildSeats() const {
    return hasChildSeats;
}

void BusinessCar::setHasClimateControl(bool has) {
    hasClimateControl = has;
}

void BusinessCar::setHasSeatHeating(bool has) {
    hasSeatHeating = has;
}

void BusinessCar::setHasSeatMassage(bool has) {
    hasSeatMassage = has;
}

void BusinessCar::setHasNavigation(bool has) {
    hasNavigation = has;
}

void BusinessCar::setHasCruiseControl(bool has) {
    hasCruiseControl = has;
}

void BusinessCar::setHasSteeringWheelHeating(bool has) {
    hasSteeringWheelHeating = has;
}

void BusinessCar::setHasChildSeats(bool has) {
    hasChildSeats = has;
}

// Получить тип транспортного средства
std::string BusinessCar::getType() const {
    return "BusinessCar";                           // Вернуть строку с типом
}

// Создать копию объекта
Vehicle* BusinessCar::clone() const {
    return new BusinessCar(*this);                  // Создать новый объект через конструктор копирования
}

// Преобразовать объект в строку для отображения
std::string BusinessCar::toString() const {
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
std::string BusinessCar::toFileString() const {
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
void BusinessCar::fromFileString(const std::string& data) {
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
    } else if (tokens.size() >= 14) {
        // Старый формат - только почасовая стоимость, кожаные сиденья, премиум-аудио
        auto it = tokens.begin();
        for (int i = 0; i < 11 && it != tokens.end(); ++i, ++it) {}
        if (it != tokens.end()) {
            hourlyPrice = std::stod(*it++);
            if (it != tokens.end()) hasLeatherSeats = std::stoi(*it++) != 0;
            if (it != tokens.end()) hasPremiumAudio = std::stoi(*it) != 0;
        }
        // Остальные опции по умолчанию false
    }
}

