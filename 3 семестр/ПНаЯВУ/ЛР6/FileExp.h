#ifndef FILEEXP_H
#define FILEEXP_H

#include "Exp.h"
#include "List.cpp"

class FileExp : public Exp
{
protected:
    char error[60];

public:
    FileExp() : Exp()
    {
        strcpy_s(error, 60, "");
    }

    FileExp(int c, const char* err) : Exp(c, "File Error")
    {
        strcpy_s(error, 60, err);
    }

    FileExp(const FileExp& other) : Exp(other)
    {
        strcpy_s(error, 60, other.error);
    }

    template<typename Stream>
    bool isOpenFile(Stream& f);

    template<typename Stream>
    bool isWriteFile(Stream& f);
};

#endif

