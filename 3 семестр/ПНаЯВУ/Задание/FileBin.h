#ifndef FILEBIN_H
#define FILEBIN_H

#include "File.h"

class FileBin : public File {
public:
    FileBin(const std::string& fname) : File(fname) {}

    void write(Student* students, int count) override;
    int read(Student* students) override;

    void createSuccessfulStudentsFile(const std::string& outputFile);
};

#endif 