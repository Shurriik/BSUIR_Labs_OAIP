#ifndef ECONOMYCAR_H
#define ECONOMYCAR_H

#include "TaxiVehicle.h"

// Класс автомобиля эконом-класса, наследуется от TaxiVehicle
class EconomyCar : public TaxiVehicle {
private:
    double hourlyPrice;                        // Почасовая стоимость аренды в рублях
    bool hasClimateControl;                    // Наличие климат-контроля
    bool hasSeatHeating;                       // Наличие подогрева сидений
    bool hasSeatMassage;                       // Наличие массажа сидений
    bool hasNavigation;                        // Наличие навигации
    bool hasCruiseControl;                     // Наличие круиз-контроля
    bool hasSteeringWheelHeating;              // Наличие подогрева руля
    bool hasLeatherSeats;                      // Наличие кожаных сидений
    bool hasPremiumAudio;                      // Наличие премиум-аудио
    bool hasChildSeats;                        // Наличие детских кресел

public:
    EconomyCar();                              // Конструктор по умолчанию
    EconomyCar(const std::string& brand, const std::string& model, int year,
               const std::string& licensePlate, int mileage, VehicleStatus status,
               int seats, const std::string& category, int luggageCapacity, double hourlyPrice,
               bool hasClimateControl = false, bool hasSeatHeating = false,
               bool hasSeatMassage = false, bool hasNavigation = false,
               bool hasCruiseControl = false, bool hasSteeringWheelHeating = false,
               bool hasLeatherSeats = false, bool hasPremiumAudio = false,
               bool hasChildSeats = false);     // Конструктор с параметрами
    virtual ~EconomyCar() = default;          // Виртуальный деструктор

    double getHourlyPrice() const;             // Получить почасовую стоимость
    void setHourlyPrice(double price);         // Установить почасовую стоимость
    bool getHasClimateControl() const;         // Получить наличие климат-контроля
    bool getHasSeatHeating() const;            // Получить наличие подогрева сидений
    bool getHasSeatMassage() const;            // Получить наличие массажа сидений
    bool getHasNavigation() const;              // Получить наличие навигации
    bool getHasCruiseControl() const;          // Получить наличие круиз-контроля
    bool getHasSteeringWheelHeating() const;   // Получить наличие подогрева руля
    bool getHasLeatherSeats() const;            // Получить наличие кожаных сидений
    bool getHasPremiumAudio() const;           // Получить наличие премиум-аудио
    bool getHasChildSeats() const;             // Получить наличие детских кресел
    void setHasClimateControl(bool has);       // Установить наличие климат-контроля
    void setHasSeatHeating(bool has);          // Установить наличие подогрева сидений
    void setHasSeatMassage(bool has);          // Установить наличие массажа сидений
    void setHasNavigation(bool has);           // Установить наличие навигации
    void setHasCruiseControl(bool has);        // Установить наличие круиз-контроля
    void setHasSteeringWheelHeating(bool has); // Установить наличие подогрева руля
    void setHasLeatherSeats(bool has);         // Установить наличие кожаных сидений
    void setHasPremiumAudio(bool has);         // Установить наличие премиум-аудио
    void setHasChildSeats(bool has);           // Установить наличие детских кресел

    std::string getType() const override;       // Получить тип транспортного средства (переопределение)
    Vehicle* clone() const override;            // Создать копию объекта (переопределение)
    std::string toString() const override;      // Преобразовать в строку для отображения (переопределение)
    std::string toFileString() const override;  // Преобразовать в строку для файла (переопределение)
    void fromFileString(const std::string& data) override;  // Восстановить из строки файла (переопределение)
};

#endif // ECONOMYCAR_H

