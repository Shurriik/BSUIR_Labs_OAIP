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

    int numCubes;                                               // ���������� ��� �������� ���������� �������
    InputNumber(&numCubes, "������� ���������� �������: ");

    while (getchar() != '\n');

    
    Cube* cubes = allocateCubes(numCubes);                      // ��������� ������������ ������ ��� ������ �������� Cube
    if (!cubes) 
    {
        printf("������ ��������� ������!\n");
        return 1;  
    }
    printf("\n");

    inputCubes(cubes, numCubes);                                // ���� ������ � �������
    printColorCounts(cubes, numCubes);                          // ����� ���������� �� ������ �������
    printWoodenCubesByEdge(cubes, numCubes);                    // ����� ���������� ���������� ����� � �������� ������ n
    printMetalCubesByEdge(cubes, numCubes);                     // ����� ���������� ������������� ����� � ������ ������� m

    freeCubes(cubes);                                           // ������������ ���������� ������

    printf("\n");

    printf("������� 1, ����� ���������� ��� ����� ������ ������, ����� �����: ");
    scanf_s("%d", &choice);

    while (getchar() != '\n');

    printf("\n");

    if (choice == 1)
    {
        printf("������ ���������� ������\n");
    }
    else
    {
        printf("���������� ������ ���������\n");

    }

    printf("\n");

    }while (choice == 1);

    return 0;  
}