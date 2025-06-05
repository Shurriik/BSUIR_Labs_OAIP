#ifndef SOLUTION_H  
#define SOLUTION_H


struct Cube                                             // ��������� Cube, ���������� ������ � ������                                        
{
    int edge;                                           // ����� ����� ����
    char color[10];                                     // ���� ���� (�� 9 ��������)
    char material[10];                                  // �������� ���� (�� 9 ��������)
};


int isValidColor(const char* color);                    // ������� �������� ������������ ����� �����

int isValidMaterial(const char* material);              // ������� �������� ������������ ����� ���������

Cube* allocateCubes(int count);                         // ��������� ������ ��� ������ �����

void Input(char* buffer, int size);                     // ������� ��� ����� ������

void InputNumber(int* number, const char* prompt);

void inputCubes(Cube* cubes, int count);                // ���� ������ � �����

void printColorCounts(Cube* cubes, int count);          // ����� ���������� ����� �� ������

void printWoodenCubesByEdge(Cube* cubes, int count);    // ����� ���������� ����� ��������� �������

void printMetalCubesByEdge(Cube* cubes, int count);     // ����� ������������� ����� ������ ��������� �������

void freeCubes(Cube* cubes);                            // ������������ ������

#endif

