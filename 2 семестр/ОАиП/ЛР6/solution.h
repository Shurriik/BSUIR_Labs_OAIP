#ifndef SOLUTION_H  
#define SOLUTION_H


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define DATA_FILE "cubes_data.txt"

struct Cube                                             // Структура Cube, содержащая данные о кубике                                        
{
    int edge;                                           // Длина ребра куба
    char color[10];                                     // Цвет куба (до 9 символов)
    char material[10];                                  // Материал куба (до 9 символов)
};


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

int saveCubesToFile(const Cube* cubes, int count);      // Сохранение в файл

Cube* loadCubesFromFile(int* count);                    // Загрузка из файла

void menu(Cube** cubesPtr, int* count);

int againf();


#endif

