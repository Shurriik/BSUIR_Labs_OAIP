#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "solution.h" 


void remove_newline(char* str)                                                              // Удаление символа новой строки
{
    if (str == NULL) return;                                                                // Проверка, строка не NULL
    if (strchr(str, '\n'))                                                                  // Проверка, содержит ли строка символ новой строки
    { 
        str[strcspn(str, "\n")] = '\0';                                                     // Замена символ новой строки на нуль-символ
    }
}


void process_string(const char* input, char** result, int* sum)                             // Основная функция обработки строки
{
    if (input == NULL || result == NULL || *result == NULL || sum == NULL) return;          // Проверка входных параметров на NULL

    (*result)[0] = '\0';                                                                    // Инициализация результирующей строки как пустой
    *sum = 0;                                                                               // Инициализация суммы чисел нулём

    concat_words(input, result, 0);                                                         // Вызыв функции для конкатенации слов
    calculate_sum(input, sum, 0);                                                           // Вызыв функции для вычисления суммы чисел
}


void concat_words(const char* input, char** result, int index)                              // Функция конкатенации слов
{
    if (input[index] == '\0') return;                                                       // Если достигнут конец строки, выход из функции

    char* word = (char*)malloc(256);                                                        // Создание буфера для хранения текущего слова
    int word_index = 0;                                                                     // Инициализация индекса для буфера

    
    while (input[index] != '\0' && input[index] != ' ')                                     // Извлечение слова
    { 
        word[word_index++] = input[index++];                                                // Копирование символа в буфер слова и сдвиг индекса
    }
    word[word_index] = '\0';                                                                // Завершение строки/слова нуль-символом

    if (is_alpha(word) && strlen(word) >= 4)                                                // Проверка, слово состоит из букв и имеет длину >= 4
    { 
        unsigned long int current_length = strlen(*result);                                            // Вычислить текущую длину результирующей строки
        unsigned long int word_length = strlen(word);                                                  // Вычислить длину текущего слова

        
        *result = realloc(*result, current_length + word_length + 1);                       // Увеличение памяти для результирующей строки
        if (*result == NULL) 
        { 
            fprintf(stderr, "Ошибка выделения памяти.\n"); 
            exit(1); 
        }

        
        strcat_s(*result, current_length + word_length + 1, word);                          // Добавление слова в результирующую строку
    }


    while (input[index] == ' ')                                                             // Пропуск пробелов
    { 
        index++;
    }

    concat_words(input, result, index);                                                     // Рекурсивный вызов функции для обработки следующего слова
}


void calculate_sum(const char* input, int* sum, int index)                                  // Вычисление суммы чисел
{
    if (input[index] == '\0') return;                                                       // Если достигнут конец строки, выход из функции

    char* word = (char*)malloc(256);                                                        // Создание буфера для хранения текущего слова
    int word_index = 0;                                                                     // Инициализация индекса для буфера

    
    while (input[index] != '\0' && input[index] != ' ')                                     // Извлечение слова
    { 
        word[word_index++] = input[index++];                                                // Копирование символа в буфер слова и сдвиг индекса
    }
    word[word_index] = '\0'; 

    if (is_numeric(word))                                                                   // Если слово состоит только из цифр
    { 
        *sum += atoi(word);                                                                 // Преобразование слова в число и добавление к сумме
    }

   
    while (input[index] == ' ')                                                             // Пропуск пробелов
    { 
        index++;
    }

    calculate_sum(input, sum, index);                                                       // Рекурсивный вызов функции для обработки следующего слова
}


int is_numeric(const char* str)                                                             // Проверка на числовую строку
{
    if (str == NULL || *str == '\0') return 0;                                              // Если строка пустая или NULL
    for (int i = 0; str[i] != '\0'; i++)                                                    // Переборка символов строки
    { 
        if (str[i] < '0' || str[i] > '9') return 0;                                         // Если символ не является цифрой
    }
    return 1; 
}


int is_alpha(const char* str)                                                               // Проверка на алфавитную строку
{
    if (str == NULL || *str == '\0') return 0;                                              // Если строка пустая или NULL
    for (int i = 0; str[i] != '\0'; i++)                                                    // Переборка символов строки
    { 
        if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')))        // Если символ не является буквой
        {
            
            return 0; 
        }
    }
    return 1; 
}


