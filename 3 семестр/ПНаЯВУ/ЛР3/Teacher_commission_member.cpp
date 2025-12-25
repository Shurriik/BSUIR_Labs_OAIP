#include "Teacher_commission_member.h"
#include <iostream>
#include <limits>
#include <iomanip>

TeacherCommissionMember::TeacherCommissionMember()
    : Human(), UniversityTeacher(), CommissionMember(), commissionWorksCount(0) 
{
}

TeacherCommissionMember::TeacherCommissionMember(const std::string& first, const std::string& last,
    const std::string& pat, int year,
    const std::string& pos, const std::string& degree,
    const std::string& spec,
    const std::string& commission, int appointment,
    const std::string& cert)
    : Human(first, last, pat, year),
    UniversityTeacher(first, last, pat, year, pos, degree, spec),
    CommissionMember(first, last, pat, year, commission, appointment, cert),
    commissionWorksCount(0) 
{
}

int TeacherCommissionMember::getCommissionWorksCount() const 
{ 
    return commissionWorksCount; 
}
std::string TeacherCommissionMember::getCommissionWork(int index) const 
{
    if (index >= 0 && index < commissionWorksCount) 
    {
        return commissionWorks[index];
    }
    return "";
}

void TeacherCommissionMember::addCommissionWork(const std::string& work) 
{
    if (commissionWorksCount < MAX_COMMISSION_WORKS) 
    {
        commissionWorks[commissionWorksCount++] = work;
    }
}

void TeacherCommissionMember::removeCommissionWork(int index) 
{
    if (index >= 0 && index < commissionWorksCount)
    {
        for (int i = index; i < commissionWorksCount - 1; i++) 
        {
            commissionWorks[i] = commissionWorks[i + 1];
        }
        commissionWorksCount--;
    }
}

void TeacherCommissionMember::clearCommissionWorks() 
{
    commissionWorksCount = 0;
}

void TeacherCommissionMember::printInfo() const 
{
    UniversityTeacher::printInfo();
    std::cout << "Комиссия: " << getCommissionName() << std::endl;
    std::cout << "Год назначения в комиссию: " << getAppointmentYear() << std::endl;
    std::cout << "Номер свидетельства: " << getCertificateNumber() << std::endl;
    std::cout << "Работы в комиссии (" << commissionWorksCount << "):" << std::endl;
    for (int i = 0; i < commissionWorksCount; i++) 
    {
        std::cout << "  " << (i + 1) << ". " << commissionWorks[i] << std::endl;
    }
}

Human* TeacherCommissionMember::clone() const
{
    return new TeacherCommissionMember(*this);
}

void TeacherCommissionMember::inputFromStream(std::istream& is) 
{
    UniversityTeacher::inputFromStream(is);

    std::string commission;
    int appointment;
    std::string cert;

    std::cout << "Введите название комиссии: ";
    std::getline(is, commission);
    setCommissionName(commission);

    std::cout << "Введите год назначения в комиссию: ";
    is >> appointment;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    setAppointmentYear(appointment);

    std::cout << "Введите номер свидетельства: ";
    std::getline(is, cert);
    setCertificateNumber(cert);

    std::cout << "Введите количество работ в комиссии: ";
    int count;
    is >> count;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    commissionWorksCount = 0;
    for (int i = 0; i < count && i < MAX_COMMISSION_WORKS; i++) 
    {
        std::cout << "Введите работу в комиссии " << (i + 1) << ": ";
        std::string work;
        std::getline(is, work);
        commissionWorks[commissionWorksCount++] = work;
    }
}

void TeacherCommissionMember::outputToStream(std::ostream& os) const 
{
    UniversityTeacher::outputToStream(os);
    os << getCommissionName() << std::endl;
    os << getAppointmentYear() << std::endl;
    os << getCertificateNumber() << std::endl;
    os << commissionWorksCount << std::endl;
    for (int i = 0; i < commissionWorksCount; i++) 
    {
        os << commissionWorks[i] << std::endl;
    }
}

TeacherCommissionMember& TeacherCommissionMember::operator=(TeacherCommissionMember& other) 
{
    if (this != &other) 
    {
        UniversityTeacher::operator=(other);
        CommissionMember::operator=(other);

        commissionWorksCount = other.commissionWorksCount;
        for (int i = 0; i < commissionWorksCount; i++) 
        {
            commissionWorks[i] = other.commissionWorks[i];
        }
    }
    return *this;
}

void TeacherCommissionMember::printTableHeader() const 
{
    std::cout << std::left << std::setw(15) << "№"
        << std::setw(15) << "Тип"
        << std::setw(15) << "Фамилия"
        << std::setw(15) << "Имя"
        << std::setw(15) << "Отчество"
        << std::setw(15) << "Год рожд."
        << std::setw(15) << "Должность"
        << std::setw(15) << "Комиссия"
        << std::setw(15) << "Работ в ком." << std::endl;
    std::cout << std::string(130, '-') << std::endl;
}

void TeacherCommissionMember::printTableRow() const 
{
    std::cout << std::left
        << std::setw(15) << "Преподаватель-член"
        << std::setw(15) << getLastName()
        << std::setw(15) << getFirstName()
        << std::setw(15) << getPatronymic()
        << std::setw(15) << getBirthYear()
        << std::setw(15) << (getPosition().length() > 13 ? getPosition().substr(0, 10) + "..." : getPosition())
        << std::setw(15) << (getCommissionName().length() > 13 ? getCommissionName().substr(0, 10) + "..." : getCommissionName())
        << std::setw(15) << commissionWorksCount << std::endl;
}

std::ostream& operator<<(std::ostream& os, TeacherCommissionMember& tcm)
{
    os << dynamic_cast<UniversityTeacher&>(tcm)
        << std::setw(15) << tcm.getCommissionName() << "| ";
    return os;
}


std::istream& operator>>(std::istream& is, TeacherCommissionMember& tcm)
{

    is >> dynamic_cast<UniversityTeacher&>(tcm);

    std::cout << "Введите название комиссии: ";
    std::getline(is, tcm.commissionName);

    std::cout << "Введите год назначения в комиссию: ";
    is >> tcm.appointmentYear;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Введите номер свидетельства: ";
    std::getline(is, tcm.certificateNumber);

    std::cout << "Введите количество записей в автобиографии: ";
    int autoCount;
    is >> autoCount;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    tcm.autobiographyCount = 0;
    for (int i = 0; i < autoCount && i < CommissionMember::MAX_ENTRIES; i++) {
        std::cout << "Введите запись автобиографии " << (i + 1) << ": ";
        std::string entry;
        std::getline(is, entry);
        tcm.autobiography[tcm.autobiographyCount++] = entry;
    }

    std::cout << "Введите количество работ в комиссии: ";
    int workCount;
    is >> workCount;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    tcm.commissionWorksCount = 0;
    for (int i = 0; i < workCount && i < TeacherCommissionMember::MAX_COMMISSION_WORKS; i++) {
        std::cout << "Введите работу в комиссии " << (i + 1) << ": ";
        std::string work;
        std::getline(is, work);
        tcm.commissionWorks[tcm.commissionWorksCount++] = work;
    }
    return is;
}