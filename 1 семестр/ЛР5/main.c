#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "solution.h"

int main() 
{
    int choice;

    do
    {
        double** matrix;                                    // Двумерная матрица
        int* b;                                             // Вектор b
        int n;
        int x;

        setlocale(LC_ALL, "RUS");

        
        printf("Введите натуральное число n: ");            // Ввод n
        n = input_size();

        
        printf("Введите действительное число x: ");         // Ввод x
        x = input_size();

        
        matrix = create_matrix(n, 2 * n);                   // Создание матрицы размером n x 2n

        
        input_matrix(matrix, n, 2 * n);                     // Ввод матрицы

        
        print_matrix(matrix, n, 2 * n);                     // Вывод матрицы

        
        b = (int*)malloc(n * sizeof(int));                  // Выделить память под вектор b

        
        calculate_b(matrix, n, 2 * n, x, b);                 // Вычисляем вектор b

        
        print_b(b, n);                                       // Вывод вектора b

       
        free(b);                                             // Освободить память
        free_matrix(matrix, n);

        printf("Введите 1, чтобы повторить или любой другой символ, чтобы выйти: ");
        scanf_s("%d", &choice);

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

    }
    while (choice == 1);

    return 0;
}
