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
        printf("������� ���������� ���������: ");
        while (!inputInt(&n))
        {
            printf("������: ������� ���������� ����� ���������: ");
        }

        Student* students = allocateStudents(n);                        // ��������� ������

        for (int i = 0; i < n; i++)
        {
            printf("\n���� ������ ��� �������� %d:\n", i + 1);
            inputStudent(&(*(students + i)));
        }

        printTable(students, n);

        // ��������� �� �������
        int (*SearchFunction)(const Student*, int, int) = searchStudentsByType;

        int searchType;
        printf("������� ��� ���������� ��� ������ (1-4): ");
        while (!inputInt(&searchType) || searchType < 1 || searchType > 4)
        {
            printf("������: �������� ���������� ��� (1-4): ");
        }

        // ����� ������� ����� ��������� 
        SearchFunction(students, n, searchType);

        freeStudents(students, n);

        printf("\n������� 1, ����� ����������, ��� ����� ������ ������, ����� �����: ");
        scanf_s("%d", &choice);
        if (choice == 1)
        {
            printf("������ ���������� ������\n");
        }
        else
        {
            printf("���������� ������ ���������\n");
        }

        while (getchar() != '\n');

        printf("\n");

    } while (choice == 1);

    return 0;
}
