#include "Solution.h" 


const std::streamsize MAX_STREAM_SIZE = 1000;                                               // ������������ ������ ������ �����




RandomArrayGenerator::RandomArrayGenerator(double min, double max)                          // ����������� �� ������� 
    : gen(time(0)),  dist(min, max) {}  


std::vector<std::vector<double>> RandomArrayGenerator::generateArray(int rows, int cols)    // ����� ��������� ������� �� ���������� �������
{
    
    std::vector<std::vector<double>> array(rows, std::vector<double>(cols));                // ��������� ������ ��������� �������


    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++)  
        {
            array[i][j] = dist(gen);                                                        // ��������� ���������� �����
            
            array[i][j] = round(array[i][j] * 10) / 10.0;                                   // ���������� �� ������ ����� ����� �������
        }
    }

    return array;  
}



Array::Array(const std::vector<std::vector<double>>& InputArray)                            // ����������� 
{
    ValidDateInput(InputArray);                                                             // �������� ������������ ������� ������
    A = InputArray;                                                                         // ����������� �������� �������
    ProcessArray();                                                                         // ��������� �������
}


void Array::ValidDateInput(const std::vector<std::vector<double>>& InputArray)              // �������� ������� ������
{
    if (InputArray.empty())                                                                 // �������� �� ������ ������
    {
        throw std::invalid_argument("������ ����");  
    }

    if (InputArray.size() != 6)                                                             // �������� ���������� �����
    {
        throw std::invalid_argument("������������ ���������� ����� � �������");  
    }

    for (int i = 0; i < 6; i++)  
    {
        if (InputArray[i].size() != 7)                                                      // �������� ���������� ��������
        {
            throw std::invalid_argument("������������ ���������� �������� � �������");  
        }
    }
}


void Array::ProcessArray()                                                                  // ��������� �������
{
    countMinusOne = 0;                                                                      // ������� ��� ���������� ��������� �� ��������� -1

    X.resize(6, std::vector<double>(7, 0.0));                                               // ������������� ��������������� ������� ������

    for (int i = 0; i < 6; i++)  
    {
        for (int j = 0; j < 7; j++)  
        {
            if (A[i][j] > 0)  
            {
                X[i][j] = A[i][j] * cos(A[i][j]);  
            }
            else if (A[i][j] == 0) 
            {
                X[i][j] = 0;  
            }
            else if (A[i][j] < 0)  
            {
                X[i][j] = -1;  
                countMinusOne++;  
            }
        }
    }
}


void Array::PrintArray() const                                                              // ����� ��������� �������
{
    std::cout << "�������� ������ �(6,7):\n";  

    for (int i = 0; i < 6; i++)  
    {
        for (int j = 0; j < 7; j++)  
        {  
            std::cout << std::setw(10) << std::fixed << std::setprecision(2) << A[i][j] << " ";
        }
        std::cout << "\n";  
    }
    std::cout << "\n";  
}


void Array::PrintResultArray() const                                                        // ����� ��������������� �������
{
    std::cout << "�������������� ������ X(6,7):\n";  

    for (int i = 0; i < 6; i++)  
    {
        for (int j = 0; j < 7; j++) 
        {
            std::cout << std::setw(10) << std::fixed << std::setprecision(2) << X[i][j] << " ";
        }
        std::cout << "\n";  
    }
    std::cout << "\n";  
}


int Array::PrintCountMinusOne() const                                                       // ����� ��������� ���������� ��������� �� ��������� -1
{
    return countMinusOne;  
}


const std::vector<std::vector<double>>& Array::ResultArray() const                          // ����� ��������� ��������������� �������
{
    return X;  
}


std::vector<std::vector<double>> Array::InputArray()                                        // ����� ��� ����� ������� � ����������
{
    const int ROWS = 6;                                                                     // ���������� �����
    const int COLS = 7;                                                                     // ���������� ��������
    
    std::vector<std::vector<double>> array(ROWS, std::vector<double>(COLS, 0.0));           // ������ ������������ (6,7) ����������� ������

    std::cout << "������� �������� ������� A(6,7):\n";  

    for (int i = 0; i < ROWS; i++)  
    {
        std::cout << "������ " << (i + 1) << ": ";  

        for (int j = 0; j < COLS; j++)  
        {
            while (true)  
            {
                if (!(std::cin >> array[i][j]))  
                {
                    std::cin.clear(); 
                    std::cin.ignore(MAX_STREAM_SIZE, '\n'); 
                    std::cout << "������ �����! ����������, ������� �����: ";  
                    continue;  
                }
                break;  
            }
        }

        std::cin.ignore(MAX_STREAM_SIZE, '\n');  
    }

    return array;  
}


void displayMenu()                                                                        // ������� ����������� ����
{
    std::cout << "1. ������ ������ � ����������\n";  
    std::cout << "2. ������������ �������� ������\n";  
    std::cout << "3. ��������� ������ ���������� �������\n";  
    std::cout << "4. �����\n";  
    std::cout << "�������� �������: ";  
}

