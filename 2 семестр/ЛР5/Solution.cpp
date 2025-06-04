#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "solution.h"

/*Node* root = NULL;

// Выделение памяти
void allocateMemory() 
{
    root = NULL;
}

// Очистка дерева
void clear(Node* r) {
    if (r) {
        clear(r->left);
        clear(r->right);
        free(r->inf);
        free(r);
    }
}

void freeTree() {
    clear(root);
}

// Создание дерева
void createTree() {
    if (root != NULL) {
        puts("Дерево уже создано.");
        return;
    }
    root = (Node*)malloc(sizeof(Node));
    root->inf = (char*)malloc(N * sizeof(char));
    printf("Введите информацию для корня: ");
    scanf_s("%s", root->inf);
    root->left = root->right = NULL;
    root->n = 1;
}

// Добавление узла
void addNode() {
    if (!root) {
        puts("Дерево не создано.");
        return;
    }

    Node* temp = root;
    Node* parent = NULL;
    char* buf = (char*)malloc(N * sizeof(char));
    printf("Введите информацию: ");
    scanf_s("%s", buf, (unsigned)N);

    while (temp) {
        parent = temp;
        int cmp = strcmp(buf, temp->inf);
        if (cmp == 0) {
            temp->n++;
            puts("Узел уже существует, увеличено количество повторов.");
            free(buf);
            return;
        }
        else if (cmp < 0) {
            temp = temp->left;
        }
        else {
            temp = temp->right;
        }
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->inf = buf;
    newNode->n = 1;
    newNode->left = newNode->right = NULL;

    if (strcmp(buf, parent->inf) < 0)
        parent->left = newNode;
    else
        parent->right = newNode;
}

// Обход в симметричном порядке
void inOrderTraversal(Node* r) {
    if (r) {
        inOrderTraversal(r->left);
        printf("%s (%d)\n", r->inf, r->n);
        inOrderTraversal(r->right);
    }
}

// Удаление узла (по ключу)
void deleteNode() {
    if (!root) {
        puts("Дерево пустое.");
        return;
    }

    char key[N];
    printf("Введите информацию для удаления: ");
    scanf_s("%s", key, (unsigned)N);

    Node** current = &root;
    Node* parent = NULL;

    while (*current && strcmp((*current)->inf, key) != 0) {
        parent = *current;
        if (strcmp(key, (*current)->inf) < 0)
            current = &((*current)->left);
        else
            current = &((*current)->right);
    }

    if (!(*current)) {
        puts("Узел не найден.");
        return;
    }

    Node* target = *current;

    // Удаление узла с двумя детьми
    if (target->left && target->right) {
        Node* minRight = target->right;
        Node* minParent = target;

        while (minRight->left) {
            minParent = minRight;
            minRight = minRight->left;
        }

        free(target->inf);
        target->inf = _strdup(minRight->inf);
        target->n = minRight->n;

        if (minParent->left == minRight)
            minParent->left = minRight->right;
        else
            minParent->right = minRight->right;

        free(minRight->inf);
        free(minRight);
    }
    else {
        Node* child = target->left ? target->left : target->right;
        free(target->inf);
        free(target);
        *current = child;
    }
}

// Поиск минимума
Node* findMin(Node* r) {
    if (!r) return NULL;
    while (r->left) r = r->left;
    return r;
}

// Поиск максимума
Node* findMax(Node* r) {
    if (!r) return NULL;
    while (r->right) r = r->right;
    return r;
}

// Печать дерева в виде структуры
void printTree(Node* r, int level) {
    if (r) {
        printTree(r->right, level + 1);
        for (int i = 0; i < level; i++)
            printf("    ");
        printf("%s (%d)\n", r->inf, r->n);
        printTree(r->left, level + 1);
    }
}

// Интерфейс
void menu() {
    int choice;
    do {
        puts("\nМеню");
        puts("1 - Создать дерево");
        puts("2 - Добавить узел");
        puts("3 - Обход дерева (симметричный)");
        puts("4 - Удалить узел");
        puts("5 - Найти минимум");
        puts("6 - Найти максимум");
        puts("7 - Вывести дерево");
        puts("8 - Завершить интерфейс");
        printf("Выберите пункт: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1: createTree(); break;
        case 2: addNode(); break;
        case 3: inOrderTraversal(root); break;
        case 4: deleteNode(); break;
        case 5: {
            Node* min = findMin(root);
            if (min) printf("Минимум: %s (%d)\n", min->inf, min->n);
            else puts("Дерево пустое");
            break;
        }
        case 6: {
            Node* max = findMax(root);
            if (max) printf("Максимум: %s (%d)\n", max->inf, max->n);
            else puts("Дерево пустое");
            break;
        }
        case 7: printTree(root, 0); break;
        case 8: return;
        default: puts("Неверный пункт!");
        }
    } while (1);
}*/

Node* root = NULL;  

// Функция выделения памяти 
void allocateMemory() 
{
    root = NULL;  
}

// Рекурсивная функция очистки дерева
void clear(Node* r) 
{
    if (r) 
    {
        clear(r->left);   // Очистка левого поддерева
        clear(r->right);  // Очистка правого поддерева
        free(r->inf);     // Освобождение памяти строки
        free(r);          // Освобождение памяти узла
    }
}

// Функция очистки памяти
void freeTree() 
{
    clear(root);  
}

// Функция создания корня дерева
void createTree() 
{
    if (root != NULL) 
    {
        puts("Дерево уже создано.");  
        return;
    }
    root = (Node*)malloc(sizeof(Node));           // Выделяем память под корень

    root->inf = (char*)malloc(N * sizeof(char));  // Выделяем память под строку

    printf("Введите информацию для корня: ");
    scanf_s("%s", root->inf,(unsigned)N);
    root->left = root->right = NULL;  
    root->n = 1;                                    // Счётчик повторов
}

// Функция добавления нового узла
void addNode() 
{
    if (!root) 
    {
        puts("Дерево не создано.");
        return;
    }

    Node* temp = root;
    Node* parent = NULL;
    char* buf = (char*)malloc(N * sizeof(char));  // Буфер для новой строки
    printf("Введите информацию: ");
    scanf_s("%s", buf, (unsigned)N);

    while (temp) 
    {
        parent = temp;
        int cmp = strcmp(buf, temp->inf);  // Сравнение строки
        if (cmp == 0) 
        {
            temp->n++;  
            puts("Узел уже существует, увеличено количество повторов.");
            free(buf);
            return;
        }
        else if (cmp < 0) 
        {
            temp = temp->left;                      // Влево
        }
        else
        {
            temp = temp->right;                     // Вправо
        }
    }

    Node* newNode = (Node*)malloc(sizeof(Node));    // Создание нового узела

    newNode->inf = buf;
    newNode->n = 1;
    newNode->left = newNode->right = NULL;

    if (strcmp(buf, parent->inf) < 0)
        parent->left = newNode;                     // Вставить слева
    else
        parent->right = newNode;                    // Вставить справа
}

// Рекурсивный симметричный обход дерева(симметричный вариант обхода)
void inOrderTraversal(Node* r) 
{
    if (r) 
    {
        inOrderTraversal(r->left);  // Обход левого поддерева

        printf("%s (%d)\n", r->inf, r->n);  

        inOrderTraversal(r->right);  // Обход правого поддерева
    }
}

// Функция удаления узла 
void deleteNode() 
{
    if (!root) 
    {
        puts("Дерево пустое.");
        return;
    }

    char key[N];
    printf("Введите информацию для удаления: ");
    scanf_s("%s", key, (unsigned)N);

    Node** current = &root;
    Node* parent = NULL;

    while (*current && strcmp((*current)->inf, key) != 0) 
    {
        parent = *current;
        if (strcmp(key, (*current)->inf) < 0)
            current = &((*current)->left);
        else
            current = &((*current)->right);
    }

    if (!(*current)) {
        puts("Узел не найден.");
        return;
    }

    Node* target = *current;

    // Узел с двумя 
    if (target->left && target->right) 
    {
        Node* minRight = target->right;
        Node* minParent = target;

        while (minRight->left) {
            minParent = minRight;
            minRight = minRight->left;
        }

        free(target->inf);
        target->inf = _strdup(minRight->inf);  
        target->n = minRight->n;

        if (minParent->left == minRight)
            minParent->left = minRight->right;
        else
            minParent->right = minRight->right;

        free(minRight->inf);
        free(minRight);
    }
    else 
    {
        Node* child = target->left ? target->left : target->right;
        free(target->inf);
        free(target);
        *current = child;
    }
}

// Функция поиска минимального значения в дереве
Node* findMin(Node* r) 
{
    if (!r) return NULL;
    while (r->left) r = r->left;
    return r;
}

// Функция поиска максимального значения в дереве
Node* findMax(Node* r) 
{
    if (!r) return NULL;
    while (r->right) r = r->right;
    return r;
}

// Рекурсивная вывод дерева в виде структуры
void printTree(Node* r, int level) 
{
    if (r)
    {
        printTree(r->right, level + 1);             // Правое
        for (int i = 0; i < level; i++)
            printf("    ");
        printf("%s (%d)\n", r->inf); 
        printTree(r->left, level + 1);              // Левое
    }
}


