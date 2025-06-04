#include "solution.h" 

int isValidColor(const char* color)                                         // Функция проверки корректности цвета
{
    return (strcmp(color, "red") == 0 || strcmp(color, "yellow") == 0 || strcmp(color, "green") == 0 || strcmp(color, "blue") == 0);
}


int isValidMaterial(const char* material)                                   // Функция проверки корректности материала
{
    return (strcmp(material, "wood") == 0 || strcmp(material, "metal") == 0 || strcmp(material, "cardboard") == 0);
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
            printf("Ошибка! Число должно быть больше 0.\n");
        }
        else
        {
            printf("Ошибка! Введите корректное число.\n");
        }
        while (getchar() != '\n');
    }
}

void menu(Cube** cubes, int* count) 
{
    int choice;
    int loaded = 0; 

    do 
    {
        printf("\n");
        printf("1. Загрузить данные из файла\n");
        printf("2. Ввести новые данные\n");
        printf("3. Сохранить данные в файл\n");
        printf("4. Показать статистику\n");
        printf("5. Выход\n");
        printf("Выберите действие: ");

        if (scanf_s("%d", &choice) != 1) 
        {
            printf("Ошибка ввода!\n");
            while (getchar() != '\n'); 
            continue;
        }

        while (getchar() != '\n'); 

        switch (choice)
        {

        case 1: 

            if (*cubes != NULL) 
            {
                free(*cubes);
                *cubes = NULL;
            }

            *cubes = loadCubesFromFile(count);
            if (*cubes != NULL) 
            {
                loaded = 1;
                printf("Данные успешно загружены. Кубиков: %d\n", *count);
            }
            break;

        case 2: 

            if (*cubes != NULL) 
            {
                free(*cubes);
                *cubes = NULL;
            }

            printf("Введите количество кубиков: ");
            if (scanf_s("%d", count) != 1 || *count <= 0) 
            {
                printf("Некорректный ввод!\n");
                while (getchar() != '\n');
                break;
            }
            while (getchar() != '\n');

            *cubes = (Cube*)malloc(*count * sizeof(Cube));
            if (*cubes == NULL) 
            {
                perror("Ошибка выделения памяти");
                *count = 0;
                break;
            }

            inputCubes(*cubes, *count);
            loaded = 1;
            break;

        case 3: 

            if (!loaded || *cubes == NULL) 
            {
                printf("Нет данных для сохранения!\n");
                break;
            }

            if (saveCubesToFile(*cubes, *count)) 
            {
                printf("Данные успешно сохранены в %s\n", DATA_FILE);
            }
            break;

        case 4: 

            if (!loaded || *cubes == NULL) 
            {
                printf("Нет данных для отображения!\n");
                break;
            }

            printf("\nСтатистика\n");
            printColorCounts(*cubes, *count);
            printWoodenCubesByEdge(*cubes, *count);
            printMetalCubesByEdge(*cubes, *count);
            break;

        case 5: 

            printf("Завершение работы программы...\n");
            break;

        default:

            printf("Неверный выбор. Попробуйте снова.\n");
        }

    } while (choice != 5);
}

int againf()
{
    int again, x;
    printf("Введимте 1, чтобы продолжить или любоой другой символ, чтобы выйти: ");
    while (1)
    {
        x = scanf_s("%d", &again);
        if (x != 1 || again != 1)
        {
            printf("\n");
            printf("Завершение работы программы");
            again = 0;
            return again;
        }
        else
        {
            printf("Повтор программы");
            printf("\n");
            break;
        }

    }
    return again;
}