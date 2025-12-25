#include "Solution.h"
#include "Human.h"
#include "University_teacher.h"
#include "Commission_member.h"
#include "Teacher_commission_member.h"
#include "List.cpp"
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
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            if (value >= min && value <= max)
            {
                clearInputBuffer();
                return value;
            }
            else
            {
                cout << "Ошибка: Значение должно быть между " << min << " и " << max << endl;
            }
        }
        else
        {
            cout << "Ошибка: Пожалуйста, введите корректное число" << endl;
            clearInputBuffer();
        }
    }
}

// Функция для ввода строки
string safeInputString(const string& prompt)
{
    string value;
    cout << prompt;
    clearInputBuffer();
    getline(cin, value);
    return value;
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

// Функция работы класса Human с использованием перегруженных операторов
void demonstrateHuman()
{
    cout << "\n";
    printLine(50);
    cout << "КЛАСС HUMAN" << endl;
    printLine(50);

    Human person("Иван", "Иванов", "Иванович", 1985);

    cout << "\nТАБЛИЦА: Класс Human" << endl;
    printLine(70);
    cout << "Поле              | Значение" << endl;
    printLine(70);

    // Используем перегруженный оператор вывода для демонстрации
    cout << "Объект: " << endl;
    cout << person;

    cout << "\nДетальная информация:" << endl;
    printLine(40);
    person.printInfo();
    printLine(70);
}

// Функция работы класса UniversityTeacher с использованием перегруженных операторов
void demonstrateUniversityTeacher()
{
    cout << "\n";
    printLine(60);
    cout << "КЛАСС UNIVERSITYTEACHER" << endl;
    printLine(60);

    UniversityTeacher teacher("Анна", "Петрова", "Сергеевна", 1975, "Профессор", "Доктор наук", "Информатика");

    teacher.addScientificWork("Алгоритмы машинного обучения");
    teacher.addScientificWork("Оптимизация нейронных сетей");
    teacher.addScientificWork("Этика искусственного интеллекта");

    cout << "\nТАБЛИЦА: Класс UniversityTeacher" << endl;
    printLine(80);
    cout << "Поле              | Значение" << endl;
    printLine(80);

    // Используем перегруженный оператор вывода
    cout << "Объект в табличном формате:" << endl;
    cout << teacher;

    cout << "\nДетальная информация:" << endl;
    printLine(40);
    teacher.printInfo();
    printLine(80);
}

// Функция демонстрации работы класса CommissionMember с использованием перегруженных операторов
void demonstrateCommissionMember()
{
    cout << "\n";
    printLine(55);
    cout << "КЛАСС COMMISSIONMEMBER" << endl;
    printLine(55);

    CommissionMember member("Петр", "Сидоров", "Николаевич", 1968, "Комиссия по качеству образования", 2015, "СЕРТ-12345");

    member.addAutobiographyEntry("Окончил университет в 1990 году");
    member.addAutobiographyEntry("Начал преподавательскую карьеру в 1992 году");
    member.addAutobiographyEntry("Вступил в комиссию в 2015 году");

    cout << "\nТАБЛИЦА: Класс CommissionMember" << endl;
    printLine(80);
    cout << "Поле              | Значение" << endl;
    printLine(80);

    // Используем перегруженный оператор вывода
    cout << "Объект в табличном формате:" << endl;
    cout << member;

    cout << "\nДетальная информация:" << endl;
    printLine(40);
    member.printInfo();
    printLine(80);
}

// Функция работы класса TeacherCommissionMember с использованием перегруженных операторов
void demonstrateTeacherCommissionMember()
{
    cout << "\n";
    printLine(65);
    cout << "КЛАСС TEACHERCOMMISSIONMEMBER" << endl;
    printLine(65);

    TeacherCommissionMember tcm("Мария", "Козлова", "Александровна", 1972, "Доцент", "Кандидат наук", "Математика", "Комиссия по академическим стандартам", 2018, "СЕРТ-67890");

    tcm.addScientificWork("Исследование по высшей математике");
    tcm.addScientificWork("Математическое моделирование");
    tcm.addAutobiographyEntry("Кандидат наук по математике, 2000 год");
    tcm.addAutobiographyEntry("Профессор университета с 2002 года");
    tcm.addCommissionWork("Разработка учебных программ");
    tcm.addCommissionWork("Стандарты экзаменов");

    cout << "\nТАБЛИЦА: Класс TeacherCommissionMember" << endl;
    printLine(90);
    cout << "Поле              | Значение" << endl;
    printLine(90);

    // Используем перегруженный оператор вывода
    cout << "Объект в табличном формате:" << endl;
    cout << tcm;

    cout << "\nДетальная информация:" << endl;
    printLine(40);
    tcm.printInfo();
    printLine(90);
}

// Функция полиморфизма с использованием перегруженных операторов
void demonstratePolymorphism()
{
    cout << "\n";
    printLine(50);
    cout << "ПОЛИМОРФИЗМ" << endl;
    printLine(50);

    const int peopleCount = 4;
    Human* people[peopleCount];

    people[0] = new Human("Дмитрий", "Лебедев", "Владимирович", 1990);
    people[1] = new UniversityTeacher("Елена", "Гарсия", "Луисовна", 1980, "Преподаватель", "Магистр", "Физика");
    people[2] = new CommissionMember("Федор", "Миронов", "Иванович", 1975, "Этика", 2020, "СЕРТ-11111");
    people[3] = new TeacherCommissionMember("Галина", "Ткачева", "Павловна", 1965, "Профессор", "Доктор наук", "Химия", "Научная комиссия", 2010, "СЕРТ-22222");

    cout << "\nСВОДНАЯ ТАБЛИЦА ОБЪЕКТОВ (полиморфизм)" << endl;
    printLine(130);

    cout << left
        << setw(3) << "ID" << "| "
        << setw(15) << "Фамилия" << "| "
        << setw(15) << "Имя" << "| "
        << setw(15) << "Отчество" << "| "
        << setw(4) << "Год" << "| "
        << setw(15) << "Должность" << "| "
        << setw(15) << "Степень" << "| "
        << setw(15) << "Комиссия" << "| "
        << setw(6) << "Научка" << endl;
    cout << "---+----------------+----------------+----------------+-----+----------------+----------------+----------------+-----------------+\n";

    for (int i = 0; i < peopleCount; i++)
    {
        cout << right << setw(2) << (i + 1) << " | " << left;

        // Используем перегруженный оператор вывода для каждого объекта
        if (dynamic_cast<TeacherCommissionMember*>(people[i]))
        {
            TeacherCommissionMember* tcm = dynamic_cast<TeacherCommissionMember*>(people[i]);
            cout << *tcm;
        }
        else if (dynamic_cast<UniversityTeacher*>(people[i]))
        {
            UniversityTeacher* ut = dynamic_cast<UniversityTeacher*>(people[i]);
            cout << *ut;
        }
        else if (dynamic_cast<CommissionMember*>(people[i]))
        {
            CommissionMember* cm = dynamic_cast<CommissionMember*>(people[i]);
            cout << *cm;
        }
        else
        {
            cout << *people[i];
        }
        cout << endl;
    }
    printLine(130);

    cout << "\nДЕТАЛЬНАЯ ИНФОРМАЦИЯ ОБО ВСЕХ ОБЪЕКТАХ:" << endl;
    printLine(60);
    for (int i = 0; i < peopleCount; i++)
    {
        cout << "\nОбъект " << (i + 1) << ":" << endl;
        printLine(40);
        people[i]->printInfo();
    }
    printLine(60);

    // Очистка памяти
    for (int i = 0; i < peopleCount; i++)
    {
        delete people[i];
    }
}

// Функция для вывода таблицы с информацией об объектах с использованием перегруженных операторов
void displayObjectsTable(Human** objects, int count)
{
    if (count == 0)
    {
        cout << "Нет объектов для отображения." << endl;
        return;
    }

    cout << "\n";
    printLine(160);
    cout << "ТАБЛИЦА ОБЪЕКТОВ В СИСТЕМЕ (" << count << " записей)" << endl;
    printLine(160);

    // Заголовок таблицы
    cout << left
        << setw(3) << "ID" << "| "
        << setw(15) << "Фамилия" << "| "
        << setw(15) << "Имя" << "| "
        << setw(15) << "Отчество" << "| "
        << setw(5) << "Год" << "| "
        << setw(15) << "Должность" << "| "
        << setw(15) << "Степень" << "| "
        << setw(15) << "Комиссия" << "| "
        << setw(6) << "Науч" << "| "
        << setw(6) << "Зап" << "| "
        << setw(6) << "Ком" << endl;
    cout << "---+----------------+----------------+----------------+-------+-----------------+-----------------+-----------------+-------+-------+-------\n";

    for (int i = 0; i < count; i++)
    {
        cout << right << setw(2) << (i + 1) << " | " << left;

        // Используем перегруженный оператор вывода для каждого объекта
        if (dynamic_cast<TeacherCommissionMember*>(objects[i]))
        {
            TeacherCommissionMember* tcm = dynamic_cast<TeacherCommissionMember*>(objects[i]);
            cout << *tcm;
        }
        else if (dynamic_cast<UniversityTeacher*>(objects[i]))
        {
            UniversityTeacher* ut = dynamic_cast<UniversityTeacher*>(objects[i]);
            cout << *ut;
        }
        else if (dynamic_cast<CommissionMember*>(objects[i]))
        {
            CommissionMember* cm = dynamic_cast<CommissionMember*>(objects[i]);
            cout << *cm;
        }
        else
        {
            cout << *objects[i];
        }
        cout << endl;
    }
    printLine(160);
}

// Функция добавления нового человека в список с использованием перегруженных операторов
void addNewPerson(Human**& objects, int& count, int& capacity)
{
    if (count >= capacity)
    {
        int newCapacity = capacity * 2 + 1;
        Human** newObjects = new Human * [newCapacity];
        for (int i = 0; i < count; i++)
        {
            newObjects[i] = objects[i];
        }
        delete[] objects;
        objects = newObjects;
        capacity = newCapacity;
    }

    cout << "\n";
    printLine(40);
    cout << "ДОБАВЛЕНИЕ НОВОГО ЧЕЛОВЕКА" << endl;
    printLine(40);
    cout << "Выберите класс:\n";
    cout << "1. Human\n";
    cout << "2. UniversityTeacher\n";
    cout << "3. CommissionMember\n";
    cout << "4. TeacherCommissionMember\n";

    int choice = safeInputInt("Ваш выбор (1-4): ", 1, 4);

    try
    {
        Human* newPerson = nullptr;

        switch (choice)
        {
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
        }

        cout << "\nВведите данные:\n";
        // Используем перегруженный оператор ввода
        cin >> *newPerson;
        objects[count++] = newPerson;

        cout << "\n";
        printLine(40);
        cout << "Объект класса успешно добавлен!" << endl;
        printLine(40);

        // Показываем добавленный объект с использованием перегруженного оператора
        cout << "\nДОБАВЛЕННЫЙ ОБЪЕКТ:" << endl;
        printLine(60);
        cout << "Табличный формат:" << endl;
        cout << *newPerson;
        cout << "\nДетальная информация:" << endl;
        newPerson->printInfo();
        printLine(60);
    }
    catch (const exception& e)
    {
        cout << "Ошибка при добавлении: " << e.what() << endl;
    }
}

// Функция редактирования существующего человека в списке с использованием перегруженных операторов
void editPerson(Human** objects, int count)
{
    if (count == 0)
    {
        cout << "Список людей пуст!\n";
        return;
    }

    displayObjectsTable(objects, count);
    int id = safeInputInt("Введите ID объекта для редактирования: ", 1, count);
    int index = id - 1;

    cout << "\nТЕКУЩАЯ ИНФОРМАЦИЯ:\n";
    printLine(60);
    cout << "Табличный формат:" << endl;
    cout << *objects[index];
    cout << "\nДетальная информация:" << endl;
    objects[index]->printInfo();
    printLine(60);

    cout << "\nХотите изменить этот объект? (y/n): ";
    char choice;
    cin >> choice;
    clearInputBuffer();

    if (choice == 'y' || choice == 'Y')
    {
        try
        {
            cout << "\nВведите новые данные:\n";
            // Используем перегруженный оператор ввода
            cin >> *objects[index];

            cout << "\n";
            printLine(40);
            cout << "Данные успешно обновлены!" << endl;
            printLine(40);

            // Показываем обновленный объект с использованием перегруженного оператора
            cout << "\nОБНОВЛЕННЫЙ ОБЪЕКТ:" << endl;
            printLine(60);
            cout << "Табличный формат:" << endl;
            cout << *objects[index];
            cout << "\nДетальная информация:" << endl;
            objects[index]->printInfo();
            printLine(60);
        }
        catch (const exception& e)
        {
            cout << "Ошибка при редактировании: " << e.what() << endl;
        }
    }
}

// Функция удаления человека из списка
void deletePerson(Human**& objects, int& count)
{
    if (count == 0)
    {
        cout << "Список людей пуст!\n";
        return;
    }

    displayObjectsTable(objects, count);
    int id = safeInputInt("Введите ID объекта для удаления: ", 1, count);
    int index = id - 1;

    cout << "\nУДАЛЕНИЕ ОБЪЕКТА:\n";
    printLine(60);
    cout << "Табличный формат:" << endl;
    cout << *objects[index];
    cout << "\nДетальная информация:" << endl;
    objects[index]->printInfo();
    printLine(60);

    cout << "\nПодтвердите удаление (y/n): ";
    char choice;
    cin >> choice;
    clearInputBuffer();

    if (choice == 'y' || choice == 'Y')
    {
        delete objects[index];
        for (int i = index; i < count - 1; i++)
        {
            objects[i] = objects[i + 1];
        }
        count--;

        cout << "\n";
        printLine(40);
        cout << "Объект успешно удален!" << endl;
        printLine(40);
    }
}

// Функция показа информации о человеке с использованием перегруженных операторов
void showDetailedInfo(Human** objects, int count)
{
    if (count == 0)
    {
        cout << "Список людей пуст!\n";
        return;
    }

    displayObjectsTable(objects, count);
    int id = safeInputInt("Введите ID объекта для просмотра подробной информации: ", 1, count);
    int index = id - 1;

    cout << "\n";
    printLine(60);
    cout << "ПОДРОБНАЯ ИНФОРМАЦИЯ О ЗАПИСИ " << id << endl;
    printLine(60);

    cout << "Табличный формат:" << endl;
    cout << *objects[index];
    cout << "\nДетальная информация:" << endl;
    objects[index]->printInfo();
    printLine(60);
}

// Функция работы с людьми с использованием перегруженных операторов
void workWithPeople()
{
    cout << "\n";
    printLine(50);
    cout << "РАБОТА С ОБЪЕКТАМИ" << endl;
    printLine(50);

    Human** people = new Human * [10];
    int peopleCount = 0;
    int peopleCapacity = 10;

    // Примеры изначального заполнения 
    people[peopleCount++] = new Human("Иван", "Иванов", "Иванович", 1985);
    people[peopleCount++] = new UniversityTeacher("Анна", "Петрова", "Сергеевна", 1975, "Профессор", "Доктор наук", "Информатика");

    bool continueWorking = true;
    while (continueWorking)
    {
        cout << "\nОСНОВНОЕ МЕНЮ УПРАВЛЕНИЯ:\n";
        printLine(40);
        cout << "1. Показать все объекты\n";
        cout << "2. Добавить новый объект\n";
        cout << "3. Редактировать объект\n";
        cout << "4. Удалить объект\n";
        cout << "5. Показать подробную информацию\n";
        cout << "0. Вернуться в главное меню\n";
        printLine(40);

        int choice = safeInputInt("Выберите действие: ", 0, 5);

        switch (choice)
        {
        case 1:
            displayObjectsTable(people, peopleCount);
            break;
        case 2:
            addNewPerson(people, peopleCount, peopleCapacity);
            break;
        case 3:
            editPerson(people, peopleCount);
            break;
        case 4:
            deletePerson(people, peopleCount);
            break;
        case 5:
            showDetailedInfo(people, peopleCount);
            break;
        case 0:
            continueWorking = false;
            break;
        }
    }

    for (int i = 0; i < peopleCount; i++)
    {
        delete people[i];
    }
    delete[] people;
}

// Обновляем функцию displayMenu()
void displayMenu()
{
    cout << "\n";
    printLine(45);
    cout << "ГЛАВНОЕ МЕНЮ СИСТЕМЫ" << endl;
    printLine(45);
    //cout << "1. Класс Human" << endl;
    //cout << "2. Класс UniversityTeacher" << endl;
    //cout << "3. Класс CommissionMember" << endl;
    //cout << "4. Класс TeacherCommissionMember" << endl;
    //cout << "5. Полиморфизм" << endl;
    cout << "1. Работа с объектами" << endl;
    //cout << "7. Демонстрация списка" << endl;
    cout << "2. Работа со списком" << endl;
    cout << "0. Выход из программы" << endl;
    printLine(45);
}

// Функция меню 
// Обновляем функцию runMenu()
void runMenu()
{
    int choice = 0;

    do
    {
        displayMenu();
        choice = safeInputInt("Введите ваш выбор: ", 0, 8);

        switch (choice)
        {
        //case 1:
        //    demonstrateHuman();
        //    break;
        //case 2:
        //    demonstrateUniversityTeacher();
        //    break;
        //case 3:
        //    demonstrateCommissionMember();
        //    break;
        //case 4:
        //    demonstrateTeacherCommissionMember();
        //    break;
        //case 5:
        //    demonstratePolymorphism();
        //    break;
        case 1:
            workWithPeople();
            break;
        /*case 7:
            demonstrateList();
            break;*/
        case 2:
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

// Функция демонстрации работы со списком
void demonstrateList()
{
    cout << "\n";
    printLine(50);
    cout << "РАБОТА СО СПИСКОМ (List)" << endl;
    printLine(50);

    List<Human*> peopleList;

    // Добавляем несколько объектов в список разными способами
    cout << "\n1. ДОБАВЛЕНИЕ ЭЛЕМЕНТОВ В СПИСОК:" << endl;
    printLine(50);

    cout << "Добавление в конец:" << endl;
    peopleList.addToEnd(new Human("Иван", "Иванов", "Иванович", 1985));
    cout << peopleList;

    cout << "Добавление в начало:" << endl;
    peopleList.addToStart(new UniversityTeacher("Анна", "Петрова", "Сергеевна", 1975, "Профессор", "Доктор наук", "Информатика"));
    cout << peopleList;


    cout << "Добавление в конец:" << endl;
    peopleList.addToEnd(new TeacherCommissionMember("Мария", "Козлова", "Александровна", 1972, "Доцент", "Кандидат наук", "Математика", "Академическая", 2018, "СЕРТ-67890"));
    cout << peopleList;

    // Демонстрация поиска по фамилии
    cout << "\n2. ПОИСК ПО ФАМИЛИИ 'Петрова':" << endl;
    printLine(40);
    ListNote<Human*>* found = peopleList.findByLastName("Петрова");
    if (found != nullptr) {
        cout << "Найден: ";
        found->data->printInfo();
    }
    else {
        cout << "Не найден!" << endl;
    }
    printLine(40);

    // Демонстрация поиска по году рождения
    cout << "\n3. ПОИСК ПО ГОДУ РОЖДЕНИЯ 1972:" << endl;
    printLine(40);
    found = peopleList.findByBirthYear(1972);
    if (found != nullptr) {
        cout << "Найден: ";
        found->data->printInfo();
    }
    else {
        cout << "Не найден!" << endl;
    }
    printLine(40);

    // Демонстрация сортировки по фамилии
    cout << "\n4. СОРТИРОВКА ПО ФАМИЛИИ:" << endl;
    printLine(40);
    peopleList.sortByLastName();
    cout << "Отсортированный список:" << endl;
    cout << peopleList;
    printLine(40);

    // Демонстрация сортировки по году рождения
    cout << "\n5. СОРТИРОВКА ПО ГОДУ РОЖДЕНИЯ:" << endl;
    printLine(40);
    peopleList.sortByBirthYear();
    cout << "Отсортированный список:" << endl;
    cout << peopleList;
    printLine(40);

    // Демонстрация удаления
    cout << "\n6. УДАЛЕНИЕ ВТОРОГО ЭЛЕМЕНТА (индекс 1):" << endl;
    printLine(40);

    // Сохраняем указатель перед удалением, чтобы освободить память
    Human* toDelete = peopleList[1];
    peopleList.remove(1);
    delete toDelete; // Освобождаем память

    cout << "Список после удаления:" << endl;
    cout << peopleList;
    printLine(40);


    // Демонстрация доступа по индексу
    cout << "\n7. ДОСТУП К ЭЛЕМЕНТАМ ПО ИНДЕКСУ:" << endl;
    printLine(40);
    if (peopleList.getSize() > 0) {
        cout << "Первый элемент (индекс 0):" << endl;
        peopleList[0]->printInfo();

        if (peopleList.getSize() > 1) {
            cout << "\nПоследний элемент (индекс " << (peopleList.getSize() - 1) << "):" << endl;
            peopleList[peopleList.getSize() - 1]->printInfo();
        }
    }
    printLine(40);

    // Очистка памяти
    cout << "\n9. ОЧИСТКА ПАМЯТИ:" << endl;
    printLine(40);
    for (int i = 0; i < peopleList.getSize(); i++) {
        delete peopleList[i];
    }
    peopleList.clear();
    cout << "Размер списка после очистки: " << peopleList.getSize() << endl;
    cout << "Список после очистки:" << endl;
    cout << peopleList;
    printLine(40);
}


void workWithList()
{
    cout << "\n";
    printLine(50);
    cout << "РАБОТА СО СПИСКОМ" << endl;
    printLine(50);

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
            // Очистка всех списков перед выходом
            for (int i = 0; i < humanList.getSize(); i++) {
                delete humanList[i];
            }
            for (int i = 0; i < teacherList.getSize(); i++) {
                delete teacherList[i];
            }
            for (int i = 0; i < commissionList.getSize(); i++) {
                delete commissionList[i];
            }
            for (int i = 0; i < teacherCommissionList.getSize(); i++) {
                delete teacherCommissionList[i];
            }
            continueWorking = false;
            break;
        }

        // Выбираем список для работы
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

        // Меню действий для выбранного класса
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
                }

                cout << "\nВведите данные:\n";
                cin >> *newPerson;

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
            case 2: {
                if (currentList->getSize() == 0) {
                    cout << "Список пуст!" << endl;
                    break;
                }
                cout << *currentList;
                int index = safeInputInt("Введите индекс для удаления: ", 0, currentList->getSize() - 1);
                delete (*currentList)[index];
                currentList->remove(index);
                cout << "Элемент удален!" << endl;
                break;
            }
            case 3: {
                if (currentList->getSize() == 0) {
                    cout << "Список пуст!" << endl;
                    break;
                }
                cout << *currentList;
                string lastName = safeInputString("Введите фамилию для удаления: ");
                ListNote<Human*>* found = currentList->findByLastName(lastName);
                if (found != nullptr) {
                    for (int i = 0; i < currentList->getSize(); i++) {
                        if ((*currentList)[i] == found->data) {
                            delete (*currentList)[i];
                            currentList->remove(i);
                            cout << "Элемент удален!" << endl;
                            break;
                        }
                    }
                }
                else {
                    cout << "Элемент не найден!" << endl;
                }
                break;
            }
            case 4:
                cout << "\nСОДЕРЖИМОЕ СПИСКА " << className << " (" << currentList->getSize() << " элементов):" << endl;
                cout << *currentList;
                break;
            case 5: {
                string lastName = safeInputString("Введите фамилию для поиска: ");
                ListNote<Human*>* found = currentList->findByLastName(lastName);
                if (found != nullptr) {
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
            case 6: {
                int year = safeInputInt("Введите год рождения для поиска: ", 1900, 2023);
                ListNote<Human*>* found = currentList->findByBirthYear(year);
                if (found != nullptr) {
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
                for (int i = 0; i < currentList->getSize(); i++) {
                    delete (*currentList)[i];
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