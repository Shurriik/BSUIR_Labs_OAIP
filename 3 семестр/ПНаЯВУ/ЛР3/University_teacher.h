#ifndef UNIVERSITY_TEACHER_H
#define UNIVERSITY_TEACHER_H

#include "Human.h"
#include <string>

class UniversityTeacher : virtual public Human
{
protected:
    std::string position;                       // ƒолжность преподавател€
    std::string academicDegree;                 // ”чена€ степень
    std::string specialty;                      // —пециальность
    static const int MAX_WORKS = 100;           // ћаксимальное количество научных трудов
    std::string scientificWorks[MAX_WORKS];     // ћассив научных трудов
    int scientificWorksCount;                   // “екущее количество научных трудов

public:
    UniversityTeacher();                                        //  онструктор по умолчанию
    UniversityTeacher(const std::string& first, const std::string& last,
        const std::string& pat, int year,
        const std::string& pos, const std::string& degree,
        const std::string& spec);                               //  онструктор с параметрами
    ~UniversityTeacher() override = default;                    // ƒеструктор

    std::string getPosition() const;                                // должность
    std::string getAcademicDegree() const;                          // ученую степень
    std::string getSpecialty() const;                               // специальность
    int getScientificWorksCount() const;                            // количество научных работ
    std::string getScientificWork(int index) const;                 

    void setPosition(const std::string& pos);           // должность
    void setAcademicDegree(const std::string& degree);  // ученую степень
    void setSpecialty(const std::string& spec);         // специальность
    void addScientificWork(const std::string& work);    // научную работу
    void removeScientificWork(int index);               // научную работу по индексу
    void clearScientificWorks();                        

    void printInfo() const override;                        
    Human* clone() const override;                          
    void inputFromStream(std::istream& is) override;        
    void outputToStream(std::ostream& os) const override;   
    void printTableHeader() const override;                 
    void printTableRow() const override;         

    friend std::ostream& operator<<(std::ostream& os, UniversityTeacher& teacher);
    friend std::istream& operator>>(std::istream& is, UniversityTeacher& teacher);
};

#endif