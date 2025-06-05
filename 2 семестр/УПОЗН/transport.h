#ifndef TRANSPORT_H
#define TRANSPORT_H


#include <locale.h>
#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  
#include <time.h>  
#include <ctype.h>
  

#define MAX_STRING 50                   // Максимальная длина строки
#define EXPORT_FILE "export.txt"        // Файл для экспорта 

// Перечисление типов ТС
typedef enum TransportType
{
    TRUCK,              // Грузовой транспорт
    PASSENGER           // Пассажирский транспорт
};

// Структура для хранения информации о бронировании
typedef struct Booking
{
    char date[20];          // Дата ЧЧ:ММ:ГГГГ
    char time[10];          // Время ЧЧ:ММ
    char user[MAX_STRING];  // Имя заказчика
};

// Структура для хранения информации о транспортном средстве
typedef struct Transport
{
    int id;                                 // Уникальный идентификатор ТС
    TransportType type;                     // Тип ТС
    char model[MAX_STRING];                 // Модель ТС 
    int capacity;                           // Вместимость ТС 
    int available;                          // Количество доступных единиц данного ТС
    char current_status[MAX_STRING];        // Текущий статус ТС
    Booking* bookings;                      // Указатель на динамический массив бронирований для данного ТС
    int booking_count;                      // Количество бронирований для данного ТС
};

void exportToTextFile();                            // Экспорт данных во временный текстовый файл

void saveToFile();                                  // Сохранение данных в файл

int loadFromFile(const char* filename);             // Загрузка данных из файла

int loadFromExportFile();                           // Экспорт данных в текстовый файл

int isLeapYear(int year);                           // Проверка високосного года

int isValidDate(int day, int month, int year);      // Корректность даты

int isValidTime(int hour, int minute);              // Корректность времени

int isVehicleAvailable(int id, const char* date);   // Доступность ТС

void addTransport();                                // Добавление нового ТС

void orderTransport();                              // Бронирование ТС

void editBooking();                                 // Редактирование бронирования

void cancelBooking();                               // Отмена бронирования

void updateAvailability();                          // Обновление доступности ТС

void checkStatus();                                 // Проверка статуса ТС

void filterTransport();                             // Фильтр ТС

void countAvailableByDate();                        // Подсчет доступных ТС на дату

void printStatistics();                             // Вывод статистики по ТС

void printTransports();                             // Печать списка всех ТС

void searchTransport();                             // Поиск ТС

void editTransport();                               // Редактирование информации о ТС

void deleteTransport();                             // Удаление ТС

void validateTransportData();                       // Проверка целостности данных

void TransportSystem();                             // Выделение памяти

void ensureCapacity();                              // Перераспределение памяти

void cleanupTransportSystem();                      // Очистка памяти

void trim(char* str);                               // Функция для удаления пробелов в начале и конце строки

void menu();                                        // Меню

int againf();                                       // Повтор программы

#endif 