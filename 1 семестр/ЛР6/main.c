#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "solution.h"


int main()
{
	int choice;
	setlocale(LC_ALL, "RUS");
    do
    {
        char* input = input_string();
        if(!input)
        {
            printf(stderr, "Ошибка при выделении памяти для ввода.\n");
            while (getchar() != '\n');
        }
     
       
            // Проверка входных данных
            if (!validate_input(input))
            {
                printf(stderr, "Ошибка: строка должна содержать хотя бы одно двоеточие.\n");
                //free_memory(input);
                return 1;

            }
           

        // Вызов функции для поиска первого и второго двоеточия
        const char* first_colon = find_first_colon(input);
        const char* second_colon = find_second_colon(first_colon);

        // Вызов функции для извлечения символов между двоеточиями
        char* result = extract_colons(first_colon, second_colon);

        if (result) 
        {
            printf("Извлеченная подстрока: %s\n", result);
        }
        else 
        {
            if (second_colon) 
            {
                printf("Между двоеточиями ничего нет.\n");
            }
            else 
            {
                printf("После первого двоеточия ничего нет.\n");
            }
        }

        // Очистка памяти
        free_memory(input);
        free_memory(result);

        printf("Введите 1, чтобы продолжить или любой другой символ, чтобы выйти: ");
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

