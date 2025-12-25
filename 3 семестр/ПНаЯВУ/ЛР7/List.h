#ifndef LIST_H
#define LIST_H

#include "ListNote.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <iterator>

template<typename T> class List;


template<typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& list);

template<typename T>
class List
{
public:
    List();
    ~List();

    // Вложенный итератор для обхода списка
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(ListNote<T>* node = nullptr) : current(node) {}

        reference operator*() const { return current->data; }
        pointer operator->() const { return &current->data; }

        Iterator& operator++() { if (current) current = current->next; return *this; }
        Iterator operator++(int) { Iterator tmp(*this); ++(*this); return tmp; }

        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }

    private:
        ListNote<T>* current;
    };

    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        ConstIterator(const ListNote<T>* node = nullptr) : current(node) {}

        reference operator*() const { return current->data; }
        pointer operator->() const { return &current->data; }

        ConstIterator& operator++() { if (current) current = current->next; return *this; }
        ConstIterator operator++(int) { ConstIterator tmp(*this); ++(*this); return tmp; }

        bool operator==(const ConstIterator& other) const { return current == other.current; }
        bool operator!=(const ConstIterator& other) const { return !(*this == other); }

    private:
        const ListNote<T>* current;
    };

    void addToEnd(const T& value);
    void addToStart(const T& value);
    void addToMiddle(int index, const T& value);

    void remove(int index);
    void remove(const T& value);

    ListNote<T>* findByLastName(const std::string& lastName);
    ListNote<T>* findByBirthYear(int birthYear);

    void sortByLastName();
    void sortByBirthYear();

    int getSize() const;
    void clear();
    T& get(int index);
    const T& get(int index) const;
    T& operator[](int index);
    const T& operator[](int index) const;

    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;
    ConstIterator cbegin() const;
    ConstIterator cend() const;

    friend class Algorithms;

private:
    ListNote<T>* head;
    int size;


    friend std::ostream& operator<< <T>(std::ostream& os, const List<T>& list);
};



#endif