#ifndef SOLUTION_H  
#define SOLUTION_H  

#include <iostream>    
#include <vector>      
#include <cmath>       
#include <stdexcept>   
#include <iomanip>     
#include <limits>      
#include <random>      
#include <ctime> 
#include <locale.h>



class RandomArrayGenerator
{

private:

    std::mt19937 gen;                                                               // Генератор случайных чисел 

    std::uniform_real_distribution<double> dist;                                    // Равномерное распределение 

public:
    
    RandomArrayGenerator(double min = -10.0, double max = 10.0);                    // Конструктор с параметрами по умолчанию
    
    std::vector<std::vector<double>> generateArray(int rows = 6, int cols = 7);     // Метод для генерации массива 
};


class Array
{
private:

    std::vector<std::vector<double>> A;                                             // Исходный массив

    std::vector<std::vector<double>> X;                                             // Результирующий массив

    int countMinusOne;                                                              // Счетчик элементов со значением -1

    void ValidDateInput(const std::vector<std::vector<double>>& InputArray);        // Проверка входных данных

    void ProcessArray();                                                            // Обработка массива по формуле

public:

    Array(const std::vector<std::vector<double>>& InputArray);                      // Конструктор, принимающий входной массив

    void PrintArray() const;                                                        // Вывод исходного массива

    void PrintResultArray() const;                                                  // Вывод результирующего массива

    int PrintCountMinusOne() const;                                                 // Получение количества элементов -1

    const std::vector<std::vector<double>>& ResultArray() const;                    // Получение результирующего массива

    static std::vector<std::vector<double>> InputArray();                           // Статический метод для ввода массива
};

void displayMenu();                                                                 // Функция меню

#endif  