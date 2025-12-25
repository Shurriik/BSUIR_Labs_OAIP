#include <iostream>
#include <cstdlib>    
#include <ctime>      
using namespace std;


class Array 
{
private:

    int* data;                                      // Указатель на динамически выделенный массив целых чисел
    int size;                                       // Размер массива 

public:
    
    Array();                                        // Пустой массив
        
    Array(int size);                                // Массив с размером
    
    Array(const Array& other);                      // Массив для копирования

    ~Array();                                       // Деструктор - освобождает динамически выделенную память

    void input();                                   // Ввод элементов массива

    void print() const;                             // Вывод элементов массива

    Array combine(const Array& other) const;        // Объединения массивов

    int getSize() const;                            // Размер массива

    int getElement(int index) const;                // Элемент по индексу в массиве

    void setElement(int index, int value);          // Значение элемента по индексу в массиве

    void changeElement(int index, int newValue);    // Изменение элемента по индексу
};