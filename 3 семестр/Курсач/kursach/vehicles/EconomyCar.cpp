#include "EconomyCar.h"
#include "../core/List.h"
#include <sstream>
#include <stdexcept>

// Конструктор по умолчанию
EconomyCar::EconomyCar()
    : TaxiVehicle(), hourlyPrice(100.0), hasClimateControl(false), hasSeatHeating(false),
      hasSeatMassage(false), hasNavigation(false), hasCruiseControl(false),
      hasSteeringWheelHeating(false), hasLeatherSeats(false), hasPremiumAudio(false),
      hasChildSeats(false) {
    vehicleType = VehicleType::ECONOMY;            // Установить тип транспортного средства
}

// Конструктор с параметрами
EconomyCar::EconomyCar(const std::string& brand, const std::string& model, int year,
                       const std::string& licensePlate, int mileage, VehicleStatus status,
                       int seats, const std::string& category, int luggageCapacity, double hourlyPrice,
                       bool hasClimateControl, bool hasSeatHeating, bool hasSeatMassage,
                       bool hasNavigation, bool hasCruiseControl, bool hasSteeringWheelHeating,
                       bool hasLeatherSeats, bool hasPremiumAudio, bool hasChildSeats)
    : TaxiVehicle(brand, model, year, licensePlate, mileage, status,
                  VehicleType::ECONOMY, seats, category, luggageCapacity),
      hourlyPrice(hourlyPrice), hasClimateControl(hasClimateControl),
      hasSeatHeating(hasSeatHeating), hasSeatMassage(hasSeatMassage),
      hasNavigation(hasNavigation), hasCruiseControl(hasCruiseControl),
      hasSteeringWheelHeating(hasSteeringWheelHeating), hasLeatherSeats(hasLeatherSeats),
      hasPremiumAudio(hasPremiumAudio), hasChildSeats(hasChildSeats) {
    if (hourlyPrice < 0) {                         // Проверка корректности почасовой стоимости
        throw std::invalid_argument("Hourly price cannot be negative");
    }
}

// Получить почасовую стоимость
double EconomyCar::getHourlyPrice() const {
    return hourlyPrice;                              // Вернуть почасовую стоимость
}

// Установить почасовую стоимость
void EconomyCar::setHourlyPrice(double price) {
    if (price < 0) {                                // Проверка корректности стоимости
        throw std::invalid_argument("Hourly price cannot be negative");
    }
    hourlyPrice = price;                            // Установить почасовую стоимость
}

bool EconomyCar::getHasClimateControl() const {
    return hasClimateControl;
}

bool EconomyCar::getHasSeatHeating() const {
    return hasSeatHeating;
}

bool EconomyCar::getHasSeatMassage() const {
    return hasSeatMassage;
}

bool EconomyCar::getHasNavigation() const {
    return hasNavigation;
}

bool EconomyCar::getHasCruiseControl() const {
    return hasCruiseControl;
}

bool EconomyCar::getHasSteeringWheelHeating() const {
    return hasSteeringWheelHeating;
}

bool EconomyCar::getHasLeatherSeats() const {
    return hasLeatherSeats;
}

bool EconomyCar::getHasPremiumAudio() const {
    return hasPremiumAudio;
}

bool EconomyCar::getHasChildSeats() const {
    return hasChildSeats;
}

void EconomyCar::setHasClimateControl(bool has) {
    hasClimateControl = has;
}

void EconomyCar::setHasSeatHeating(bool has) {
    hasSeatHeating = has;
}

void EconomyCar::setHasSeatMassage(bool has) {
    hasSeatMassage = has;
}

void EconomyCar::setHasNavigation(bool has) {
    hasNavigation = has;
}

void EconomyCar::setHasCruiseControl(bool has) {
    hasCruiseControl = has;
}

void EconomyCar::setHasSteeringWheelHeating(bool has) {
    hasSteeringWheelHeating = has;
}

void EconomyCar::setHasLeatherSeats(bool has) {
    hasLeatherSeats = has;
}

void EconomyCar::setHasPremiumAudio(bool has) {
    hasPremiumAudio = has;
}

void EconomyCar::setHasChildSeats(bool has) {
    hasChildSeats = has;
}

// Получить тип транспортного средства
std::string EconomyCar::getType() const {
    return "EconomyCar";                            // Вернуть строку с типом
}

// Создать копию объекта
Vehicle* EconomyCar::clone() const {
    return new EconomyCar(*this);                   // Создать новый объект через конструктор копирования
}

// Преобразовать объект в строку для отображения
std::string EconomyCar::toString() const {
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
std::string EconomyCar::toFileString() const {
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
void EconomyCar::fromFileString(const std::string& data) {
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
    } else if (tokens.size() >= 12) {
        // Старый формат - только почасовая стоимость
        auto it = tokens.begin();
        for (int i = 0; i < 11 && it != tokens.end(); ++i, ++it) {}
        if (it != tokens.end()) {
            hourlyPrice = std::stod(*it);
        }
        // Все опции по умолчанию false
    }
}

