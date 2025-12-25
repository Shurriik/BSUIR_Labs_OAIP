#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <ctime>

// Класс заказа на аренду транспортного средства
class Order {
private:
    int id;                                    // Уникальный идентификатор заказа
    int vehicleId;                              // Идентификатор транспортного средства
    std::string clientName;                     // Имя клиента
    std::string clientPhone;                    // Телефон клиента
    std::string pickupAddress;                  // Адрес подачи транспортного средства
    std::string destinationAddress;             // Адрес назначения
    std::tm orderDateTime;                      // Дата и время начала заказа
    std::tm returnDateTime;                     // Дата и время возврата транспортного средства
    bool completed;                             // Статус выполнения заказа

    static int nextId;                         // Статическая переменная для генерации следующего идентификатора

public:
    Order();                                    // Конструктор по умолчанию
    Order(int vehicleId, const std::string& clientName, const std::string& clientPhone,
          const std::string& pickupAddress, const std::string& destinationAddress,
          const std::tm& orderDateTime, const std::tm& returnDateTime);  // Конструктор с параметрами
    ~Order() = default;                        // Деструктор

    int getId() const;                         // Получить идентификатор заказа
    int getVehicleId() const;                 // Получить идентификатор транспортного средства
    std::string getClientName() const;         // Получить имя клиента
    std::string getClientPhone() const;        // Получить телефон клиента
    std::string getPickupAddress() const;     // Получить адрес подачи
    std::string getDestinationAddress() const;  // Получить адрес назначения
    std::tm getOrderDateTime() const;          // Получить дату и время начала заказа
    std::tm getReturnDateTime() const;         // Получить дату и время возврата
    bool isCompleted() const;                  // Проверить статус выполнения заказа

    void setVehicleId(int id);                // Установить идентификатор транспортного средства
    void setClientName(const std::string& name);  // Установить имя клиента
    void setClientPhone(const std::string& phone);  // Установить телефон клиента
    void setPickupAddress(const std::string& address);  // Установить адрес подачи
    void setDestinationAddress(const std::string& address);  // Установить адрес назначения
    void setOrderDateTime(const std::tm& dt);  // Установить дату и время начала заказа
    void setReturnDateTime(const std::tm& dt); // Установить дату и время возврата
    void setCompleted(bool completed);         // Установить статус выполнения заказа

    std::string toString() const;              // Преобразовать объект в строку для отображения
    std::string toFileString() const;          // Преобразовать объект в строку для сохранения в файл
    void fromFileString(const std::string& data);  // Восстановить объект из строки файла
    
    bool operator==(const Order& other) const; // Оператор сравнения заказов
};

#endif 

