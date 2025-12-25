#include "OrderList.h"

// Конструктор по умолчанию
OrderList::OrderList() {
}

// Добавить заказ в список
void OrderList::addOrder(const Order& order) {
    orders.push_back(order);
}

// Удалить заказ по идентификатору
void OrderList::removeOrder(int orderId) {
    for (auto it = orders.begin(); it != orders.end(); ++it) {
        if (it->getId() == orderId) {           // Найти заказ с указанным идентификатором
            orders.erase(it);                  // Удалить найденный заказ
            return;
        }
    }
}

// Найти заказ по идентификатору
Order* OrderList::findOrder(int orderId) {
    for (auto& order : orders) {
        if (order.getId() == orderId) {         // Проверить идентификатор заказа
            return &order;                     // Вернуть указатель на найденный заказ
        }
    }
    return nullptr;                            // Заказ не найден
}

// Получить все заказы для указанного транспортного средства
List<Order*> OrderList::getOrdersByVehicle(int vehicleId) {
    List<Order*> result;                       // Результирующий список заказов
    for (auto& order : orders) {
        if (order.getVehicleId() == vehicleId) {  // Проверить идентификатор транспортного средства
            result.push_back(&order);          // Добавить заказ в результат
        }
    }
    return result;
}

// Получить все заказы на указанную дату
List<Order*> OrderList::getOrdersByDate(const std::tm& date) {
    List<Order*> result;                       // Результирующий список заказов
    for (auto& order : orders) {
        std::tm orderDate = order.getOrderDateTime();  // Получить дату начала заказа
        if (orderDate.tm_year == date.tm_year &&      // Сравнить год
            orderDate.tm_mon == date.tm_mon &&         // Сравнить месяц
            orderDate.tm_mday == date.tm_mday) {       // Сравнить день
            result.push_back(&order);          // Добавить заказ в результат
        }
    }
    return result;
}

// Получить заказы в диапазоне дат
List<Order*> OrderList::getOrdersByDateRange(time_t startTime, time_t endTime) {
    List<Order*> result;                       // Результирующий список заказов
    for (auto& order : orders) {
        std::tm orderDateTime = order.getOrderDateTime();    // Получить дату и время начала заказа
        std::tm returnDateTime = order.getReturnDateTime(); // Получить дату и время возврата
        
        // Преобразовать в time_t для сравнения
        std::tm orderTm = orderDateTime;
        std::tm returnTm = returnDateTime;
        time_t orderTime = std::mktime(&orderTm);      // Время начала заказа
        time_t returnTime = std::mktime(&returnTm);    // Время возврата
        
        // Проверить пересечение заказа с диапазоном дат
        if ((orderTime >= startTime && orderTime <= endTime) ||      // Начало заказа в диапазоне
            (returnTime >= startTime && returnTime <= endTime) ||   // Возврат в диапазоне
            (orderTime <= startTime && returnTime >= endTime)) {    // Заказ полностью покрывает диапазон
            result.push_back(&order);          // Добавить заказ в результат
        }
    }
    return result;
}

// Получить заказ по индексу
Order* OrderList::getOrder(int index) {
    if (index < 0 || index >= static_cast<int>(orders.size())) {  // Проверка корректности индекса
        return nullptr;
    }
    
    int i = 0;                                 // Счетчик индексов
    for (auto it = orders.begin(); it != orders.end(); ++it, ++i) {
        if (i == index) {                     // Найти элемент с указанным индексом
            return &(*it);                    // Вернуть указатель на заказ
        }
    }
    return nullptr;
}

// Получить все заказы
List<Order*> OrderList::getAllOrders() const {
    List<Order*> result;                       // Результирующий список заказов
    for (auto it = orders.begin(); it != orders.end(); ++it) {
        result.push_back(const_cast<Order*>(&(*it)));  // Добавить указатель на заказ
    }
    return result;
}

// Получить количество заказов
size_t OrderList::size() const {
    return orders.size();
}

// Очистить список заказов
void OrderList::clear() {
    orders.clear();
}

