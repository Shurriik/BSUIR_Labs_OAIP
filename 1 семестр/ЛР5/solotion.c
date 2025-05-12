#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "solution.h"


int input_size(void)                                                            // ������� ���� ���������� ������� � ���������
{
    int size;                                                                   // �������� ������ �������
    do
    {

        if (scanf_s("%d", &size) != 1)
        {
            printf("������\n");
            while (getchar() != '\n');
        }
        else if (size < 1)
        {
            printf("������\n");
            while (getchar() != '\n');
        }
        else if (getchar() != '\n')
        {
            printf("������\n");
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



double** create_matrix(int n, int m)                                            // ������� �������� �������
{
    double** matrix = (double**)malloc(n * sizeof(double*));                    // ������ ��� �����

    for (int i = 0; i < n; i++) 
    {
        *(matrix+i) = (double*)malloc(m * sizeof(double));                        // ������ ��� ��������� ������
    }
    return matrix;
}


void free_matrix(double** matrix, int n)                                        // ������� ������������ ������ �������
{
    for (int i = 0; i < n; i++) 
    {
        free(*(matrix + i));                                                        // ���������� ������ ������
    }
    free(matrix);                                                               // ���������� ������ ����������
}


void input_matrix(double** matrix, int n, int m)                                // ������� ����� ��������� �������
{
    int fill_choice;

    printf("����� �����\n");
    printf("1 - ��������� ����\n");
    printf("2 - ���� ������� �������\n");
    printf("��� �����:");

    do
    {
        if (scanf_s("%d", &fill_choice) != 1)
        {
            printf("������: ������������ ����");
            while (getchar() != '\n');
        }
        else if (fill_choice != 1 && fill_choice != 2)
        {
            printf("������: ������������ ����");
            while (getchar() != '\n');
        }
        else if (getchar() != '\n')
        {
            printf("������: ������������ ����");
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
        printf("������� �������� ������� �������� %dx%d:\n", n, m);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                printf("������� [%d][%d]: ", i, j);
                do
                {

                    if (scanf_s("%lf", (*(matrix + i) + j)) != 1)
                    {
                        printf("������:\n");
                        while (getchar() != '\n');
                    }
                    else if (getchar() != '\n')
                    {
                        printf("������:\n");
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


void print_matrix(double** matrix, int n, int m)                                // ������� ������ �������
{
    printf("�������:\n");
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


void calculate_b(double** matrix, int n, int m, double x, int* b)               // ������� ���������� ������� b
{
    for (int i = 0; i < n; i++) 
    {
        *(b+i) = 1;                                                               // ��������� ��������� �������� ������� �������� ������ ������ �

        for (int j = 0; j < m; j++) 
        {
            if (*(*(matrix+i)+j) > x)                                               // ���� ���� �� ���� ������� ������ x
            {   
                *(b+i) = 0;                                                       // ��������� ������ �������� 0

                break;    
            }
        }
    }
}


void print_b(int* b, int n)                                                 // ������� ������ ������� b
{
    printf("������ b:\n");
    printf("\n");

    for (int i = 0; i < n; i++) 
    {
        printf("%d", *(b+i)); 
    }

    printf("\n");
    printf("\n");
}
