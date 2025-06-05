#ifndef SOLUTION_H  
#define SOLUTION_H


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <Windows.h>


#define DATA_FILE "cubes_data.dat"                     // Название бинарного файла для кубиков


struct Cube                                             // Структура содержащая данные о кубике                                        
{
    int edge;                                           // Длина ребра куба
    char color[10];                                     // Цвет куба 
    char material[10];                                  // Материал куба 
};



int inputInt(int* value);

int isValidColor(const char* color);                    // Функции проверки корректности ввода цвета

int isValidMaterial(const char* material);              // Функции проверки корректности ввода материала

Cube* allocateCubes(int count);                         // Выделение памяти под массив кубов

void Input(char* buffer, int size);                     // Функция для ввода строки

void InputNumber(int* number, const char* prompt);      // Ввод чисел 

void inputCubes(Cube* cubes, int count);                // Ввод данных о кубах

void printColorCounts(Cube* cubes, int count);          // Вывод количества кубов по цветам

void printWoodenCubesByEdge(Cube* cubes, int count);    // Вывод деревянных кубов заданного размера

void printMetalCubesByEdge(Cube* cubes, int count);     // Вывод металлических кубов больше заданного размера

void freeCubes(Cube* cubes);                            // Освобождение памяти

int saveCubesToBinFile(const Cube* cubes, int count);   // Сохранение в бинарный файл

Cube* loadCubesFromBinFile(int* count);                 // Загрузка из бинарного файла

void menu();

int againf();

#endif