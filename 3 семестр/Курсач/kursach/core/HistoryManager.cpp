#include "HistoryManager.h"
#include "../vehicles/EconomyCar.h"
#include "../vehicles/ComfortCar.h"
#include "../vehicles/BusinessCar.h"
#include "../vehicles/Minivan.h"
#include <algorithm>

// Конструктор копирования состояния истории
HistoryManager::HistoryState::HistoryState(const HistoryState& other) 
{
    for (auto it = other.vehicles.begin(); it != other.vehicles.end(); ++it)
     {
        if (*it != nullptr) {
            vehicles.push_back((*it)->clone());     // Создать копию каждого транспортного средства
        }
    }
    description = other.description;                // Скопировать описание
}

// Деструктор состояния истории
HistoryManager::HistoryState::~HistoryState() {
    for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
        delete *it;                                 // Освободить память для каждого транспортного средства
    }
    vehicles.clear();                               // Очистить список
}

// Оператор присваивания состояния истории
HistoryManager::HistoryState& HistoryManager::HistoryState::operator=(const HistoryState& other) {
    if (this != &other) {
        // Очистить текущие транспортные средства
        for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
            delete *it;                             // Освободить память
        }
        vehicles.clear();                           // Очистить список
        
        // Скопировать транспортные средства
        for (auto it = other.vehicles.begin(); it != other.vehicles.end(); ++it) {
            if (*it != nullptr) {
                vehicles.push_back((*it)->clone()); // Создать копию каждого транспортного средства
            }
        }
        description = other.description;           // Скопировать описание
    }
    return *this;                                   // Вернуть ссылку на текущий объект
}

// Конструктор менеджера истории
HistoryManager::HistoryManager() {
}

// Деструктор менеджера истории
HistoryManager::~HistoryManager() {
    clear();                                        // Очистить всю историю
}

// Создать снимок состояния списка транспортных средств
HistoryManager::HistoryState HistoryManager::createSnapshot(const List<Vehicle*>& vehicles, const std::string& description) {
    HistoryState state;                             // Создать новое состояние
    state.description = description;                // Установить описание
    
    for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
        if (*it != nullptr) {
            state.vehicles.push_back((*it)->clone()); // Создать копию каждого транспортного средства
        }
    }
    
    return state;                                   // Вернуть состояние
}

// Очистить стек повтора действий
void HistoryManager::clearRedoStack() {
    for (auto it = redoStack.begin(); it != redoStack.end(); ++it) {
        for (auto vit = it->vehicles.begin(); vit != it->vehicles.end(); ++vit) {
            delete *vit;                            // Освободить память для каждого транспортного средства
        }
    }
    redoStack.clear();                              // Очистить стек повтора
}

// Сохранить текущее состояние в историю
void HistoryManager::saveState(const List<Vehicle*>& vehicles, const std::string& description) {
    // Очистить стек повтора при выполнении нового действия
    clearRedoStack();
    
    // Создать снимок состояния
    HistoryState snapshot = createSnapshot(vehicles, description);
    
    // Добавить в стек отмены
    undoStack.push_back(snapshot);
    
    // Ограничить размер стека отмены
    while (undoStack.size() > MAX_HISTORY_SIZE) {
        HistoryState first = undoStack.front();     // Получить первое состояние
        undoStack.pop_front();                      // Удалить первое состояние
        // Первое состояние автоматически уничтожается
    }
}

// Проверить возможность отмены действия
bool HistoryManager::canUndo() const {
    return !undoStack.empty();                      // Вернуть true если стек отмены не пуст
}

// Проверить возможность повтора действия
bool HistoryManager::canRedo() const {
    return !redoStack.empty();                      // Вернуть true если стек повтора не пуст
}

// Отменить последнее действие
List<Vehicle*> HistoryManager::undo(List<Vehicle*>& currentVehicles) {
    if (undoStack.empty()) {                        // Проверить что стек отмены не пуст
        return currentVehicles;                     // Вернуть текущее состояние если стек пуст
    }
    
    // Сохранить текущее состояние в стек повтора
    HistoryState currentSnapshot = createSnapshot(currentVehicles, "Текущее состояние");
    redoStack.push_back(currentSnapshot);
    
    // Ограничить размер стека повтора
    while (redoStack.size() > MAX_HISTORY_SIZE) {
        HistoryState first = redoStack.front();     // Получить первое состояние
        redoStack.pop_front();                       // Удалить первое состояние
    }
    
    // Получить предыдущее состояние
    HistoryState previousState = undoStack.back();   // Получить последнее состояние из стека отмены
    undoStack.pop_back();                            // Удалить его из стека
    
    // Очистить текущие транспортные средства
    for (auto it = currentVehicles.begin(); it != currentVehicles.end(); ++it) {
        delete *it;                                  // Освободить память
    }
    currentVehicles.clear();                        // Очистить список
    
    // Восстановить предыдущее состояние
    List<Vehicle*> restored;                        // Список для восстановленных транспортных средств
    for (auto it = previousState.vehicles.begin(); it != previousState.vehicles.end(); ++it) {
        if (*it != nullptr) {
            restored.push_back((*it)->clone());      // Создать копию каждого транспортного средства
        }
    }
    
    return restored;                                 // Вернуть восстановленное состояние
}

// Повторить последнее отмененное действие
List<Vehicle*> HistoryManager::redo(List<Vehicle*>& currentVehicles) {
    if (redoStack.empty()) {                        // Проверить что стек повтора не пуст
        return currentVehicles;                     // Вернуть текущее состояние если стек пуст
    }
    
    // Сохранить текущее состояние в стек отмены
    HistoryState currentSnapshot = createSnapshot(currentVehicles, "Текущее состояние");
    undoStack.push_back(currentSnapshot);
    
    // Ограничить размер стека отмены
    while (undoStack.size() > MAX_HISTORY_SIZE) {
        HistoryState first = undoStack.front();     // Получить первое состояние
        undoStack.pop_front();                       // Удалить первое состояние
    }
    
    // Получить следующее состояние
    HistoryState nextState = redoStack.back();      // Получить последнее состояние из стека повтора
    redoStack.pop_back();                            // Удалить его из стека
    
    // Очистить текущие транспортные средства
    for (auto it = currentVehicles.begin(); it != currentVehicles.end(); ++it) {
        delete *it;                                  // Освободить память
    }
    currentVehicles.clear();                        // Очистить список
    
    // Восстановить следующее состояние
    List<Vehicle*> restored;                        // Список для восстановленных транспортных средств
    for (auto it = nextState.vehicles.begin(); it != nextState.vehicles.end(); ++it) {
        if (*it != nullptr) {
            restored.push_back((*it)->clone());      // Создать копию каждого транспортного средства
        }
    }
    
    return restored;                                // Вернуть восстановленное состояние
}

// Получить описание действия для отмены
std::string HistoryManager::getUndoDescription() const {
    if (undoStack.empty()) {                        // Проверить что стек отмены не пуст
        return "";                                  // Вернуть пустую строку если стек пуст
    }
    return undoStack.back().description;            // Вернуть описание последнего действия
}

// Получить описание действия для повтора
std::string HistoryManager::getRedoDescription() const {
    if (redoStack.empty()) {                        // Проверить что стек повтора не пуст
        return "";                                  // Вернуть пустую строку если стек пуст
    }
    return redoStack.back().description;            // Вернуть описание последнего отмененного действия
}

// Очистить всю историю
void HistoryManager::clear() {
    // Очистить стек отмены
    for (auto it = undoStack.begin(); it != undoStack.end(); ++it) {
        for (auto vit = it->vehicles.begin(); vit != it->vehicles.end(); ++vit) {
            delete *vit;                            // Освободить память для каждого транспортного средства
        }
    }
    undoStack.clear();                              // Очистить стек отмены
    
    // Очистить стек повтора
    clearRedoStack();
}

