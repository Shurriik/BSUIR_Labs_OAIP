#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "List.h"
#include <string>

class Algorithms {
public:
    template<typename T>
    static void sortByLastName(List<T>& list);

    template<typename T>
    static void sortByBirthYear(List<T>& list);

    template<typename T>
    static ListNote<T>* findByLastName(List<T>& list, const std::string& lastName);

    template<typename T>
    static ListNote<T>* findByBirthYear(List<T>& list, int birthYear);
};

// ==== Реализации шаблонов ====
template<typename T>
void Algorithms::sortByLastName(List<T>& list) {
    if (list.getSize() < 2) return;

    bool swapped;
    do {
        swapped = false;
        auto current = list.head;
        while (current && current->next) {
            if (current->data->getLastName() > current->next->data->getLastName()) {
                std::swap(current->data, current->next->data);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

template<typename T>
void Algorithms::sortByBirthYear(List<T>& list) {
    if (list.getSize() < 2) return;

    bool swapped;
    do {
        swapped = false;
        auto current = list.head;
        while (current && current->next) {
            if (current->data->getBirthYear() > current->next->data->getBirthYear()) {
                std::swap(current->data, current->next->data);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

template<typename T>
ListNote<T>* Algorithms::findByLastName(List<T>& list, const std::string& lastName) {
    auto current = list.head;
    while (current) {
        if (current->data->getLastName() == lastName) return current;
        current = current->next;
    }
    return nullptr;
}

template<typename T>
ListNote<T>* Algorithms::findByBirthYear(List<T>& list, int birthYear) {
    auto current = list.head;
    while (current) {
        if (current->data->getBirthYear() == birthYear) return current;
        current = current->next;
    }
    return nullptr;
}


#endif
