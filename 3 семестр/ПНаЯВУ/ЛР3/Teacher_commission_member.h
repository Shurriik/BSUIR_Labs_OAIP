#ifndef TEACHER_COMMISSION_MEMBER_H
#define TEACHER_COMMISSION_MEMBER_H

#include "University_teacher.h"
#include "Commission_member.h"
#include <string>



class TeacherCommissionMember : public UniversityTeacher, public CommissionMember
{
private:
    static const int MAX_COMMISSION_WORKS = 100;                                // Максимальное количество работ
    std::string commissionWorks[MAX_COMMISSION_WORKS];                          // Массив работ выполненных в комиссии
    

public:
    TeacherCommissionMember();                                                  // Конструктор по умолчанию
    TeacherCommissionMember(const std::string& first, const std::string& last,
        const std::string& pat, int year,
        const std::string& pos, const std::string& degree,
        const std::string& spec,
        const std::string& commission, int appointment,
        const std::string& cert);                                               // Конструктор с параметрами
    ~TeacherCommissionMember() override = default;                              // Деструктор
    int commissionWorksCount;                                                   // Текущее количество работ
    int getCommissionWorksCount() const;
    std::string getCommissionWork(int index) const;             // Получить работу в комиссии по индексу
    void addCommissionWork(const std::string& work);            // Добавить работу в комиссии
    void removeCommissionWork(int index);                       // Удалить работу из комиссии по индексу
    void clearCommissionWorks();                                // Очистить список работ в комиссии

    void printInfo() const override;
    Human* clone() const override;
    void inputFromStream(std::istream& is) override;
    void outputToStream(std::ostream& os) const override;
    void printTableHeader() const override;
    void printTableRow() const override;

    TeacherCommissionMember& operator=(TeacherCommissionMember& other);

    friend std::ostream& operator<<(std::ostream& os, TeacherCommissionMember& tcm);
    friend std::istream& operator>>(std::istream& is, TeacherCommissionMember& tcm);

};
#endif