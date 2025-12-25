#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "../core/Vehicle.h"
#include "../core/Order.h"
#include "../core/OrderList.h"
#include "../core/List.h"
#include "../exceptions/TaxiParkException.h"
#include <string>

// Класс для управления сохранением и загрузкой данных из файлов
class FileManager {
private:
    std::string dataDirectory;                 // Путь к директории с данными
    std::string ordersFile;                     // Путь к файлу с заказами
    std::string getDataDirectory() const;       // Получить путь к директории с данными
    std::string getVehicleTypeDirectory(const std::string& vehicleType) const;  // Получить директорию для типа ТС
    std::string getVehicleFilePath(int vehicleId, const std::string& vehicleType) const;  // Получить путь к файлу ТС
    std::string getVehicleClassFilePath(const std::string& vehicleType) const;  // Получить путь к файлу класса ТС
    Vehicle* loadVehicleFromType(int vehicleId, const std::string& vehicleType);  // Загрузить ТС из файла типа
    List<Vehicle*> loadVehiclesFromClass(const std::string& vehicleType);  // Загрузить все ТС из файла класса
    void saveVehiclesToClass(const std::string& vehicleType, const List<Vehicle*>& vehicles);  // Сохранить ТС в файл класса

public:
    FileManager(const std::string& dataDir = "", 
                const std::string& ordersFile = "");  // Конструктор с параметрами
    ~FileManager() = default;                  // Деструктор

    void saveVehicle(Vehicle* vehicle);        // Сохранить транспортное средство в файл
    Vehicle* loadVehicle(int vehicleId);       // Загрузить транспортное средство по идентификатору
    List<Vehicle*> loadAllVehicles();          // Загрузить все транспортные средства
    void deleteVehicle(int vehicleId);         // Удалить транспортное средство из файла
    bool vehicleExists(int vehicleId);         // Проверить существование транспортного средства

    void saveOrders(const OrderList& orders);  // Сохранить список заказов в файл
    OrderList loadOrders();                    // Загрузить список заказов из файла

    void createDirectories();                  // Создать необходимые директории для хранения данных
};

#endif // FILEMANAGER_H

