#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "solution.h" 


void remove_newline(char* str)                                                              // �������� ������� ����� ������
{
    if (str == NULL) return;                                                                // ��������, ������ �� NULL
    if (strchr(str, '\n'))                                                                  // ��������, �������� �� ������ ������ ����� ������
    { 
        str[strcspn(str, "\n")] = '\0';                                                     // ������ ������ ����� ������ �� ����-������
    }
}


void process_string(const char* input, char** result, int* sum)                             // �������� ������� ��������� ������
{
    if (input == NULL || result == NULL || *result == NULL || sum == NULL) return;          // �������� ������� ���������� �� NULL

    (*result)[0] = '\0';                                                                    // ������������� �������������� ������ ��� ������
    *sum = 0;                                                                               // ������������� ����� ����� ����

    concat_words(input, result, 0);                                                         // ����� ������� ��� ������������ ����
    calculate_sum(input, sum, 0);                                                           // ����� ������� ��� ���������� ����� �����
}


void concat_words(const char* input, char** result, int index)                              // ������� ������������ ����
{
    if (input[index] == '\0') return;                                                       // ���� ��������� ����� ������, ����� �� �������

    char* word = (char*)malloc(256);                                                        // �������� ������ ��� �������� �������� �����
    int word_index = 0;                                                                     // ������������� ������� ��� ������

    
    while (input[index] != '\0' && input[index] != ' ')                                     // ���������� �����
    { 
        word[word_index++] = input[index++];                                                // ����������� ������� � ����� ����� � ����� �������
    }
    word[word_index] = '\0';                                                                // ���������� ������/����� ����-��������

    if (is_alpha(word) && strlen(word) >= 4)                                                // ��������, ����� ������� �� ���� � ����� ����� >= 4
    { 
        unsigned long int current_length = strlen(*result);                                            // ��������� ������� ����� �������������� ������
        unsigned long int word_length = strlen(word);                                                  // ��������� ����� �������� �����

        
        *result = realloc(*result, current_length + word_length + 1);                       // ���������� ������ ��� �������������� ������
        if (*result == NULL) 
        { 
            fprintf(stderr, "������ ��������� ������.\n"); 
            exit(1); 
        }

        
        strcat_s(*result, current_length + word_length + 1, word);                          // ���������� ����� � �������������� ������
    }


    while (input[index] == ' ')                                                             // ������� ��������
    { 
        index++;
    }

    concat_words(input, result, index);                                                     // ����������� ����� ������� ��� ��������� ���������� �����
}


void calculate_sum(const char* input, int* sum, int index)                                  // ���������� ����� �����
{
    if (input[index] == '\0') return;                                                       // ���� ��������� ����� ������, ����� �� �������

    char* word = (char*)malloc(256);                                                        // �������� ������ ��� �������� �������� �����
    int word_index = 0;                                                                     // ������������� ������� ��� ������

    
    while (input[index] != '\0' && input[index] != ' ')                                     // ���������� �����
    { 
        word[word_index++] = input[index++];                                                // ����������� ������� � ����� ����� � ����� �������
    }
    word[word_index] = '\0'; 

    if (is_numeric(word))                                                                   // ���� ����� ������� ������ �� ����
    { 
        *sum += atoi(word);                                                                 // �������������� ����� � ����� � ���������� � �����
    }

   
    while (input[index] == ' ')                                                             // ������� ��������
    { 
        index++;
    }

    calculate_sum(input, sum, index);                                                       // ����������� ����� ������� ��� ��������� ���������� �����
}


int is_numeric(const char* str)                                                             // �������� �� �������� ������
{
    if (str == NULL || *str == '\0') return 0;                                              // ���� ������ ������ ��� NULL
    for (int i = 0; str[i] != '\0'; i++)                                                    // ��������� �������� ������
    { 
        if (str[i] < '0' || str[i] > '9') return 0;                                         // ���� ������ �� �������� ������
    }
    return 1; 
}


int is_alpha(const char* str)                                                               // �������� �� ���������� ������
{
    if (str == NULL || *str == '\0') return 0;                                              // ���� ������ ������ ��� NULL
    for (int i = 0; str[i] != '\0'; i++)                                                    // ��������� �������� ������
    { 
        if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')))        // ���� ������ �� �������� ������
        {
            
            return 0; 
        }
    }
    return 1; 
}


