#ifndef FILE_H
#define FILE_H

#include "Student.h"
#include <string>

class File {
protected:
    std::string filename;

public:
    File(const std::string& fname) : filename(fname) {}
    virtual ~File() = default;

    virtual void write(Student* students, int count) = 0;
    virtual int read(Student* students) = 0; 

    std::string getFilename() const { return filename; }
    void setFilename(const std::string& fname) { filename = fname; }
};

#endif 