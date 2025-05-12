#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "solution.h"


int input_size(void)                                                            // Функция ввод параметром матрицы с проверкой
{
    int size;                                                                   // Объявить размер массива
    do
    {

        if (scanf_s("%d", &size) != 1)
        {
            printf("Ошибка\n");
            while (getchar() != '\n');
        }
        else if (size < 1)
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
    } 
    while (1);

    return size;
}



double** create_matrix(int n, int m)                                            // Функция создания матрицы
{
    double** matrix = (double**)malloc(n * sizeof(double*));                    // Память для строк

    for (int i = 0; i < n; i++) 
    {
        *(matrix+i) = (double*)malloc(m * sizeof(double));                        // Память для элементов строки
    }
    return matrix;
}


void free_matrix(double** matrix, int n)                                        // Функция освобождения памяти матрицы
{
    for (int i = 0; i < n; i++) 
    {
        free(*(matrix + i));                                                        // Освободить каждую строку
    }
    free(matrix);                                                               // Освободить массив указателей
}


void input_matrix(double** matrix, int n, int m)                                // Функция ввода элементов матрицы
{
    int fill_choice;

    printf("Выбор ввода\n");
    printf("1 - рандомный ввод\n");
    printf("2 - ввод матрицы вручную\n");
    printf("Ваш выбор:");

    do
    {
        if (scanf_s("%d", &fill_choice) != 1)
        {
            printf("Ошибка: некорректный ввод");
            while (getchar() != '\n');
        }
        else if (fill_choice != 1 && fill_choice != 2)
        {
            printf("Ошибка: некорректный ввод");
            while (getchar() != '\n');
        }
        else if (getchar() != '\n')
        {
            printf("Ошибка: некорректный ввод");
            while (getchar() != '\n');
        }
        else
        {
            break;
        }
    } while (1);

    

    if (fill_choice == 1)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                *(*(matrix + i) + j) = (rand() % 101) - 50;
            }
        }
    }
    if(fill_choice == 2)
    {
        printf("Введите элементы матрицы размером %dx%d:\n", n, m);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                printf("Элемент [%d][%d]: ", i, j);
                do
                {

                    if (scanf_s("%lf", (*(matrix + i) + j)) != 1)
                    {
                        printf("Ошибка:\n");
                        while (getchar() != '\n');
                    }
                    else if (getchar() != '\n')
                    {
                        printf("Ошибка:\n");
                        while (getchar() != '\n');
                    }
                    else
                    {
                        break;
                    }

                } while (1);
            }
        }
    }
    printf("\n");
}


void print_matrix(double** matrix, int n, int m)                                // Функция вывода матрицы
{
    printf("Матрица:\n");
    printf("\n");

    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            printf("%7.2lf", *(*(matrix+i)+j));
        }

        printf("\n");
    }

    printf("\n");
}


void calculate_b(double** matrix, int n, int m, double x, int* b)               // Функция вычисления массива b
{
    for (int i = 0; i < n; i++) 
    {
        *(b+i) = 1;                                                               // Присвоить начальное значение каждого элемента строки меньше х

        for (int j = 0; j < m; j++) 
        {
            if (*(*(matrix+i)+j) > x)                                               // Если хотя бы один элемент больше x
            {   
                *(b+i) = 0;                                                       // Присвоить строке значение 0

                break;    
            }
        }
    }
}


void print_b(int* b, int n)                                                 // Функция вывода массива b
{
    printf("Вектор b:\n");
    printf("\n");

    for (int i = 0; i < n; i++) 
    {
        printf("%d", *(b+i)); 
    }

    printf("\n");
    printf("\n");
}
