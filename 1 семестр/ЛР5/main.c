#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "solution.h"

int main() 
{
    int choice;

    do
    {
        double** matrix;                                    // ��������� �������
        int* b;                                             // ������ b
        int n;
        int x;

        setlocale(LC_ALL, "RUS");

        
        printf("������� ����������� ����� n: ");            // ���� n
        n = input_size();

        
        printf("������� �������������� ����� x: ");         // ���� x
        x = input_size();

        
        matrix = create_matrix(n, 2 * n);                   // �������� ������� �������� n x 2n

        
        input_matrix(matrix, n, 2 * n);                     // ���� �������

        
        print_matrix(matrix, n, 2 * n);                     // ����� �������

        
        b = (int*)malloc(n * sizeof(int));                  // �������� ������ ��� ������ b

        
        calculate_b(matrix, n, 2 * n, x, b);                 // ��������� ������ b

        
        print_b(b, n);                                       // ����� ������� b

       
        free(b);                                             // ���������� ������
        free_matrix(matrix, n);

        printf("������� 1, ����� ��������� ��� ����� ������ ������, ����� �����: ");
        scanf_s("%d", &choice);

        printf("\n");

        if (choice == 1)
        {
            printf("������ ���������� ������\n");
        }
        else
        {
            printf("���������� ������ ���������\n");
        }

        printf("\n");

    }
    while (choice == 1);

    return 0;
}
