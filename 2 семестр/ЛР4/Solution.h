#ifndef SOLUTION_H
#define SOLUTION_H

#define MAX_PLATE_LENGTH 11 
#define MAX_WAITLIST 100    
#define MAX_INPUT 100
#define MIN_TOTALSPACE 1
#define MAX_TOTALSPACE 100

// ��������� ������
typedef struct 
{
    char plate[MAX_PLATE_LENGTH];       // ����� ������
} Car;

// �������
typedef struct zap 
{
    char inf[MAX_PLATE_LENGTH];         // ����� ������
    struct zap* nx;                     // ��������� �� ��������� �������
} zap;

// ��������� ��������
typedef struct 
{
    int id;                     // ����� ��������
    int totalSpaces;            // ����� ���������� ����
    int freeSpaces;             // ���������� ��������� ����
    Car* cars;                  // ������ �������������� �����
    zap* waitlistHead;          // ������ �������
    zap* waitlistTail;          // ����� �������
} Parking;


void initializeParkings();                            // ������������� ������� ��������

void createNewParking(int);                           // �������� ����� ��������

void listAllParkings();                               // ����� ������ ���� ��������

void displayParking(int);                             // ���������� � ��������

int parkCar(int, const char*);                        // ������������ ������

int removeCar(int, const char*);                      // ������� ������

void showWaitlist(int);                               // �������� ������� ��������

void inputCarPlate(char*);                            // ���� ������ ������

void clearInputBuffer();                              // ������� ������ �����

void freeMemory();                                    // ������� ���������� ������

int getPositiveInt(const char* prompt, int min, int max);  // ���� ����� � �������� ��������� 

int isPositiveInteger(const char* str);                   // �������� �� ������������� �����

// �������
void addToQueue(zap**, zap**, const char*);           // ���������� � �������

void removeFromQueue(zap**, zap**);                   // �������� �� �������

int isQueueEmpty(zap*);                               // ��������, ����� �� �������

void printQueue(zap*);                                // ������ �������

#endif

