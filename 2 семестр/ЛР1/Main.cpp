#include <stdio.h>
#include <stdlib.h>
#include "solution.h"
#include <locale.h>

int main() 
{
 
    setlocale(LC_ALL, "RUS");
    int choice;

    do
    {

    int numCubes;                                               // Переменная для хранения количества кубиков
    InputNumber(&numCubes, "Введите количество кубиков: ");

    while (getchar() != '\n');

    
    Cube* cubes = allocateCubes(numCubes);                      // Выделение динамической памятя под массив структур Cube
    if (!cubes) 
    {
        printf("Ошибка выделения памяти!\n");
        return 1;  
    }
    printf("\n");

    inputCubes(cubes, numCubes);                                // Ввод данных о кубиках
    printColorCounts(cubes, numCubes);                          // Вывод статистики по цветам кубиков
    printWoodenCubesByEdge(cubes, numCubes);                    // Вывод количества деревянных кубов с заданным ребром n
    printMetalCubesByEdge(cubes, numCubes);                     // Вывод количества металлических кубов с ребром большим m

    freeCubes(cubes);                                           // Освобождение выделенной памяти

    printf("\n");

    printf("Введите 1, чтобы продолжить или любой другой символ, чтобы выйти: ");
    scanf_s("%d", &choice);

    while (getchar() != '\n');

    printf("\n");

    if (choice == 1)
    {
        printf("Повтор выполнения задачи\n");
    }
    else
    {
        printf("Завершение работы программы\n");

    }

    printf("\n");

    }while (choice == 1);

    return 0;  
}