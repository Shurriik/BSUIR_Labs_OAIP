#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdexcept>

template<typename T>
class Iterator {
public:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

private:
    Node* current;

public:
    Iterator(Node* start) : current(start) {}

    bool hasNext() const {
        return current != nullptr;
    }

    T& next() {
        if (!current)
            throw std::out_of_range("Нет следующего элемента");
        T& value = current->data;
        current = current->next;
        return value;
    }
};

#endif
