#ifndef EXP_H
#define EXP_H

#include <cstring>
#include <climits>

#define MAX_STR 256

class Exp
{
protected:
    int code;
    char message[MAX_STR];

public:
    Exp()
    {
        code = 0;
        message[0] = '\0';
    }

    Exp(int code, const char* message)
    {
        this->code = code;
        strcpy_s(this->message, message);
    }

    Exp(const Exp& other)
    {
        code = other.code;
        strcpy_s(message, other.message);
    }

    ~Exp() = default;
};

#endif

