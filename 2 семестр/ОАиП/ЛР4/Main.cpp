#include <stdio.h>
#include <locale.h>
#include <Windows.h>
#include "solution.h"

int main() 
{
    setlocale(LC_ALL, "RUS");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    initializeParkings(); // ������������� �������

    int choice;
    while (1) 
    {
        printf("\n����:\n");
        printf("1. ������� ��������\n");
        printf("2. ������������ ������\n");
        printf("3. ������� ������\n");
        printf("4. �������� ��������\n");
        printf("5. ������ ��������\n");
        printf("6. ������� ��������\n");
        printf("0. �����\n");
        printf("��������: ");

        if (scanf_s("%d", &choice) != 1) 
        {
            printf("������������ ����\n");
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
            totalSpace = getPositiveInt("������� ���������� ���� : ", MIN_TOTALSPACE, MAX_TOTALSPACE);
            createNewParking(totalSpace);
            break;
        case 2:
            id = getPositiveInt("������� ����� ��������: ", MIN_TOTALSPACE, MAX_TOTALSPACE);
            inputCarPlate(plate);
            parkCar(id, plate);
            break;
        case 3:
            id = getPositiveInt("������� ����� ��������: ", MIN_TOTALSPACE, MAX_TOTALSPACE);       
            inputCarPlate(plate);
            removeCar(id, plate);
            break;
        case 4:
            id = getPositiveInt("������� ����� ��������: ", MIN_TOTALSPACE, MAX_TOTALSPACE);       
            displayParking(id);
            break;
        case 5:
            listAllParkings();
            break;
        case 6:
            id = getPositiveInt("������� ����� ��������: ", MIN_TOTALSPACE, MAX_TOTALSPACE);
            showWaitlist(id);
            break;
        case 0:
            freeMemory();
            return 0;
        default:
            printf("�������� �����\n");
        }
    }
}
