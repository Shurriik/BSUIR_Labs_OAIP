#include <stdio.h>    
#include <stdlib.h>  
#include <ctype.h>
#include "solution.h" 

struct stack* push(struct stack* top, char symbol)                  // ���������� ������� � ����
{
    struct stack* New = (struct stack*)malloc(sizeof(struct stack)); 
  
    New->inf = symbol; // ���������� �������
    New->next = top;   // ����� � ����������
    return New;        
}


struct stack* pop(struct stack* top, char* symbol)                 // �������� �������� �� �����
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


void freeStack(struct stack* top)                                   // ������������ ������
{
    struct stack* temp;
    while (top != NULL) 
    {    
        temp = top;           
        top = top->next;      
        free(temp);           
    }
}


int isOpenBracket(char c)                                       // �������� �� ����������� ������
{
    return c == '(' || c == '[' || c == '{'; 
}

        
int isCloseBracket(char c)                                      // �������� �� ����������� ������
{
    return c == ')' || c == ']' || c == '}'; 
}


int isMatchingPair(char open, char close)                       // �������� �� ������������ ������
{
    return (open == '(' && close == ')') || (open == '[' && close == ']') || (open == '{' && close == '}');
}

int checkSyntaxError(const char* expression)                    // �������� ����������
{
    int i;
    char prev = '\0'; 

    for (i = 0; (*(expression + i)) != '\0'; i++)
    {
        char c = (*(expression + i));

       
        if (i == 0 && (c == '*' || c == '/' || c == '+')) 
        {
            printf("������: ��������� �� ������ ���������� � ��������� '%c'.\n", c);
            return 1;
        }

       
        if ((prev == '(' || prev == '[' || prev == '{') &&
            (c == '*' || c == '/' || c == '+' || c == ')')) 
        {
            printf("������: ������������ ������ '%c' ����� ����������� ������ �� ������� %d.\n", c, i + 1);
            return 1;
        }

       
        if ((prev == '+' || prev == '-' || prev == '*' || prev == '/') && (c == '+' || c == '-' || c == '*' || c == '/')) 
        {
            printf("������: ��� ��������� ������ ('%c%c') �� ������� %d.\n", prev, c, i);
            return 1;
        }

      
        if ((c == ')' || c == ']' || c == '}') && (prev == '+' || prev == '-' || prev == '*' || prev == '/')) 
        {
            printf("������: �������� '%c' ����� ����������� ������� �� ������� %d.\n", prev, i);
            return 1;
        }

        prev = c;
    }

   
    if (prev == '+' || prev == '-' || prev == '*' || prev == '/') 
    {
        printf("������: ��������� �� ������ ������������� �� �������� '%c'.\n", prev);
       return 1;
    }

    return 0; 
}


void checkBrackets(const char* expression)                                  // ������� �������� ���������
{
    struct stack* top = NULL;  
    int i, error = 0;          // ����������: ������ � ���� ������
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
                printf("������: ������ ����������� ������ '%c' �� ������� %d.\n", c, i + 1);
                error = 1;
                break;
            }
            if (!isMatchingPair(from_stack, c)) 
            { 
                printf("������: ������������� ������ '%c' � '%c' �� ������� %d.\n", from_stack, c, i + 1);
                error = 1;
                break;
            }
        }
    }

    if (!error && top != NULL) 
    { 
        printf("������: ������ ����������� ������ '%c'.\n", top->inf);
        error = 1;
    }

    if (!error) 
    { 
        printf("������ � ��������� ����������� ���������.\n");
    }

    freeStack(top);
}