#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "solution.h"


// ������� ����� �������� ��������
int inputInt(int* value) 
{
    char buffer[MAX_LEN];

    while (1) 
    {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) 
        {
            printf("������ �����! ���������� �����: ");
            continue;
        }
  
        buffer[strcspn(buffer, "\n")] = '\0';

        // ��������, ��� ���� �������� ������ �����
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

        printf("������: ������� ���������� ������������� �����: ");
    }
}

// ������� ����� ������
int inputString(char* buffer, int size) 
{
    do 
    {
        if (fgets(buffer, size, stdin) == NULL) 
        {
            printf("������ �����! ���������� �����: ");
            continue;
        }

        unsigned long int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') 
        {
            buffer[len - 1] = '\0';
            len--;
        }
        
        int hasLetter = 0, valid = 1;                           // ��������, ��� ���� �������� ������ �����
        for (unsigned long int i = 0; i < len; i++) 
        {
            
            if (((*(buffer + i)) >= 'A' && (*(buffer + i)) <= 'Z') ||
                ((*(buffer + i)) >= 'a' && (*(buffer + i)) <= 'z') ||
                ((*(buffer + i)) >= '�' && (*(buffer + i)) <= '�') ||
                ((*(buffer + i)) >= '�' && (*(buffer + i)) <= '�') ||
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

        printf("������: ������� ���������� ����� ��� ���� � ������������: ");
    } while (1);
}



// ������� ����� ���������� � ���������
void inputStudent(Student* student) 
{


    printf("������� ��� ��������: ");
    inputString(student->name, MAX_LEN);

    printf("�������� ��� ����������:\n");
    printf("1 - �����\n2 - ������� � �����\n3 - ����� � �����\n4 - ����� � �������\n");

    while (!inputInt(&student->type) || student->type < 1 || student->type > 4) 
    {
        printf("������: �������� ���������� ��� (1-4): ");
    }

    switch (student->type) 
    {
    case 1:
        printf("������� �����: ");
        inputString(student->address.city.street, MAX_LEN);
        printf("������� ����� ����: ");
        inputInt(&student->address.city.house);
        printf("������� ����� ��������: ");
        inputInt(&student->address.city.apartment);
        break;
    case 2:
        printf("������� �����: ");
        inputString(student->address.regionCity.city, MAX_LEN);
        printf("������� �����: ");
        inputString(student->address.regionCity.street, MAX_LEN);
        printf("������� ����� ����: ");
        inputInt(&student->address.regionCity.house);
        printf("������� ����� ��������: ");
        inputInt(&student->address.regionCity.apartment);
        break;
    case 3:
        printf("������� �������: ");
        inputString(student->address.districtCity.region, MAX_LEN);
        printf("������� �����: ");
        inputString(student->address.districtCity.district, MAX_LEN);
        printf("������� �����: ");
        inputString(student->address.districtCity.city, MAX_LEN);
        printf("������� �����: ");
        inputString(student->address.districtCity.street, MAX_LEN);
        printf("������� ����� ����: ");
        inputInt(&student->address.districtCity.house);
        printf("������� ����� ��������: ");
        inputInt(&student->address.districtCity.apartment);
        break;
    case 4:
        printf("������� �������: ");
        inputString(student->address.village.region, MAX_LEN);
        printf("������� �����: ");
        inputString(student->address.village.district, MAX_LEN);
        printf("������� �������: ");
        inputString(student->address.village.village, MAX_LEN);
        printf("������� ����� ����: ");
        inputInt(&student->address.village.house);
        break;
    }
}


// ������� ������ ���������� � ���������
void printTable(Student* students, int count) 
{
    printf("\n-----------------------------------------------------------------------------------------------------------------------\n");
    printf("| �  | ���               | �������           | �����             | �����/�������      | �����             | ���  | ��.  |\n");
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
            strcpy_s(cityOrVillage, MAX_LEN, "�����");
            strcpy_s(street, MAX_LEN, (*(students + i)).address.city.street);
            house = (*(students + i)).address.city.house;
            apartment = (*(students + i)).address.city.apartment;
            break;
        case 2:
            strcpy_s(region, MAX_LEN, "�������");
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


// ������� ��� ��������, ������������� �� ������� ��������� ���� ����������
int matchStudentType(const Student* student, int type) 
{
    return student->type == type;
}

// ������� ������ ��������� �� ��������� ��������� 
int searchStudentsByType(const Student* students, int count, int type)
{

    
    int found = 0;
    printf("\n���������� ������ ��� ���� %d:\n", type);
    printf("-------------------------------------------------------------------------------------\n");
    printf("| �  | ���               | �����                                                  |  \n");
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
                    printf("�����: �����, �����: %s, ���: %d, ��.: %d |\n",
                        (*(students + i)).address.city.street, (*(students + i)).address.city.house, (*(students + i)).address.city.apartment);
                    break;
                case 2:
                    printf("�����: %s, �����: %s, ���: %d, ��.: %d |\n",
                        (*(students + i)).address.regionCity.city, (*(students + i)).address.regionCity.street,
                        (*(students + i)).address.regionCity.house, (*(students + i)).address.regionCity.apartment);
                    break;
                case 3:
                    printf("�������: %s, �����: %s, �����: %s, �����: %s, ���: %d, ��.: %d |\n",
                        (*(students + i)).address.districtCity.region, (*(students + i)).address.districtCity.district,
                        (*(students + i)).address.districtCity.city, (*(students + i)).address.districtCity.street,
                        (*(students + i)).address.districtCity.house, (*(students + i)).address.districtCity.apartment);
                    break;
                case 4:
                    printf("�������: %s, �����: %s, �������: %s, ���: %d |\n",
                        (*(students + i)).address.village.region, (*(students + i)).address.village.district,
                        (*(students + i)).address.village.village, (*(students + i)).address.village.house);
                    break;
                }
            }
        }

        if (!found)
        {
            printf("| ��� ��������� � ����� ����� ���������� |\n");
        }

        printf("-------------------------------------------------------------------------------------\n");
        return found;
}


// ������� ������������� ��������� ������
Student* allocateStudents(int count) 
{
    return (Student*)malloc(count * sizeof(Student));
}


// ������� ������� ������ 
void freeStudents(Student* students, int count) 
{
    free(students);
}
