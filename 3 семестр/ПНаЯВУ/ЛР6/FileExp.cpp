#include "FileExp.h"
#include <fstream>
#include <iostream>
#include "List.cpp"

template <typename Stream>
bool FileExp::isOpenFile(Stream& f)
{
    try
    {
        if (!f.is_open())
        {
            throw FileExp(30, ", файл не открыт");
        }

        if (f.fail() || f.bad())
        {
            throw FileExp(31, ", ошибка при открытии файла");
        }
        std::cout << "Файл открыт для чтения или записи" << std::endl;
        return true;
    }
    catch (const FileExp& e)
    {
        std::cout << e.message << e.error << " [ code: " << e.code << " ]" << std::endl;
        return false;
    }
}

template <typename Stream>
bool FileExp::isWriteFile(Stream& f)
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

template bool FileExp::isOpenFile<std::ifstream>(std::ifstream& f);
template bool FileExp::isOpenFile<std::ofstream>(std::ofstream& f);
template bool FileExp::isOpenFile<std::fstream>(std::fstream& f);
template bool FileExp::isOpenFile<std::basic_ifstream<char>>(std::basic_ifstream<char>& f);
template bool FileExp::isOpenFile<std::basic_ofstream<char>>(std::basic_ofstream<char>& f);

template bool FileExp::isWriteFile<std::ifstream>(std::ifstream& f);
template bool FileExp::isWriteFile<std::ofstream>(std::ofstream& f);
template bool FileExp::isWriteFile<std::fstream>(std::fstream& f);
template bool FileExp::isWriteFile<std::basic_ifstream<char>>(std::basic_ifstream<char>& f);
template bool FileExp::isWriteFile<std::basic_ofstream<char>>(std::basic_ofstream<char>& f);
