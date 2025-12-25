#include <iostream>
#include <locale>
#include <cstring>
 
#define MAX_STR 150  

class String
{
    char* str;                                                      // Указатель на массив 
    int size;                                                       // Размер строки

public:
    String();                                                       // Конструктор без параметра
    String(int size);                                      // Конструктор с параметром
    String(const char* text);
    String(const String& other);                                    // Конструктор копирования
    ~String();                                                      // Деструктор
    friend std::ostream& operator<<(std::ostream& os, String& s);   // Функция вывода
    friend std::istream& operator>>(std::istream& os, String& s);   // Функция ввода
    friend String operator+(const char* lhs, const String& rhs);
    String operator+(const char* other);
    String operator+(const String& other);                          // Оператор сложения строк 
    String operator=(const String& other);                          // Оператор присваивания
    String operator+=(const String& other);                         // Оператор сложения с присваиванием
    bool operator==(const String& other);                           // Оператор сравнения на равенство
    bool operator!=(const String& other);                           // Оператор сравнения на неравенство
    bool operator>(const String& other);                            // Оператор "больше"
    bool operator>=(const String& other);                           // Оператор "больше или равно"
    bool operator<(const String& other);                            // Оператор "меньше"
    bool operator<=(const String& other);                           // Оператор "меньше или равно"
    String operator()(int start, int length);                       // Оператор извлечения подстроки
    char operator[](int num);                                       // Оператор доступа к символу по индексу
};

void menu();                                                        // Функция для отображения меню
int runAgain();                                                     // Функция для повторения программы