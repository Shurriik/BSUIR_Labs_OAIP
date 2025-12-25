#include "Student.h"
#include "Exp.h"
#include "ExpInput.h"
#include <stdexcept>
#include <limits>
#include <sstream>
#include <iostream>
#include <cctype>

Student::Student() : gradesCount(0) {
    for (int i = 0; i < MAX_GRADES; i++) {
        grades[i] = 0;
    }
}

Student::Student(const std::string& last, const std::string& first,
    const std::string& subj, const int* gr, int count)
    : lastName(last), firstName(first), subject(subj), gradesCount(count > MAX_GRADES ? MAX_GRADES : count) {

    if (count > MAX_GRADES) {
        throw InputException("Слишком много оценок. Максимум: " + std::to_string(MAX_GRADES));
    }

    for (int i = 0; i < gradesCount; ++i) {
        if (gr[i] < 0 || gr[i] > 10) {
            throw InputException("Оценка должна быть от 0 до 10");
        }
        grades[i] = gr[i];
    }

    for (int i = gradesCount; i < MAX_GRADES; i++) {
        grades[i] = 0;
    }
}

double Student::getAverageGrade() const {
    if (gradesCount == 0) return 0.0;

    double sum = 0;
    for (int i = 0; i < gradesCount; ++i) {
        sum += grades[i];
    }
    return sum / gradesCount;
}

bool Student::hasPassed() const {
    return getAverageGrade() >= 4.0;
}

std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << student.lastName << " " << student.firstName
        << " | Дисциплина: " << student.subject
        << " | Оценки: ";

    for (int i = 0; i < student.gradesCount; ++i) {
        os << student.grades[i];
        if (i != student.gradesCount - 1) os << ", ";
    }

    os << " | Средний балл: " << student.getAverageGrade();
    return os;
}

bool isValidName(const std::string& name) {
    if (name.empty()) return false;

    // Проверяем, что имя состоит только из букв и начинается с заглавной
    if (!std::isalpha(name[0]) || !std::isupper(name[0])) {
        return false;
    }

    for (size_t i = 1; i < name.length(); ++i) {
        if (!std::isalpha(name[i]) && name[i] != '-') {
            return false;
        }
    }

    return true;
}

std::istream& operator>>(std::istream& is, Student& student) {
    // Ввод фамилии
    bool validLastName = false;
    while (!validLastName) {
        try {
            std::cout << "Введите фамилию: ";
            std::string lastName;
            if (!std::getline(is, lastName)) {
                throw InputException("Ошибка ввода фамилии");
            }

            if (lastName.empty()) {
                throw InputException("Фамилия не может быть пустой");
            }

            // Проверяем, что фамилия состоит только из букв
            for (char c : lastName) {
                if (std::isdigit(c)) {
                    throw InputException("Фамилия не должна содержать цифры");
                }
                if (!std::isalpha(c) && c != '-') {
                    throw InputException("Фамилия должна содержать только буквы и дефисы");
                }
            }

            // Проверяем, что первая буква заглавная
            if (!std::isupper(lastName[0])) {
                throw InputException("Фамилия должна начинаться с заглавной буквы");
            }

            student.lastName = lastName;
            validLastName = true;
        }
        catch (const InputException& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
            std::cout << "Пожалуйста, введите фамилию заново.\n";
        }
    }

    // Ввод имени
    bool validFirstName = false;
    while (!validFirstName) {
        try {
            std::cout << "Введите имя: ";
            std::string firstName;
            if (!std::getline(is, firstName)) {
                throw InputException("Ошибка ввода имени");
            }

            if (firstName.empty()) {
                throw InputException("Имя не может быть пустым");
            }

            // Проверяем, что имя состоит только из букв
            for (char c : firstName) {
                if (std::isdigit(c)) {
                    throw InputException("Имя не должно содержать цифры");
                }
                if (!std::isalpha(c) && c != '-') {
                    throw InputException("Имя должно содержать только буквы и дефисы");
                }
            }

            // Проверяем, что первая буква заглавная
            if (!std::isupper(firstName[0])) {
                throw InputException("Имя должно начинаться с заглавной буквы");
            }

            student.firstName = firstName;
            validFirstName = true;
        }
        catch (const InputException& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
            std::cout << "Пожалуйста, введите имя заново.\n";
        }
    }

    // Ввод названия дисциплины (здесь можно допускать цифры, например "Математика 1")
    std::cout << "Введите название дисциплины: ";
    if (!std::getline(is, student.subject)) {
        throw InputException("Ошибка ввода названия дисциплины");
    }

    if (student.subject.empty()) {
        throw InputException("Название дисциплины не может быть пустым");
    }

    // Ввод количества оценок
    int count;
    bool validCount = false;
    while (!validCount) {
        try {
            std::cout << "Сколько оценок? (максимум " << Student::MAX_GRADES << "): ";
            std::string countStr;
            if (!std::getline(is, countStr)) {
                throw InputException("Ошибка ввода количества оценок");
            }

            // Проверяем, что введено число
            bool isNumber = true;
            for (char c : countStr) {
                if (!std::isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }

            if (!isNumber) {
                throw InputException("Количество оценок должно быть числом");
            }

            count = std::stoi(countStr);

            if (count < 0) {
                throw InputException("Количество оценок не может быть отрицательным");
            }

            if (count > Student::MAX_GRADES) {
                throw InputException("Слишком много оценок. Максимум: " + std::to_string(Student::MAX_GRADES));
            }

            validCount = true;
        }
        catch (const InputException& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
            std::cout << "Пожалуйста, введите количество оценок заново.\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
            std::cout << "Пожалуйста, введите количество оценок заново.\n";
        }
    }

    // Ввод оценок
    student.gradesCount = 0;
    for (int i = 0; i < count; ++i) {
        bool validGrade = false;
        while (!validGrade) {
            try {
                std::cout << "Оценка " << (i + 1) << " (от 0 до 10): ";
                std::string gradeStr;
                if (!std::getline(is, gradeStr)) {
                    throw InputException("Ошибка ввода оценки");
                }

                // Проверяем, что введено число
                bool isNumber = true;
                for (char c : gradeStr) {
                    if (!std::isdigit(c)) {
                        isNumber = false;
                        break;
                    }
                }

                if (!isNumber) {
                    throw InputException("Оценка должна быть числом");
                }

                int grade = std::stoi(gradeStr);

                if (grade < 0 || grade > 10) {
                    throw InputException("Оценка должна быть от 0 до 10");
                }

                student.grades[student.gradesCount++] = grade;
                validGrade = true;
            }
            catch (const InputException& e) {
                std::cerr << "Ошибка: " << e.what() << std::endl;
                std::cout << "Пожалуйста, введите оценку заново.\n";
            }
            catch (const std::exception& e) {
                std::cerr << "Ошибка: " << e.what() << std::endl;
                std::cout << "Пожалуйста, введите оценку заново.\n";
            }
        }
    }

    for (int i = student.gradesCount; i < Student::MAX_GRADES; i++) {
        student.grades[i] = 0;
    }

    return is;
}

void Student::serialize(std::ostream& out) const {
    size_t len = lastName.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(lastName.c_str(), len);

    len = firstName.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(firstName.c_str(), len);

    len = subject.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(subject.c_str(), len);

    out.write(reinterpret_cast<const char*>(&gradesCount), sizeof(gradesCount));

    out.write(reinterpret_cast<const char*>(grades), sizeof(int) * gradesCount);
}

void Student::deserialize(std::istream& in) {
    size_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (in.gcount() != sizeof(len)) {
        throw FileException("Ошибка чтения длины фамилии");
    }
    lastName.resize(len);
    in.read(&lastName[0], len);

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    firstName.resize(len);
    in.read(&firstName[0], len);

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    subject.resize(len);
    in.read(&subject[0], len);

    in.read(reinterpret_cast<char*>(&gradesCount), sizeof(gradesCount));
    if (gradesCount < 0 || gradesCount > MAX_GRADES) {
        throw FileException("Некорректное количество оценок в файле");
    }

    in.read(reinterpret_cast<char*>(grades), sizeof(int) * gradesCount);

    for (int i = gradesCount; i < MAX_GRADES; i++) {
        grades[i] = 0;
    }
}

bool Student::addGrade(int grade) {
    if (gradesCount >= MAX_GRADES) {
        return false;
    }

    if (grade < 0 || grade > 10) {
        throw InputException("Оценка должна быть от 0 до 10");
    }

    grades[gradesCount++] = grade;
    return true;
}