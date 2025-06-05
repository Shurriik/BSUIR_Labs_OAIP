#ifndef TRANSPORT_H
#define TRANSPORT_H


#include <locale.h>
#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  
#include <time.h>  
#include <ctype.h>
  

#define MAX_STRING 50                   // ������������ ����� ������
#define EXPORT_FILE "export.txt"        // ���� ��� �������� 

// ������������ ����� ��
typedef enum TransportType
{
    TRUCK,              // �������� ���������
    PASSENGER           // ������������ ���������
};

// ��������� ��� �������� ���������� � ������������
typedef struct Booking
{
    char date[20];          // ���� ��:��:����
    char time[10];          // ����� ��:��
    char user[MAX_STRING];  // ��� ���������
};

// ��������� ��� �������� ���������� � ������������ ��������
typedef struct Transport
{
    int id;                                 // ���������� ������������� ��
    TransportType type;                     // ��� ��
    char model[MAX_STRING];                 // ������ �� 
    int capacity;                           // ����������� �� 
    int available;                          // ���������� ��������� ������ ������� ��
    char current_status[MAX_STRING];        // ������� ������ ��
    Booking* bookings;                      // ��������� �� ������������ ������ ������������ ��� ������� ��
    int booking_count;                      // ���������� ������������ ��� ������� ��
};

void exportToTextFile();                            // ������� ������ �� ��������� ��������� ����

void saveToFile();                                  // ���������� ������ � ����

int loadFromFile(const char* filename);             // �������� ������ �� �����

int loadFromExportFile();                           // ������� ������ � ��������� ����

int isLeapYear(int year);                           // �������� ����������� ����

int isValidDate(int day, int month, int year);      // ������������ ����

int isValidTime(int hour, int minute);              // ������������ �������

int isVehicleAvailable(int id, const char* date);   // ����������� ��

void addTransport();                                // ���������� ������ ��

void orderTransport();                              // ������������ ��

void editBooking();                                 // �������������� ������������

void cancelBooking();                               // ������ ������������

void updateAvailability();                          // ���������� ����������� ��

void checkStatus();                                 // �������� ������� ��

void filterTransport();                             // ������ ��

void countAvailableByDate();                        // ������� ��������� �� �� ����

void printStatistics();                             // ����� ���������� �� ��

void printTransports();                             // ������ ������ ���� ��

void searchTransport();                             // ����� ��

void editTransport();                               // �������������� ���������� � ��

void deleteTransport();                             // �������� ��

void validateTransportData();                       // �������� ����������� ������

void TransportSystem();                             // ��������� ������

void ensureCapacity();                              // ����������������� ������

void cleanupTransportSystem();                      // ������� ������

void trim(char* str);                               // ������� ��� �������� �������� � ������ � ����� ������

void menu();                                        // ����

int againf();                                       // ������ ���������

#endif 