#include "University_teacher.h"
#include <iostream>
#include <limits>
#include <iomanip>

UniversityTeacher::UniversityTeacher() : Human(), position(""), academicDegree(""), specialty(""), scientificWorksCount(0)
{
}

UniversityTeacher::UniversityTeacher(const std::string& first, const std::string& last, const std::string& pat, int year, const std::string& pos, const std::string& degree,
    const std::string& spec) : Human(first, last, pat, year), position(pos), academicDegree(degree), specialty(spec), scientificWorksCount(0)
{
}

std::string UniversityTeacher::getPosition() const
{
    return position;
}
std::string UniversityTeacher::getAcademicDegree() const
{
    return academicDegree;
}
std::string UniversityTeacher::getSpecialty() const
{
    return specialty;
}
int UniversityTeacher::getScientificWorksCount() const
{
    return scientificWorksCount;
}
std::string UniversityTeacher::getScientificWork(int index) const
{
    if (index >= 0 && index < scientificWorksCount)
    {
        return scientificWorks[index];
    }
    return "";
}

void UniversityTeacher::setPosition(const std::string& pos)
{
    position = pos;
}
void UniversityTeacher::setAcademicDegree(const std::string& degree)
{
    academicDegree = degree;
}
void UniversityTeacher::setSpecialty(const std::string& spec)
{
    specialty = spec;
}

void UniversityTeacher::addScientificWork(const std::string& work)
{
    if (scientificWorksCount < MAX_WORKS)
    {
        scientificWorks[scientificWorksCount++] = work;
    }
}

void UniversityTeacher::removeScientificWork(int index)
{
    if (index >= 0 && index < scientificWorksCount)
    {
        for (int i = index; i < scientificWorksCount - 1; i++)
        {
            scientificWorks[i] = scientificWorks[i + 1];
        }
        scientificWorksCount--;
    }
}

void UniversityTeacher::clearScientificWorks()
{
    scientificWorksCount = 0;
}

void UniversityTeacher::printInfo() const
{
    Human::printInfo();
    std::cout << "Должность: " << position << std::endl;
    std::cout << "Ученая степень: " << academicDegree << std::endl;
    std::cout << "Специальность: " << specialty << std::endl;
    std::cout << "Научные труды (" << scientificWorksCount << "):" << std::endl;
    for (int i = 0; i < scientificWorksCount; i++)
    {
        std::cout << "  " << (i + 1) << ". " << scientificWorks[i] << std::endl;
    }
}

Human* UniversityTeacher::clone() const
{
    return new UniversityTeacher(*this);
}

void UniversityTeacher::inputFromStream(std::istream& is)
{
    Human::inputFromStream(is);

    std::cout << "Введите должность: ";
    std::getline(is, position);
    std::cout << "Введите ученую степень: ";
    std::getline(is, academicDegree);
    std::cout << "Введите специальность: ";
    std::getline(is, specialty);

    std::cout << "Введите количество научных трудов: ";
    int count;
    is >> count;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    scientificWorksCount = 0;
    for (int i = 0; i < count && i < MAX_WORKS; i++)
    {
        std::cout << "Введите научный труд " << (i + 1) << ": ";
        std::string work;
        std::getline(is, work);
        scientificWorks[scientificWorksCount++] = work;
    }
}

void UniversityTeacher::outputToStream(std::ostream& os) const
{
    Human::outputToStream(os);
    os << position << std::endl;
    os << academicDegree << std::endl;
    os << specialty << std::endl;
    os << scientificWorksCount << std::endl;
    for (int i = 0; i < scientificWorksCount; i++)
    {
        os << scientificWorks[i] << std::endl;
    }
}
void UniversityTeacher::printTableHeader() const
{
    std::cout << std::left << std::
        setw(15) << "№"
        << std::setw(15) << "Тип"
        << std::setw(15) << "Фамилия"
        << std::setw(15) << "Имя"
        << std::setw(15) << "Отчество"
        << std::setw(15) << "Год рожд."
        << std::setw(15) << "Должность"
        << std::setw(15) << "Степень"
        << std::setw(15) << "Науч. работы" << std::endl;
    std::cout << std::string(135, '-') << std::endl;
}

void UniversityTeacher::printTableRow() const
{
    std::cout << std::left
        << std::setw(15) << "Преподаватель"
        << std::setw(15) << lastName
        << std::setw(15) << firstName
        << std::setw(15) << patronymic
        << std::setw(15) << birthYear
        << std::setw(15) << (position.length() > 18 ? position.substr(0, 15) + "..." : position)
        << std::setw(15) << (academicDegree.length() > 13 ? academicDegree.substr(0, 10) + "..." : academicDegree)
        << std::setw(15) << scientificWorksCount << std::endl;
}

std::ostream& operator<<(std::ostream& os, UniversityTeacher& teacher)
{
    os << static_cast<Human&>(teacher);
    os << std::setw(15) << teacher.position << "| "
        << std::setw(15) << teacher.academicDegree << "| "
        << std::setw(15) << teacher.specialty << "| ";
    return os;
}

std::istream& operator>>(std::istream& is, UniversityTeacher& teacher)
{
    is >> static_cast<Human&>(teacher);

    std::cout << "Введите должность: ";
    std::getline(is, teacher.position);
    std::cout << "Введите ученую степень: ";
    std::getline(is, teacher.academicDegree);
    std::cout << "Введите специальность: ";
    std::getline(is, teacher.specialty);

    std::cout << "Введите количество научных трудов: ";
    int count;
    is >> count;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    teacher.scientificWorksCount = 0;
    for (int i = 0; i < count && i < UniversityTeacher::MAX_WORKS; i++) {
        std::cout << "Введите научный труд " << (i + 1) << ": ";
        std::string work;
        std::getline(is, work);
        teacher.scientificWorks[teacher.scientificWorksCount++] = work;
    }
    return is;
}