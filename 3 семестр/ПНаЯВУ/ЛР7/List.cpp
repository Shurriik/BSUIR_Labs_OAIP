#ifndef LIST_CPP
#define LIST_CPP

#include "List.h"
#include "Human.h"
#include "University_teacher.h"
#include "Commission_member.h"
#include "Teacher_commission_member.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

template<typename T>
List<T>::List() : head(nullptr), size(0) {}

template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
void List<T>::addToEnd(const T& value) {
    ListNote<T>* newNote = new ListNote<T>(value);
    if (!head) head = newNote;
    else {
        ListNote<T>* current = head;
        while (current->next) current = current->next;
        current->next = newNote;
    }
    size++;
}

template<typename T>
void List<T>::addToStart(const T& value) {
    ListNote<T>* newNote = new ListNote<T>(value);
    newNote->next = head;
    head = newNote;
    size++;
}

template<typename T>
void List<T>::addToMiddle(int index, const T& value) {
    if (index < 0 || index > size) {
        std::cout << "Неверный индекс!" << std::endl;
        return;
    }
    if (index == 0) { addToStart(value); return; }
    if (index == size) { addToEnd(value); return; }

    ListNote<T>* current = head;
    for (int i = 0; i < index - 1; i++) current = current->next;
    ListNote<T>* newNote = new ListNote<T>(value);
    newNote->next = current->next;
    current->next = newNote;
    size++;
}

template<typename T>
void List<T>::remove(int index) {
    if (index < 0 || index >= size) { std::cout << "Неверный индекс!" << std::endl; return; }
    if (index == 0) {
        ListNote<T>* temp = head;
        head = head->next;
        delete temp;
    }
    else {
        ListNote<T>* current = head;
        for (int i = 0; i < index - 1; i++) current = current->next;
        ListNote<T>* temp = current->next;
        current->next = temp->next;
        delete temp;
    }
    size--;
}

template<typename T>
void List<T>::remove(const T& value) {
    ListNote<T>* current = head;
    ListNote<T>* prev = nullptr;
    int idx = 0;
    while (current) {
        if (current->data == value) {
            if (!prev) head = current->next;
            else prev->next = current->next;
            delete current;
            size--;
            std::cout << "Элемент удален по индексу " << idx << std::endl;
            return;
        }
        prev = current;
        current = current->next;
        idx++;
    }
    std::cout << "Элемент не найден!" << std::endl;
}

template<typename T>
ListNote<T>* List<T>::findByLastName(const std::string& lastName) {
    ListNote<T>* current = head;
    while (current) {
        if (current->data->getLastName() == lastName) return current;
        current = current->next;
    }
    return nullptr;
}

template<typename T>
ListNote<T>* List<T>::findByBirthYear(int year) {
    ListNote<T>* current = head;
    while (current) {
        if (current->data->getBirthYear() == year) return current;
        current = current->next;
    }
    return nullptr;
}

template<typename T>
void List<T>::sortByLastName() {
    if (size < 2) return;
    bool swapped;
    do {
        swapped = false;
        ListNote<T>* current = head;
        while (current && current->next) {
            if (current->data->getLastName() > current->next->data->getLastName()) {
                T temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

template<typename T>
void List<T>::sortByBirthYear() {
    if (size < 2) return;
    bool swapped;
    do {
        swapped = false;
        ListNote<T>* current = head;
        while (current && current->next) {
            if (current->data->getBirthYear() > current->next->data->getBirthYear()) {
                T temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

template<typename T>
int List<T>::getSize() const { return size; }

template<typename T>
void List<T>::clear() {
    while (head) {
        ListNote<T>* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

template<typename T>
T& List<T>::get(int index) {
    if (index < 0 || index >= size) throw std::out_of_range("Неверный индекс!");
    ListNote<T>* current = head;
    for (int i = 0; i < index; i++) current = current->next;
    return current->data;
}

template<typename T>
T& List<T>::operator[](int index) { return get(index); }

template<typename T>
const T& List<T>::get(int index) const {
    if (index < 0 || index >= size) throw std::out_of_range("Неверный индекс!");
    ListNote<T>* current = head;
    for (int i = 0; i < index; i++) current = current->next;
    return current->data;
}

template<typename T>
const T& List<T>::operator[](int index) const { return get(index); }

template<typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& list) {
    if (!list.head) { os << "Список пуст!\n"; return os; }

    os << "===== СПИСОК (" << list.size << " элементов) =====\n";
    ListNote<T>* current = list.head;
    int idx = 0;
    while (current) {
        os << idx++ << ": " << current->data->getLastName() << " "
            << current->data->getFirstName() << " (" << current->data->getBirthYear() << ")\n";
        current = current->next;
    }
    os << "============================\n";
    return os;
}

// ===================== Вложенный итератор =====================
template<typename T>
typename List<T>::Iterator List<T>::begin() { return Iterator(head); }

template<typename T>
typename List<T>::Iterator List<T>::end() { return Iterator(nullptr); }

template<typename T>
typename List<T>::ConstIterator List<T>::begin() const { return ConstIterator(head); }

template<typename T>
typename List<T>::ConstIterator List<T>::end() const { return ConstIterator(nullptr); }

template<typename T>
typename List<T>::ConstIterator List<T>::cbegin() const { return ConstIterator(head); }

template<typename T>
typename List<T>::ConstIterator List<T>::cend() const { return ConstIterator(nullptr); }

#endif
