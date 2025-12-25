#include "Human.h"
#include <iostream>
#include <limits>
#include <iomanip>

Human::Human() : firstName(""), lastName(""), patronymic(""), birthYear(0) {}

Human::Human(const std::string& first, const std::string& last, const std::string& pat, int year) : firstName(first), lastName(last), patronymic(pat), birthYear(year)
{
}

std::string Human::getFirstName() const
{
    return firstName;
}
std::string Human::getLastName() const
{
    return lastName;
}
std::string Human::getPatronymic() const
{
    return patronymic;
}
int Human::getBirthYear() const
{
    return birthYear;
}

void Human::setFirstName(const std::string& first)
{
    firstName = first;
}
void Human::setLastName(const std::string& last)
{
    lastName = last;
}
void Human::setPatronymic(const std::string& pat)
{
    patronymic = pat;
}
void Human::setBirthYear(int year)
{
    birthYear = year;
}

void Human::printInfo() const
{
    std::cout << "ФИО: " << lastName << " " << firstName << " " << patronymic << std::endl;
    std::cout << "Год рождения: " << birthYear << std::endl;
}

Human* Human::clone() const
{
    return new Human(*this);
}

void Human::inputFromStream(std::istream& is)
{
    std::cout << "Введите имя: ";
    std::getline(is, firstName);
    std::cout << "Введите фамилию: ";
    std::getline(is, lastName);
    std::cout << "Введите отчество: ";
    std::getline(is, patronymic);
    std::cout << "Введите год рождения: ";
    is >> birthYear;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Human::outputToStream(std::ostream& os) const
{
    os << firstName << std::endl;
    os << lastName << std::endl;
    os << patronymic << std::endl;
    os << birthYear << std::endl;
}

std::ostream& operator<<(std::ostream& os, Human& human)
{
    os << std::setw(15) << human.lastName << "| "
        << std::setw(15) << human.firstName << "| "
        << std::setw(15) << human.patronymic << "| "
        << std::setw(4) << human.birthYear << "| ";
    return os;
}

std::istream& operator>>(std::istream& is, Human& human)
{
    std::cout << "Введите фамилию: ";
    std::getline(is, human.lastName);
    std::cout << "Введите имя: ";
    std::getline(is, human.firstName);
    std::cout << "Введите отчество: ";
    std::getline(is, human.patronymic);
    std::cout << "Введите год рождения: ";
    is >> human.birthYear;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}

void Human::printTableHeader() const
{
    std::cout << std::left << std::setw(15) << "№"
        << std::setw(15) << "Тип"
        << std::setw(15) << "Фамилия"
        << std::setw(15) << "Имя"
        << std::setw(15) << "Отчество"
        << std::setw(4) << "Год рожд." << std::endl;
    std::cout << std::string(85, '-') << std::endl;
}

void Human::printTableRow() const
{
    std::cout << std::left
        << std::setw(15) << "Человек"
        << std::setw(15) << lastName
        << std::setw(15) << firstName
        << std::setw(15) << patronymic
        << std::setw(4) << birthYear << std::endl;
}

bool Human:: operator==(const Human& other) const
{
    return firstName == other.firstName &&
        lastName == other.lastName &&
        patronymic == other.patronymic &&
        birthYear == other.birthYear;
}

bool Human::operator<(const Human& other) const
{
    if (lastName != other.lastName) return lastName < other.lastName;
    if (firstName != other.firstName) return firstName < other.firstName;
    if (patronymic != other.patronymic) return patronymic < other.patronymic;
    return birthYear < other.birthYear;
}