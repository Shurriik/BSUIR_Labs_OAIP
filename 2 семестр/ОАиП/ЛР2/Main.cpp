#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#include "solution.h"

int main()
{
    setlocale(LC_ALL, "RUS");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int choice;
    do
    {
        int n;
        printf("Введите количество студентов: ");
        while (!inputInt(&n))
        {
            printf("Ошибка: введите корректное число студентов: ");
        }

        Student* students = allocateStudents(n);                        // Выделение памяти

        for (int i = 0; i < n; i++)
        {
            printf("\nВвод данных для студента %d:\n", i + 1);
            inputStudent(&(*(students + i)));
        }

        printTable(students, n);

        // Указатель на функцию
        int (*SearchFunction)(const Student*, int, int) = searchStudentsByType;

        int searchType;
        printf("Введите тип проживания для поиска (1-4): ");
        while (!inputInt(&searchType) || searchType < 1 || searchType > 4)
        {
            printf("Ошибка: выберите корректный тип (1-4): ");
        }

        // Вызов функции через указатель 
        SearchFunction(students, n, searchType);

        freeStudents(students, n);

        printf("\nВведите 1, чтобы продолжить, или любой другой символ, чтобы выйти: ");
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

        printf("\n");

    } while (choice == 1);

    return 0;
}
