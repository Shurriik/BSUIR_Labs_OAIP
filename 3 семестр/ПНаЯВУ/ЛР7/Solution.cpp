#include "Solution.h"
#include "Human.h"
#include "University_teacher.h"
#include "Commission_member.h"
#include "Teacher_commission_member.h"
#include "Algorithms.h"
#include "List.cpp"
#include "ExpInput.h"
#include "FileTxt.h"
#include "FileBin.h"
#include "FileTxt.cpp"
#include "FileBin.cpp"
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
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

void demoIteratorsAndAlgorithms()
{
    cout << "\nДемонстрация работы моего List, std::list и алгоритмов\n";

    Human h1("Ivan", "Ivanov", "Petrovich", 1990);
    Human h2("Petr", "Petrov", "Ivanovich", 1995);
    Human h3("Sergey", "Sidorov", "Alekseevich", 1992);

    List<Human*> customList;
    std::list<Human*> stlList;

    auto addSample = [&](const Human& h) {
        customList.addToEnd(h.clone());
        stlList.push_back(h.clone());
        };

    addSample(h1);
    addSample(h2);
    addSample(h3);

    cout << "\nМой List через вложенный итератор:\n";
    for (auto it = customList.begin(); it != customList.end(); ++it)
        (*it)->printInfo();

    Algorithms::sortByLastName(customList);
    cout << "\nОтсортировано по фамилии (Algorithms::sortByLastName):\n";
    for (auto it = customList.begin(); it != customList.end(); ++it)
        (*it)->printInfo();

    auto foundByYear = Algorithms::findByBirthYear(customList, 1992);
    if (foundByYear)
    {
        cout << "\nНайден в моём списке по году рождения 1992:\n";
        foundByYear->data->printInfo();
    }

    stlList.sort([](const Human* a, const Human* b) { return a->getLastName() < b->getLastName(); });
    cout << "\nstd::list после сортировки по фамилии:\n";
    for (Human* h : stlList) h->printInfo();

    auto stlFound = std::find_if(stlList.begin(), stlList.end(),
        [](const Human* h) { return h->getBirthYear() == 1995; });
    if (stlFound != stlList.end())
    {
        cout << "\nНайден в std::list по году рождения 1995:\n";
        (*stlFound)->printInfo();
    }

    // Очистка выделенной памяти
    for (auto it = customList.begin(); it != customList.end(); ++it) delete* it;
    customList.clear();

    for (Human* h : stlList) delete h;
    stlList.clear();
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
                // Сортировка с использованием внешнего алгоритма
                Algorithms::sortByLastName(*currentList);
                break;

            case 8:
                // Сортировка с использованием внешнего алгоритма
                Algorithms::sortByBirthYear(*currentList);
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

void workWithStdList()
{
    std::list<Human*> humanList;
    std::list<Human*> teacherList;
    std::list<Human*> commissionList;
    std::list<Human*> teacherCommissionList;

    bool continueListMode = true;

    while (continueListMode)
    {
        cout << "\nВЫБЕРИТЕ КЛАСС (std::list):\n";
        printLine(40);
        cout << "1. Human\n";
        cout << "2. UniversityTeacher\n";
        cout << "3. CommissionMember\n";
        cout << "4. TeacherCommissionMember\n";
        cout << "0. Назад\n";
        printLine(40);

        int classChoice = safeInputInt("Ваш выбор: ", 0, 4);
        if (classChoice == 0) break;

        std::list<Human*>* currentList = nullptr;
        string className;

        switch (classChoice)
        {
        case 1:
            currentList = &humanList;
            className = "Human";
            break;
        case 2:
            currentList = &teacherList;
            className = "UniversityTeacher";
            break;
        case 3:
            currentList = &commissionList;
            className = "CommissionMember";
            break;
        case 4:
            currentList = &teacherCommissionList;
            className = "TeacherCommissionMember";
            break;
        }

        bool continueWithClass = true;
        while (continueWithClass)
        {
            cout << "\nМЕНЮ РАБОТЫ С КЛАССОМ (std::list) " << className << ":\n";
            printLine(40);
            cout << "1. Добавить человека\n";
            cout << "2. Удалить по фамилии\n";
            cout << "3. Показать список\n";
            cout << "4. Поиск по фамилии\n";
            cout << "5. Поиск по году рождения\n";
            cout << "6. Сортировать по фамилии\n";
            cout << "7. Сортировать по году рождения\n";
            cout << "8. Очистить список\n";
            cout << "0. Назад\n";
            printLine(40);

            int action = safeInputInt("Ваш выбор: ", 0, 8);

            switch (action)
            {
            case 1: {
                Human* obj = nullptr;
                if (classChoice == 1) obj = new Human();
                if (classChoice == 2) obj = new UniversityTeacher();
                if (classChoice == 3) obj = new CommissionMember();
                if (classChoice == 4) obj = new TeacherCommissionMember();
                cin >> *obj;
                currentList->push_back(obj);
                break;
            }
            case 2: {
                string ln = safeInputString("Фамилия: ");
                bool removed = false;
                for (auto it = currentList->begin(); it != currentList->end(); ++it) {
                    if ((*it)->getLastName() == ln) {
                        delete* it;
                        currentList->erase(it);
                        removed = true;
                        break;
                    }
                }
                if (!removed) cout << "Не найдено.\n";
                break;
            }
            case 3: {
                if (currentList->empty()) {
                    cout << "Список пуст!\n";
                }
                else {
                    int idx = 0;
                    for (Human* h : *currentList) {
                        cout << idx++ << ": ";
                        h->printInfo();
                    }
                }
                break;
            }
            case 4: {
                string ln = safeInputString("Фамилия: ");
                bool found = false;
                for (auto it = currentList->begin(); it != currentList->end(); ++it) {
                    if ((*it)->getLastName() == ln) {
                        (*it)->printInfo();
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Не найдено.\n";
                break;
            }
            case 5: {
                int year = safeInputInt("Год рождения: ", 1900, 2025);
                bool found = false;
                for (auto it = currentList->begin(); it != currentList->end(); ++it) {
                    if ((*it)->getBirthYear() == year) {
                        (*it)->printInfo();
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Не найдено.\n";
                break;
            }
            case 6:
                currentList->sort([](const Human* a, const Human* b) {
                    return a->getLastName() < b->getLastName();
                    });
                break;
            case 7:
                currentList->sort([](const Human* a, const Human* b) {
                    return a->getBirthYear() < b->getBirthYear();
                    });
                break;
            case 8:
                for (Human* h : *currentList) delete h;
                currentList->clear();
                break;
            case 0:
                continueWithClass = false;
                break;
            }
        }
    }

    auto freeList = [](std::list<Human*>& lst) {
        for (Human* h : lst) delete h;
        lst.clear();
        };

    freeList(humanList);
    freeList(teacherList);
    freeList(commissionList);
    freeList(teacherCommissionList);
}


void displayMenu()
{
    cout << "\n";
    printLine(45);
    cout << "ГЛАВНОЕ МЕНЮ\n";
    printLine(45);
    cout << "1. Работа с моим List\n";
    cout << "2. Работа с std::list\n";
    cout << "0. Выход\n";
    printLine(45);
}

void runMenu()
{
    int choice;
    do {
        displayMenu();
        choice = safeInputInt("Ваш выбор: ", 0, 2);
        if (choice == 1) workWithList();
        else if (choice == 2) workWithStdList();
    } while (choice != 0);
}
