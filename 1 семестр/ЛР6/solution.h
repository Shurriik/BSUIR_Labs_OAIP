#ifndef SOLUTION_H
#define SOLUTION_H


char* input_string();														// Функция для ввода строки с динамическим выделением памяти


int validate_input(const char* input);										// Проверяет, является ли строка допустимой (не пустой и содержит хотя бы одно двоеточие)


const char* find_first_colon(const char* input);							// Возвращает указатель на первое двоеточие в строке


const char* find_second_colon(const char* first_colon);						// Возвращает указатель на второе двоеточие в строке


char* extract_colons(const char* first_colon, const char* second_colon);	// Функция для извлечения символов между первым и вторым двоеточиями


char* allocate_memory(unsigned int size);									// Функция для выделения памяти


void free_memory(void* memory);												// Функция для освобождения памяти


#endif // SOLUTION_H