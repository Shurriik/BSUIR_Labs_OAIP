#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include "solution.h" 


int isValidColor(const char* color)                                         // ������� �������� ������������ �����
{
    return (strcmp(color, "red") == 0 || strcmp(color, "yellow") == 0 || strcmp(color, "green") == 0 || strcmp(color, "blue") == 0);
}


int isValidMaterial(const char* material)                                   // ������� �������� ������������ ���������
{
    return (strcmp(material, "wood") == 0 || strcmp(material, "metal") == 0 || strcmp(material, "cardboard") == 0);
}

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

void InputNumber(int* number, const char* prompt )
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
        int volume = (*(cubes+i)).edge * (*(cubes + i)).edge * (*(cubes + i)).edge;                 // ���������� ����� ����

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