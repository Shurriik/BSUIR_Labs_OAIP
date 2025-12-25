#ifndef LIST_H
#define LIST_H

#include <stdexcept>

// Шаблонный класс двусвязного списка
template<typename T>
class List {
private:
    // Структура узла двусвязного списка
    struct Node {
        T data;                                 // Данные, хранящиеся в узле
        Node* next;                             // Указатель на следующий узел
        Node* prev;                             // Указатель на предыдущий узел
        
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}  // Конструктор узла
    };
    
    Node* head;                                // Указатель на головной элемент списка
    Node* tail;                                // Указатель на хвостовой элемент списка
    size_t size_;                              // Размер списка

public:
    // Класс итератора для обхода списка
    class Iterator {
    private:
        Node* current;                         // Указатель на текущий узел
        
    public:
        Iterator(Node* node) : current(node) {}  // Конструктор итератора
        
        Iterator& operator++() {                // Префиксный инкремент (переход к следующему элементу)
            if (current) current = current->next;
            return *this;
        }
        
        Iterator operator++(int) {             // Постфиксный инкремент
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
        
        Iterator& operator--() {                // Префиксный декремент (переход к предыдущему элементу)
            if (current) current = current->prev;
            return *this;
        }
        
        Iterator operator--(int) {              // Постфиксный декремент
            Iterator temp = *this;
            --(*this);
            return temp;
        }
        
        T& operator*() {                        // Оператор разыменования (получить значение)
            if (current == nullptr) {
                throw std::runtime_error("Dereferencing null iterator");
            }
            return current->data;
        }
        
        T* operator->() {                       // Оператор доступа к членам
            if (current == nullptr) {
                throw std::runtime_error("Dereferencing null iterator");
            }
            return &current->data;
        }
        
        bool operator==(const Iterator& other) const {  // Оператор сравнения на равенство
            return current == other.current;
        }
        
        bool operator!=(const Iterator& other) const {  // Оператор сравнения на неравенство
            return current != other.current;
        }
        
        Node* getNode() const { return current; }  // Получить указатель на текущий узел
    };
    
    List();                                     // Конструктор по умолчанию
    ~List();                                    // Деструктор
    List(const List& other);                    // Конструктор копирования
    List& operator=(const List& other);         // Оператор присваивания
    
    void push_back(const T& value);             // Добавить элемент в конец списка
    void push_front(const T& value);            // Добавить элемент в начало списка
    void pop_back();                            // Удалить элемент с конца списка
    void pop_front();                           // Удалить элемент с начала списка
    void insert(const Iterator& pos, const T& value);  // Вставить элемент перед указанной позицией
    void erase(const Iterator& pos);           // Удалить элемент в указанной позиции
    void clear();                               // Очистить весь список
    
    T& front();                                 // Получить ссылку на первый элемент
    const T& front() const;                     // Получить константную ссылку на первый элемент
    T& back();                                  // Получить ссылку на последний элемент
    const T& back() const;                      // Получить константную ссылку на последний элемент
    
    bool empty() const;                         // Проверить, пуст ли список
    size_t size() const;                        // Получить размер списка
    
    Iterator begin();                           // Получить итератор на начало списка
    Iterator end();                            // Получить итератор на конец списка (после последнего элемента)
    Iterator rbegin();                          // Получить итератор на конец списка (для обратного обхода)
    Iterator rend();                            // Получить итератор на начало списка (для обратного обхода)
    
    Iterator begin() const;                     // Получить константный итератор на начало списка
    Iterator end() const;                       // Получить константный итератор на конец списка
    
    T* find(const T& value);                    // Найти элемент по значению
    void remove(const T& value);                // Удалить все элементы с указанным значением
};

// Реализация шаблона
template<typename T>
List<T>::List() : head(nullptr), tail(nullptr), size_(0) {
}

template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
List<T>::List(const List& other) : head(nullptr), tail(nullptr), size_(0) {
    for (const auto& item : other) {
        push_back(item);
    }
}

template<typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
        clear();
        for (const auto& item : other) {
            push_back(item);
        }
    }
    return *this;
}

template<typename T>
void List<T>::push_back(const T& value) {
    Node* newNode = new Node(value);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size_++;
}

template<typename T>
void List<T>::push_front(const T& value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
    size_++;
}

template<typename T>
void List<T>::pop_back() {
    if (tail == nullptr) {
        throw std::runtime_error("List is empty");
    }
    Node* temp = tail;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete temp;
    size_--;
}

template<typename T>
void List<T>::pop_front() {
    if (head == nullptr) {
        throw std::runtime_error("List is empty");
    }
    Node* temp = head;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    delete temp;
    size_--;
}

template<typename T>
void List<T>::insert(const Iterator& pos, const T& value) {
    Node* newNode = new Node(value);
    Node* current = pos.getNode();
    
    if (current == nullptr) {
        push_back(value);
        return;
    }
    
    newNode->next = current;
    newNode->prev = current->prev;
    
    if (current->prev) {
        current->prev->next = newNode;
    } else {
        head = newNode;
    }
    
    current->prev = newNode;
    size_++;
}

template<typename T>
void List<T>::erase(const Iterator& pos) {
    Node* current = pos.getNode();
    if (current == nullptr) {
        return;
    }
    
    if (current->prev) {
        current->prev->next = current->next;
    } else {
        head = current->next;
    }
    
    if (current->next) {
        current->next->prev = current->prev;
    } else {
        tail = current->prev;
    }
    
    delete current;
    size_--;
}

template<typename T>
void List<T>::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size_ = 0;
}

template<typename T>
T& List<T>::front() {
    if (head == nullptr) {
        throw std::runtime_error("List is empty");
    }
    return head->data;
}

template<typename T>
const T& List<T>::front() const {
    if (head == nullptr) {
        throw std::runtime_error("List is empty");
    }
    return head->data;
}

template<typename T>
T& List<T>::back() {
    if (tail == nullptr) {
        throw std::runtime_error("List is empty");
    }
    return tail->data;
}

template<typename T>
const T& List<T>::back() const {
    if (tail == nullptr) {
        throw std::runtime_error("List is empty");
    }
    return tail->data;
}

template<typename T>
bool List<T>::empty() const {
    return size_ == 0;
}

template<typename T>
size_t List<T>::size() const {
    return size_;
}

template<typename T>
typename List<T>::Iterator List<T>::begin() {
    return Iterator(head);
}

template<typename T>
typename List<T>::Iterator List<T>::end() {
    return Iterator(nullptr);
}

template<typename T>
typename List<T>::Iterator List<T>::rbegin() {
    return Iterator(tail);
}

template<typename T>
typename List<T>::Iterator List<T>::rend() {
    return Iterator(nullptr);
}

template<typename T>
typename List<T>::Iterator List<T>::begin() const {
    return Iterator(const_cast<Node*>(head));
}

template<typename T>
typename List<T>::Iterator List<T>::end() const {
    return Iterator(nullptr);
}

template<typename T>
T* List<T>::find(const T& value) {
    for (auto it = begin(); it != end(); ++it) {
        if (*it == value) {
            return &(*it);
        }
    }
    return nullptr;
}

template<typename T>
void List<T>::remove(const T& value) {
    for (auto it = begin(); it != end();) {
        if (*it == value) {
            auto toErase = it;
            ++it;
            erase(toErase);
        } else {
            ++it;
        }
    }
}

#endif // LIST_H

