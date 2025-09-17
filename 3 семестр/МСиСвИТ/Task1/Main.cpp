#include "Solution.h"



int main() 
{

    setlocale(LC_ALL, "RUS");
    const std::streamsize MAX_STREAM_SIZE = 1000;
    
    try 
    {
        int choice;
        
        do 
        {
            
            displayMenu();

            while (!(std::cin >> choice) || choice < 1 || choice > 4)
            {
                std::cin.clear();
                std::cin.ignore(MAX_STREAM_SIZE, '\n');
                std::cout << "�������� �����! ������� 1, 2, 3 ��� 4: ";
            }

            if (choice == 4)
            {
                std::cout << "����� �� ���������...\n";
                break;
            }

            std::vector<std::vector<double>> inputArray;

            if (choice == 1)
            {
                inputArray = Array::InputArray();
            }
            else if (choice == 2)
            {
                inputArray = 
                {
                    {1.5, -2.3, 0.0, 4.7, -1.8, 3.2, 0.0},
                    {-3.1, 2.8, 1.0, -4.5, 0.0, 2.1, -6.7},
                    {0.0, 5.6, -7.2, 3.9, -2.4, 0.0, 4.8},
                    {6.3, -8.1, 0.0, 2.5, -3.6, 7.4, -1.2},
                    {-4.9, 0.0, 8.2, -5.3, 6.7, -2.8, 3.1},
                    {9.4, -6.5, 4.2, 0.0, -7.8, 5.9, -3.4}
                };
                std::cout << "������������ �������� ������.\n\n";
            }
            else if (choice == 3)
            {
                double min, max;
                std::cout << "������� ����������� ��������: ";
                std::cin >> min;
                std::cout << "������� ������������ ��������: ";
                std::cin >> max;

                // ������� ������ ���������� � ���������� ������
                RandomArrayGenerator generator(min, max);
                inputArray = generator.generateArray();
                std::cout << "������ �������� ���������� ������� �� " << min << " �� " << max << "\n\n";
            }

            Array processor(inputArray);

            std::cout << "\n";
            processor.PrintArray();
            processor.PrintResultArray();

            int minusOneCount = processor.PrintCountMinusOne();
            std::cout << "���������� ��������� �� ��������� -1: " << minusOneCount << "\n\n";

            std::cout << "������� Enter ��� �����������...";
            std::cin.ignore(MAX_STREAM_SIZE, '\n');
            std::cin.get();

        } while (true);
    }
    catch (const std::exception& e)
    {
        std::cerr << "������: " << e.what() << "\n";
        std::cout << "������� Enter ��� ������...";
        std::cin.ignore(MAX_STREAM_SIZE, '\n');
        std::cin.get();
        return 1;
    }

    return 0;
}
