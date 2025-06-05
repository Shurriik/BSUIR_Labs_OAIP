#include <stdio.h>
#include <stdlib.h>
#include <string.h>         
#include <locale.h>
#include "solution.h"       


int main() 
{
    setlocale(LC_ALL, "RUS");
    char expression[M]; 
    int choice;
    do
    {

        printf("Введите математическое выражение: ");
        if (fgets(expression, M, stdin) == NULL)
        {
            printf("Ошибка при вводе.\n");
            return 1;
        }

        expression[strcspn(expression, "\n")] = '\0';

        checkSyntaxError(expression);
      
        checkBrackets(expression); // Проверка выражения

        printf("Введите 1, чтобы продолжить или любой другой символ, чтобы завершить программу: ");
        scanf_s("%d", &choice);

        if (choice == 1)
        {
            printf("Повтор выполнения задачи\n");
        }
        else
        {
            printf("Завершение работы программы\n");
        }
        while (getchar() != '\n');
    } while (choice == 1);

    return 0;
}

