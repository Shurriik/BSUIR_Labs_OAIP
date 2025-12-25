#include "solution.h"


Array::Array() : data(nullptr), size(0) {}                  // Конструктор без параметров

// Конструктор с параметрами
Array::Array(int size) {
    this->size = size;
    data = new int[size];
    // Инициализируем нулями
    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }
}

// Конструктор копирования
Array::Array(const Array& other) {
    size = other.size;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

// Деструктор
Array::~Array() {
    delete[] data;
}

// Функция ввода массива (ИСПРАВЛЕННАЯ)
void Array::input() {
    if (size == 0) {
        // Если массив пустой, запрашиваем размер
        cout << "Введите размер массива: ";
        cin >> size;
        data = new int[size];
        cout << "Введите " << size << " элементов массива:" << endl;
    } else {
        // Если массив уже имеет размер (создан через конструктор с параметрами)
        cout << "Введите " << size << " элементов массива:" << endl;
    }
    
    for (int i = 0; i < size; i++) {
        cout << "Элемент " << i + 1 << ": ";
        cin >> data[i];
    }
}

// Функция вывода массива
void Array::print() const {
    if (size == 0) {
        cout << "Массив пуст" << endl;
        return;
    }
    
    cout << "Массив[" << size << "]: [";
    for (int i = 0; i < size; i++) {
        cout << data[i];
        if (i < size - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

// Функция объединения массивов
Array Array::combine(const Array& other) const {
    int newSize = size + other.size;
    Array result(newSize);
    
    // Копируем элементы из первого массива
    for (int i = 0; i < size; i++) {
        result.data[i] = data[i];
    }
    
    // Копируем элементы из второго массива
    for (int i = 0; i < other.size; i++) {
        result.data[size + i] = other.data[i];
    }
    
    return result;
}

// Получение размера массива
int Array::getSize() const {
    return size;
}

// Получение элемента по индексу
int Array::getElement(int index) const {
    if (index >= 0 && index < size) {
        return data[index];
    }
    return 0;
}

// Установка элемента по индексу
void Array::setElement(int index, int value) {
    if (index >= 0 && index < size) {
        data[index] = value;
    }
}

// Функция для изменения элемента по индексу 
void Array::changeElement(int index, int newValue) {
    if (index >= 0 && index < size) {  // Проверка корректности индекса
        int oldValue = data[index];    // Сохраняем старое значение
        data[index] = newValue;        // Устанавливаем новое значение
        cout << "✓ Элемент [" << index << "] успешно изменен: "
            << oldValue << " -> " << newValue << endl;
    }
    else {
        // Выводим сообщение об ошибке, но не прерываем выполнение
        cout << "✗ Ошибка: индекс " << index << " выходит за границы массива! "
            << "Допустимый диапазон: [0, " << size - 1 << "]" << endl;
    }
}