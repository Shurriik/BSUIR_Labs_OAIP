#ifndef LISTNOTE_H
#define LISTNOTE_H

template<typename T>
class ListNote 
{
public:
    T data;
    ListNote<T>* next;

    ListNote(const T& value) : data(value), next(nullptr) {}
};

#endif
