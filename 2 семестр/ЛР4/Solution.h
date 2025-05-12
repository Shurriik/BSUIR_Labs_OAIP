#ifndef SOLUTION_H
#define SOLUTION_H

#define MAX_PLATE_LENGTH 11 
#define MAX_WAITLIST 100    
#define MAX_INPUT 100
#define MIN_TOTALSPACE 1
#define MAX_TOTALSPACE 100

// Структура машины
typedef struct 
{
    char plate[MAX_PLATE_LENGTH];       // Номер машины
} Car;

// Очередь
typedef struct zap 
{
    char inf[MAX_PLATE_LENGTH];         // Номер машины
    struct zap* nx;                     // Указатель на следующий элемент
} zap;

// Структура парковки
typedef struct 
{
    int id;                     // Номер парковки
    int totalSpaces;            // Общее количество мест
    int freeSpaces;             // Количество свободных мест
    Car* cars;                  // Массив припаркованных машин
    zap* waitlistHead;          // Голова очереди
    zap* waitlistTail;          // Хвост очереди
} Parking;


void initializeParkings();                            // Инициализация массива парковок

void createNewParking(int);                           // Создание новой парковки

void listAllParkings();                               // Вывод списка всех парковок

void displayParking(int);                             // Информации о парковке

int parkCar(int, const char*);                        // Припарковать машину

int removeCar(int, const char*);                      // Удалить машину

void showWaitlist(int);                               // Показать очередь ожидания

void inputCarPlate(char*);                            // Ввод номера машины

void clearInputBuffer();                              // Очистка буфера ввода

void freeMemory();                                    // Очистка выделенной памяти

int getPositiveInt(const char* prompt, int min, int max);  // Ввод числа в заданном диапазоне 

int isPositiveInteger(const char* str);                   // Проверка на положительные числа

// Очередь
void addToQueue(zap**, zap**, const char*);           // Добавление в очередь

void removeFromQueue(zap**, zap**);                   // Удаление из очереди

int isQueueEmpty(zap*);                               // Проверка, пуста ли очередь

void printQueue(zap*);                                // Печать очереди

#endif

