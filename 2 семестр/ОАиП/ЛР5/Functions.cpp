#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "solution.h"
#include <stdlib.h>



int isPositiveInteger(const char* str)      // Проверка на положительные числа
{
    if (!str || *str == '\0') return 0;

    if ((*(str + 0)) == '-') return 0;

    for (int i = 0; (*(str + i)); i++)
    {
        if (!isdigit((*(str + i)))) return 0;
    }

    return 1;
}


int getPositiveInt(const char* prompt, int min, int max)        // Ввод числа в заданном диапазоне 
{
    char buffer[MAX_INPUT];
    int value;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';


            if (isPositiveInteger(buffer))
            {
                value = atoi(buffer);

                if (value >= min && value <= max)
                {
                    return value;
                }
                else
                {

                    printf("Ошибка: число должно быть от %d до %d.\n", min, max);
                }
            }
            else
            {

                printf("Ошибка: введите положительное целое число.\n");
            }
        }
    }
}


// Меню пользователя
void menu()
{
    int choice;
    do
    {

        puts("\nМеню");
        puts("1 - Создать дерево");
        puts("2 - Добавить узел");
        puts("3 - Обход дерева (симметричный)");
        puts("4 - Удалить узел");
        puts("5 - Найти минимум");
        puts("6 - Найти максимум");
        puts("7 - Вывести дерево");
        puts("8 - Завершить интерфейс");
        printf("Выберите пункт.");
        
        choice = getPositiveInt("Ваш выбор: ", MIN_INPUT, MAX_INPUT);


        switch (choice)
        {
        case 1: createTree(); break;

        case 2: addNode(); break;

        case 3: inOrderTraversal(root); break;

        case 4: deleteNode(); break;

        case 5:
        {
            Node* min = findMin(root);
            if (min) printf("Минимум: %s (%d)\n", min->inf, min->n);
            else puts("Дерево пустое");
            break;
        }

        case 6:
        {
            Node* max = findMax(root);
            if (max) printf("Максимум: %s (%d)\n", max->inf, max->n);
            else puts("Дерево пустое");
            break;
        }

        case 7: printTree(root, 0); break;

        case 8: return;

        default: puts("Неверный пункт!");
        }
    } while (1);
}

int againf()
{
    int again, x;
    printf("Введимте 1, чтобы продолжить или любоой другой символ, чтобы выйти: ");
    while (1)
    {
        x = scanf_s("%d", &again);
        if (x != 1 || again != 1)
        {
            printf("\n");
            printf("Завершение работы программы");
            again = 0;
            return again;
        }
        else
        {
            printf("Повтор программы");
            printf("\n");
            break;
        }

    }
    return again;

}