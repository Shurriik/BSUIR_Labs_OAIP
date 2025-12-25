#include "Student.h"
#include "FileBin.h"
#include "Exp.h"
#include "ExpInput.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <locale.h>

void displayMenu() {
    std::cout << "\nМеню:\n";
    std::cout << "1. Создать студентов\n";
    std::cout << "2. Сохранить в файл\n";
    std::cout << "3. Загрузить из файла\n";
    std::cout << "4. Добавить нового студента в файл\n";
    std::cout << "5. Показать статистику\n";
    std::cout << "6. Выход\n";
    std::cout << "Выберите опцию: ";
}


Student students[Student::MAX_STUDENTS];
int studentsCount = 0;
bool hasUnsavedChanges = false;

void createStudents() {
    try 
    {
        std::cout << "\nСоздание студентов\n";

        std::cout << "Количество студентов (1-" << Student::MAX_STUDENTS << "): ";
        std::string countStr;
        std::getline(std::cin, countStr);

        if (countStr.empty()) 
        {
            throw InputException("Ввод не может быть пустым");
        }

        for (char c : countStr) 
        {
            if (!std::isdigit(c)) 
            {
                throw InputException("Должно быть число");
            }
        }

        int count = std::stoi(countStr);

        if (count < 1 || count > Student::MAX_STUDENTS) 
        {
            throw InputException("От 1 до " + std::to_string(Student::MAX_STUDENTS));
        }

        studentsCount = 0;
        for (int i = 0; i < count; ++i) 
        {
            std::cout << "\nСтудент " << (i + 1) << ":\n";

            bool validInput = false;
            while (!validInput) 
            {
                try 
                {
                    std::cin >> students[studentsCount];
                    studentsCount++;
                    validInput = true;
                }
                catch (const InputException& e) 
                {
                    std::cerr << "Ошибка: " << e.what() << std::endl;
                    std::cout << "Введите заново:\n";
                }
            }
        }

        hasUnsavedChanges = true;
        std::cout << "\nСоздано студентов: " << studentsCount << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void saveToFile() 
{
    try
    {
        if (studentsCount == 0)
        {
            std::cout << "\nНет данных для сохранения. Сначала создайте студентов.\n";
            return;
        }

        std::cout << "\nСохранение в файл\n";

        std::string filename;
        std::cout << "Имя файла: ";
        std::getline(std::cin, filename);

        if (filename.empty()) 
        {
            throw InputException("Имя файла не может быть пустым");
        }

        FileBin file(filename);
        file.write(students, studentsCount);

        hasUnsavedChanges = false;
        std::cout << "Сохранено в файл: " << filename << std::endl;
        std::cout << "Сохранено студентов: " << studentsCount << std::endl;

    }
    catch (const std::exception& e) 
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void loadFromFile() 
{
    try 
    {
        std::cout << "\nЗагрузка из файла\n";

        std::string filename;
        std::cout << "Имя файла: ";
        std::getline(std::cin, filename);

        if (filename.empty()) 
        {
            throw InputException("Имя файла не может быть пустым");
        }

        FileBin file(filename);
        studentsCount = file.read(students);

        std::cout << "\nЗагружено из файла: " << filename << std::endl;
        std::cout << "Загружено студентов: " << studentsCount << std::endl;

        // Показать загруженных студентов
        if (studentsCount > 0) 
        {
            std::cout << "\nЗагруженные студенты:\n";
            for (int i = 0; i < studentsCount; ++i) 
            {
                std::cout << (i + 1) << ". " << students[i] << std::endl;
            }
        }

        hasUnsavedChanges = false;

    }
    catch (const FileException& e) 
    {
        std::cerr << "Ошибка файла: " << e.what() << std::endl;
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void createSuccessfulFile()
{
    try
    {
        std::cout << "\nСоздание файла успешных студентов\n";

        if (studentsCount == 0)
        {
            std::cout << "Нет данных. Сначала загрузите или создайте студентов.\n";
            return;
        }

        std::string outputFile;
        std::cout << "Имя файла для успешных студентов: ";
        std::getline(std::cin, outputFile);

        if (outputFile.empty()) 
        {
            throw InputException("Имя файла не может быть пустым");
        }


        std::string tempFile = "temp_successful_check.bin";
        FileBin temp(tempFile);
        temp.write(students, studentsCount);

        FileBin input(tempFile);
        input.createSuccessfulStudentsFile(outputFile);

        remove(tempFile.c_str());

        std::cout << "Файл успешных студентов создан: " << outputFile << std::endl;

    }
    catch (const std::exception& e) 
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void addStudentToFile() 
{
    try 
    {
        std::cout << "\nДобавление студента\n";

        if (studentsCount >= Student::MAX_STUDENTS) 
        {
            throw FileException("Достигнут максимум студентов: " + std::to_string(Student::MAX_STUDENTS));
        }

        std::cout << "Новый студент:\n";

        bool validInput = false;
        while (!validInput) 
        {
            try
            {
                std::cin >> students[studentsCount];
                studentsCount++;
                validInput = true;
                hasUnsavedChanges = true;
            }
            catch (const InputException& e) 
            {
                std::cerr << "Ошибка: " << e.what() << std::endl;
                std::cout << "Введите заново:\n";
            }
        }

        std::cout << "Студент добавлен. Всего студентов: " << studentsCount << std::endl;

    }
    catch (const FileException& e) 
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void displayStatistics() 
{
    try 
    {
        std::cout << "\nСтатистика\n";

        if (studentsCount == 0) 
        {
            std::cout << "Нет данных для статистики.\n";
            return;
        }

        int successful = 0;
        int failed = 0;
        double totalAverage = 0.0;
        double highestAverage = 0.0;
        double lowestAverage = 10.0;
        std::string bestStudent, worstStudent;

        for (int i = 0; i < studentsCount; ++i) 
        {
            double avg = students[i].getAverageGrade();

            if (students[i].hasPassed()) 
            {
                successful++;
            }
            else 
            {
                failed++;
            }

            totalAverage += avg;

            if (avg > highestAverage) 
            {
                highestAverage = avg;
                bestStudent = students[i].getLastName() + " " + students[i].getFirstName();
            }

            if (avg < lowestAverage) 
            {
                lowestAverage = avg;
                worstStudent = students[i].getLastName() + " " + students[i].getFirstName();
            }
        }

        std::cout << "Всего студентов: " << studentsCount << std::endl;
        std::cout << "Успешно сдали: " << successful << " ("
            << std::fixed << std::setprecision(1) << (successful * 100.0 / studentsCount) << "%)" << std::endl;
        std::cout << "Не сдали: " << failed << " ("
            << std::fixed << std::setprecision(1) << (failed * 100.0 / studentsCount) << "%)" << std::endl;
        std::cout << "Общий средний балл: " << std::fixed << std::setprecision(2)
            << (totalAverage / studentsCount) << std::endl;

        if (studentsCount > 1) {
            std::cout << "Лучший студент: " << bestStudent << " ("
                << std::fixed << std::setprecision(2) << highestAverage << ")" << std::endl;
            std::cout << "Худший студент: " << worstStudent << " ("
                << std::fixed << std::setprecision(2) << lowestAverage << ")" << std::endl;
        }

        // Дополнительная опция для создания файла успешных
        if (successful > 0) {
            std::cout << "\nСоздать файл успешных студентов? (y/n): ";
            std::string answer;
            std::getline(std::cin, answer);

            if (answer == "y" || answer == "Y") {
                createSuccessfulFile();
            }
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void checkUnsavedChanges() 
{
    if (hasUnsavedChanges)
    {
        std::cout << "\nЕсть несохраненные изменения. Сохранить перед выходом? (y/n): ";
        std::string answer;
        std::getline(std::cin, answer);

        if (answer == "y" || answer == "Y") {
            saveToFile();
        }
    }
}

int main() 
{
    setlocale(LC_ALL, "RUS");
    int choice;
    bool running = true;

    std::cout << "=== Управление данными студентов ===\n";
    std::cout << "Максимум студентов: " << Student::MAX_STUDENTS << std::endl;
    std::cout << "Максимум оценок на студента: " << Student::MAX_GRADES << std::endl;
    std::cout << "Шкала оценок: 0-10 баллов\n";

    while (running) {
        try {
            displayMenu();

            std::string input;
            std::getline(std::cin, input);

            if (std::cin.fail()) {
                std::cin.clear();
                throw MenuException("Ошибка ввода");
            }

            if (input.empty()) {
                throw MenuException("Ввод не может быть пустым");
            }

            for (char c : input) {
                if (!std::isdigit(c)) {
                    throw MenuException("Должно быть число");
                }
            }

            choice = std::stoi(input);

            switch (choice) {
            case 1:
                createStudents();
                break;
            case 2:
                saveToFile();
                break;
            case 3:
                loadFromFile();
                break;
            case 4:
                addStudentToFile();
                break;
            case 5:
                displayStatistics();
                break;
            case 6:
                checkUnsavedChanges();
                running = false;
                std::cout << "\nВыход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Введите число от 1 до 6.\n";
            }

        }
        catch (const MenuException& e) {
            std::cerr << "Ошибка меню: " << e.what() << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }
    }

    return 0;
}