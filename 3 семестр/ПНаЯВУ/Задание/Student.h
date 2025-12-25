#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

class Student {
public:
    static const int MAX_GRADES = 20;
    static const int MAX_STUDENTS = 100;

private:
    std::string lastName;
    std::string firstName;
    std::string subject;
    int grades[MAX_GRADES];
    int gradesCount;

public:
    Student();
    Student(const std::string& last, const std::string& first,
        const std::string& subj, const int* gr, int count);

    std::string getLastName() const { return lastName; }
    std::string getFirstName() const { return firstName; }
    std::string getSubject() const { return subject; }
    const int* getGrades() const { return grades; }
    int getGradesCount() const { return gradesCount; }

    double getAverageGrade() const;
    bool hasPassed() const;

    friend std::ostream& operator<<(std::ostream& os, const Student& student);
    friend std::istream& operator>>(std::istream& is, Student& student);

    void serialize(std::ostream& out) const;
    void deserialize(std::istream& in);

    bool addGrade(int grade);
    void clearGrades() { gradesCount = 0; }
};

#endif 