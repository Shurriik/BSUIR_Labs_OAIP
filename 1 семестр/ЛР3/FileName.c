#include <stdio.h>      // Подключение стандартной библиотеки 
#include <conio.h>
#include <locale.h>     // Библиотека для настройки локализации программы 

#define N 100           // Определение константы `N`, которая задает максимальный размер матрицы

int main()              
{
    int choice;                // Переменная для хранения выбора пользователя в конце программы
    double Array[N][N];        // Двумерный массив для хранения элементов матрицы (размер N x N)
    int n;                     // Переменная для хранения порядка матрицы 
    int i, j;                  
    double max;                // Переменная для хранения максимального значения в заданной области матрицы
    int fill_choice;;

    setlocale(LC_ALL, "RUS");  

    do 
    {
        
        do                                                                  // Цикл для ввода размера матрицы и проверки корректности
        {
            printf("Введите порядок матрицы: ");  

            if (scanf_s("%d", &n) != 1) 
            {
                printf("Ошибка, введено некорректное значение\n");                          
                while (getchar() != '\n');                                  // Очищистка входного поток 
            }
            else if (n < 1) 
            {                  
                printf("Ошибка, введено некорректное значение\n");
                while (getchar() != '\n');       
            }
            else if (n > N) 
            {                  
                printf("Ошибка, введено некорректное значение\n");
                while (getchar() != '\n');       
            }
            else if (getchar() != '\n')                                     // Проверка: нет ли лишних символов после числа
            {      
                printf("!!!!!!!Ошибка, введено некорректное значение\n");
                while (getchar() != '\n');       
            }
            else 
            {
                break;                           
            }
        } 
        while (1);   

        printf("Выбор ввода\n");
        printf("1 - рандомный ввод\n");
        printf("Else - ввод матрицы вручную\n");
        printf("Ваш выбор:");

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
                        printf("Введите элемент Array[%d][%d]: ", i, j);
                        if (scanf_s("%lf", &Array[i][j]) != 1)
                        {
                            printf("Ошибка: введите действительное число для элемента Array[%d][%d]\n", i, j);
                            while (getchar() != '\n');
                        }
                        else if (getchar() != '\n')
                        {
                            printf("Ошибка: введите действительное число для элемента Array[%d][%d]\n", i, j);
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
 /*       printf("Выбор ввода\n");
        printf("1 - рандомный ввод\n");
        printf("2 - ввод матрицы вручную\n");
        printf("Ваш выбор:");

        do
        {
            if (scanf_s("%d", &fill_choice) != 1)
            {
                printf("Ошибка: некорректный ввод");
                while (getchar() != '\n');
            }
            else if (fill_choice != 1 && fill_choice != 2)
            {
                printf("Ошибка: некорректный ввод");
                while (getchar() != '\n');
            }
            else if (getchar() != '\n')
            {
                printf("Ошибка: некорректный ввод");
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
                        printf("Введите элемент Array[%d][%d]: ", i, j);
                        if (scanf_s("%lf", &Array[i][j]) != 1)
                        {
                            printf("Ошибка: введите действительное число для элемента Array[%d][%d]\n", i, j);
                            while (getchar() != '\n');
                        }
                        else if (getchar() != '\n')
                        {
                            printf("Ошибка: введите действительное число для элемента Array[%d][%d]\n", i, j);
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
        

        printf("\nВведенная матрица:\n");
        for (i = 0; i < n; ++i) 
        {                
            for (j = 0; j < n; ++j) 
            {            
                printf("%6.2lf", Array[i][j]);   
            }
            printf("\n");                        
        }

        
        printf("\nМатрица с выделением верхней треугольной области и максимального элемента:\n");
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

    
        // Нахождение максимального элемента в матрице
        max = Array[0][0];                                              // Инициализация максимального значением Array[0][0]
        for (i = 0; i < n; i++) 
        {
            for (j = 0; j < n; j++) 
            {
                if (j >= i && j <= n - 1 - i)                           // Условие для заданной области
                { 
                    if (Array[i][j] > max)                              // Если текущий элемент больше текущего максимума
                    { 
                        max = Array[i][j];                              // Обновляем значение максимума
                    }
                }
            }
        }


        printf("Максимальный элемент в заштрихованной области: %.2lf\n", max);  
        printf("\n");
        
        printf("Введите 1, чтобы повторить или любой другой символ, чтобы выйти: ");
        scanf_s("%d", &choice);

        printf("\n");

        if (choice == 1)
        {
            printf("Повтор выполнения задачи\n");
        }
        else
        {
            printf("Завершение работы программы\n");
        }

        printf("\n");

    }
    while (choice == 1);

    return 0;                                    
}
