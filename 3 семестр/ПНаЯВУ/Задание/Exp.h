#ifndef EXP_H
#define EXP_H

#include <string>
#include <exception>

class FileException : public std::exception {
private:
    std::string message;

public:
    FileException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InputException : public std::exception {
private:
    std::string message;

public:
    InputException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class MenuException : public std::exception {
private:
    std::string message;

public:
    MenuException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif 