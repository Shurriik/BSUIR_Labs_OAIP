#include "solution.h" 

const char* filename = "cubes.txt";

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
        int volume = (*(cubes + i)).edge * (*(cubes + i)).edge * (*(cubes + i)).edge;                 // Вычисление объем куба

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

int saveCubesToFile(const Cube* cubes, int count) 
{
    FILE* file = NULL;
    if (fopen_s(&file, DATA_FILE, "w") != 0 || file == NULL) 
    {
        perror("Ошибка открытия файла для записи");
        return 0; 
    }

    fprintf(file, "%d\n", count);
    for (int i = 0; i < count; i++) 
    {
        if (fprintf(file, "%d %s %s\n", (*(cubes + i)).edge, (*(cubes + i)).color, (*(cubes + i)).material) < 0) {
            perror("Ошибка записи в файл");
            fclose(file);
            return 0;
        }
    }

    return 1; 
}

Cube* loadCubesFromFile(int* count) 
{
    FILE* file = NULL;


    if (fopen_s(&file, DATA_FILE, "r") != 0 || file == NULL) 
    {
        perror("Ошибка открытия файла");
        return NULL;
    }


    if (fscanf_s(file, "%d", count) != 1 || *count <= 0) 
    {
        printf("Ошибка: файл пуст или содержит некорректные значения\n");
        fclose(file);
        return NULL;
    }


    while (fgetc(file) != '\n');


    Cube* cubes = (Cube*)malloc(*count * sizeof(Cube));
    if (cubes == NULL) 
    {
        perror("Ошибка выделения памяти");
        fclose(file);
        return NULL;
    }


    for (int i = 0; i < *count; i++) 
    {
        if (fscanf_s(file, "%d %9s %9s", &(*(cubes + i)).edge, (*(cubes + i)).color, (unsigned)_countof((*(cubes + i)).color),
            (*(cubes + i)).material, (unsigned)_countof((*(cubes + i)).material)) != 3) 
        {
            printf("Ошибка чтения данных кубика %d!\n", i + 1);
            free(cubes);
            fclose(file);
            return NULL;
        }
    }


    if (fclose(file) != 0)
    {
        perror("Ошибка закрытия файла");
        free(cubes);
        return NULL;
    }

    printf("Успешно загружено %d кубиков из %s\n", *count, DATA_FILE);
    return cubes;
}

