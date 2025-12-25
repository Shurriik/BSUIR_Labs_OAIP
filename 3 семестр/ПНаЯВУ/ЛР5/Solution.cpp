#include "Solution.h"
#include "Human.h"
#include "University_teacher.h"
#include "Commission_member.h"
#include "Teacher_commission_member.h"
#include "List.cpp"
#include "ExpInput.h"
#include <stdexcept>
#include <new>
using namespace std;

Human** objects = nullptr;
int objectsCount = 0;
int objectsCapacity = 0;

// Функция для очистки буфера ввода 
void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Функция для ввода 
int safeInputInt(const string& prompt, int min, int max)
{
    ExpInput expInput;
    cout << prompt;
    return expInput.isNumber(cin, min, max);
}

// Функция для ввода строки
string safeInputString(const string& prompt)
{
    ExpInput expInput;
    cout << prompt;
    return expInput.isString(cin);
}

// Разделительная линия
void printLine(int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << "=";
    }
    cout << endl;
}




void workWithList()
{

    List<Human*> humanList;
    List<Human*> teacherList;
    List<Human*> commissionList;
    List<Human*> teacherCommissionList;

    bool continueWorking = true;

    while (continueWorking) {
        cout << "\nВЫБЕРИТЕ КЛАСС ДЛЯ РАБОТЫ:\n";
        printLine(40);
        cout << "1. Human\n";
        cout << "2. UniversityTeacher\n";
        cout << "3. CommissionMember\n";
        cout << "4. TeacherCommissionMember\n";
        cout << "0. Вернуться в главное меню\n";
        printLine(40);

        int classChoice = safeInputInt("Выберите класс: ", 0, 4);

        if (classChoice == 0) {
            try
            {
                int size = humanList.getSize();
                for (int i = 0; i < size; i++) {
                    try
                    {
                        Human* item = humanList[i];
                        if (item != nullptr) delete item;
                    }
                    catch (const out_of_range&) {}
                }
                size = teacherList.getSize();
                for (int i = 0; i < size; i++) {
                    try
                    {
                        Human* item = teacherList[i];
                        if (item != nullptr) delete item;
                    }
                    catch (const out_of_range&) {}
                }
                size = commissionList.getSize();
                for (int i = 0; i < size; i++) {
                    try
                    {
                        Human* item = commissionList[i];
                        if (item != nullptr) delete item;
                    }
                    catch (const out_of_range&) {}
                }
                size = teacherCommissionList.getSize();
                for (int i = 0; i < size; i++) {
                    try
                    {
                        Human* item = teacherCommissionList[i];
                        if (item != nullptr) delete item;
                    }
                    catch (const out_of_range&) {}
                }
            }
            catch (const ExpInput&) {}
            continueWorking = false;
            break;
        }

        List<Human*>* currentList = nullptr;
        string className = "";

        switch (classChoice) {
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
        while (continueWithClass) {
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
            cout << "0. Вернуться к выбору класса\n";
            printLine(40);

            int actionChoice = safeInputInt("Выберите действие: ", 0, 9);

            switch (actionChoice) {
            case 1: {
                Human* newPerson = nullptr;

                try
                {
                    switch (classChoice) {
                    case 1:
                        newPerson = new Human();
                        break;
                    case 2:
                        newPerson = new UniversityTeacher();
                        break;
                    case 3:
                        newPerson = new CommissionMember();
                        break;
                    case 4:
                        newPerson = new TeacherCommissionMember();
                        break;
                    default:
                        throw ExpInput(", неверный выбор класса", 23);
                    }
                }
                catch (const bad_alloc&)
                {
                    throw ExpInput(", ошибка выделения памяти для нового объекта", 24);
                }

                if (newPerson == nullptr)
                {
                    throw ExpInput(", не удалось создать объект", 25);
                }

                cout << "\nВведите данные:\n";
                try
                {
                    cin >> *newPerson;
                }
                catch (const ios_base::failure&)
                {
                    delete newPerson;
                    throw ExpInput(", ошибка ввода данных", 27);
                }

                cout << "\nВыберите позицию для добавления:\n";
                cout << "1. В начало списка\n";
                cout << "2. В конец списка\n";

                int positionChoice = safeInputInt("Ваш выбор (1-2): ", 1, 2);

                switch (positionChoice)
                {
                case 1:
                    currentList->addToStart(newPerson);
                    cout << "Объект добавлен в НАЧАЛО списка!" << endl;
                    break;
                case 2:
                    currentList->addToEnd(newPerson);
                    cout << "Объект добавлен в КОНЕЦ списка!" << endl;
                    break;
                }
                break;
            }
            case 2:
            {
                if (currentList->getSize() == 0) {
                    cout << "Список пуст!" << endl;
                    break;
                }
                cout << *currentList;
                try
                {
                    int index = safeInputInt("Введите индекс для удаления: ", 0, currentList->getSize() - 1);
                    Human* toDelete = nullptr;
                    try
                    {
                        toDelete = (*currentList)[index];
                    }
                    catch (const out_of_range&)
                    {
                        throw ExpInput(", индекс выходит за границы списка", 42);
                    }
                    if (toDelete == nullptr)
                    {
                        throw ExpInput(", элемент списка равен nullptr", 41);
                    }
                    currentList->remove(index);
                    delete toDelete;
                    cout << "Элемент удален!" << endl;
                }
                catch (const ExpInput&)
                {
                    cout << "Ошибка при удалении!" << endl;
                }
                break;
            }
            case 3:
            {
                if (currentList->getSize() == 0) {
                    cout << "Список пуст!" << endl;
                    break;
                }
                cout << *currentList;
                string lastName = safeInputString("Введите фамилию для удаления: ");
                ListNote<Human*>* found = currentList->findByLastName(lastName);
                if (found != nullptr) {
                    try
                    {
                        for (int i = 0; i < currentList->getSize(); i++) {
                            try
                            {
                                Human* item = (*currentList)[i];
                                if (item == found->data) {
                                    if (item != nullptr)
                                    {
                                        delete item;
                                    }
                                    currentList->remove(i);
                                    cout << "Элемент удален!" << endl;
                                    break;
                                }
                            }
                            catch (const out_of_range&)
                            {
                                throw ExpInput(", индекс выходит за границы списка", 42);
                            }
                        }
                    }
                    catch (const ExpInput&)
                    {
                        cout << "Ошибка при удалении!" << endl;
                    }
                }
                else
                {
                    cout << "Элемент не найден!" << endl;
                }
                break;
            }
            case 4:
                cout << "\nСОДЕРЖИМОЕ СПИСКА " << className << " (" << currentList->getSize() << " элементов):" << endl;
                cout << *currentList;
                break;
            case 5:
            {
                string lastName = safeInputString("Введите фамилию для поиска: ");
                ListNote<Human*>* found = currentList->findByLastName(lastName);
                if (found != nullptr) {
                    if (found->data == nullptr)
                    {
                        throw ExpInput(", найденный элемент равен nullptr", 41);
                    }
                    cout << "НАЙДЕН:" << endl;
                    printLine(40);
                    found->data->printInfo();
                    printLine(40);
                }
                else
                {
                    cout << "Не найден!" << endl;
                }
                break;
            }
            case 6:
            {
                int year = safeInputInt("Введите год рождения для поиска: ", 1900, 2023);
                ListNote<Human*>* found = currentList->findByBirthYear(year);
                if (found != nullptr) {
                    if (found->data == nullptr)
                    {
                        throw ExpInput(", найденный элемент равен nullptr", 41);
                    }
                    cout << "НАЙДЕН:" << endl;
                    printLine(40);
                    found->data->printInfo();
                    printLine(40);
                }
                else {
                    cout << "Не найден!" << endl;
                }
                break;
            }
            case 7:
                currentList->sortByLastName();
                cout << "Список отсортирован по фамилии!" << endl;
                cout << *currentList;
                break;
            case 8:
                currentList->sortByBirthYear();
                cout << "Список отсортирован по году рождения!" << endl;
                cout << *currentList;
                break;
            case 9:
                try
                {
                    int size = currentList->getSize();
                    for (int i = 0; i < size; i++) {
                        try
                        {
                            Human* item = (*currentList)[i];
                            if (item != nullptr)
                            {
                                delete item;
                            }
                        }
                        catch (const out_of_range&)
                        {
                            throw ExpInput(", индекс выходит за границы списка", 42);
                        }
                    }
                }
                catch (const ExpInput&)
                {
                    cout << "Ошибка при очистке списка!" << endl;
                }
                currentList->clear();
                cout << "Список очищен!" << endl;
                cout << *currentList;
                break;
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
    cout << "ГЛАВНОЕ МЕНЮ СИСТЕМЫ" << endl;
    printLine(45);
    cout << "1. Работа с исключениями" << endl;
    cout << "0. Выход из программы" << endl;
    printLine(45);
}


void runMenu()
{
    int choice = 0;

    do
    {
        displayMenu();
        choice = safeInputInt("Введите ваш выбор: ", 0, 1);

        switch (choice)
        {
        case 1:
            workWithList();
            break;
        case 0:
            cout << "\n";
            printLine(40);
            cout << "Выход из программы. До свидания!" << endl;
            printLine(40);
            break;
        }

    } while (choice != 0);
}