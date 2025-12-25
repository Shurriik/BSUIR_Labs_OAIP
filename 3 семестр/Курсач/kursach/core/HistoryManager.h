#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include "List.h"
#include "Vehicle.h"
#include <string>

// Класс для управления историей изменений (отмена/повтор действий)
class HistoryManager 
{
private:
    struct HistoryState 
    {
        List<Vehicle*> vehicles;                // Список транспортных средств в данном состоянии
        std::string description;                // Описание действия, приведшего к этому состоянию
        
        HistoryState() = default;              // Конструктор по умолчанию
        HistoryState(const HistoryState& other);  // Конструктор копирования
        ~HistoryState();                        // Деструктор
        HistoryState& operator=(const HistoryState& other);  // Оператор присваивания
    };
    
    List<HistoryState> undoStack;              // Стек состояний для отмены действий
    List<HistoryState> redoStack;              // Стек состояний для повтора действий
    static const int MAX_HISTORY_SIZE = 5;     // Максимальное количество состояний в истории
    
    HistoryState createSnapshot(const List<Vehicle*>& vehicles, const std::string& description);  // Создать снимок состояния
    void clearRedoStack();                     // Очистить стек повтора
    
public:
    HistoryManager();                          // Конструктор
    ~HistoryManager();                         // Деструктор
    
    void saveState(const List<Vehicle*>& vehicles, const std::string& description);  // Сохранить текущее состояние
    bool canUndo() const;                      // Проверить возможность отмены действия
    bool canRedo() const;                      // Проверить возможность повтора действия
    List<Vehicle*> undo(List<Vehicle*>& currentVehicles);  // Отменить последнее действие
    List<Vehicle*> redo(List<Vehicle*>& currentVehicles);  // Повторить последнее отмененное действие
    std::string getUndoDescription() const;   // Получить описание действия для отмены
    std::string getRedoDescription() const;    // Получить описание действия для повтора
    void clear();                              // Очистить всю историю
};

#endif 

