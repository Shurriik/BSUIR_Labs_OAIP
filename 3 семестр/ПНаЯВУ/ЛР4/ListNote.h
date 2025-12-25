#ifndef LISTNOTE_H
#define LISTNOTE_H

template<typename T>
class ListNote 
{
public:
    T data;
    ListNote<T>* prev;
    ListNote<T>* next;

    ListNote(const T& data) : data(data), prev(nullptr), next(nullptr) {}
};

#endif
