#include "solution.h"

const char* filename = "data.txt";
// ������� ����� �������� ��������
int inputInt(int* value)
{
    char buffer[MAX_LEN];

    while (1)
    {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            printf("������ �����! ���������� �����: ");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        // ��������, ��� ���� �������� ������ �����
        int valid = 1;
        for (unsigned long int i = 0; (*(buffer + i)) != '\0'; i++)
        {
            if ((*(buffer + i)) < '0' || (*(buffer + i)) > '9')
            {
                valid = 0;
                break;
            }
        }

        if (valid)
        {
            *value = atoi(buffer);
            if (*value > 0) return 1;
        }

        printf("������: ������� ���������� ������������� �����: ");
    }
}

// ������� ����� ������
int inputString(char* buffer, int size)
{
    do
    {
        if (fgets(buffer, size, stdin) == NULL)
        {
            printf("������ �����! ���������� �����: ");
            continue;
        }

        unsigned long int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
            len--;
        }

        int hasLetter = 0, valid = 1;                           // ��������, ��� ���� �������� ������ �����
        for (unsigned long int i = 0; i < len; i++)
        {

            if (((*(buffer + i)) >= 'A' && (*(buffer + i)) <= 'Z') ||
                ((*(buffer + i)) >= 'a' && (*(buffer + i)) <= 'z') ||
                ((*(buffer + i)) >= '�' && (*(buffer + i)) <= '�') ||
                ((*(buffer + i)) >= '�' && (*(buffer + i)) <= '�') ||
                ((*(buffer + i)) == ' '))
            {
                if ((*(buffer + i)) != ' ') hasLetter = 1;
            }
            else
            {
                valid = 0;
                break;
            }
        }

        if (valid && hasLetter) return 1;

        printf("������: ������� ���������� ����� ��� ���� � ������������: ");
    } while (1);
}

void menu()
{
    Student* students = NULL;
    int n = 0;
    int choice;
    int search;

    do
    {
        printf("\n����:\n");
        printf("1. ������ ���������� � ���������\n");
        printf("2. �������� ��������\n");
        printf("3. ����� ��������� �� ���� ����������\n");
        printf("4. ��������� ���������� � ����\n");
        printf("5. ��������� ���������� �� �����\n");
        printf("6. �����\n");
        printf("�������� �����: ");

        while (!inputInt(&choice) || choice < 1 || choice > 6)
        {
            printf("������: ������� ����� �� 1 �� 5: ");
        }

        switch (choice)
        {
        case 1:
        {

            if (students != NULL)
            {
                freeStudents(students, n);
                students = NULL;
                n = 0;
            }

            printf("������� ���������� ���������: ");
            while (!inputInt(&n) || n <= 0)
            {
                printf("������: ������� ������������� �����: ");
            }

            students = allocateStudents(n);

            for (int i = 0; i < n; i++)
            {
                printf("\n���� ������ ��� �������� %d:\n", i + 1);
                inputStudent(&(*(students + i)));
            }

            printTable(students, n);
            break;
        }

        case 2:
        {
            if (students == NULL)
            {
                printf("��� ������������ ���������. ������� �������� ����� 1 ��� 4.\n");
                break;
            }

            int addCount = 0;
            printf("������� ���������� ��������� ��� ����������: ");
            while (!inputInt(&addCount) || addCount <= 0)
            {
                printf("������: ������� ������������� �����: ");
            }

            // ����������� ������
            Student* newArray = (Student*)realloc(students, (n + addCount) * sizeof(Student));
            if (!newArray)
            {
                printf("������ ����������������� ������.\n");
                break;
            }

            students = newArray;

            for (int i = 0; i < addCount; i++)
            {
                printf("\n���� ������ ��� ������ �������� %d:\n", n + i + 1);
                inputStudent(&students[n + i]);
            }

            n += addCount;
            printf("���������� ���������. ���������� ������ ���������:\n");
            printTable(students, n);
            break;
        }

        case 3:
        {
            if (students == NULL || n == 0)
            {
                printf("��� ������ � ���������. ������� ������� ����������.\n");
                break;
            }

            do
            {

              
                int searchType;
                printf("������� ��� ���������� ��� ������ (1-4): ");
                while (!inputInt(&searchType) || searchType < 1 || searchType > 4)
                {
                    printf("������: �������� ���������� ��� (1-4): ");
                }


                searchStudentsByType (students, n, searchType);
                printf("\n������� 1, ����� ���������, ��� ����� ������ ������, ����� ���������: ");
                scanf_s("%d", &search);
                while (getchar() != '\n');
            } while (search == 1);
            break;
        }

        case 4:
        {
            if (students == NULL || n == 0)
            {
                printf("��� ������ ��� ����������. ������� ������� ���������.\n");
                break;
            }

            saveToFile(filename, students, n);
            printf("������ ��������� � ���� '%s'.\n", filename);
            break;
        }

        case 5:
        {
            if (students != NULL)
            {
                freeStudents(students, n);
                students = NULL;
                n = 0;
            }

            n = loadFromFile(filename, &students);
            if (n > 0)
            {
                printf("������ ������� ��������� �� �����.\n");
                printTable(students, n);
            }
            else
            {
                printf("������ �������� ������ �� �����.\n");
            }
            break;
        }

        case 6:

            printf("���������� ������...\n");
            break;
        }

    } while (choice != 6);

    if (students != NULL)
    {
        freeStudents(students, n);
    }
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
    while (getchar() != '\n');
    return again;
}