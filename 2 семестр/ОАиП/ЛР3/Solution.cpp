#include <stdio.h>    
#include <stdlib.h>  
#include <ctype.h>
#include "solution.h" 

struct stack* push(struct stack* top, char symbol)                  // Добавление символа в стек
{
    struct stack* New = (struct stack*)malloc(sizeof(struct stack)); 
  
    New->inf = symbol; // Сохранение символа
    New->next = top;   // Связь с предыдущим
    return New;        
}


struct stack* pop(struct stack* top, char* symbol)                 // Удаление элемента из стека
{
    if (top == NULL) 
    {       
        *symbol = '\0';       
        return NULL;          
    }
    struct stack* temp = top; 
    *symbol = temp->inf;      
    top = temp->next;         
    free(temp);               
    return top;               
}


void freeStack(struct stack* top)                                   // Освобождение памяти
{
    struct stack* temp;
    while (top != NULL) 
    {    
        temp = top;           
        top = top->next;      
        free(temp);           
    }
}


int isOpenBracket(char c)                                       // Проверка на открывающую скобку
{
    return c == '(' || c == '[' || c == '{'; 
}

        
int isCloseBracket(char c)                                      // Проверка на закрывающую скобку
{
    return c == ')' || c == ']' || c == '}'; 
}


int isMatchingPair(char open, char close)                       // Проверка на соответствие скобок
{
    return (open == '(' && close == ')') || (open == '[' && close == ']') || (open == '{' && close == '}');
}

int checkSyntaxError(const char* expression)                    // Проверка синтаксиса
{
    int i;
    char prev = '\0'; 

    for (i = 0; (*(expression + i)) != '\0'; i++)
    {
        char c = (*(expression + i));

       
        if (i == 0 && (c == '*' || c == '/' || c == '+')) 
        {
            printf("Ошибка: выражение не должно начинаться с оператора '%c'.\n", c);
            return 1;
        }

       
        if ((prev == '(' || prev == '[' || prev == '{') &&
            (c == '*' || c == '/' || c == '+' || c == ')')) 
        {
            printf("Ошибка: недопустимый символ '%c' после открывающей скобки на позиции %d.\n", c, i + 1);
            return 1;
        }

       
        if ((prev == '+' || prev == '-' || prev == '*' || prev == '/') && (c == '+' || c == '-' || c == '*' || c == '/')) 
        {
            printf("Ошибка: два оператора подряд ('%c%c') на позиции %d.\n", prev, c, i);
            return 1;
        }

      
        if ((c == ')' || c == ']' || c == '}') && (prev == '+' || prev == '-' || prev == '*' || prev == '/')) 
        {
            printf("Ошибка: оператор '%c' перед закрывающей скобкой на позиции %d.\n", prev, i);
            return 1;
        }

        prev = c;
    }

   
    if (prev == '+' || prev == '-' || prev == '*' || prev == '/') 
    {
        printf("Ошибка: выражение не должно заканчиваться на оператор '%c'.\n", prev);
       return 1;
    }

    return 0; 
}


void checkBrackets(const char* expression)                                  // Функция проверки выражения
{
    struct stack* top = NULL;  
    int i, error = 0;          // Переменные: индекс и флаг ошибки
    char from_stack;           


    for (i = 0; (*(expression + i)) != '\0'; i++) 
    {

        char c = (*(expression + i));
        if (isOpenBracket(c)) 
        {         
            top = push(top, c);         
        }
        else if (isCloseBracket(c)) 
        { 
            top = pop(top, &from_stack);
            if (from_stack == '\0') 
            {    
                printf("Ошибка: лишняя закрывающая скобка '%c' на позиции %d.\n", c, i + 1);
                error = 1;
                break;
            }
            if (!isMatchingPair(from_stack, c)) 
            { 
                printf("Ошибка: несовпадающие скобки '%c' и '%c' на позиции %d.\n", from_stack, c, i + 1);
                error = 1;
                break;
            }
        }
    }

    if (!error && top != NULL) 
    { 
        printf("Ошибка: лишняя открывающая скобка '%c'.\n", top->inf);
        error = 1;
    }

    if (!error) 
    { 
        printf("Скобки в выражении расставлены правильно.\n");
    }

    freeStack(top);
}