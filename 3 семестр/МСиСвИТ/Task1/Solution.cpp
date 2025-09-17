#include "Solution.h" 


const std::streamsize MAX_STREAM_SIZE = 1000;                                               // Максимальный размер буфера ввода




RandomArrayGenerator::RandomArrayGenerator(double min, double max)                          // Конструктор со списком 
    : gen(time(0)),  dist(min, max) {}  


std::vector<std::vector<double>> RandomArrayGenerator::generateArray(int rows, int cols)    // Метод генерации массива со случайными числами
{
    
    std::vector<std::vector<double>> array(rows, std::vector<double>(cols));                // Двумерный массив заданного размера


    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++)  
        {
            array[i][j] = dist(gen);                                                        // Генерация случайного числа
            
            array[i][j] = round(array[i][j] * 10) / 10.0;                                   // Округление до одного знака после запятой
        }
    }

    return array;  
}



Array::Array(const std::vector<std::vector<double>>& InputArray)                            // Конструктор 
{
    ValidDateInput(InputArray);                                                             // Проверка корректности входных данных
    A = InputArray;                                                                         // Копирование входного массива
    ProcessArray();                                                                         // Обработка массива
}


void Array::ValidDateInput(const std::vector<std::vector<double>>& InputArray)              // Проверка входных данных
{
    if (InputArray.empty())                                                                 // Проверка на пустой массив
    {
        throw std::invalid_argument("Массив пуст");  
    }

    if (InputArray.size() != 6)                                                             // Проверка количества строк
    {
        throw std::invalid_argument("Некорректное количество строк в массиве");  
    }

    for (int i = 0; i < 6; i++)  
    {
        if (InputArray[i].size() != 7)                                                      // Проверка количества столбцов
        {
            throw std::invalid_argument("Некорректное количество столбцов в массиве");  
        }
    }
}


void Array::ProcessArray()                                                                  // Обработка массива
{
    countMinusOne = 0;                                                                      // Счетчик для количества элементов со значением -1

    X.resize(6, std::vector<double>(7, 0.0));                                               // Инициализация результирующего массива нулями

    for (int i = 0; i < 6; i++)  
    {
        for (int j = 0; j < 7; j++)  
        {
            if (A[i][j] > 0)  
            {
                X[i][j] = A[i][j] * cos(A[i][j]);  
            }
            else if (A[i][j] == 0) 
            {
                X[i][j] = 0;  
            }
            else if (A[i][j] < 0)  
            {
                X[i][j] = -1;  
                countMinusOne++;  
            }
        }
    }
}


void Array::PrintArray() const                                                              // Вывод исходного массива
{
    std::cout << "Исходный массив А(6,7):\n";  

    for (int i = 0; i < 6; i++)  
    {
        for (int j = 0; j < 7; j++)  
        {  
            std::cout << std::setw(10) << std::fixed << std::setprecision(2) << A[i][j] << " ";
        }
        std::cout << "\n";  
    }
    std::cout << "\n";  
}


void Array::PrintResultArray() const                                                        // Вывод результирующего массива
{
    std::cout << "Результирующий массив X(6,7):\n";  

    for (int i = 0; i < 6; i++)  
    {
        for (int j = 0; j < 7; j++) 
        {
            std::cout << std::setw(10) << std::fixed << std::setprecision(2) << X[i][j] << " ";
        }
        std::cout << "\n";  
    }
    std::cout << "\n";  
}


int Array::PrintCountMinusOne() const                                                       // Метод получения количества элементов со значением -1
{
    return countMinusOne;  
}


const std::vector<std::vector<double>>& Array::ResultArray() const                          // Метод получения результирующего массива
{
    return X;  
}


std::vector<std::vector<double>> Array::InputArray()                                        // Метод для ввода массива с клавиатуры
{
    const int ROWS = 6;                                                                     // Количество строк
    const int COLS = 7;                                                                     // Количество столбцов
    
    std::vector<std::vector<double>> array(ROWS, std::vector<double>(COLS, 0.0));           // Массив размерностью (6,7) заполненный нулями

    std::cout << "Введите элементы массива A(6,7):\n";  

    for (int i = 0; i < ROWS; i++)  
    {
        std::cout << "Строка " << (i + 1) << ": ";  

        for (int j = 0; j < COLS; j++)  
        {
            while (true)  
            {
                if (!(std::cin >> array[i][j]))  
                {
                    std::cin.clear(); 
                    std::cin.ignore(MAX_STREAM_SIZE, '\n'); 
                    std::cout << "Ошибка ввода! Пожалуйста, введите число: ";  
                    continue;  
                }
                break;  
            }
        }

        std::cin.ignore(MAX_STREAM_SIZE, '\n');  
    }

    return array;  
}


void displayMenu()                                                                        // Функция отображения меню
{
    std::cout << "1. Ввести массив с клавиатуры\n";  
    std::cout << "2. Использовать тестовый массив\n";  
    std::cout << "3. Заполнить массив случайными числами\n";  
    std::cout << "4. Выйти\n";  
    std::cout << "Выберите вариант: ";  
}

