#ifndef SOLUTION_H            
#define SOLUTION_H

#define M 60

// Структура стека
struct stack 
{
    char inf;                // Хранит символ скобки
    struct stack* next;      // Указатель на следующий элемент
};


struct stack* push(struct stack* top, char symbol);                 // Функции добавления элемента в стек

struct stack* pop(struct stack* top, char* symbol);                 // Функции удаления элемента из стека

int isOpenBracket(char c);                                          // Проверка, является ли символ открывающей скобкой

int isCloseBracket(char c);                                         // Проверка, является ли символ закрывающей скобкой

int isMatchingPair(char open, char close);                          // Проверка соответствия скобок

int checkSyntaxError(const char* expression);                       // Проверка синтаксиса 

void checkBrackets(const char* expression);                         // Функция проверки корректности скобок

void freeStack(struct stack* top);                                  // Функции освобождения памяти 

#endif  

