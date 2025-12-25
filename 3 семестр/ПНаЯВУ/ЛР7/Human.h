#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include <iostream>

class Human
{
protected:
    std::string firstName;      // Имя человека
    std::string lastName;       // Фамилия человека  
    std::string patronymic;     // Отчество человека
    int birthYear;              // Год рождения человека

public:
    Human();                                                    // Конструктор по умолчанию
    Human(const std::string& first, const std::string& last,
        const std::string& pat, int year);                      // Конструктор с параметрами
    virtual ~Human() = default;                                 // Виртуальный деструктор

    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPatronymic() const;
    int getBirthYear() const;

    void setFirstName(const std::string& first);
    void setLastName(const std::string& last);
    void setPatronymic(const std::string& pat);
    void setBirthYear(int year);

    virtual void printInfo() const;
    virtual Human* clone() const;
    virtual void inputFromStream(std::istream& is);
    virtual void outputToStream(std::ostream& os) const;
    virtual void printTableHeader() const;
    virtual void printTableRow() const;

    friend std::ostream& operator<<(std::ostream& os, Human& human);
    friend std::istream& operator>>(std::istream& is, Human& human);

    bool operator==(const Human& other) const;

    bool operator<(const Human& other) const;
};

#endif