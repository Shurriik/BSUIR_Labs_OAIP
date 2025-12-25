#include "Solution.h"
#include "Human.h"
#include "University_teacher.h"
#include "Commission_member.h"
#include "Teacher_commission_member.h"
#include "List.cpp"
#include "ExpInput.h"
#include "FileTxt.h"
#include "FileBin.h"
#include "FileTxt.cpp"
#include "FileBin.cpp"
#include "FileExp.h"
#include "FileExp.cpp"
#include <iostream>
#include <fstream>
#include <new>
using namespace std;

const string HUMAN_TXT = "Human.txt";
const string HUMAN_BIN = "Human.bin";

const string TEACHER_TXT = "UniversityTeacher.txt";
const string TEACHER_BIN = "UniversityTeacher.bin";

const string COMMISSION_TXT = "CommissionMember.txt";
const string COMMISSION_BIN = "CommissionMember.bin";

const string TEACHER_COMMISSION_TXT = "TeacherCommissionMember.txt";
const string TEACHER_COMMISSION_BIN = "TeacherCommissionMember.bin";

void printLine(int length)
{
    for (int i = 0; i < length; i++)
        cout << "=";
    cout << endl;
}

int safeInputInt(const string& prompt, int min, int max)
{
    ExpInput exp;
    cout << prompt;
    return exp.isNumber(cin, min, max);
}

string safeInputString(const string& prompt)
{
    ExpInput exp;
    cout << prompt;
    return exp.isString(cin);
}

bool fileExists(const string& filename)
{
    ifstream f(filename.c_str());
    return f.good();
}


void workWithList()
{
    List<Human*> humanList;
    List<Human*> teacherList;
    List<Human*> commissionList;
    List<Human*> teacherCommissionList;

    bool continueListMode = true;

    while (continueListMode)
    {
        cout << "\nВЫБЕРИТЕ КЛАСС:\n";
        printLine(40);
        cout << "1. Human\n";
        cout << "2. UniversityTeacher\n";
        cout << "3. CommissionMember\n";
        cout << "4. TeacherCommissionMember\n";
        cout << "0. Назад\n";
        printLine(40);

        int classChoice = safeInputInt("Ваш выбор: ", 0, 4);
        if (classChoice == 0) break;

        List<Human*>* currentList = nullptr;
        string className, txtFile, binFile;

        switch (classChoice)
        {
        case 1:
            currentList = &humanList;
            className = "Human";
            txtFile = HUMAN_TXT;
            binFile = HUMAN_BIN;
            break;
        case 2:
            currentList = &teacherList;
            className = "UniversityTeacher";
            txtFile = TEACHER_TXT;
            binFile = TEACHER_BIN;
            break;
        case 3:
            currentList = &commissionList;
            className = "CommissionMember";
            txtFile = COMMISSION_TXT;
            binFile = COMMISSION_BIN;
            break;
        case 4:
            currentList = &teacherCommissionList;
            className = "TeacherCommissionMember";
            txtFile = TEACHER_COMMISSION_TXT;
            binFile = TEACHER_COMMISSION_BIN;
            break;
        }

        bool continueWithClass = true;

        while (continueWithClass)
        {
            cout << "\nМЕНЮ РАБОТЫ С КЛАССОМ " << className << ":\n";
            printLine(40);
            cout << "1. Добавить человека\n";
            cout << "2. Удалить по индексу\n";
            cout << "3. Удалить по фамилии\n";
            cout << "4. Показать список\n";
            cout << "5. Поиск по фамилии\n";
            cout << "6. Поиск по году рождения\n";
            cout << "7. Сортировать по фамилии\n";
            cout << "8. Сортировать по году рождения\n";
            cout << "9. Очистить список\n";
            cout << "10. Сохранить в TXT\n";
            cout << "11. Загрузить из TXT\n";
            cout << "12. Сохранить в BIN\n";
            cout << "13. Загрузить из BIN\n";
            cout << "0. Назад\n";
            printLine(40);

            int action = safeInputInt("Ваш выбор: ", 0, 13);

            switch (action)
            {
            case 1: {
                Human* obj = nullptr;
                if (classChoice == 1) obj = new Human();
                if (classChoice == 2) obj = new UniversityTeacher();
                if (classChoice == 3) obj = new CommissionMember();
                if (classChoice == 4) obj = new TeacherCommissionMember();
                cin >> *obj;
                currentList->addToEnd(obj);
                break;
            }

            case 2: {
                int idx = safeInputInt("Индекс: ", 0, currentList->getSize() - 1);
                delete (*currentList)[idx];
                currentList->remove(idx);
                break;
            }

            case 3: {
                string ln = safeInputString("Фамилия: ");
                auto node = currentList->findByLastName(ln);
                if (node)
                {
                    for (int i = 0; i < currentList->getSize(); i++)
                        if ((*currentList)[i] == node->data)
                        {
                            delete (*currentList)[i];
                            currentList->remove(i);
                            break;
                        }
                }
                break;
            }

            case 4:
                cout << *currentList;
                break;

            case 5: {
                string ln = safeInputString("Фамилия: ");
                auto node = currentList->findByLastName(ln);
                if (node) node->data->printInfo();
                break;
            }

            case 6: {
                int year = safeInputInt("Год рождения: ", 1900, 2025);
                auto node = currentList->findByBirthYear(year);
                if (node) node->data->printInfo();
                break;
            }

            case 7:
                currentList->sortByLastName();
                break;

            case 8:
                currentList->sortByBirthYear();
                break;

            case 9:
                for (int i = 0; i < currentList->getSize(); i++)
                    delete (*currentList)[i];
                currentList->clear();
                break;

            case 10: {
                FileTxt<Human*> txt(txtFile);
                txt.writeLinkedList(*currentList);
                cout << "Сохранено в " << txtFile << endl;
                break;
            }

            case 11: {
                if (!fileExists(txtFile)) {
                    cout << "Файл не найден!\n";
                    break;
                }
                for (int i = 0; i < currentList->getSize(); i++)
                    delete (*currentList)[i];
                currentList->clear();
                FileTxt<Human*> txt(txtFile);
                txt.readLinkedList(*currentList);
                cout << "Загружено из " << txtFile << endl;
                break;
            }

            case 12: {
                FileBin<Human*> bin(binFile);
                bin.writeLinkedList(*currentList);
                cout << "Сохранено в " << binFile << endl;
                break;
            }

            case 13: {
                if (!fileExists(binFile)) {
                    cout << "Файл не найден!\n";
                    break;
                }
                for (int i = 0; i < currentList->getSize(); i++)
                    delete (*currentList)[i];
                currentList->clear();
                FileBin<Human*> bin(binFile);
                bin.readLinkedList(*currentList);
                cout << "Загружено из " << binFile << endl;
                break;
            }

            case 0:
                continueWithClass = false;
                break;
            }
        }
    }
}


void displayMenu()
{
    cout << "\n";
    printLine(45);
    cout << "ГЛАВНОЕ МЕНЮ\n";
    printLine(45);
    cout << "1. Работа с файлами \n";
    cout << "0. Выход\n";
    printLine(45);
}

void runMenu()
{
    int choice;
    do {
        displayMenu();
        choice = safeInputInt("Ваш выбор: ", 0, 1);
        if (choice == 1)
            workWithList();
    } while (choice != 0);
}
