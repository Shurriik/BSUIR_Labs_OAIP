#ifndef SOLUTION_H  
#define SOLUTION_H


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <Windows.h>


#define DATA_FILE "cubes_data.dat"                     // �������� ��������� ����� ��� �������


struct Cube                                             // ��������� ���������� ������ � ������                                        
{
    int edge;                                           // ����� ����� ����
    char color[10];                                     // ���� ���� 
    char material[10];                                  // �������� ���� 
};



int inputInt(int* value);

int isValidColor(const char* color);                    // ������� �������� ������������ ����� �����

int isValidMaterial(const char* material);              // ������� �������� ������������ ����� ���������

Cube* allocateCubes(int count);                         // ��������� ������ ��� ������ �����

void Input(char* buffer, int size);                     // ������� ��� ����� ������

void InputNumber(int* number, const char* prompt);      // ���� ����� 

void inputCubes(Cube* cubes, int count);                // ���� ������ � �����

void printColorCounts(Cube* cubes, int count);          // ����� ���������� ����� �� ������

void printWoodenCubesByEdge(Cube* cubes, int count);    // ����� ���������� ����� ��������� �������

void printMetalCubesByEdge(Cube* cubes, int count);     // ����� ������������� ����� ������ ��������� �������

void freeCubes(Cube* cubes);                            // ������������ ������

int saveCubesToBinFile(const Cube* cubes, int count);   // ���������� � �������� ����

Cube* loadCubesFromBinFile(int* count);                 // �������� �� ��������� �����

void menu();

int againf();

#endif