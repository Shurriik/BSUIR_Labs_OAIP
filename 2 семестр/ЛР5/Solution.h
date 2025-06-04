#ifndef SOLUTION_H
#define SOLUTION_H


#define N 50  
#define MAX_INPUT 100
#define MIN_INPUT 1


// ��������� ���� ��������� ������
typedef struct node 
{
    char* inf;          // �������������� ����
    int n;              // ���������� ��������
    struct node* left;  // ����� �������
    struct node* right; // ������ �������
} Node;

extern Node* root;

// ��������� �������
void allocateMemory(void);
void freeTree(void);
void createTree(void);
void addNode(void);
void inOrderTraversal(Node* r);
void deleteNode(void);
Node* findMin(Node* r);
Node* findMax(Node* r);
void printTree(Node* r, int level);
void menu(void);

int againf();


#endif
