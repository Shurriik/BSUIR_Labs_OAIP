#include "solution.h" 

int inputInt(int* value)
{
    char buffer[100];

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

int isValidColor(const char* color)                                         // ������� �������� ������������ �����
{
    return (strcmp(color, "red") == 0 || strcmp(color, "yellow") == 0 || strcmp(color, "green") == 0 || strcmp(color, "blue") == 0);
}


int isValidMaterial(const char* material)                                   // ������� �������� ������������ ���������
{
    return (strcmp(material, "wood") == 0 || strcmp(material, "metal") == 0 || strcmp(material, "cardboard") == 0);
}


void Input(char* buffer, int size)                                                  // ������� ��� ����� ������ � ������������ �� �����
{
    if (fgets(buffer, size, stdin))
    {
        unsigned long int len = strlen(buffer);                                     // ����� ������
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }
        else
        {
            while (getchar() != '\n');
        }
    }
}

void InputNumber(int* number, const char* prompt)
{

    while (1)
    {
        printf("%s", prompt);
        if (scanf_s("%d", number) == 1)
        {
            if (*number > 0)
            {
                break;
            }
            printf("������! ����� ������ ���� ������ 0.\n");
        }
        else
        {
            printf("������! ������� ���������� �����.\n");
        }
        while (getchar() != '\n');
    }
}


void menu()
{
    Cube* cubes = NULL;
    int count = 0;
    int choice;
    int loaded = 0;

    do
    {
        printf("\n");
        printf("1. ��������� ������ �� �����\n");
        printf("2. ������ ����� ������\n");
        printf("3. ��������� ������ � ����\n");
        printf("4. �������� ����������\n");
        printf("5. �����\n");
        printf("�������� ��������: ");

        while (!inputInt(&choice) || choice < 1 || choice > 5)
        {
            printf("������: ������� ����� �� 1 �� 5: ");
        }

        switch (choice)
        {

        case 1:

            if (cubes != NULL)
            {
                free(cubes);
                cubes = NULL;
            }

            cubes = loadCubesFromBinFile(&count);
            if (cubes != NULL)
            {
                loaded = 1;
                printf("������ ������� ���������. �������: %d\n", count);
            }
            break;

        case 2:

            if (cubes != NULL)
            {
                free(cubes);
                cubes = NULL;
            }

            printf("������� ���������� �������: ");
            if (scanf_s("%d", &count) != 1 || count <= 0)
            {
                printf("������������ ����!\n");
                while (getchar() != '\n');
                break;
            }
            while (getchar() != '\n');

            cubes = (Cube*)malloc(count * sizeof(Cube));
            if (cubes == NULL)
            {
                perror("������ ��������� ������");
                count = 0;
                break;
            }

            inputCubes(cubes, count);
            loaded = 1;
            break;

        case 3:

            if (!loaded || cubes == NULL)
            {
                printf("��� ������ ��� ����������!\n");
                break;
            }

            if (saveCubesToBinFile(cubes, count))
            {
                printf("������ ������� ��������� � %s\n", DATA_FILE);
            }
            break;

        case 4:

            if (!loaded || cubes == NULL)
            {
                printf("��� ������ ��� �����������!\n");
                break;
            }

            printf("\n����������\n");
            printColorCounts(cubes, count);
            printWoodenCubesByEdge(cubes, count);
            printMetalCubesByEdge(cubes, count);
            break;

        case 5:

            printf("���������� ������ ���������...\n");
            break;

        default:

            printf("�������� �����. ���������� �����.\n");
        }

    } while (choice != 5);
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