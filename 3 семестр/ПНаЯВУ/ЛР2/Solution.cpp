#include "Solution.h"

// Конструктор без параметра
String::String()
{
    str = nullptr;  
    size = 0;       
}

// Конструктор с параметром
String::String(int size)
{
    str = new char[size + 1];                       // Динамическое выделение пармяти
    this->size = size;                              // Сохранение размера в класс
    str[0] = '\0';             
}

// Конструктор копирования
String::String(const char* text)
{
    if (text == nullptr) 
    {
        str = nullptr;
        size = 0;
        return;
    }

    size = std::strlen(text);
    str = new char[size + 1];
    strcpy_s(str, size + 1, text);
}

// Конструктор копирования
String::String(const String& other)
{
    str = new char[other.size + 1];                 // Выделение памяти под строку
    size = other.size;                              // Копирование размера
    for (int i = 0; i < other.size; i++)            // Поэлементное копирование символов
    {
        str[i] = other.str[i];       
    }
    str[size] = '\0';                
}

// Деструктор 
String::~String()
{
    delete[] str; 
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, String& s)
{
    if (s.str != nullptr) 
    {  
        os << s.str;                                // Вывод строки
    }
    return os;               
}

// Оператор ввода 
std::istream& operator>>(std::istream& is, String& s)
{
    char temp[MAX_STR];                         // Временный буфер для ввода строки
    is >> temp;                                 // Считать строку во временный буфер
    delete[] s.str;              
    s.size = std::strlen(temp);                 // Определение длинны введенной строки
    s.str = new char[s.size + 1];               // Выделение новой памяти под строку нужного размера

    
    if (s.size < MAX_STR) 
    {
        strcpy_s(s.str, s.size + 1, temp);  
    }
    else 
    {
        strncpy_s(s.str, s.size + 1, temp, s.size);  
        s.str[s.size] = '\0';  
    }
    return is;  
}

// Оператор сложения строк 
String String::operator+(const String& other)
{
    int newSize = size + other.size;            // Вычисление общего размера новой строки
    String res(newSize);                    

    if (size > 0) 
    {  
        strcpy_s(res.str, newSize + 1, str);  
    }
    else 
    {
        res.str[0] = '\0'; 
    }

    if (other.size > 0) 
    {  
        strcat_s(res.str, newSize + 1, other.str);  
    }

    return res;  
}

// Оператор присваивания
String String::operator=(const String& other)
{
    if (this == &other)  
        return *this;    

    delete[] this->str;    
    this->size = other.size;  
    this->str = new char[size + 1];  

    strcpy_s(this->str, size + 1, other.str);  

    return *this;  
}

// Оператор сложения с присваиванием 
String String::operator+=(const String& other)
{
    *this = *this + other;  
    return *this;           
}

// Оператор сравнения на равенство 
bool String::operator==(const String& other)
{
    if (str == nullptr || other.str == nullptr) return false;       // Проверка на существование строк
    return std::strcmp(this->str, other.str) == 0;                  // Сравнивнение строк
}

// Оператор сравнения на неравенство 
bool String::operator!=(const String& other)
{
    if (str == nullptr || other.str == nullptr) return true;   
    return std::strcmp(this->str, other.str) != 0;  
}

// Оператор "меньше"
bool String::operator<(const String& other)
{
    if (str == nullptr || other.str == nullptr) return false;  
    return std::strcmp(this->str, other.str) < 0;  
}

// Оператор "больше" 
bool String::operator>(const String& other)
{
    if (str == nullptr || other.str == nullptr) return false;  
    return std::strcmp(this->str, other.str) > 0;  
}

// Оператор "меньше или равно" 
bool String::operator<=(const String& other)
{
    if (str == nullptr || other.str == nullptr) return false; 
    return std::strcmp(this->str, other.str) <= 0; 
}

// Оператор "больше или равно"
bool String::operator>=(const String& other)
{
    if (str == nullptr || other.str == nullptr) return false; 
    return std::strcmp(this->str, other.str) >= 0; 
}

// Оператор доступа к символу по индексу 
char String::operator[](int num)
{
    if (str == nullptr) return -1;  

    if (num >= 1 && num <= size)  
    {
        return this->str[num - 1];  
    }
    return -1;  
}

// Оператор извлечения подстроки 
String String::operator()(int start, int length)
{
    String res(length);  

    if (str == nullptr) 
    {  
        res.str[0] = '\0';  
        return res;
    }

    // Проверка корректности параметров 
    if ((start <= size) && start > 0 && length <= (size - start + 1))
    {
        int pos = 0; 
        // Копирование символов из исходной строки в подстроку
        for (int i = (start - 1); i < (length + start - 1); i++)
        {
            res.str[pos] = str[i];  
            pos++;                  
        }
        res.str[length] = '\0';  
    }
    else
    {
        res.str[0] = '\0';  
    }
    return res;  
}

//String operator+(const char* lhs, const String& rhs)
//{
//    if (lhs == nullptr) return rhs;  
//
//    int lhsSize = std::strlen(lhs);  
//    int newSize = lhsSize + rhs.size; 
//    String res(newSize);              
//
//    
//    if (lhsSize > 0)
//    {
//        strcpy_s(res.str, newSize + 1, lhs);
//    }
//
//    if (rhs.size > 0)
//    {
//        strcat_s(res.str, newSize + 1, rhs.str);
//    }
//
//    return res;
//}
String String::operator+(const char* other)
{
    if (other == nullptr) return *this;  

    int otherSize = std::strlen(other);  
    int newSize = size + otherSize;      
    String res(newSize);              

    if (size > 0)
    {
        strcpy_s(res.str, newSize + 1, str);
    }

    if (otherSize > 0)
    {
        strcat_s(res.str, newSize + 1, other);
    }

    return res;
}

// Функция меню
void menu()
{
    int choice;              
    String s1, s2, s3;    

    while (true)          
    {
        std::cout << "1.  Создать первую строку" << std::endl;
        std::cout << "2.  Создать вторую строку" << std::endl;
        std::cout << "3.  Вывести первую строку" << std::endl;
        std::cout << "4.  Вывести вторую строку" << std::endl;
        std::cout << "5.  Сложение строк" << std::endl;
        std::cout << "6.  Присваивание" << std::endl;
        std::cout << "7.  Добавление строки" << std::endl;
        std::cout << "8.  Сравнение на равенство" << std::endl;
        std::cout << "9.  Сравнение на неравенство" << std::endl;
        std::cout << "10. Сравнение больше" << std::endl;
        std::cout << "11. Сравнение меньше" << std::endl;
        std::cout << "12. Сравнение больше или равно" << std::endl;
        std::cout << "13. Сравнение меньше или равно" << std::endl;
        std::cout << "14. Получить символ по индексу" << std::endl;
        std::cout << "15. Получить подстроку" << std::endl;
        std::cout << "16. Выход" << std::endl;
        std::cout << "Ваш выбор: ";
        std::cin >> choice; 
        std::cout << "\n" << std::endl;

        
        switch (choice)
        {
        case 1: 
        {
            std::cout << "Введите первую строку: ";
            std::cin >> s1;        
            std::cout << "Строка создана: " << s1 << std::endl;
            break;                 
        }
        case 2:  
        {
            std::cout << "Введите вторую строку: ";
            std::cin >> s2;       
            std::cout << "Строка создана: " << s2 << std::endl;
            break;
        }
        case 3: 
        {
            std::cout << "Первая строка: " << s1 << std::endl;
            break;
        }
        case 4:  
        {
            std::cout << "Вторая строка: " << s2 << std::endl;
            break;
        }
        case 5:  
        {
            s3 = "BSUIR" + s1 + s2;
            std::cout << "Результат сложения: " << s3 << std::endl;
            break;
        }
        case 6:  
        {
            s1 = s2;               
            std::cout << "Присваивание выполнено. s1 = " << s1 << std::endl;
            break;
        }
        case 7:  
        {
            s1 += s2;              
            std::cout << "Добавление выполнено. s1 = " << s1 << std::endl;
            break;
        }
        case 8:  
        {
            if (s1 == s2)         
            {
                std::cout << "Строки равны" << std::endl;
            }
            else
            {
                std::cout << "Строки не равны" << std::endl;
            }
            break;
        }
        case 9:  
        {
            if (s1 != s2)          
                std::cout << "Строки не равны" << std::endl;
            else
                std::cout << "Строки равны" << std::endl;
            break;
        }
        case 10: 
        {
            if (s1 > s2)           
                std::cout << "s1 больше s2" << std::endl;
            else
                std::cout << "s1 меньше s2" << std::endl;
            break;
        }
        case 11: 
        {
            if (s1 < s2)           
                std::cout << "s1 меньше s2" << std::endl;
            else
                std::cout << "s1 больше s2" << std::endl;
            break;
        }
        case 12:
        {
            if (s1 >= s2)          
                std::cout << "s1 больше или равно s2" << std::endl;
            else
                std::cout << "s1 меньше s2" << std::endl;
            break;
        }
        case 13: 
        {
            if (s1 <= s2)          
                std::cout << "s1 меньше или равно s2" << std::endl;
            else
                std::cout << "s1 больше s2" << std::endl;
            break;
        }
        case 14: 
        {
            int index;              // Переменная для хранения индекса
            std::cout << "Введите номер элемента строки: ";
            std::cin >> index;      
            char ch = s1[index];    // Получение символа по индексу
            if (ch != -1)          
                std::cout << "Символ с индексом " << index << ": '" << ch << "'" << std::endl;
            else
                std::cout << "Неверный индекс!" << std::endl;
            break;
        }
        case 15: 
        {
            int start, length;      // Переменные для начальной позиции и длины
            std::cout << "Введите начальную позицию: ";
            std::cin >> start;      
            std::cout << "Введите длину подстроки: ";
            std::cin >> length;    
            String substring = s1(start, length);  // Извлечение подстроки
            std::cout << "Подстрока: " << substring << std::endl;
            break;
        }
        case 16: 
        {
            std::cout << "Выход из программы." << std::endl;
            return;                 
        }
        default: 
        {
            std::cout << "Неверная команда!" << std::endl;
            break;
        }
        }
    }
}

// Функция для повторения программы
int runAgain()
{
    int again;
    std::cout << "Введите 1, чтобы продолжить или любой другой символ, чтобы выйти: ";

    std::cin >> again;
    std::cin.ignore(10000, '\n'); 

    if (again == 1)
    {
        std::cout << "Повтор программы" << std::endl;
        std::cout << std::endl;
        return 1;
    }
    else
    {
        std::cout << "\nЗавершение работы программы" << std::endl;
        return 0;
    }
}