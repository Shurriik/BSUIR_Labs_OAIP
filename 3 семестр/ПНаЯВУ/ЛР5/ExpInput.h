#ifndef EXPINPUT_H
#define EXPINPUT_H

#include "Exp.h"
#include <iostream>
#include <string>
#include <climits>
#include <locale>
#include <codecvt>

class ExpInput : public Exp
{
    char err[MAX_STR];

public:
    ExpInput() : Exp()
    {
        err[0] = '\0';
        // Устанавливаем локаль для поддержки русского языка
        std::locale::global(std::locale(""));
        std::wcout.imbue(std::locale());
        std::wcin.imbue(std::locale());
    };

    ExpInput(const char* err, int code) : Exp(code, "Ошибка ввода")
    {
        strcpy_s(this->err, err);
        std::locale::global(std::locale(""));
        std::wcout.imbue(std::locale());
        std::wcin.imbue(std::locale());
    };

    ExpInput(const Exp& other) : Exp(other) {};

    ~ExpInput() = default;

    int isNumber(std::istream& input);
    int isNumber(std::istream& input, int minInt, int maxInt);
    bool isBool(std::istream& input);
    std::string isString(std::istream& input);
    std::string isStringWithNumbers(std::istream& input);
    std::string isStringRussian(std::istream& input); // Новая функция для русского ввода
    std::string isStringRussianWithNumbers(std::istream& input); // Для русского с цифрами
};

#endif