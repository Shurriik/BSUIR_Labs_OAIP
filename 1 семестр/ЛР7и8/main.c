#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <locale.h> 
#include "solution.h" 

int main()
{
    int choice=0;                                                         // Переменная для хранения выбора пользователя (продолжить или выйти)

    do 
    {
        setlocale(LC_ALL, "RUS"); 
        char* input = NULL;                                             // Указатель для ввода строки
        char* result = NULL;                                            // Указатель для обработанной строки
        int  buffer_size = 0;                                           // Размер буфера для строки
        int sum = 0;                                                    // Переменная для хранения суммы чисел
        int valid_input = 0;                                            // Флаг для проверки корректности ввода

       
  
        do
        {
            printf("Введите начальный размер буфера: ");
            if (scanf_s("%d", &buffer_size) != 1)
            {
                printf("Ошибка\n");
                while (getchar() != '\n');
            }
            else if (buffer_size < 3)
            {
                printf("Ошибка\n");
                while (getchar() != '\n');
            }
            else if (getchar() != '\n')
            {
                printf("Ошибка\n");
                while (getchar() != '\n');
            }
            else
            {

                break;
            }
        } while (1);
        
      

        
        input = (char*)malloc(buffer_size * sizeof(char));              // Выделение памяти для строки
        if (input == NULL) 
        { 
            printf(stderr, "Ошибка выделения памяти для ввода.\n"); 
            return 1; 
        }

        do 
        { 
            printf("Введите строку: "); 
            if (fgets(input, (int)buffer_size, stdin) == NULL)          // Чтение строки с проверкой на ошибку
            { 
                fprintf(stderr, "Ошибка ввода строки. Попробуйте ещё раз.\n"); 
                continue; 
            }

            valid_input = 1;  
        } while (!valid_input);
    

        remove_newline(input);                                          // Удаление символа новой строки из введённой строки

        
        result = malloc(1);                                             // Выделение памяти для результирующей строки
        if (result == NULL) 
        { 
            fprintf(stderr, "Ошибка выделения памяти для результата.\n"); 
            free(input);                                                // Освобождение памяти для ввода
            return 1; 
        }
        result[0] = '\0';                                               // Инициализация результирующей строки как пустой

        
        process_string(input, &result, &sum);                           // Обработка строки: конкатенация слова и подсчёт суммы чисел

        
       
        printf("Обработанная строка: %s\n", result); 
        printf("Сумма чисел: %d\n", sum); 

        
        free(input);                                                    // Освобождение памяти для ввода
        free(result);                                                   // Освобождение памяти для результата

        printf("Введите 1, чтобы повторить или любой другой символ, чтобы выйти: "); 
        scanf_s("%d", &choice); 

        while (getchar() != '\n'); 

        printf("\n");

        if (choice == 1) 
        {
            printf("Повтор выполнения задачи\n"); 
        }
        else 
        {
            printf("Завершение работы программы\n"); 
        }

        printf("\n");

    } while (choice == 1); 
    return 0; 
}
