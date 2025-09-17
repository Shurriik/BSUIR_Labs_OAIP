#ifndef SOLUTION_H  
#define SOLUTION_H  

#include <iostream>    
#include <vector>      
#include <cmath>       
#include <stdexcept>   
#include <iomanip>     
#include <limits>      
#include <random>      
#include <ctime> 
#include <locale.h>



class RandomArrayGenerator
{

private:

    std::mt19937 gen;                                                               // ��������� ��������� ����� 

    std::uniform_real_distribution<double> dist;                                    // ����������� ������������� 

public:
    
    RandomArrayGenerator(double min = -10.0, double max = 10.0);                    // ����������� � ����������� �� ���������
    
    std::vector<std::vector<double>> generateArray(int rows = 6, int cols = 7);     // ����� ��� ��������� ������� 
};


class Array
{
private:

    std::vector<std::vector<double>> A;                                             // �������� ������

    std::vector<std::vector<double>> X;                                             // �������������� ������

    int countMinusOne;                                                              // ������� ��������� �� ��������� -1

    void ValidDateInput(const std::vector<std::vector<double>>& InputArray);        // �������� ������� ������

    void ProcessArray();                                                            // ��������� ������� �� �������

public:

    Array(const std::vector<std::vector<double>>& InputArray);                      // �����������, ����������� ������� ������

    void PrintArray() const;                                                        // ����� ��������� �������

    void PrintResultArray() const;                                                  // ����� ��������������� �������

    int PrintCountMinusOne() const;                                                 // ��������� ���������� ��������� -1

    const std::vector<std::vector<double>>& ResultArray() const;                    // ��������� ��������������� �������

    static std::vector<std::vector<double>> InputArray();                           // ����������� ����� ��� ����� �������
};

void displayMenu();                                                                 // ������� ����

#endif  