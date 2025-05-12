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
            printf(stderr, "������ ��� ��������� ������ ��� �����.\n");
            while (getchar() != '\n');
        }
     
       
            // �������� ������� ������
            if (!validate_input(input))
            {
                printf(stderr, "������: ������ ������ ��������� ���� �� ���� ���������.\n");
                //free_memory(input);
                return 1;

            }
           

        // ����� ������� ��� ������ ������� � ������� ���������
        const char* first_colon = find_first_colon(input);
        const char* second_colon = find_second_colon(first_colon);

        // ����� ������� ��� ���������� �������� ����� �����������
        char* result = extract_colons(first_colon, second_colon);

        if (result) 
        {
            printf("����������� ���������: %s\n", result);
        }
        else 
        {
            if (second_colon) 
            {
                printf("����� ����������� ������ ���.\n");
            }
            else 
            {
                printf("����� ������� ��������� ������ ���.\n");
            }
        }

        // ������� ������
        free_memory(input);
        free_memory(result);

        printf("������� 1, ����� ���������� ��� ����� ������ ������, ����� �����: ");
        scanf_s("%d", &choice);

        while (getchar() != '\n');

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

	} while (choice == 1);

	return 0;
}

