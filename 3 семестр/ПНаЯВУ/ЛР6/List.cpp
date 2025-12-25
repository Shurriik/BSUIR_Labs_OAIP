#ifndef LIST_CPP
#define LIST_CPP

#include "List.h"
#include "Human.h"
#include "University_teacher.h"
#include "Commission_member.h"
#include "Teacher_commission_member.h"


template<typename T>
List<T>::List() : head(nullptr), size(0) {}


template<typename T>
List<T>::~List() 
{
    clear();
}


template<typename T>
void List<T>::addToEnd(const T& value) 
{
    ListNote<T>* newNote = new ListNote<T>(value);

    if (head == nullptr) 
    {
        head = newNote;
    }
    else 
    {
        ListNote<T>* current = head;
        while (current->next != nullptr) 
        {
            current = current->next;
        }
        current->next = newNote;
    }
    size++;
}

template<typename T>
void List<T>::addToStart(const T& value) 
{
    ListNote<T>* newNote = new ListNote<T>(value);
    newNote->next = head;
    head = newNote;
    size++;
}


template<typename T>
void List<T>::addToMiddle(int index, const T& value) 
{
    if (index < 0 || index > size) 
    {
        std::cout << "Неверный индекс!" << std::endl;
        return;
    }

    if (index == 0) 
    {
        addToStart(value);
        return;
    }

    if (index == size)
    {
        addToEnd(value);
        return;
    }

    ListNote<T>* newNote = new ListNote<T>(value);
    ListNote<T>* current = head;

    for (int i = 0; i < index - 1; i++) 
    {
        current = current->next;
    }

    newNote->next = current->next;
    current->next = newNote;
    size++;
}


template<typename T>
void List<T>::remove(int index) 
{
    if (index < 0 || index >= size) 
    {
        std::cout << "Неверный индекс!" << std::endl;
        return;
    }

    if (index == 0)
    {
        ListNote<T>* temp = head;
        head = head->next;
        delete temp;
    }
    else
    {
        ListNote<T>* current = head;
        for (int i = 0; i < index - 1; i++) 
        {
            current = current->next;
        }
        ListNote<T>* temp = current->next;
        current->next = temp->next;
        delete temp;
    }
    size--;
}


template<typename T>
void List<T>::remove(const T& value) 
{
    ListNote<T>* current = head;
    ListNote<T>* prev = nullptr;
    int index = 0;

    while (current != nullptr) 
    {
        if (current->data == value) 
        {
            if (prev == nullptr) 
            {
                head = current->next;
            }
            else 
            {
                prev->next = current->next;
            }
            delete current;
            size--;
            std::cout << "Элемент удален по индексу " << index << std::endl;
            return;
        }
        prev = current;
        current = current->next;
        index++;
    }
    std::cout << "Элемент не найден!" << std::endl;
}


template<typename T>
ListNote<T>* List<T>::findByLastName(const std::string& lastName)
{
    ListNote<T>* current = head;
    while (current != nullptr)
    {
        if (current->data->getLastName() == lastName)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}


template<typename T>
ListNote<T>* List<T>::findByBirthYear(int birthYear) 
{
    ListNote<T>* current = head;
    while (current != nullptr) 
    {
        if (current->data->getBirthYear() == birthYear) 
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template<typename T>
void List<T>::sortByLastName() 
{
    if (size < 2) return;

    bool swapped;
    do 
    {
        swapped = false;
        ListNote<T>* current = head;
        ListNote<T>* prev = nullptr;

        while (current->next != nullptr) 
        {
            if (current->data->getLastName() > current->next->data->getLastName()) 
            {
                T temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            prev = current;
            current = current->next;
        }
    } while (swapped);
}


template<typename T>
void List<T>::sortByBirthYear() 
{
    if (size < 2) return;

    bool swapped;
    do {
        swapped = false;
        ListNote<T>* current = head;
        ListNote<T>* prev = nullptr;

        while (current->next != nullptr)
        {
            if (current->data->getBirthYear() > current->next->data->getBirthYear()) 
            {
                T temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            prev = current;
            current = current->next;
        }
    } while (swapped);
}


template<typename T>
int List<T>::getSize() const 
{
    return size;
}


template<typename T>
void List<T>::clear() 
{
    while (head != nullptr) 
    {
        ListNote<T>* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}


template<typename T>
T& List<T>::get(int index) 
{
    if (index < 0 || index >= size) 
    {
        throw std::out_of_range("Неверный индекс!");
    }

    ListNote<T>* current = head;
    for (int i = 0; i < index; i++) 
    {
        current = current->next;
    }
    return current->data;
}


template<typename T>
T& List<T>::operator[](int index) 
{
    return get(index);
}


template<typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& list)
{
    if (list.head == nullptr) 
    {
        os << "Список пуст!" << std::endl;
        return os;
    }

    os << "\n";
    os << "======================================================================================================================" << std::endl;
    os << "СПИСОК ОБЪЕКТОВ (" << list.size << " элементов)" << std::endl;
    os << "======================================================================================================================" << std::endl;
    os << "Индекс | Фамилия          | Имя              | Отчество         | Год   | Тип объекта" << std::endl;
    os << "-------+------------------+------------------+------------------+-------+-----------------------------------" << std::endl;

    ListNote<T>* current = list.head;
    int index = 0;
    while (current != nullptr) 
    {
        os << std::setw(6) << std::right << index << " | ";
        os << std::setw(16) << std::left << current->data->getLastName() << " | ";
        os << std::setw(16) << std::left << current->data->getFirstName() << " | ";
        os << std::setw(16) << std::left << current->data->getPatronymic() << " | ";
        os << std::setw(5) << std::right << current->data->getBirthYear() << " | ";


        if (dynamic_cast<TeacherCommissionMember*>(current->data))
        {
            os << "TeacherCommissionMember";
        }
        else if (dynamic_cast<UniversityTeacher*>(current->data))
        {
            os << "UniversityTeacher";
        }
        else if (dynamic_cast<CommissionMember*>(current->data)) 
        {
            os << "CommissionMember";
        }
        else
        {
            os << "Human";
        }
        os << std::endl;

        current = current->next;
        index++;
    }
    os << "======================================================================================================================" << std::endl;

    return os;
}
template<typename T>
const T& List<T>::get(int index) const
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range(" !");
    }

    ListNote<T>* current = head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current->data;
}


template<typename T>
const T& List<T>::operator[](int index) const
{
    return get(index);
}

#endif