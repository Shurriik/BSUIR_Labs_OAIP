#ifndef FILEEXP_H
#define FILEEXP_H

#include "File.h"

class FileExp : public File {
public:
    FileExp(const std::string& fname) : File(fname) {}

    void write(Student* students, int count) override;
    int read(Student* students) override;
};

#endif 