#ifndef FILE_H
#define FILE_H

#include "List.cpp"
#include <string>


class File
{
protected:
    std::string filename;

public:
    File(const std::string& name) : filename(name) {}
    virtual ~File() {}

    std::string getFilename() const { return filename; }
    void setFilename(const std::string& name) { filename = name; }
};

#endif

