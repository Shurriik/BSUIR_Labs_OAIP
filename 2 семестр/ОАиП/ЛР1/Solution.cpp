#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include "solution.h" 


int isValidColor(const char* color)                                         // Функция проверки корректности цвета
{
    return (strcmp(color, "red") == 0 || strcmp(color, "yellow") == 0 || strcmp(color, "green") == 0 || strcmp(color, "blue") == 0);
}


int isValidMaterial(const char* material)                                   // Функция проверки корректности материала
{
    return (strcmp(material, "wood") == 0 || strcmp(material, "metal") == 0 || strcmp(material, "cardboard") == 0);
}

Cube* allocateCubes(int count)                                              // Функция для выделения динамической памяти под массив кубиков
{
    if (count <= 0)                                                         // Проверка на количесво кубов
    {  
        return NULL;
    }

    
    Cube* cubes = (Cube*)malloc(count * sizeof(Cube));                      // Выделение памяти под массив структур 

    if (!cubes) 
    {  
        printf("Ошибка при выделении памяти!\n");
        exit(1);
    }
    return cubes;  
}


void Input(char* buffer, int size)                                                  // Функция для ввода строки с ограничением по длине
{
    if (fgets(buffer, size, stdin)) 
    {  
        unsigned long int len = strlen(buffer);                                     // Длина строки
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
        printf("Ошибка! Число должно быть больше 0.\n");
    }
    else
    {
        printf("Ошибка! Введите корректное число.\n");
    }
    while (getchar() != '\n'); 
}
}

void inputCubes(Cube* cubes, int count)                                             // Функция для ввода информации о кубах
{   
    for (int i = 0; i < count; i++) 
    {

       InputNumber(&(*(cubes + i)).edge, "Введите длину ребра для куба: ");
       while (getchar() != '\n');


        do 
        {
        printf("\nВведите цвет куба (red, yellow, green, blue) %d: ", i + 1);
        Input((*(cubes + i)).color, sizeof((*(cubes + i)).color));

        if (!isValidColor((*(cubes + i)).color))
        {
            printf("Некорректный ввод!\n");
        }
        else 
        {
            break;
        }
        } while (1);

        do 
        {
        printf("\nВведите материал куба (wood, metal, cardboard) %d: ", i + 1);
        Input((*(cubes + i)).material, sizeof((*(cubes + i)).material));
        if (!isValidMaterial((*(cubes + i)).material))
        {
            printf("Некорректный ввод!\n");
        }
        else 
        {
            break;
        }
        } while (1);
        printf("\n");
    }
}


void printColorCounts(Cube* cubes, int count)                                       // Функция для подсчета количества кубиков каждого цвета и их суммарного объема
{
    int red = 0, yellow = 0, green = 0, blue = 0;
    int redVolume = 0, yellowVolume = 0, greenVolume = 0, blueVolume = 0;

    for (int i = 0; i < count; i++) 
    {
        int volume = (*(cubes+i)).edge * (*(cubes + i)).edge * (*(cubes + i)).edge;                 // Вычисление объем куба

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
    printf("|   Цвет     | Количество |   Объём    |\n");
    printf("+------------+------------+------------+\n");
    printf("| Красный    | %-10d | %-10d |\n", red, redVolume);
    printf("+------------+------------+------------+\n");
    printf("| Жёлтый     | %-10d | %-10d |\n", yellow, yellowVolume);
    printf("+------------+------------+------------+\n");
    printf("| Зелёный    | %-10d | %-10d |\n", green, greenVolume);
    printf("+------------+------------+------------+\n");
    printf("| Синий      | %-10d | %-10d |\n", blue, blueVolume);
    printf("+------------+------------+------------+\n");
}


void printWoodenCubesByEdge(Cube* cubes, int count)                                 // Функция для вывода количества деревянных кубиков заданного размера
{
    int n;
    InputNumber(&n, "\nВведите размер разбра n для деревянных кубиков: ");

    while (getchar() != '\n');

    int woodenCount = 0;
    for (int i = 0; i < count; i++) 
    {
        if (strcmp((*(cubes + i)).material, "wood") == 0 && (*(cubes + i)).edge == n)
        {
            woodenCount++;
        }
    }
    printf("\nДеревянные кубики с ребром %d: %d\n", n, woodenCount);
}


void printMetalCubesByEdge(Cube* cubes, int count)                                   // Функция для вывода количества металлических кубов с ребром больше заданного размера
{
    int m;
    InputNumber(&m, "\nВведите минимальный размер ребра m для металлических кубиков: ");
    
    while (getchar() != '\n');

    int metalCount = 0;
    for (int i = 0; i < count; i++) 
    {
        if (strcmp((*(cubes + i)).material, "metal") == 0 && (*(cubes + i)).edge > m)
        {
            metalCount++;
        }
    }
    printf("\nМеталлические кубики с ребром более %d: %d\n", m, metalCount);
}

void freeCubes(Cube* cubes)                                                 // Функция для освобождения памяти
{
    if (cubes) 
    {  
        free(cubes);  
    }
}