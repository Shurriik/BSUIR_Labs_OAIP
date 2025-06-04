#ifndef SOLUTION_H
#define SOLUTION_H

#define MAX_LEN 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <Windows.h>



// Структура для хранения адреса в городе
typedef struct CityAddress
{
    char city[MAX_LEN];             // Название города
    char street[MAX_LEN];           // Название улицы
    int house;                      // Номер дома
    int apartment;                  // Номер квартиры
};

// Структура для хранения адреса в формате область
typedef struct RegionCityAddress
{
    char region[MAX_LEN];          // Название области
    char city[MAX_LEN];            // Название города
    char street[MAX_LEN];          // Название улицы
    int house;                     // Номер дома
    int apartment;                 // Номер квартиры
};

// Структура для хранения адреса в формате район
typedef struct DistrictCityAddress
{
    char region[MAX_LEN];           // Название области
    char district[MAX_LEN];         // Название района
    char city[MAX_LEN];             // Название города
    char street[MAX_LEN];           // Название улицы
    int house;                      // Номер дома
    int apartment;                  // Номер квартиры
};

// Структура для хранения адреса в формате район-деревня
typedef struct VillageAddress
{
    char region[MAX_LEN];           // Название области
    char district[MAX_LEN];         // Название района
    char village[MAX_LEN];          // Название деревни
    int house;                      // Номер дома
};



// Объединение для хранения только одного из возможных вариантов адреса
typedef union Address
{
    CityAddress city;                       // Адрес в городе
    RegionCityAddress regionCity;           // Адрес в формате "область-город"
    DistrictCityAddress districtCity;       // Адрес в формате "район-город"
    VillageAddress village;                 // Адрес в формате "район-деревня"
};

// Структура для хранения данных о студенте
typedef struct Student
{
    char name[MAX_LEN];             // Имя студента
    int type;                       // Тип проживания:  1 - город, 2 - область-город, 3 - район-город, 4 - район-деревня
    Address address;                // Адрес проживания (в зависимости от типа)
};

Student* allocateStudents(int count);                                       // Функция динамического выделения памяти

void freeStudents(Student* students, int count);                            // Функция очистки памяти 

int inputInt(int* value);                                                   // Функция ввода числовых значений

int inputString(char* buffer, int size);                                    // Функция ввода строки

void inputStudent(Student* student);                                        // Функция ввода информации о студентах

void printTable(Student* students, int count);                              // Функция вывода информации о студентах 

int searchStudentsByType(const Student* students, int count, int type);     // Функция поиска студентов по заданному параметру 

int matchStudentType(const Student* student, int type);                     // Функция для проверки, соответствует ли студент заданному типу проживания

void saveToFile(const char* filename, const Student* students, int count);  // Сохранение в файл

int loadFromFile(const char* filename, Student** students);                 // Загрузка из файла
                        
void menu();

int againf();

#endif 