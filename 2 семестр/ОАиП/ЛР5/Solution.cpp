#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "solution.h"

/*Node* root = NULL;

// ��������� ������
void allocateMemory() 
{
    root = NULL;
}

// ������� ������
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

// �������� ������
void createTree() {
    if (root != NULL) {
        puts("������ ��� �������.");
        return;
    }
    root = (Node*)malloc(sizeof(Node));
    root->inf = (char*)malloc(N * sizeof(char));
    printf("������� ���������� ��� �����: ");
    scanf_s("%s", root->inf);
    root->left = root->right = NULL;
    root->n = 1;
}

// ���������� ����
void addNode() {
    if (!root) {
        puts("������ �� �������.");
        return;
    }

    Node* temp = root;
    Node* parent = NULL;
    char* buf = (char*)malloc(N * sizeof(char));
    printf("������� ����������: ");
    scanf_s("%s", buf, (unsigned)N);

    while (temp) {
        parent = temp;
        int cmp = strcmp(buf, temp->inf);
        if (cmp == 0) {
            temp->n++;
            puts("���� ��� ����������, ��������� ���������� ��������.");
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

// ����� � ������������ �������
void inOrderTraversal(Node* r) {
    if (r) {
        inOrderTraversal(r->left);
        printf("%s (%d)\n", r->inf, r->n);
        inOrderTraversal(r->right);
    }
}

// �������� ���� (�� �����)
void deleteNode() {
    if (!root) {
        puts("������ ������.");
        return;
    }

    char key[N];
    printf("������� ���������� ��� ��������: ");
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
        puts("���� �� ������.");
        return;
    }

    Node* target = *current;

    // �������� ���� � ����� ������
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

// ����� ��������
Node* findMin(Node* r) {
    if (!r) return NULL;
    while (r->left) r = r->left;
    return r;
}

// ����� ���������
Node* findMax(Node* r) {
    if (!r) return NULL;
    while (r->right) r = r->right;
    return r;
}

// ������ ������ � ���� ���������
void printTree(Node* r, int level) {
    if (r) {
        printTree(r->right, level + 1);
        for (int i = 0; i < level; i++)
            printf("    ");
        printf("%s (%d)\n", r->inf, r->n);
        printTree(r->left, level + 1);
    }
}

// ���������
void menu() {
    int choice;
    do {
        puts("\n����");
        puts("1 - ������� ������");
        puts("2 - �������� ����");
        puts("3 - ����� ������ (������������)");
        puts("4 - ������� ����");
        puts("5 - ����� �������");
        puts("6 - ����� ��������");
        puts("7 - ������� ������");
        puts("8 - ��������� ���������");
        printf("�������� �����: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1: createTree(); break;
        case 2: addNode(); break;
        case 3: inOrderTraversal(root); break;
        case 4: deleteNode(); break;
        case 5: {
            Node* min = findMin(root);
            if (min) printf("�������: %s (%d)\n", min->inf, min->n);
            else puts("������ ������");
            break;
        }
        case 6: {
            Node* max = findMax(root);
            if (max) printf("��������: %s (%d)\n", max->inf, max->n);
            else puts("������ ������");
            break;
        }
        case 7: printTree(root, 0); break;
        case 8: return;
        default: puts("�������� �����!");
        }
    } while (1);
}*/

Node* root = NULL;  

// ������� ��������� ������ 
void allocateMemory() 
{
    root = NULL;  
}

// ����������� ������� ������� ������
void clear(Node* r) 
{
    if (r) 
    {
        clear(r->left);   // ������� ������ ���������
        clear(r->right);  // ������� ������� ���������
        free(r->inf);     // ������������ ������ ������
        free(r);          // ������������ ������ ����
    }
}

// ������� ������� ������
void freeTree() 
{
    clear(root);  
}

// ������� �������� ����� ������
void createTree() 
{
    if (root != NULL) 
    {
        puts("������ ��� �������.");  
        return;
    }
    root = (Node*)malloc(sizeof(Node));           // �������� ������ ��� ������

    root->inf = (char*)malloc(N * sizeof(char));  // �������� ������ ��� ������

    printf("������� ���������� ��� �����: ");
    scanf_s("%s", root->inf,(unsigned)N);
    root->left = root->right = NULL;  
    root->n = 1;                                    // ������� ��������
}

// ������� ���������� ������ ����
void addNode() 
{
    if (!root) 
    {
        puts("������ �� �������.");
        return;
    }

    Node* temp = root;
    Node* parent = NULL;
    char* buf = (char*)malloc(N * sizeof(char));  // ����� ��� ����� ������
    printf("������� ����������: ");
    scanf_s("%s", buf, (unsigned)N);

    while (temp) 
    {
        parent = temp;
        int cmp = strcmp(buf, temp->inf);  // ��������� ������
        if (cmp == 0) 
        {
            temp->n++;  
            puts("���� ��� ����������, ��������� ���������� ��������.");
            free(buf);
            return;
        }
        else if (cmp < 0) 
        {
            temp = temp->left;                      // �����
        }
        else
        {
            temp = temp->right;                     // ������
        }
    }

    Node* newNode = (Node*)malloc(sizeof(Node));    // �������� ������ �����

    newNode->inf = buf;
    newNode->n = 1;
    newNode->left = newNode->right = NULL;

    if (strcmp(buf, parent->inf) < 0)
        parent->left = newNode;                     // �������� �����
    else
        parent->right = newNode;                    // �������� ������
}

// ����������� ������������ ����� ������(������������ ������� ������)
void inOrderTraversal(Node* r) 
{
    if (r) 
    {
        inOrderTraversal(r->left);  // ����� ������ ���������

        printf("%s (%d)\n", r->inf, r->n);  

        inOrderTraversal(r->right);  // ����� ������� ���������
    }
}

// ������� �������� ���� 
void deleteNode() 
{
    if (!root) 
    {
        puts("������ ������.");
        return;
    }

    char key[N];
    printf("������� ���������� ��� ��������: ");
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
        puts("���� �� ������.");
        return;
    }

    Node* target = *current;

    // ���� � ����� 
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

// ������� ������ ������������ �������� � ������
Node* findMin(Node* r) 
{
    if (!r) return NULL;
    while (r->left) r = r->left;
    return r;
}

// ������� ������ ������������� �������� � ������
Node* findMax(Node* r) 
{
    if (!r) return NULL;
    while (r->right) r = r->right;
    return r;
}

// ����������� ����� ������ � ���� ���������
void printTree(Node* r, int level) 
{
    if (r)
    {
        printTree(r->right, level + 1);             // ������
        for (int i = 0; i < level; i++)
            printf("    ");
        printf("%s (%d)\n", r->inf); 
        printTree(r->left, level + 1);              // �����
    }
}


