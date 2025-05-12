#ifndef SOLUTION_H
#define SOLUTION_H


int input_size(void);                                                                   // ������� ���� ���������� �������

void input_matrix(double** matrix, int n, int m);										// ���� �������

void print_matrix(double** matrix, int n, int m);										// ����� �������

void calculate_b(double** matrix, int n, int m, double x, int* b);						// ���������� ������� b

void print_b(int* b, int n);															// ����� ������� b

double** create_matrix(int n, int m);													// �������� �������

void free_matrix(double** matrix, int n);												// ������������ ������ �������


#endif SOLUTION_H