#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>   
#include <ctype.h>
#include "solution.h"   


static Parking* parkings = NULL;     // ��������� �� ������������ ������ ��������
static int parkingCount = 0;         // ������� ���������� ��������� ��������
static int maxParkings = 2;          // ������������ ���������� ��������, ������� ����� ������� ��� ����������������� ������



int isPositiveInteger(const char* str)      // �������� �� ������������� �����
{
    if (!str || *str == '\0') return 0; 

    if ((*(str + 0)) == '-') return 0;

    for (int i = 0; (*(str + i)); i++)
    {
        if (!isdigit((*(str + i)))) return 0; 
    }

    return 1; 
}


int getPositiveInt(const char* prompt, int min, int max)        // ���� ����� � �������� ��������� 
{
    char buffer[MAX_INPUT]; 
    int value;        

    while (1)
    { 
        printf("%s", prompt); 

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) 
        {
            buffer[strcspn(buffer, "\n")] = '\0';


            if (isPositiveInteger(buffer)) 
            {
                value = atoi(buffer); 

                if (value >= min && value <= max) 
                {
                    return value; 
                }
                else 
                {

                    printf("������: ����� ������ ���� �� %d �� %d.\n", min, max);
                }
            }
            else 
            {

                printf("������: ������� ������������� ����� �����.\n");
            }
        }
    }
}

void initializeParkings()                                           // ������� ������������� ������� ��������
{
    parkings = (Parking*)malloc(maxParkings * sizeof(Parking));         
}


void createNewParking(int totalSpaces)                              // ������� �������� ����� ��������
{
    if (parkingCount >= maxParkings) 
    {                      
        maxParkings *= 2;                                    
        parkings = (Parking*)realloc(parkings, maxParkings * sizeof(Parking)); 
    }

    Parking* p = &parkings[parkingCount];                   
    p->id = parkingCount + 1;                               // ����� ��������
    p->totalSpaces = totalSpaces;                           // ������� ������ ����� ����
    p->freeSpaces = totalSpaces;                            // ���������� ��� ����� ��������
    p->cars = (Car*)malloc(totalSpaces * sizeof(Car));      // ��������� ������ ��� ������ �����
    p->waitlistHead = NULL;                                 // ������� �������� �����
    p->waitlistTail = NULL;
    parkingCount++;                                         
    printf("������� �������� #%d\n", p->id);                
}


void listAllParkings()                                            // ����� ������ ���� �������� � ���� �������
{
    printf("ID | ����� | ��������\n");               
    for (int i = 0; i < parkingCount; i++) 
    {         
        printf("%2d | %6d | %8d\n",                  
            (*(parkings + i)).id,
            (*(parkings + i)).totalSpaces,
            (*(parkings + i)).freeSpaces
        );
    }
}


void displayParking(int id)                                     // ����� ���������� � ���������� ��������
{
    for (int i = 0; i < parkingCount; i++) 
    {         
        if ((*(parkings + i)).id == id)
        {
            printf("�������� #%d | �����: %d | ��������: %d\n", id, (*(parkings + i)).totalSpaces, (*(parkings + i)).freeSpaces);
            printf("������:\n");                     
            for (int j = 0; j < (*(parkings + i)).totalSpaces - (*(parkings + i)).freeSpaces; j++) 
            {
                printf(" - %s\n", (*(parkings + i)).cars[j].plate); 
            }
            return;                                  
        }
    }
    printf("�������� �� �������.\n");                
}


int parkCar(int id, const char* plate)                              // �������� ������ ��� ���������� � �������
{
    for (int i = 0; i < parkingCount; i++) 
    {
        if ((*(parkings + i)).id == id) 
        {
            Parking* p = &(*(parkings + i));
            if (p->freeSpaces > 0) 
            {  
                strcpy_s(p->cars[p->totalSpaces - p->freeSpaces].plate, MAX_PLATE_LENGTH, plate); 
                p->freeSpaces--;      
                printf("������ %s ������������.\n", plate);
            }
            else 
            {  
                addToQueue(&p->waitlistHead, &p->waitlistTail, plate);
                printf("����� ���. ������ ��������� � �������.\n");
            }
            return 0; 
        }
    }
    printf("�������� �� �������.\n"); 
    return -1;
}

 
int removeCar(int id, const char* plate)                                // �������� ������ � ���������� ����� �� �������
{
    for (int i = 0; i < parkingCount; i++) 
    {
        if ((*(parkings + i)).id == id)
        {
            Parking* p = &(*(parkings + i));
            int count = p->totalSpaces - p->freeSpaces; 

            for (int j = 0; j < count; j++) 
            {
                if (strcmp(p->cars[j].plate, plate) == 0) 
                { 
                    for (int k = j; k < count - 1; k++) 
                    {   
                        strcpy_s(p->cars[k].plate, MAX_PLATE_LENGTH, p->cars[k + 1].plate);
                    }
                    p->freeSpaces++;  
                    printf("������ %s �������.\n", plate);

                    if (!isQueueEmpty(p->waitlistHead)) 
                    {
                        char moved[MAX_PLATE_LENGTH];
                        strcpy_s(moved, MAX_PLATE_LENGTH, p->waitlistHead->inf);
                        removeFromQueue(&p->waitlistHead, &p->waitlistTail);
                        strcpy_s(p->cars[p->totalSpaces - p->freeSpaces].plate, MAX_PLATE_LENGTH, moved);
                        p->freeSpaces--;
                        printf("������ %s ������������ � �������.\n", moved);
                    }

                    return 0;
                }
            }
            printf("������ �� �������.\n");
            return -1;
        }
    }
    printf("�������� �� �������.\n");
    return -1;
}


void showWaitlist(int id)                                   // ����� ������� �������� ���������� ��������
{
    for (int i = 0; i < parkingCount; i++) 
    {
        if ((*(parkings + i)).id == id)
        {
            printf("������� ��������:\n");
            printQueue((*(parkings + i)).waitlistHead);
            return;
        }
    }
    printf("�������� �� �������.\n");
}


void inputCarPlate(char* plate)                                 // ���� ������ ������ � ����������
{
    printf("������� ����� ������ (�� 10 ��������): ");
    fgets(plate, MAX_PLATE_LENGTH, stdin);
    plate[strcspn(plate, "\n")] = 0;  
}


void clearInputBuffer()                                 // ������� ������ ����� 
{
    int c;
    while ((c = getchar()) != '\n'); 
}


void freeMemory()                                       // ������������ ���� ���������� ������
{
    for (int i = 0; i < parkingCount; i++) 
    {
        free((*(parkings + i)).cars);

        zap* curr = (*(parkings + i)).waitlistHead;
        while (curr) 
        {
            zap* tmp = curr;
            curr = curr->nx;
            free(tmp);
        }
    }
    free(parkings); 
}



void addToQueue(zap** head, zap** tail, const char* plate)          // ���������� ������ � �������
{
    zap* node = (zap*)malloc(sizeof(zap));  
    strcpy_s(node->inf, MAX_PLATE_LENGTH, plate);  
    node->nx = NULL;

    if (!*head) 
        *head = *tail = node;
    else 
    {
        (*tail)->nx = node; 
        *tail = node;
    }
}


void removeFromQueue(zap** head, zap** tail)                    // �������� ������ �� ������ �������
{
    if (*head) 
    {
        zap* tmp = *head;
        *head = (*head)->nx;
        if (!*head) 
            *tail = NULL;
        free(tmp);
    }
}


int isQueueEmpty(zap* head)                                     // �������� �� ������� �������
{
    return head == NULL;
}


void printQueue(zap* head)                                      // ������ ����������� �������
{
    while (head) 
    {
        printf(" - %s\n", head->inf);
        head = head->nx;
    }
}
