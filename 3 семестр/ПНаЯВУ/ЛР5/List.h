#ifndef LIST_H
#define LIST_H

#include "ListNote.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>

template<typename T> class List;


template<typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& list);

template<typename T>
class List
{
private:
    ListNote<T>* head;
    int size;

public:
    List();
    ~List();

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
    T& operator[](int index);


    friend std::ostream& operator<< <T>(std::ostream& os, const List<T>& list);
};



#endif