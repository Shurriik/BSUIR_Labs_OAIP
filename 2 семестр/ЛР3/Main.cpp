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

        printf("������� �������������� ���������: ");
        if (fgets(expression, M, stdin) == NULL)
        {
            printf("������ ��� �����.\n");
            return 1;
        }

        expression[strcspn(expression, "\n")] = '\0';

        checkSyntaxError(expression);
      
        checkBrackets(expression); // �������� ���������

        printf("������� 1, ����� ���������� ��� ����� ������ ������, ����� ��������� ���������: ");
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
    } while (choice == 1);

    return 0;
}

