#include "solution.h" 



Cube* allocateCubes(int count)                                              // ������� ��� ��������� ������������ ������ ��� ������ �������
{
    if (count <= 0)                                                         // �������� �� ��������� �����
    {
        return NULL;
    }


    Cube* cubes = (Cube*)malloc(count * sizeof(Cube));                      // ��������� ������ ��� ������ �������� 

    if (!cubes)
    {
        printf("������ ��� ��������� ������!\n");
        exit(1);
    }
    return cubes;
}



void inputCubes(Cube* cubes, int count)                                             // ������� ��� ����� ���������� � �����
{
    for (int i = 0; i < count; i++)
    {

        InputNumber(&(*(cubes + i)).edge, "������� ����� ����� ��� ����: ");
        while (getchar() != '\n');


        do
        {
            printf("\n������� ���� ���� (red, yellow, green, blue) %d: ", i + 1);
            Input((*(cubes + i)).color, sizeof((*(cubes + i)).color));

            if (!isValidColor((*(cubes + i)).color))
            {
                printf("������������ ����!\n");
            }
            else
            {
                break;
            }
        } while (1);

        do
        {
            printf("\n������� �������� ���� (wood, metal, cardboard) %d: ", i + 1);
            Input((*(cubes + i)).material, sizeof((*(cubes + i)).material));
            if (!isValidMaterial((*(cubes + i)).material))
            {
                printf("������������ ����!\n");
            }
            else
            {
                break;
            }
        } while (1);
        printf("\n");
    }
}


void printColorCounts(Cube* cubes, int count)                                       // ������� ��� �������� ���������� ������� ������� ����� � �� ���������� ������
{
    int red = 0, yellow = 0, green = 0, blue = 0;
    int redVolume = 0, yellowVolume = 0, greenVolume = 0, blueVolume = 0;

    for (int i = 0; i < count; i++)
    {
        int volume = (*(cubes + i)).edge * (*(cubes + i)).edge * (*(cubes + i)).edge;                 // ���������� ����� ����

        if (strcmp((*(cubes + i)).color, "red") == 0)
        {
            red++; redVolume += volume;
        }
        else if (strcmp((*(cubes + i)).color, "yellow") == 0)
        {
            yellow++; yellowVolume += volume;
        }
        else if (strcmp((*(cubes + i)).color, "green") == 0)
        {
            green++; greenVolume += volume;
        }
        else if (strcmp((*(cubes + i)).color, "blue") == 0)
        {
            blue++; blueVolume += volume;
        }
    }


    printf("+------------+------------+------------+\n");
    printf("|   ����     | ���������� |   �����    |\n");
    printf("+------------+------------+------------+\n");
    printf("| �������    | %-10d | %-10d |\n", red, redVolume);
    printf("+------------+------------+------------+\n");
    printf("| Ƹ����     | %-10d | %-10d |\n", yellow, yellowVolume);
    printf("+------------+------------+------------+\n");
    printf("| ������    | %-10d | %-10d |\n", green, greenVolume);
    printf("+------------+------------+------------+\n");
    printf("| �����      | %-10d | %-10d |\n", blue, blueVolume);
    printf("+------------+------------+------------+\n");
}


void printWoodenCubesByEdge(Cube* cubes, int count)                                 // ������� ��� ������ ���������� ���������� ������� ��������� �������
{
    int n;
    InputNumber(&n, "\n������� ������ ������ n ��� ���������� �������: ");

    while (getchar() != '\n');

    int woodenCount = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcmp((*(cubes + i)).material, "wood") == 0 && (*(cubes + i)).edge == n)
        {
            woodenCount++;
        }
    }
    printf("\n���������� ������ � ������ %d: %d\n", n, woodenCount);
}


void printMetalCubesByEdge(Cube* cubes, int count)                                   // ������� ��� ������ ���������� ������������� ����� � ������ ������ ��������� �������
{
    int m;
    InputNumber(&m, "\n������� ����������� ������ ����� m ��� ������������� �������: ");

    while (getchar() != '\n');

    int metalCount = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcmp((*(cubes + i)).material, "metal") == 0 && (*(cubes + i)).edge > m)
        {
            metalCount++;
        }
    }
    printf("\n������������� ������ � ������ ����� %d: %d\n", m, metalCount);
}

void freeCubes(Cube* cubes)                                                 // ������� ��� ������������ ������
{
    if (cubes)
    {
        free(cubes);
    }
}

// ���������� � �������� ����
int saveCubesToBinFile(const Cube* cubes, int count)
{
    FILE* file = NULL;
    if (fopen_s(&file, DATA_FILE, "wb") != 0 || file == NULL)
    {
        perror("������ �������� ����� ��� ������");
        return 0;
    }

    // ������� ���������� ���������� �������
    if (fwrite(&count, sizeof(int), 1, file) != 1)
    {
        perror("������ ������ ���������� � ����");
        fclose(file);
        return 0;
    }

    // ����� ���������� ���� ������
    if (fwrite(cubes, sizeof(Cube), count, file) != count)
    {
        perror("������ ������ ������� � ����");
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}

// �������� �� ��������� �����
Cube* loadCubesFromBinFile(int* count)
{
    FILE* file = NULL;

    if (fopen_s(&file, DATA_FILE, "rb") != 0 || file == NULL)
    {
        perror("������ �������� �����");
        return NULL;
    }

    // ������� ������ ����������
    if (fread(count, sizeof(int), 1, file) != 1 || *count <= 0)
    {
        printf("������: ���� ���� ��� �������� ������������ ������\n");
        fclose(file);
        return NULL;
    }

    Cube* cubes = (Cube*)malloc(*count * sizeof(Cube));
    if (cubes == NULL)
    {
        perror("������ ��������� ������");
        fclose(file);
        return NULL;
    }

    // ������ ������� �����
    if (fread(cubes, sizeof(Cube), *count, file) != *count)
    {
        printf("������ ������ ������� �� �����\n");
        free(cubes);
        fclose(file);
        return NULL;
    }

    if (fclose(file) != 0)
    {
        perror("������ �������� �����");
        free(cubes);
        return NULL;
    }

    printf("������� ��������� %d ������� �� %s\n", *count, DATA_FILE);
    return cubes;
}