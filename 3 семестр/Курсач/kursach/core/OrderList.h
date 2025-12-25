#ifndef ORDERLIST_H
#define ORDERLIST_H

#include "Order.h"
#include "List.h"

// Класс для управления списком заказов
class OrderList {
private:
    List<Order> orders;                        // Список всех заказов

public:
    OrderList();                               // Конструктор по умолчанию
    ~OrderList() = default;                    // Деструктор

    void addOrder(const Order& order);         // Добавить заказ в список
    void removeOrder(int orderId);             // Удалить заказ по идентификатору
    Order* findOrder(int orderId);             // Найти заказ по идентификатору
    Order* getOrder(int index);                // Получить заказ по индексу
    List<Order*> getOrdersByVehicle(int vehicleId);  // Получить все заказы для указанного транспортного средства
    List<Order*> getOrdersByDate(const std::tm& date);  // Получить все заказы на указанную дату
    List<Order*> getOrdersByDateRange(time_t startTime, time_t endTime);  // Получить заказы в диапазоне дат
    List<Order*> getAllOrders() const;         // Получить все заказы
    size_t size() const;                       // Получить количество заказов
    void clear();                              // Очистить список заказов
};

#endif 

