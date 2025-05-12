#ifndef SOLUTION_H
#define SOLUTION_H


char* input_string();														// ������� ��� ����� ������ � ������������ ���������� ������


int validate_input(const char* input);										// ���������, �������� �� ������ ���������� (�� ������ � �������� ���� �� ���� ���������)


const char* find_first_colon(const char* input);							// ���������� ��������� �� ������ ��������� � ������


const char* find_second_colon(const char* first_colon);						// ���������� ��������� �� ������ ��������� � ������


char* extract_colons(const char* first_colon, const char* second_colon);	// ������� ��� ���������� �������� ����� ������ � ������ �����������


char* allocate_memory(unsigned int size);									// ������� ��� ��������� ������


void free_memory(void* memory);												// ������� ��� ������������ ������


#endif // SOLUTION_H