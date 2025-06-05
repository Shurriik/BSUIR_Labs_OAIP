#include <stdio.h>
#include <locale.h>
#include <Windows.h>
#include "solution.h"

int main() 
{
    setlocale(LC_ALL, "RUS");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    initializeParkings(); // Инициализация системы

    int choice;
    while (1) 
    {
        printf("\nМеню:\n");
        printf("1. Создать парковку\n");
        printf("2. Припарковать машину\n");
        printf("3. Удалить машину\n");
        printf("4. Показать парковку\n");
        printf("5. Список парковок\n");
        printf("6. Очередь ожидания\n");
        printf("0. Выход\n");
        printf("Выберите: ");

        if (scanf_s("%d", &choice) != 1) 
        {
            printf("Некорректный ввод\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        int totalSpace;
        char plate[MAX_PLATE_LENGTH];
        int id;

        switch (choice) 
        {
        case 1:
            totalSpace = getPositiveInt("Введите количество мест : ", MIN_TOTALSPACE, MAX_TOTALSPACE);
            createNewParking(totalSpace);
            break;
        case 2:
            id = getPositiveInt("Введите номер парковки: ", MIN_TOTALSPACE, MAX_TOTALSPACE);
            inputCarPlate(plate);
            parkCar(id, plate);
            break;
        case 3:
            id = getPositiveInt("Введите номер парковки: ", MIN_TOTALSPACE, MAX_TOTALSPACE);       
            inputCarPlate(plate);
            removeCar(id, plate);
            break;
        case 4:
            id = getPositiveInt("Введите номер парковки: ", MIN_TOTALSPACE, MAX_TOTALSPACE);       
            displayParking(id);
            break;
        case 5:
            listAllParkings();
            break;
        case 6:
            id = getPositiveInt("Введите номер парковки: ", MIN_TOTALSPACE, MAX_TOTALSPACE);
            showWaitlist(id);
            break;
        case 0:
            freeMemory();
            return 0;
        default:
            printf("Неверный выбор\n");
        }
    }
}
