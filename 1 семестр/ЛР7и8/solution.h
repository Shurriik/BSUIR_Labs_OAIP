#ifndef SOLUTION_H
#define SOLUTION_H


void remove_newline(char* str);										// ������� ��� �������� ������� ����� ������ �� ������

void process_string(const char* input, char** result, int* sum);	// ������� ��� ��������� ������ (������������ ���� � ������� ����� �����)

void concat_words(const char* input, char** result, int index);		// ����������� ������� ��� ������������ ����, ���������� ������ ����� � ������ ����� 4 ��������

void calculate_sum(const char* input, int* sum, int index);			// ����������� ������� ��� �������� ����� ����� � ������

int is_numeric(const char* str);									// ������� ��� ��������, �������� �� ������ �������� (�������� ������ �����)

int is_alpha(const char* str);										// ������� ��� ��������, �������� �� ������ ���������� (�������� ������ �����)


#endif