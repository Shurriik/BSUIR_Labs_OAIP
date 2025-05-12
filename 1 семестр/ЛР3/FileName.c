#include <stdio.h>      // ����������� ����������� ���������� 
#include <conio.h>
#include <locale.h>     // ���������� ��� ��������� ����������� ��������� 

#define N 100           // ����������� ��������� `N`, ������� ������ ������������ ������ �������

int main()              
{
    int choice;                // ���������� ��� �������� ������ ������������ � ����� ���������
    double Array[N][N];        // ��������� ������ ��� �������� ��������� ������� (������ N x N)
    int n;                     // ���������� ��� �������� ������� ������� 
    int i, j;                  
    double max;                // ���������� ��� �������� ������������� �������� � �������� ������� �������
    int fill_choice;;

    setlocale(LC_ALL, "RUS");  

    do 
    {
        
        do                                                                  // ���� ��� ����� ������� ������� � �������� ������������
        {
            printf("������� ������� �������: ");  

            if (scanf_s("%d", &n) != 1) 
            {
                printf("������, ������� ������������ ��������\n");                          
                while (getchar() != '\n');                                  // ��������� �������� ����� 
            }
            else if (n < 1) 
            {                  
                printf("������, ������� ������������ ��������\n");
                while (getchar() != '\n');       
            }
            else if (n > N) 
            {                  
                printf("������, ������� ������������ ��������\n");
                while (getchar() != '\n');       
            }
            else if (getchar() != '\n')                                     // ��������: ��� �� ������ �������� ����� �����
            {      
                printf("!!!!!!!������, ������� ������������ ��������\n");
                while (getchar() != '\n');       
            }
            else 
            {
                break;                           
            }
        } 
        while (1);   

        printf("����� �����\n");
        printf("1 - ��������� ����\n");
        printf("Else - ���� ������� �������\n");
        printf("��� �����:");

        if (_getch() == '1')
        {
            for (i = 0; i < n; ++i)
            {
                for (j = 0; j < n; ++j)
                {
                    Array[i][j] = (rand() % 101) - 50;
                }
            }
        }

        else {
            for (i = 0; i < n; ++i)
            {
                for (j = 0; j < n; ++j)
                {
                    do
                    {
                        printf("������� ������� Array[%d][%d]: ", i, j);
                        if (scanf_s("%lf", &Array[i][j]) != 1)
                        {
                            printf("������: ������� �������������� ����� ��� �������� Array[%d][%d]\n", i, j);
                            while (getchar() != '\n');
                        }
                        else if (getchar() != '\n')
                        {
                            printf("������: ������� �������������� ����� ��� �������� Array[%d][%d]\n", i, j);
                            while (getchar() != '\n');
                        }
                        else
                        {
                            break;
                        }
                    } while (1);
                }
            }
        }
 /*       printf("����� �����\n");
        printf("1 - ��������� ����\n");
        printf("2 - ���� ������� �������\n");
        printf("��� �����:");

        do
        {
            if (scanf_s("%d", &fill_choice) != 1)
            {
                printf("������: ������������ ����");
                while (getchar() != '\n');
            }
            else if (fill_choice != 1 && fill_choice != 2)
            {
                printf("������: ������������ ����");
                while (getchar() != '\n');
            }
            else if (getchar() != '\n')
            {
                printf("������: ������������ ����");
                while (getchar() != '\n');
            }
            else
            {
                break;
            }
        } while (1);

        if (fill_choice == 1)
        {
            for (i = 0; i < n; ++i)
            {
                for (j = 0; j < n; ++j)
                {
                    Array[i][j] = (rand() % 101) - 50;
                }
            }
        }

        if (fill_choice == 2)
        {
            for (i = 0; i < n; ++i)
            {
                for (j = 0; j < n; ++j)
                {
                    do
                    {
                        printf("������� ������� Array[%d][%d]: ", i, j);
                        if (scanf_s("%lf", &Array[i][j]) != 1)
                        {
                            printf("������: ������� �������������� ����� ��� �������� Array[%d][%d]\n", i, j);
                            while (getchar() != '\n');
                        }
                        else if (getchar() != '\n')
                        {
                            printf("������: ������� �������������� ����� ��� �������� Array[%d][%d]\n", i, j);
                            while (getchar() != '\n');
                        }
                        else
                        {
                            break;
                        }
                    } while (1);
                }
            }
        }
 */
        

        printf("\n��������� �������:\n");
        for (i = 0; i < n; ++i) 
        {                
            for (j = 0; j < n; ++j) 
            {            
                printf("%6.2lf", Array[i][j]);   
            }
            printf("\n");                        
        }

        
        printf("\n������� � ���������� ������� ����������� ������� � ������������� ��������:\n");
        for (i = 0; i < n; i++) 
        {                
            for (j = 0; j < n; j++) 
            {            
                if (j >= i && j <= n - 1 - i) 
                {  
                    printf("\033[1;32m%6.2lf\033[0m", Array[i][j]); 
                }
                else 
                {
                    printf("%6.2lf", Array[i][j]); 
                }
            }
            printf("\n");                       
        }

    
        // ���������� ������������� �������� � �������
        max = Array[0][0];                                              // ������������� ������������� ��������� Array[0][0]
        for (i = 0; i < n; i++) 
        {
            for (j = 0; j < n; j++) 
            {
                if (j >= i && j <= n - 1 - i)                           // ������� ��� �������� �������
                { 
                    if (Array[i][j] > max)                              // ���� ������� ������� ������ �������� ���������
                    { 
                        max = Array[i][j];                              // ��������� �������� ���������
                    }
                }
            }
        }


        printf("������������ ������� � �������������� �������: %.2lf\n", max);  
        printf("\n");
        
        printf("������� 1, ����� ��������� ��� ����� ������ ������, ����� �����: ");
        scanf_s("%d", &choice);

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

    }
    while (choice == 1);

    return 0;                                    
}
