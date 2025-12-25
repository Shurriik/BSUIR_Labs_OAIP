#include "FileManager.h"
#include "../vehicles/EconomyCar.h"
#include "../vehicles/ComfortCar.h"
#include "../vehicles/BusinessCar.h"
#include "../vehicles/Minivan.h"
#include "../core/List.h"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#endif

// Получить путь к директории с данными
std::string FileManager::getDataDirectory() const {
    // Попытаться найти директорию данных относительно исполняемого файла
    std::filesystem::path exePath;
    
    #ifdef _WIN32
        // В Windows попытаться получить путь к исполняемому файлу
        char buffer[MAX_PATH];
        DWORD length = GetModuleFileNameA(NULL, buffer, MAX_PATH);
        if (length > 0) {
            exePath = std::filesystem::path(buffer).parent_path();
        } else {
            exePath = std::filesystem::current_path();
        }
    #else
        // В Linux/Mac использовать текущую директорию или путь к исполняемому файлу
        exePath = std::filesystem::current_path();
    #endif
    
    // Попытаться найти корень проекта (искать директорию data)
    std::filesystem::path currentPath = exePath;
    
    // Проверить, находимся ли мы в директории build, подняться к корню проекта
    if (currentPath.filename() == "build") {
        currentPath = currentPath.parent_path();
    }
    
    // Создать директорию data в корне проекта
    std::filesystem::path dataPath = currentPath / "data";
    std::filesystem::create_directories(dataPath);
    
    return dataPath.string();
}

// Конструктор менеджера файлов
FileManager::FileManager(const std::string& dataDir, const std::string& ordersFile) {
    if (dataDir.empty()) {
        dataDirectory = getDataDirectory();
    } else {
        dataDirectory = dataDir;
    }
    
    if (ordersFile.empty()) {
        this->ordersFile = (std::filesystem::path(dataDirectory) / "orders_data.txt").string();
    } else {
        this->ordersFile = ordersFile;
    }
    
    createDirectories();
}

// Создать необходимые директории для хранения данных
void FileManager::createDirectories() {
    try {
        // Создать директорию данных если она не существует
        // Файлы теперь хранятся непосредственно в директории data (например, business.txt, comfort.txt)
        std::filesystem::create_directories(dataDirectory);
    } catch (const std::exception& e) {
        throw TaxiParkException(ExceptionType::FILE_ERROR,
                              "Cannot create directories: " + std::string(e.what()));
    }
}

// Получить директорию для указанного типа транспортного средства
std::string FileManager::getVehicleTypeDirectory(const std::string& vehicleType) const {
    std::string typeDir;
    if (vehicleType == "EconomyCar") {
        typeDir = "economy";
    } else if (vehicleType == "ComfortCar") {
        typeDir = "comfort";
    } else if (vehicleType == "BusinessCar") {
        typeDir = "business";
    } else if (vehicleType == "Minivan") {
        typeDir = "minivan";
    } else {
        typeDir = "other";
    }
    return (std::filesystem::path(dataDirectory) / typeDir).string();
}

// Получить путь к файлу транспортного средства
std::string FileManager::getVehicleFilePath(int vehicleId, const std::string& vehicleType) const {
    std::string typeDir = getVehicleTypeDirectory(vehicleType);
    std::filesystem::path filePath = std::filesystem::path(typeDir) / ("vehicle_" + std::to_string(vehicleId) + ".txt");
    return filePath.string();
}

// Получить путь к файлу класса транспортных средств
std::string FileManager::getVehicleClassFilePath(const std::string& vehicleType) const {
    std::string fileName;
    if (vehicleType == "EconomyCar") {
        fileName = "economy.txt";
    } else if (vehicleType == "ComfortCar") {
        fileName = "comfort.txt";
    } else if (vehicleType == "BusinessCar") {
        fileName = "business.txt";
    } else if (vehicleType == "Minivan") {
        fileName = "minivan.txt";
    } else {
        fileName = "other.txt";
    }
    return (std::filesystem::path(dataDirectory) / fileName).string();
}

List<Vehicle*> FileManager::loadVehiclesFromClass(const std::string& vehicleType) {
    List<Vehicle*> vehicles;
    std::string filePath = getVehicleClassFilePath(vehicleType);
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        return vehicles; // Файл еще не существует, вернуть пустой список
    }

    try {
        std::string line;
        bool expectingType = true;
        std::string currentType;
        
        while (std::getline(file, line)) {
            if (line.empty()) {
                continue; // Пропустить пустые строки
            }
            
            if (expectingType) {
                // Проверить, является ли эта строка именем типа или данными (старый формат)
                if (line == "EconomyCar" || line == "ComfortCar" || 
                    line == "BusinessCar" || line == "Minivan") {
                    // Новый формат: строка с типом
                    currentType = line;
                    expectingType = false;
                } else {
                    // Старый формат: строка данных без префикса типа
                    // Использовать ожидаемый vehicleType
                    currentType = vehicleType;
                    expectingType = false;
                    
                    // Обработать эту строку как данные
                    Vehicle* vehicle = nullptr;
                    if (vehicleType == "EconomyCar") {
                        vehicle = new EconomyCar();
                    } else if (vehicleType == "ComfortCar") {
                        vehicle = new ComfortCar();
                    } else if (vehicleType == "BusinessCar") {
                        vehicle = new BusinessCar();
                    } else if (vehicleType == "Minivan") {
                        vehicle = new Minivan();
                    } else {
                        continue; // Пропустить неизвестные типы
                    }
                    
                    vehicle->fromFileString(line);
                    vehicles.push_back(vehicle);
                    expectingType = true; // Следующая строка должна быть типом (или данными в старом формате)
                }
            } else {
                // Это строка с данными
                Vehicle* vehicle = nullptr;
                
                // Использовать тип из файла, но проверить соответствие ожидаемому типу
                if (currentType == "EconomyCar") {
                    vehicle = new EconomyCar();
                } else if (currentType == "ComfortCar") {
                    vehicle = new ComfortCar();
                } else if (currentType == "BusinessCar") {
                    vehicle = new BusinessCar();
                } else if (currentType == "Minivan") {
                    vehicle = new Minivan();
                } else {
                    // Резервный вариант - использовать ожидаемый тип
                    if (vehicleType == "EconomyCar") {
                        vehicle = new EconomyCar();
                    } else if (vehicleType == "ComfortCar") {
                        vehicle = new ComfortCar();
                    } else if (vehicleType == "BusinessCar") {
                        vehicle = new BusinessCar();
                    } else if (vehicleType == "Minivan") {
                        vehicle = new Minivan();
                    } else {
                        expectingType = true;
                        continue; // Пропустить неизвестные типы
                    }
                }
                
                vehicle->fromFileString(line);
                vehicles.push_back(vehicle);
                expectingType = true; // Следующая строка должна быть типом
            }
        }
        file.close();
    } catch (const std::exception& e) {
        file.close();
        // Очистить все транспортные средства, которые были загружены до ошибки
        for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
            delete *it;
        }
        vehicles.clear();
        throw TaxiParkException(ExceptionType::FILE_ERROR,
                              "Error reading vehicle data: " + std::string(e.what()));
    }

    return vehicles;
}

void FileManager::saveVehiclesToClass(const std::string& vehicleType, const List<Vehicle*>& vehicles) {
    std::string filePath = getVehicleClassFilePath(vehicleType);
    std::ofstream file(filePath);
    
    if (!file.is_open()) {
        throw TaxiParkException(ExceptionType::FILE_ERROR,
                              "Cannot open file for writing: " + filePath);
    }

    try {
        for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
            Vehicle* vehicle = *it;
            if (vehicle != nullptr) {
                // Записать строку с типом сначала, затем строку с данными
                file << vehicleType << "\n";
                file << vehicle->toFileString() << "\n";
            }
        }
        file.close();
    } catch (const std::exception& e) {
        file.close();
        throw TaxiParkException(ExceptionType::FILE_ERROR,
                              "Error writing vehicle data: " + std::string(e.what()));
    }
}

void FileManager::saveVehicle(Vehicle* vehicle) {
    if (vehicle == nullptr) {
        throw TaxiParkException(ExceptionType::INVALID_OPERATION, "Vehicle пуст");
    }

    std::string vehicleType = vehicle->getType();
    
    // Загрузить все транспортные средства этого класса
    List<Vehicle*> vehicles = loadVehiclesFromClass(vehicleType);
    
    // Найти и обновить существующее транспортное средство или добавить новое
    bool found = false;
    for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
        if ((*it)->getId() == vehicle->getId()) {
            delete *it;
            *it = vehicle->clone();
            found = true;
            break;
        }
    }
    
    if (!found) {
        vehicles.push_back(vehicle->clone());
    }
    
    // Сохранить все транспортные средства обратно в файл
    saveVehiclesToClass(vehicleType, vehicles);
    
    // Очистить загруженные транспортные средства (но не то, которое мы сохраняем)
    for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
        delete *it;
    }
}

// Загрузить транспортное средство из файла указанного типа
Vehicle* FileManager::loadVehicleFromType(int vehicleId, const std::string& vehicleType) {
    std::string filePath = getVehicleFilePath(vehicleId, vehicleType);
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        return nullptr;
    }

    try {
        std::string type;
        std::getline(file, type);
        
        std::string data;
        std::getline(file, data);
        file.close();

        Vehicle* vehicle = nullptr;
        
        if (type == "EconomyCar") {
            vehicle = new EconomyCar();
        } else if (type == "ComfortCar") {
            vehicle = new ComfortCar();
        } else if (type == "BusinessCar") {
            vehicle = new BusinessCar();
        } else if (type == "Minivan") {
            vehicle = new Minivan();
        } else {
            throw TaxiParkException(ExceptionType::DATA_CORRUPTION,
                                  "Unknown vehicle type: " + type);
        }

        vehicle->fromFileString(data);
        return vehicle;
    } catch (const std::exception& e) {
        file.close();
        throw TaxiParkException(ExceptionType::FILE_ERROR,
                              "Error reading vehicle data: " + std::string(e.what()));
    }
}

Vehicle* FileManager::loadVehicle(int vehicleId) {
    // Попытаться загрузить из каждого файла класса типа
    List<std::string> types;
    types.push_back("EconomyCar");
    types.push_back("ComfortCar");
    types.push_back("BusinessCar");
    types.push_back("Minivan");
    
    for (auto it = types.begin(); it != types.end(); ++it) {
        List<Vehicle*> vehicles = loadVehiclesFromClass(*it);
        for (auto vIt = vehicles.begin(); vIt != vehicles.end(); ++vIt) {
            if ((*vIt)->getId() == vehicleId) {
                Vehicle* found = *vIt;
                // Удалить из списка перед возвратом
                vehicles.erase(vIt);
                // Очистить оставшиеся транспортные средства
                for (auto cleanupIt = vehicles.begin(); cleanupIt != vehicles.end(); ++cleanupIt) {
                    delete *cleanupIt;
                }
                return found;
            }
        }
        // Очистить транспортные средства если не найдено
        for (auto vIt = vehicles.begin(); vIt != vehicles.end(); ++vIt) {
            delete *vIt;
        }
    }
    
    return nullptr;
}

List<Vehicle*> FileManager::loadAllVehicles() {
    List<Vehicle*> allVehicles;
    
    try {
        // Проверить существование директории данных
        if (!std::filesystem::exists(dataDirectory)) {
            return allVehicles; // Вернуть пустой список если директория не существует
        }
        
        // Загрузить из каждого файла класса типа
        List<std::string> types;
        types.push_back("EconomyCar");
        types.push_back("ComfortCar");
        types.push_back("BusinessCar");
        types.push_back("Minivan");
        
        for (auto it = types.begin(); it != types.end(); ++it) {
            List<Vehicle*> classVehicles = loadVehiclesFromClass(*it);
            // Переместить все транспортные средства из списка класса в основной список
            for (auto vIt = classVehicles.begin(); vIt != classVehicles.end(); ++vIt) {
                allVehicles.push_back(*vIt);
            }
            classVehicles.clear(); // Очистить список (транспортные средства теперь в allVehicles)
        }
    } catch (const std::filesystem::filesystem_error&) {
        // Директория не существует или другая ошибка файловой системы - вернуть пустой список
        return allVehicles;
    } catch (const std::exception& e) {
        throw TaxiParkException(ExceptionType::FILE_ERROR,
                              "Error loading vehicles: " + std::string(e.what()));
    }

    return allVehicles;
}

// Удалить транспортное средство из файла
void FileManager::deleteVehicle(int vehicleId) {
    // Попытаться удалить из каждого файла класса типа
    List<std::string> types;
    types.push_back("EconomyCar");
    types.push_back("ComfortCar");
    types.push_back("BusinessCar");
    types.push_back("Minivan");
    
    for (auto it = types.begin(); it != types.end(); ++it) {
        List<Vehicle*> vehicles = loadVehiclesFromClass(*it);
        bool found = false;
        
        for (auto vIt = vehicles.begin(); vIt != vehicles.end(); ++vIt) {
            if ((*vIt)->getId() == vehicleId) {
                delete *vIt;
                vehicles.erase(vIt);
                found = true;
                break;
            }
        }
        
        if (found) {
            // Сохранить обновленный список без удаленного транспортного средства
            saveVehiclesToClass(*it, vehicles);
            // Очистить оставшиеся транспортные средства
            for (auto vIt = vehicles.begin(); vIt != vehicles.end(); ++vIt) {
                delete *vIt;
            }
            return; // Найдено и удалено
        }
        
        // Очистить транспортные средства если не найдено в этом классе
        for (auto vIt = vehicles.begin(); vIt != vehicles.end(); ++vIt) {
            delete *vIt;
        }
    }
    
    // Если мы дошли сюда, транспортное средство не найдено - это нормально, просто вернуться
}

// Проверить существование транспортного средства
bool FileManager::vehicleExists(int vehicleId) {
    // Проверить во всех файлах классов типов
    List<std::string> types;
    types.push_back("EconomyCar");
    types.push_back("ComfortCar");
    types.push_back("BusinessCar");
    types.push_back("Minivan");
    
    for (auto it = types.begin(); it != types.end(); ++it) {
        List<Vehicle*> vehicles = loadVehiclesFromClass(*it);
        for (auto vIt = vehicles.begin(); vIt != vehicles.end(); ++vIt) {
            if ((*vIt)->getId() == vehicleId) {
                // Очистить транспортные средства перед возвратом
                for (auto cleanupIt = vehicles.begin(); cleanupIt != vehicles.end(); ++cleanupIt) {
                    delete *cleanupIt;
                }
                return true;
            }
        }
        // Очистить транспортные средства если не найдено
        for (auto vIt = vehicles.begin(); vIt != vehicles.end(); ++vIt) {
            delete *vIt;
        }
    }
    
    return false;
}

void FileManager::saveOrders(const OrderList& orders) {
    std::ofstream file(ordersFile);
    
    if (!file.is_open()) {
        throw TaxiParkException(ExceptionType::FILE_ERROR,
                              "Cannot open orders file for writing: " + ordersFile);
    }

    try {
        List<Order*> allOrders = orders.getAllOrders();
        for (auto it = allOrders.begin(); it != allOrders.end(); ++it) {
            Order* order = *it;
            file << order->toFileString() << "\n";
        }
        file.close();
    } catch (const std::exception& e) {
        file.close();
        throw TaxiParkException(ExceptionType::FILE_ERROR,
                              "Error writing orders data: " + std::string(e.what()));
    }
}

OrderList FileManager::loadOrders() {
    OrderList orders;
    std::ifstream file(ordersFile);
    
    if (!file.is_open()) {
        return orders; // Файл еще не существует, вернуть пустой список
    }

    try {
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                Order order;
                order.fromFileString(line);
                orders.addOrder(order);
            }
        }
        file.close();
    } catch (const std::exception& e) {
        file.close();
        throw TaxiParkException(ExceptionType::FILE_ERROR,
                              "Error reading orders data: " + std::string(e.what()));
    }

    return orders;
}

