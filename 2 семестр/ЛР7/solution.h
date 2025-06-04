#ifndef SOLUTION_H
#define SOLUTION_H

#define MAX_LEN 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <Windows.h>



// ��������� ��� �������� ������ � ������
typedef struct CityAddress
{
    char city[MAX_LEN];             // �������� ������
    char street[MAX_LEN];           // �������� �����
    int house;                      // ����� ����
    int apartment;                  // ����� ��������
};

// ��������� ��� �������� ������ � ������� �������
typedef struct RegionCityAddress
{
    char region[MAX_LEN];          // �������� �������
    char city[MAX_LEN];            // �������� ������
    char street[MAX_LEN];          // �������� �����
    int house;                     // ����� ����
    int apartment;                 // ����� ��������
};

// ��������� ��� �������� ������ � ������� �����
typedef struct DistrictCityAddress
{
    char region[MAX_LEN];           // �������� �������
    char district[MAX_LEN];         // �������� ������
    char city[MAX_LEN];             // �������� ������
    char street[MAX_LEN];           // �������� �����
    int house;                      // ����� ����
    int apartment;                  // ����� ��������
};

// ��������� ��� �������� ������ � ������� �����-�������
typedef struct VillageAddress
{
    char region[MAX_LEN];           // �������� �������
    char district[MAX_LEN];         // �������� ������
    char village[MAX_LEN];          // �������� �������
    int house;                      // ����� ����
};



// ����������� ��� �������� ������ ������ �� ��������� ��������� ������
typedef union Address
{
    CityAddress city;                       // ����� � ������
    RegionCityAddress regionCity;           // ����� � ������� "�������-�����"
    DistrictCityAddress districtCity;       // ����� � ������� "�����-�����"
    VillageAddress village;                 // ����� � ������� "�����-�������"
};

// ��������� ��� �������� ������ � ��������
typedef struct Student
{
    char name[MAX_LEN];             // ��� ��������
    int type;                       // ��� ����������:  1 - �����, 2 - �������-�����, 3 - �����-�����, 4 - �����-�������
    Address address;                // ����� ���������� (� ����������� �� ����)
};

Student* allocateStudents(int count);                                       // ������� ������������� ��������� ������

void freeStudents(Student* students, int count);                            // ������� ������� ������ 

int inputInt(int* value);                                                   // ������� ����� �������� ��������

int inputString(char* buffer, int size);                                    // ������� ����� ������

void inputStudent(Student* student);                                        // ������� ����� ���������� � ���������

void printTable(Student* students, int count);                              // ������� ������ ���������� � ��������� 

int searchStudentsByType(const Student* students, int count, int type);     // ������� ������ ��������� �� ��������� ��������� 

int matchStudentType(const Student* student, int type);                     // ������� ��� ��������, ������������� �� ������� ��������� ���� ����������

void saveToFile(const char* filename, const Student* students, int count);  // ���������� � ����

int loadFromFile(const char* filename, Student** students);                 // �������� �� �����
                        
void menu();

int againf();

#endif 