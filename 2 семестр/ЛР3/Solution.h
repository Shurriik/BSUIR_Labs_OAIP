#ifndef SOLUTION_H            
#define SOLUTION_H

#define M 60

// ��������� �����
struct stack 
{
    char inf;                // ������ ������ ������
    struct stack* next;      // ��������� �� ��������� �������
};


struct stack* push(struct stack* top, char symbol);                 // ������� ���������� �������� � ����

struct stack* pop(struct stack* top, char* symbol);                 // ������� �������� �������� �� �����

int isOpenBracket(char c);                                          // ��������, �������� �� ������ ����������� �������

int isCloseBracket(char c);                                         // ��������, �������� �� ������ ����������� �������

int isMatchingPair(char open, char close);                          // �������� ������������ ������

int checkSyntaxError(const char* expression);                       // �������� ���������� 

void checkBrackets(const char* expression);                         // ������� �������� ������������ ������

void freeStack(struct stack* top);                                  // ������� ������������ ������ 

#endif  

