#include "FileBin.h"
#include "Exp.h"
#include <fstream>

void FileBin::write(Student* students, int count) {
    if (count < 0) {
        throw InputException("Количество студентов не может быть отрицательным");
    }

    if (count > Student::MAX_STUDENTS) {
        throw InputException("Слишком много студентов. Максимум: " + std::to_string(Student::MAX_STUDENTS));
    }

    std::ofstream out(filename, std::ios::binary);
    if (!out.is_open()) {
        throw FileException("Не удалось открыть файл для записи: " + filename);
    }

    out.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (int i = 0; i < count; ++i) {
        students[i].serialize(out);
    }

    out.close();
}

int FileBin::read(Student* students) {
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open()) {
        throw FileException("Не удалось открыть файл для чтения: " + filename);
    }

    int count;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));

    if (count < 0 || count > Student::MAX_STUDENTS) {
        in.close();
        throw FileException("Некорректное количество студентов в файле: " + std::to_string(count));
    }

    for (int i = 0; i < count; ++i) {
        students[i].deserialize(in);
    }

    in.close();
    return count;
}

void FileBin::createSuccessfulStudentsFile(const std::string& outputFile) {

    Student allStudents[Student::MAX_STUDENTS];
    int count = read(allStudents);


    Student successfulStudents[Student::MAX_STUDENTS];
    int successfulCount = 0;

    for (int i = 0; i < count; ++i) {
        if (allStudents[i].hasPassed()) {
            successfulStudents[successfulCount++] = allStudents[i];
        }
    }


    FileBin output(outputFile);
    output.write(successfulStudents, successfulCount);
}