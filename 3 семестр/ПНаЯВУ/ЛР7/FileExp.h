#ifndef FILEEXP_H
#define FILEEXP_H

#include "Exp.h"
#include <cstring>
#include <fstream>
#include <iostream>

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
    bool isOpenFile(Stream& f)
    {
        try
        {
            if (!f.is_open())
            {
                throw FileExp(30, ", файл не открыт");
            }

            if (f.fail() || f.bad())
            {
                throw FileExp(31, ", ошибка при работе с файлом");
            }
            std::cout << "Файл открыт и готов к чтению/записи" << std::endl;
            return true;
        }
        catch (const FileExp& e)
        {
            std::cout << e.message << e.error << " [ code: " << e.code << " ]" << std::endl;
            return false;
        }
    }

    template<typename Stream>
    bool isWriteFile(Stream& f)
    {
        try
        {
            if (!f.is_open())
            {
                throw FileExp(40, ", файл не открыт");
            }
            if (f.fail() || f.bad())
            {
                throw FileExp(41, ", ошибка при записи в файл");
            }
            return true;
        }
        catch (const FileExp& e)
        {
            std::cout << e.message << e.error << " [ code: " << e.code << " ]" << std::endl;
            return false;
        }
    }
};

#endif

