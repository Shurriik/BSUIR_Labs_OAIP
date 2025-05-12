#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "solution.h"


char* str_input(const char* str) 
{
    if (!str) return NULL;
    unsigned long int len = strlen(str) + 1;
    char* copy = (char*)malloc(len);
    if (copy) 
    {
        strcpy_s(copy, len, str);
    }
    return copy;
}

// ������� ��� ����� ������ � ������������ ���������� ������
char* input_string() 
{
    char buffer[100];
    printf("������� ������ (�������� 99 ��������): ");
    if (!fgets(buffer, sizeof(buffer), stdin)) 
    {
        return NULL;
    }

    unsigned long int len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') 
    {
        buffer[len - 1] = '\0';
    }

    char* result = allocate_memory(len + 1);
    if (result) 
    {
        strcpy_s(result, len + 1, buffer);
    }
    return result;
}

// ���������, �������� �� ������ ���������� (�� ������ � �������� ���� �� ���� ���������)
int validate_input(const char* input) 
{
    if (!input || strlen(input) == 0) 
    {
        return 0;
    }
    if (!strchr(input, ':')) 
    {
        return 0;
    }
    return 1;
}

// ���������� ��������� �� ������ ��������� � ������
const char* find_first_colon(const char* input) 
{
    return strchr(input, ':');
}

// ���������� ��������� �� ������ ��������� � ������
const char* find_second_colon(const char* first_colon) 
{
    if (!first_colon) 
    {
        return NULL;
    }
    return strchr(first_colon + 1, ':');
}

// ������� ��� ���������� �������� ����� ������ � ������ �����������
char* extract_colons(const char* first_colon, const char* second_colon) 
{
    if (!first_colon) 
    {
        return NULL;
    }

    if (!second_colon) 
    {
        if (*(first_colon + 1) == '\0') 
        {
            return NULL;
        }
        return str_input(first_colon + 1);
    }

    if (second_colon == first_colon + 1) 
    {
        return NULL;
    }

    unsigned long int length = second_colon - first_colon - 1;
    char* result = allocate_memory(length + 1);
    if (result) 
    {
        strncpy_s(result, length + 1, first_colon + 1, length);
        result[length] = '\0';
    }
    return result;
}

// ������� ��� ��������� ������
char* allocate_memory(unsigned int size) 
{
    char* ptr = (char*)malloc(size);
    if (!ptr) 
    {
        printf(stderr, "������ ��������� ������.\n");
    }
    return ptr;
}

// ������� ��� ������������ ������
void free_memory(void* memory) 
{
    if (memory) 
    {
        free(memory);
    }
}
