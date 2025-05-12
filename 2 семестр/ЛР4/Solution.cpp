#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>   
#include <ctype.h>
#include "solution.h"   


static Parking* parkings = NULL;     // Указатель на динамический массив парковок
static int parkingCount = 0;         // Текущее количество созданных парковок
static int maxParkings = 2;          // Максимальное количество парковок, которое можно хранить без перераспределения памяти



int isPositiveInteger(const char* str)      // Проверка на положительные числа
{
    if (!str || *str == '\0') return 0; 

    if ((*(str + 0)) == '-') return 0;

    for (int i = 0; (*(str + i)); i++)
    {
        if (!isdigit((*(str + i)))) return 0; 
    }

    return 1; 
}


int getPositiveInt(const char* prompt, int min, int max)        // Ввод числа в заданном диапазоне 
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

                    printf("Ошибка: число должно быть от %d до %d.\n", min, max);
                }
            }
            else 
            {

                printf("Ошибка: введите положительное целое число.\n");
            }
        }
    }
}

void initializeParkings()                                           // Функция инициализации массива парковок
{
    parkings = (Parking*)malloc(maxParkings * sizeof(Parking));         
}


void createNewParking(int totalSpaces)                              // Функция создания новой парковки
{
    if (parkingCount >= maxParkings) 
    {                      
        maxParkings *= 2;                                    
        parkings = (Parking*)realloc(parkings, maxParkings * sizeof(Parking)); 
    }

    Parking* p = &parkings[parkingCount];                   
    p->id = parkingCount + 1;                               // Номер парковки
    p->totalSpaces = totalSpaces;                           // Задание общего числа мест
    p->freeSpaces = totalSpaces;                            // Изначально все места свободны
    p->cars = (Car*)malloc(totalSpaces * sizeof(Car));      // Выделение памяти под список машин
    p->waitlistHead = NULL;                                 // Очередь ожидания пуста
    p->waitlistTail = NULL;
    parkingCount++;                                         
    printf("Создана парковка #%d\n", p->id);                
}


void listAllParkings()                                            // Вывод списка всех парковок в виде таблицы
{
    printf("ID | Всего | Свободно\n");               
    for (int i = 0; i < parkingCount; i++) 
    {         
        printf("%2d | %6d | %8d\n",                  
            (*(parkings + i)).id,
            (*(parkings + i)).totalSpaces,
            (*(parkings + i)).freeSpaces
        );
    }
}


void displayParking(int id)                                     // Вывод информации о конкретной парковке
{
    for (int i = 0; i < parkingCount; i++) 
    {         
        if ((*(parkings + i)).id == id)
        {
            printf("Парковка #%d | Всего: %d | Свободно: %d\n", id, (*(parkings + i)).totalSpaces, (*(parkings + i)).freeSpaces);
            printf("Машины:\n");                     
            for (int j = 0; j < (*(parkings + i)).totalSpaces - (*(parkings + i)).freeSpaces; j++) 
            {
                printf(" - %s\n", (*(parkings + i)).cars[j].plate); 
            }
            return;                                  
        }
    }
    printf("Парковка не найдена.\n");                
}


int parkCar(int id, const char* plate)                              // Парковка машины или постановка в очередь
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
                printf("Машина %s припаркована.\n", plate);
            }
            else 
            {  
                addToQueue(&p->waitlistHead, &p->waitlistTail, plate);
                printf("Места нет. Машина добавлена в очередь.\n");
            }
            return 0; 
        }
    }
    printf("Парковка не найдена.\n"); 
    return -1;
}

 
int removeCar(int id, const char* plate)                                // Удаление машины и добавление новой из очереди
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
                    printf("Машина %s удалена.\n", plate);

                    if (!isQueueEmpty(p->waitlistHead)) 
                    {
                        char moved[MAX_PLATE_LENGTH];
                        strcpy_s(moved, MAX_PLATE_LENGTH, p->waitlistHead->inf);
                        removeFromQueue(&p->waitlistHead, &p->waitlistTail);
                        strcpy_s(p->cars[p->totalSpaces - p->freeSpaces].plate, MAX_PLATE_LENGTH, moved);
                        p->freeSpaces--;
                        printf("Машина %s припаркована с очереди.\n", moved);
                    }

                    return 0;
                }
            }
            printf("Машина не найдена.\n");
            return -1;
        }
    }
    printf("Парковка не найдена.\n");
    return -1;
}


void showWaitlist(int id)                                   // Вывод очереди ожидания конкретной парковки
{
    for (int i = 0; i < parkingCount; i++) 
    {
        if ((*(parkings + i)).id == id)
        {
            printf("Очередь ожидания:\n");
            printQueue((*(parkings + i)).waitlistHead);
            return;
        }
    }
    printf("Парковка не найдена.\n");
}


void inputCarPlate(char* plate)                                 // Ввод номера машины с клавиатуры
{
    printf("Введите номер машины (до 10 символов): ");
    fgets(plate, MAX_PLATE_LENGTH, stdin);
    plate[strcspn(plate, "\n")] = 0;  
}


void clearInputBuffer()                                 // Очистка буфера ввода 
{
    int c;
    while ((c = getchar()) != '\n'); 
}


void freeMemory()                                       // Освобождение всей выделенной памяти
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



void addToQueue(zap** head, zap** tail, const char* plate)          // Добавление машины в очередь
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


void removeFromQueue(zap** head, zap** tail)                    // Удаление машины из начала очереди
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


int isQueueEmpty(zap* head)                                     // Проверка на пустоту очереди
{
    return head == NULL;
}


void printQueue(zap* head)                                      // Печать содержимого очереди
{
    while (head) 
    {
        printf(" - %s\n", head->inf);
        head = head->nx;
    }
}
