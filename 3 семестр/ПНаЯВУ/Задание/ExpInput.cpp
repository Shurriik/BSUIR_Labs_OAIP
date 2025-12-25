#include "ExpInput.h"
#include "Exp.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <cctype>
#include <algorithm>

int ExpInput::getInt(const std::string& prompt, int min, int max) {
    int value;
    bool validInput = false;

    while (!validInput) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);

        if (std::cin.fail()) {
            std::cin.clear();
            throw InputException("Ошибка ввода");
        }

        if (input.empty()) {
            throw InputException("Ввод не может быть пустым");
        }

        std::stringstream ss(input);
        if (!(ss >> value)) {
            throw InputException("Некорректное целое число: " + input);
        }

        // Проверяем, не осталось ли что-то в строке после числа
        std::string remaining;
        if (ss >> remaining) {
            throw InputException("Некорректный ввод. Введите только число");
        }

        if (value < min || value > max) {
            throw InputException("Число вне диапазона. Должно быть от " +
                std::to_string(min) + " до " + std::to_string(max));
        }

        validInput = true;
    }

    return value;
}

double ExpInput::getDouble(const std::string& prompt, double min, double max) {
    double value;
    bool validInput = false;

    while (!validInput) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);

        if (std::cin.fail()) {
            std::cin.clear();
            throw InputException("Ошибка ввода");
        }

        if (input.empty()) {
            throw InputException("Ввод не может быть пустым");
        }

        std::stringstream ss(input);
        if (!(ss >> value)) {
            throw InputException("Некорректное число: " + input);
        }

        std::string remaining;
        if (ss >> remaining) {
            throw InputException("Некорректный ввод. Введите только число");
        }

        if (value < min || value > max) {
            throw InputException("Число вне диапазона. Должно быть от " +
                std::to_string(min) + " до " + std::to_string(max));
        }

        validInput = true;
    }

    return value;
}

std::string ExpInput::getString(const std::string& prompt, bool allowEmpty, bool allowNumbers) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);

    if (std::cin.fail()) {
        std::cin.clear();
        throw InputException("Ошибка ввода строки");
    }

    if (!allowEmpty && value.empty()) {
        throw InputException("Строка не может быть пустой");
    }

    // Проверка на наличие цифр в строке
    if (!allowNumbers && containsNumbers(value)) {
        throw InputException("Строка не должна содержать цифры");
    }

    return value;
}

void ExpInput::clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool ExpInput::isNumber(const std::string& s) {
    if (s.empty()) return false;

    for (char c : s) {
        if (!std::isdigit(c) && c != '-' && c != '.') {
            return false;
        }
    }
    return true;
}

bool ExpInput::containsOnlyLetters(const std::string& s) {
    if (s.empty()) return false;

    for (char c : s) {
        if (!std::isalpha(c) && c != ' ' && c != '-') {
            return false;
        }
    }
    return true;
}

bool ExpInput::containsNumbers(const std::string& s) {
    for (char c : s) {
        if (std::isdigit(c)) {
            return true;
        }
    }
    return false;
}