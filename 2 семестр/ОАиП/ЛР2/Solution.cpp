#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "solution.h"


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



// Функция ввода информации о студентах
void inputStudent(Student* student) 
{


    printf("Введите имя студента: ");
    inputString(student->name, MAX_LEN);

    printf("Выберите тип проживания:\n");
    printf("1 - Город\n2 - Область и город\n3 - Район и город\n4 - Район и деревня\n");

    while (!inputInt(&student->type) || student->type < 1 || student->type > 4) 
    {
        printf("Ошибка: выберите корректный тип (1-4): ");
    }

    switch (student->type) 
    {
    case 1:
        printf("Введите улицу: ");
        inputString(student->address.city.street, MAX_LEN);
        printf("Введите номер дома: ");
        inputInt(&student->address.city.house);
        printf("Введите номер квартиры: ");
        inputInt(&student->address.city.apartment);
        break;
    case 2:
        printf("Введите город: ");
        inputString(student->address.regionCity.city, MAX_LEN);
        printf("Введите улицу: ");
        inputString(student->address.regionCity.street, MAX_LEN);
        printf("Введите номер дома: ");
        inputInt(&student->address.regionCity.house);
        printf("Введите номер квартиры: ");
        inputInt(&student->address.regionCity.apartment);
        break;
    case 3:
        printf("Введите область: ");
        inputString(student->address.districtCity.region, MAX_LEN);
        printf("Введите район: ");
        inputString(student->address.districtCity.district, MAX_LEN);
        printf("Введите город: ");
        inputString(student->address.districtCity.city, MAX_LEN);
        printf("Введите улицу: ");
        inputString(student->address.districtCity.street, MAX_LEN);
        printf("Введите номер дома: ");
        inputInt(&student->address.districtCity.house);
        printf("Введите номер квартиры: ");
        inputInt(&student->address.districtCity.apartment);
        break;
    case 4:
        printf("Введите область: ");
        inputString(student->address.village.region, MAX_LEN);
        printf("Введите район: ");
        inputString(student->address.village.district, MAX_LEN);
        printf("Введите деревню: ");
        inputString(student->address.village.village, MAX_LEN);
        printf("Введите номер дома: ");
        inputInt(&student->address.village.house);
        break;
    }
}


// Функция вывода информации о студентах
void printTable(Student* students, int count) 
{
    printf("\n-----------------------------------------------------------------------------------------------------------------------\n");
    printf("| №  | Имя               | Область           | Район             | Город/Деревня      | Улица             | Дом  | Кв.  |\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) 
    {
        char region[MAX_LEN] = "-";
        char district[MAX_LEN] = "-";
        char cityOrVillage[MAX_LEN] = "-";
        char street[MAX_LEN] = "-";
        int house = 0;
        int apartment = 0;
        char apartmentStr[5];

        switch ((*(students + i)).type)
        {
        case 1:
            strcpy_s(cityOrVillage, MAX_LEN, "Минск");
            strcpy_s(street, MAX_LEN, (*(students + i)).address.city.street);
            house = (*(students + i)).address.city.house;
            apartment = (*(students + i)).address.city.apartment;
            break;
        case 2:
            strcpy_s(region, MAX_LEN, "Минская");
            strcpy_s(cityOrVillage, MAX_LEN, (*(students + i)).address.regionCity.city);
            strcpy_s(street, MAX_LEN, (*(students + i)).address.regionCity.street);
            house = (*(students + i)).address.regionCity.house;
            apartment = (*(students + i)).address.regionCity.apartment;
            break;
        case 3:
            strcpy_s(region, MAX_LEN, (*(students + i)).address.districtCity.region);
            strcpy_s(district, MAX_LEN, (*(students + i)).address.districtCity.district);
            strcpy_s(cityOrVillage, MAX_LEN, (*(students + i)).address.districtCity.city);
            strcpy_s(street, MAX_LEN, (*(students + i)).address.districtCity.street);
            house = (*(students + i)).address.districtCity.house;
            apartment = (*(students + i)).address.districtCity.apartment;
            break;
        case 4:
            strcpy_s(region, MAX_LEN, (*(students + i)).address.village.region);
            strcpy_s(district, MAX_LEN, (*(students + i)).address.village.district);
            strcpy_s(cityOrVillage, MAX_LEN, (*(students + i)).address.village.village);
            house = (*(students + i)).address.village.house;
            break;
        }

        if ((*(students + i)).type == 4)
        {
            strcpy_s(apartmentStr, sizeof(apartmentStr), "-");
        }
        else 
        {
            snprintf(apartmentStr, sizeof(apartmentStr), "%d", apartment);
        }

        printf("| %-4d | %-17s | %-16s | %-17s | %-18s | %-16s | %-4d | %-4s |\n",
            i + 1, (*(students + i)).name, region, district, cityOrVillage, street, house, apartmentStr);
    }
    printf("--------------------------------------------------------------------------------------------------------------------\n");
}


// Функция для проверки, соответствует ли студент заданному типу проживания
int matchStudentType(const Student* student, int type) 
{
    return student->type == type;
}

// Функция поиска студентов по заданному параметру 
int searchStudentsByType(const Student* students, int count, int type)
{

    
    int found = 0;
    printf("\nРезультаты поиска для типа %d:\n", type);
    printf("-------------------------------------------------------------------------------------\n");
    printf("| №  | Имя               | Адрес                                                  |  \n");
    printf("-------------------------------------------------------------------------------------\n");

 


        for (int i = 0; i < count; i++)
        {
            if ((*(students + i)).type == type)
            {
                found = 1;
                printf("| %-4d | %-17s | ", i + 1, (*(students + i)).name);

                switch (type)
                {
                case 1:
                    printf("Город: Минск, Улица: %s, Дом: %d, Кв.: %d |\n",
                        (*(students + i)).address.city.street, (*(students + i)).address.city.house, (*(students + i)).address.city.apartment);
                    break;
                case 2:
                    printf("Город: %s, Улица: %s, Дом: %d, Кв.: %d |\n",
                        (*(students + i)).address.regionCity.city, (*(students + i)).address.regionCity.street,
                        (*(students + i)).address.regionCity.house, (*(students + i)).address.regionCity.apartment);
                    break;
                case 3:
                    printf("Область: %s, Район: %s, Город: %s, Улица: %s, Дом: %d, Кв.: %d |\n",
                        (*(students + i)).address.districtCity.region, (*(students + i)).address.districtCity.district,
                        (*(students + i)).address.districtCity.city, (*(students + i)).address.districtCity.street,
                        (*(students + i)).address.districtCity.house, (*(students + i)).address.districtCity.apartment);
                    break;
                case 4:
                    printf("Область: %s, Район: %s, Деревня: %s, Дом: %d |\n",
                        (*(students + i)).address.village.region, (*(students + i)).address.village.district,
                        (*(students + i)).address.village.village, (*(students + i)).address.village.house);
                    break;
                }
            }
        }

        if (!found)
        {
            printf("| Нет студентов с таким типом проживания |\n");
        }

        printf("-------------------------------------------------------------------------------------\n");
        return found;
}


// Функция динамического выделения памяти
Student* allocateStudents(int count) 
{
    return (Student*)malloc(count * sizeof(Student));
}


// Функция очистки памяти 
void freeStudents(Student* students, int count) 
{
    free(students);
}
