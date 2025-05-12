#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <locale.h> 
#include "solution.h" 

int main()
{
    int choice=0;                                                         // ���������� ��� �������� ������ ������������ (���������� ��� �����)

    do 
    {
        setlocale(LC_ALL, "RUS"); 
        char* input = NULL;                                             // ��������� ��� ����� ������
        char* result = NULL;                                            // ��������� ��� ������������ ������
        int  buffer_size = 0;                                           // ������ ������ ��� ������
        int sum = 0;                                                    // ���������� ��� �������� ����� �����
        int valid_input = 0;                                            // ���� ��� �������� ������������ �����

       
  
        do
        {
            printf("������� ��������� ������ ������: ");
            if (scanf_s("%d", &buffer_size) != 1)
            {
                printf("������\n");
                while (getchar() != '\n');
            }
            else if (buffer_size < 3)
            {
                printf("������\n");
                while (getchar() != '\n');
            }
            else if (getchar() != '\n')
            {
                printf("������\n");
                while (getchar() != '\n');
            }
            else
            {

                break;
            }
        } while (1);
        
      

        
        input = (char*)malloc(buffer_size * sizeof(char));              // ��������� ������ ��� ������
        if (input == NULL) 
        { 
            printf(stderr, "������ ��������� ������ ��� �����.\n"); 
            return 1; 
        }

        do 
        { 
            printf("������� ������: "); 
            if (fgets(input, (int)buffer_size, stdin) == NULL)          // ������ ������ � ��������� �� ������
            { 
                fprintf(stderr, "������ ����� ������. ���������� ��� ���.\n"); 
                continue; 
            }

            valid_input = 1;  
        } while (!valid_input);
    

        remove_newline(input);                                          // �������� ������� ����� ������ �� �������� ������

        
        result = malloc(1);                                             // ��������� ������ ��� �������������� ������
        if (result == NULL) 
        { 
            fprintf(stderr, "������ ��������� ������ ��� ����������.\n"); 
            free(input);                                                // ������������ ������ ��� �����
            return 1; 
        }
        result[0] = '\0';                                               // ������������� �������������� ������ ��� ������

        
        process_string(input, &result, &sum);                           // ��������� ������: ������������ ����� � ������� ����� �����

        
       
        printf("������������ ������: %s\n", result); 
        printf("����� �����: %d\n", sum); 

        
        free(input);                                                    // ������������ ������ ��� �����
        free(result);                                                   // ������������ ������ ��� ����������

        printf("������� 1, ����� ��������� ��� ����� ������ ������, ����� �����: "); 
        scanf_s("%d", &choice); 

        while (getchar() != '\n'); 

        printf("\n");

        if (choice == 1) 
        {
            printf("������ ���������� ������\n"); 
        }
        else 
        {
            printf("���������� ������ ���������\n"); 
        }

        printf("\n");

    } while (choice == 1); 
    return 0; 
}
