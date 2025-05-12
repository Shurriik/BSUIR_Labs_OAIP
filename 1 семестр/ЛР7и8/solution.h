#ifndef SOLUTION_H
#define SOLUTION_H


void remove_newline(char* str);										// Функция для удаления символа новой строки из строки

void process_string(const char* input, char** result, int* sum);	// Функция для обработки строки (конкатенация слов и подсчёт суммы чисел)

void concat_words(const char* input, char** result, int index);		// Рекурсивная функция для конкатенации слов, содержащих только буквы и длиной более 4 символов

void calculate_sum(const char* input, int* sum, int index);			// Рекурсивная функция для подсчёта суммы чисел в строке

int is_numeric(const char* str);									// Функция для проверки, является ли строка числовой (содержит только цифры)

int is_alpha(const char* str);										// Функция для проверки, является ли строка алфавитной (содержит только буквы)


#endif