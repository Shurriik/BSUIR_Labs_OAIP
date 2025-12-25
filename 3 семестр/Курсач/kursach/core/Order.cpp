#include "Order.h"
#include "List.h"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <stdexcept>
#include <cstdio>

int Order::nextId = 1;                         // Инициализация статической переменной для генерации идентификаторов

// Конструктор по умолчанию
Order::Order()
    : id(nextId++), vehicleId(0), clientName(""), clientPhone(""),
      pickupAddress(""), destinationAddress(""), completed(false) {
    std::time_t now = std::time(nullptr);      // Получить текущее время
    orderDateTime = *std::localtime(&now);     // Установить текущую дату и время начала
    returnDateTime = *std::localtime(&now);    // Установить текущую дату и время возврата
}

// Конструктор с параметрами
Order::Order(int vehicleId, const std::string& clientName, const std::string& clientPhone,
             const std::string& pickupAddress, const std::string& destinationAddress,
             const std::tm& orderDateTime, const std::tm& returnDateTime)
    : id(nextId++), vehicleId(vehicleId), clientName(clientName), clientPhone(clientPhone),
      pickupAddress(pickupAddress), destinationAddress(destinationAddress),
      orderDateTime(orderDateTime), returnDateTime(returnDateTime), completed(false) {
    if (vehicleId <= 0) {                      // Проверка корректности идентификатора транспортного средства
        throw std::invalid_argument("Invalid vehicle ID");
    }
}

// Получить идентификатор заказа
int Order::getId() const {
    return id;
}

// Получить идентификатор транспортного средства
int Order::getVehicleId() const {
    return vehicleId;
}

// Получить имя клиента
std::string Order::getClientName() const {
    return clientName;
}

// Получить телефон клиента
std::string Order::getClientPhone() const {
    return clientPhone;
}

// Получить адрес подачи
std::string Order::getPickupAddress() const {
    return pickupAddress;
}

// Получить адрес назначения
std::string Order::getDestinationAddress() const {
    return destinationAddress;
}

// Получить дату и время начала заказа
std::tm Order::getOrderDateTime() const {
    return orderDateTime;
}

// Получить дату и время возврата
std::tm Order::getReturnDateTime() const {
    return returnDateTime;
}

// Проверить статус выполнения заказа
bool Order::isCompleted() const {
    return completed;
}

// Установить идентификатор транспортного средства
void Order::setVehicleId(int id) {
    if (id <= 0) {                             // Проверка корректности идентификатора
        throw std::invalid_argument("Invalid vehicle ID");
    }
    this->vehicleId = id;
}

// Установить имя клиента
void Order::setClientName(const std::string& name) {
    clientName = name;
}

// Установить телефон клиента
void Order::setClientPhone(const std::string& phone) {
    clientPhone = phone;
}

// Установить адрес подачи
void Order::setPickupAddress(const std::string& address) {
    pickupAddress = address;
}

// Установить адрес назначения
void Order::setDestinationAddress(const std::string& address) {
    destinationAddress = address;
}

// Установить дату и время начала заказа
void Order::setOrderDateTime(const std::tm& dt) {
    orderDateTime = dt;
}

// Установить дату и время возврата
void Order::setReturnDateTime(const std::tm& dt) {
    returnDateTime = dt;
}

// Установить статус выполнения заказа
void Order::setCompleted(bool completed) {
    this->completed = completed;
}

// Преобразовать объект в строку для отображения
std::string Order::toString() const {
    std::ostringstream oss;
    oss << "Заказ #" << id << ", Автомобиль ID: " << vehicleId
        << ", Клиент: " << clientName << " (" << clientPhone << ")"
        << ", От: " << pickupAddress << " -> До: " << destinationAddress;
    return oss.str();
}

// Преобразовать объект в строку для сохранения в файл
std::string Order::toFileString() const {
    std::ostringstream oss;
    oss << id << "|" << vehicleId << "|" << clientName << "|" << clientPhone << "|"
        << pickupAddress << "|" << destinationAddress << "|"
        << (orderDateTime.tm_year + 1900) << "-"  // Год (скорректированный)
        << std::setfill('0') << std::setw(2) << (orderDateTime.tm_mon + 1) << "-"  // Месяц с ведущим нулем
        << std::setfill('0') << std::setw(2) << orderDateTime.tm_mday << " "  // День с ведущим нулем
        << std::setfill('0') << std::setw(2) << orderDateTime.tm_hour << ":"  // Час с ведущим нулем
        << std::setfill('0') << std::setw(2) << orderDateTime.tm_min << ":"  // Минута с ведущим нулем
        << std::setfill('0') << std::setw(2) << orderDateTime.tm_sec << "|"  // Секунда с ведущим нулем
        << (returnDateTime.tm_year + 1900) << "-"  // Год возврата (скорректированный)
        << std::setfill('0') << std::setw(2) << (returnDateTime.tm_mon + 1) << "-"  // Месяц возврата
        << std::setfill('0') << std::setw(2) << returnDateTime.tm_mday << " "  // День возврата
        << std::setfill('0') << std::setw(2) << returnDateTime.tm_hour << ":"  // Час возврата
        << std::setfill('0') << std::setw(2) << returnDateTime.tm_min << ":"  // Минута возврата
        << std::setfill('0') << std::setw(2) << returnDateTime.tm_sec << "|"  // Секунда возврата
        << (completed ? 1 : 0);                // Статус выполнения (1 или 0)
    return oss.str();
}

// Восстановить объект из строки файла
void Order::fromFileString(const std::string& data) {
    std::istringstream iss(data);              // Создать поток из строки данных
    std::string token;                         // Текущий токен при разборе
    List<std::string> tokens;                  // Список всех токенов
    
    while (std::getline(iss, token, '|')) {    // Разделить строку по символу '|'
        tokens.push_back(token);
    }
    
    if (tokens.size() >= 9) {                  // Проверка наличия всех необходимых полей
        auto it = tokens.begin();
        if (it != tokens.end()) {
            id = std::stoi(*it++);             // Преобразовать идентификатор заказа
            if (id >= nextId) {                // Обновить счетчик идентификаторов
                nextId = id + 1;
            }
            if (it != tokens.end()) vehicleId = std::stoi(*it++);  // Получить идентификатор ТС
            if (it != tokens.end()) clientName = *it++;             // Получить имя клиента
            if (it != tokens.end()) clientPhone = *it++;           // Получить телефон клиента
            if (it != tokens.end()) pickupAddress = *it++;         // Получить адрес подачи
            if (it != tokens.end()) destinationAddress = *it++;   // Получить адрес назначения
            
            // Разбор даты и времени начала заказа
            if (it != tokens.end()) {
                std::string dateStr1 = *it++;
                if (sscanf(dateStr1.c_str(), "%d-%d-%d %d:%d:%d",
                           &orderDateTime.tm_year, &orderDateTime.tm_mon, &orderDateTime.tm_mday,
                           &orderDateTime.tm_hour, &orderDateTime.tm_min, &orderDateTime.tm_sec) == 6) {
                    orderDateTime.tm_year -= 1900;  // Скорректировать год (tm_year отсчитывается с 1900)
                    orderDateTime.tm_mon -= 1;      // Скорректировать месяц (tm_mon отсчитывается с 0)
                }
            }
            
            // Разбор даты и времени возврата
            if (it != tokens.end()) {
                std::string dateStr2 = *it++;
                if (sscanf(dateStr2.c_str(), "%d-%d-%d %d:%d:%d",
                           &returnDateTime.tm_year, &returnDateTime.tm_mon, &returnDateTime.tm_mday,
                           &returnDateTime.tm_hour, &returnDateTime.tm_min, &returnDateTime.tm_sec) == 6) {
                    returnDateTime.tm_year -= 1900;  // Скорректировать год
                    returnDateTime.tm_mon -= 1;       // Скорректировать месяц
                }
            }
            
            if (it != tokens.end()) completed = std::stoi(*it) != 0;  // Получить статус выполнения
        }
    }
}

// Оператор сравнения заказов
bool Order::operator==(const Order& other) const {
    return id == other.id;
}

