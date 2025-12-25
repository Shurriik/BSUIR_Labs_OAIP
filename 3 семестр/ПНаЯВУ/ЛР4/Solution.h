#ifndef SOLUTION_H
#define SOLUTION_H

#include "Human.h"
#include "University_teacher.h"
#include "Commission_member.h"
#include "Teacher_commission_member.h"



void demonstrateHuman();                          // Класс Human
void demonstrateUniversityTeacher();              // Класс UniversityTeacher
void demonstrateCommissionMember();               // Класс CommissionMember
void demonstrateTeacherCommissionMember();        // Класс TeacherCommissionMember
void demonstratePolymorphism();                   // Полиморфизма

void clearInputBuffer();
int safeInputInt(const std::string& prompt, int min = 0, int max = 1000000);
std::string safeInputString(const std::string& prompt);

void displayMenu();
void runMenu();

void demonstrateList();
void workWithList();

#endif