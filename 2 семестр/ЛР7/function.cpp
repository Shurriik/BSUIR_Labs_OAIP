#include "solution.h"

const char* filename = "data.txt";
// Функция ввода числовых значений
int inputInt(int* value)
{
    char buffer[MAX_LEN];

    while (1)
    {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            printf("Ошибка ввода! Попробуйте снова: ");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        // Проверка, что ввод содержит только цифры
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

        printf("Ошибка: введите корректное положительное число: ");
    }
}

// Функция ввода строки
int inputString(char* buffer, int size)
{
    do
    {
        if (fgets(buffer, size, stdin) == NULL)
        {
            printf("Ошибка ввода! Попробуйте снова: ");
            continue;
        }

        unsigned long int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
            len--;
        }

        int hasLetter = 0, valid = 1;                           // Провкрка, что ввод содержит только буквы
        for (unsigned long int i = 0; i < len; i++)
        {

            if (((*(buffer + i)) >= 'A' && (*(buffer + i)) <= 'Z') ||
                ((*(buffer + i)) >= 'a' && (*(buffer + i)) <= 'z') ||
                ((*(buffer + i)) >= 'А' && (*(buffer + i)) <= 'Я') ||
                ((*(buffer + i)) >= 'а' && (*(buffer + i)) <= 'я') ||
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

        printf("Ошибка: введите корректные буквы без цифр и спецсимволов: ");
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
        printf("\nМЕНЮ:\n");
        printf("1. Ввести информацию о студентах\n");
        printf("2. Добавить студента\n");
        printf("3. Поиск студентов по типу проживания\n");
        printf("4. Сохранить информацию в файл\n");
        printf("5. Загрузить информацию из файла\n");
        printf("6. Выход\n");
        printf("Выберите пункт: ");

        while (!inputInt(&choice) || choice < 1 || choice > 6)
        {
            printf("Ошибка: введите число от 1 до 5: ");
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

            printf("Введите количество студентов: ");
            while (!inputInt(&n) || n <= 0)
            {
                printf("Ошибка: введите положительное число: ");
            }

            students = allocateStudents(n);

            for (int i = 0; i < n; i++)
            {
                printf("\nВвод данных для студента %d:\n", i + 1);
                inputStudent(&(*(students + i)));
            }

            printTable(students, n);
            break;
        }

        case 2:
        {
            if (students == NULL)
            {
                printf("Нет существующих студентов. Сначала выберите пункт 1 или 4.\n");
                break;
            }

            int addCount = 0;
            printf("Введите количество студентов для добавления: ");
            while (!inputInt(&addCount) || addCount <= 0)
            {
                printf("Ошибка: введите положительное число: ");
            }

            // Реаллокация памяти
            Student* newArray = (Student*)realloc(students, (n + addCount) * sizeof(Student));
            if (!newArray)
            {
                printf("Ошибка перераспределения памяти.\n");
                break;
            }

            students = newArray;

            for (int i = 0; i < addCount; i++)
            {
                printf("\nВвод данных для нового студента %d:\n", n + i + 1);
                inputStudent(&students[n + i]);
            }

            n += addCount;
            printf("Добавление завершено. Обновлённый список студентов:\n");
            printTable(students, n);
            break;
        }

        case 3:
        {
            if (students == NULL || n == 0)
            {
                printf("Нет данных о студентах. Сначала введите информацию.\n");
                break;
            }

            do
            {

              
                int searchType;
                printf("Введите тип проживания для поиска (1-4): ");
                while (!inputInt(&searchType) || searchType < 1 || searchType > 4)
                {
                    printf("Ошибка: выберите корректный тип (1-4): ");
                }


                searchStudentsByType (students, n, searchType);
                printf("\nВведите 1, чтобы повторить, или любой другой символ, чтобы закончить: ");
                scanf_s("%d", &search);
                while (getchar() != '\n');
            } while (search == 1);
            break;
        }

        case 4:
        {
            if (students == NULL || n == 0)
            {
                printf("Нет данных для сохранения. Сначала введите студентов.\n");
                break;
            }

            saveToFile(filename, students, n);
            printf("Данные сохранены в файл '%s'.\n", filename);
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
                printf("Данные успешно загружены из файла.\n");
                printTable(students, n);
            }
            else
            {
                printf("Ошибка загрузки данных из файла.\n");
            }
            break;
        }

        case 6:

            printf("Завершение работы...\n");
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
    while (getchar() != '\n');
    return again;
}