#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "solution.h"
#include <stdlib.h>



int isPositiveInteger(const char* str)      // �������� �� ������������� �����
{
    if (!str || *str == '\0') return 0;

    if ((*(str + 0)) == '-') return 0;

    for (int i = 0; (*(str + i)); i++)
    {
        if (!isdigit((*(str + i)))) return 0;
    }

    return 1;
}


int getPositiveInt(const char* prompt, int min, int max)        // ���� ����� � �������� ��������� 
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

                    printf("������: ����� ������ ���� �� %d �� %d.\n", min, max);
                }
            }
            else
            {

                printf("������: ������� ������������� ����� �����.\n");
            }
        }
    }
}


// ���� ������������
void menu()
{
    int choice;
    do
    {

        puts("\n����");
        puts("1 - ������� ������");
        puts("2 - �������� ����");
        puts("3 - ����� ������ (������������)");
        puts("4 - ������� ����");
        puts("5 - ����� �������");
        puts("6 - ����� ��������");
        puts("7 - ������� ������");
        puts("8 - ��������� ���������");
        printf("�������� �����.");
        
        choice = getPositiveInt("��� �����: ", MIN_INPUT, MAX_INPUT);


        switch (choice)
        {
        case 1: createTree(); break;

        case 2: addNode(); break;

        case 3: inOrderTraversal(root); break;

        case 4: deleteNode(); break;

        case 5:
        {
            Node* min = findMin(root);
            if (min) printf("�������: %s (%d)\n", min->inf, min->n);
            else puts("������ ������");
            break;
        }

        case 6:
        {
            Node* max = findMax(root);
            if (max) printf("��������: %s (%d)\n", max->inf, max->n);
            else puts("������ ������");
            break;
        }

        case 7: printTree(root, 0); break;

        case 8: return;

        default: puts("�������� �����!");
        }
    } while (1);
}

int againf()
{
    int again, x;
    printf("�������� 1, ����� ���������� ��� ������ ������ ������, ����� �����: ");
    while (1)
    {
        x = scanf_s("%d", &again);
        if (x != 1 || again != 1)
        {
            printf("\n");
            printf("���������� ������ ���������");
            again = 0;
            return again;
        }
        else
        {
            printf("������ ���������");
            printf("\n");
            break;
        }

    }
    return again;

}