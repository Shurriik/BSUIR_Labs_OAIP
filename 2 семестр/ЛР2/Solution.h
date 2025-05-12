#ifndef SOLUTION_H
#define SOLUTION_H

#define MAX_LEN 100


// ��������� ��� �������� ������ � ������
typedef struct
{
    char city[MAX_LEN];             // �������� ������
    char street[MAX_LEN];           // �������� �����
    int house;                      // ����� ����
    int apartment;                  // ����� ��������
} CityAddress;

// ��������� ��� �������� ������ � ������� �������
typedef struct
{
    char region[MAX_LEN];          // �������� �������
    char city[MAX_LEN];            // �������� ������
    char street[MAX_LEN];          // �������� �����
    int house;                     // ����� ����
    int apartment;                 // ����� ��������
} RegionCityAddress;

// ��������� ��� �������� ������ � ������� �����
typedef struct
{
    char region[MAX_LEN];           // �������� �������
    char district[MAX_LEN];         // �������� ������
    char city[MAX_LEN];             // �������� ������
    char street[MAX_LEN];           // �������� �����
    int house;                      // ����� ����
    int apartment;                  // ����� ��������
} DistrictCityAddress;

// ��������� ��� �������� ������ � ������� �����-�������
typedef struct
{
    char region[MAX_LEN];           // �������� �������
    char district[MAX_LEN];         // �������� ������
    char village[MAX_LEN];          // �������� �������
    int house;                      // ����� ����
} VillageAddress;



// ����������� ��� �������� ������ ������ �� ��������� ��������� ������
typedef union
{
    CityAddress city;                       // ����� � ������
    RegionCityAddress regionCity;           // ����� � ������� "�������-�����"
    DistrictCityAddress districtCity;       // ����� � ������� "�����-�����"
    VillageAddress village;                 // ����� � ������� "�����-�������"
} Address;

// ��������� ��� �������� ������ � ��������
typedef struct
{
    char name[MAX_LEN];             // ��� ��������
    int type;                       // ��� ����������:  1 - �����, 2 - �������-�����, 3 - �����-�����, 4 - �����-�������
    Address address;                // ����� ���������� (� ����������� �� ����)
} Student;

Student* allocateStudents(int count);                                       // ������� ������������� ��������� ������

void freeStudents(Student* students, int count);                            // ������� ������� ������ 

int inputInt(int* value);                                                   // ������� ����� �������� ��������

int inputString(char* buffer, int size);                                    // ������� ����� ������

void inputStudent(Student* student);                                        // ������� ����� ���������� � ���������

void printTable(Student* students, int count);                              // ������� ������ ���������� � ��������� 

int searchStudentsByType(const Student* students, int count, int type);     // ������� ������ ��������� �� ��������� ��������� 

int matchStudentType(const Student* student, int type);                     // ������� ��� ��������, ������������� �� ������� ��������� ���� ����������

#endif