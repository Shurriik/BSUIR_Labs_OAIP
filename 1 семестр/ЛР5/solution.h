#ifndef SOLUTION_H
#define SOLUTION_H


int input_size(void);                                                                   // Функция ввод параметром матрицы

void input_matrix(double** matrix, int n, int m);										// Ввод матрицы

void print_matrix(double** matrix, int n, int m);										// Вывод матрицы

void calculate_b(double** matrix, int n, int m, double x, int* b);						// Вычисление массива b

void print_b(int* b, int n);															// Вывод массива b

double** create_matrix(int n, int m);													// Создание матрицы

void free_matrix(double** matrix, int n);												// Освобождение памяти матрицы


#endif SOLUTION_H