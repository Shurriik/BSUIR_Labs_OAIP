#include "Commission_member.h"
#include <iostream>
#include <limits>
#include <iomanip>

CommissionMember::CommissionMember(): Human(), commissionName(""), appointmentYear(0), certificateNumber(""), autobiographyCount(0) 
{
}

CommissionMember::CommissionMember(const std::string& first, const std::string& last, const std::string& pat, int year, const std::string& commission, int appointment,
const std::string& cert): Human(first, last, pat, year), commissionName(commission), appointmentYear(appointment), certificateNumber(cert), autobiographyCount(0) 
{
}

std::string CommissionMember::getCommissionName() const 
{ 
    return commissionName; 
}
int CommissionMember::getAppointmentYear() const
{ 
    return appointmentYear; 
}
std::string CommissionMember::getCertificateNumber() const 
{ 
    return certificateNumber; 
}
int CommissionMember::getAutobiographyCount() const 
{ 
    return autobiographyCount;
}
std::string CommissionMember::getAutobiographyEntry(int index) const
{
    if (index >= 0 && index < autobiographyCount)
    {
        return autobiography[index];
    }
    return "";
}

void CommissionMember::setCommissionName(const std::string& commission) 
{ 
    commissionName = commission; 
}
void CommissionMember::setAppointmentYear(int year) 
{ 
    appointmentYear = year; 
}
void CommissionMember::setCertificateNumber(const std::string& cert) 
{ 
    certificateNumber = cert; 
}

void CommissionMember::addAutobiographyEntry(const std::string& entry) 
{
    if (autobiographyCount < MAX_ENTRIES) 
    {
        autobiography[autobiographyCount++] = entry;
    }
}

void CommissionMember::removeAutobiographyEntry(int index) 
{
    if (index >= 0 && index < autobiographyCount) 
    {
        for (int i = index; i < autobiographyCount - 1; i++) 
        {
            autobiography[i] = autobiography[i + 1];
        }
        autobiographyCount--;
    }
}

void CommissionMember::clearAutobiography()
{
    autobiographyCount = 0;
}

void CommissionMember::printInfo() const 
{
    Human::printInfo();
    std::cout << "Название комиссии: " << commissionName << std::endl;
    std::cout << "Год назначения: " << appointmentYear << std::endl;
    std::cout << "Номер свидетельства: " << certificateNumber << std::endl;
    std::cout << "Автобиография (" << autobiographyCount << " записей):" << std::endl;
    for (int i = 0; i < autobiographyCount; i++) 
    {
        std::cout << "  " << (i + 1) << ". " << autobiography[i] << std::endl;
    }
}

Human* CommissionMember::clone() const 
{
    return new CommissionMember(*this);
}

void CommissionMember::inputFromStream(std::istream& is) 
{
    Human::inputFromStream(is);

    std::cout << "Введите название комиссии: ";
    std::getline(is, commissionName);
    std::cout << "Введите год назначения: ";
    is >> appointmentYear;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите номер свидетельства: ";
    std::getline(is, certificateNumber);

    std::cout << "Введите количество записей в автобиографии: ";
    int count;
    is >> count;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    autobiographyCount = 0;
    for (int i = 0; i < count && i < MAX_ENTRIES; i++) 
    {
        std::cout << "Введите запись автобиографии " << (i + 1) << ": ";
        std::string entry;
        std::getline(is, entry);
        autobiography[autobiographyCount++] = entry;
    }
}

void CommissionMember::outputToStream(std::ostream& os) const 
{
    Human::outputToStream(os);
    os << commissionName << std::endl;
    os << appointmentYear << std::endl;
    os << certificateNumber << std::endl;
    os << autobiographyCount << std::endl;
    for (int i = 0; i < autobiographyCount; i++) 
    {
        os << autobiography[i] << std::endl;
    }
}

void CommissionMember::printTableHeader() const 
{
    std::cout << std::left << std::setw(15) << "№"
        << std::setw(15) << "Тип"
        << std::setw(15) << "Фамилия"
        << std::setw(15) << "Имя"
        << std::setw(15) << "Отчество"
        << std::setw(6) << "Год рожд."
        << std::setw(15) << "Комиссия"
        << std::setw(15) << "Год назн."
        << std::setw(15) << "Записей" << std::endl;
    std::cout << std::string(120, '-') << std::endl;
}

void CommissionMember::printTableRow() const 
{
    std::cout << std::left
        << std::setw(15) << "Член комиссии"
        << std::setw(15) << lastName
        << std::setw(15) << firstName
        << std::setw(15) << patronymic
        << std::setw(6) << birthYear
        << std::setw(15) << (commissionName.length() > 18 ? commissionName.substr(0, 15) + "..." : commissionName)
        << std::setw(15) << appointmentYear
        << std::setw(15) << autobiographyCount << std::endl;
}

std::ostream& operator<<(std::ostream& os, CommissionMember& cm)
{
    os << dynamic_cast<Human&>(cm)
        << std::setw(15) << "" << "| "  
        << std::setw(15) << "" << "| "  
        << std::setw(15) << cm.getCommissionName() << "| "
        << std::setw(15) << "" << "|";   
    return os;
}

std::istream& operator>>(std::istream& is, CommissionMember& member)
{
    is >> static_cast<Human&>(member);

    std::cout << "Введите название комиссии: ";
    std::getline(is, member.commissionName);
    std::cout << "Введите год назначения: ";
    is >> member.appointmentYear;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите номер свидетельства: ";
    std::getline(is, member.certificateNumber);

    std::cout << "Введите количество записей в автобиографии: ";
    int count;
    is >> count;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    member.autobiographyCount = 0;
    for (int i = 0; i < count && i < CommissionMember::MAX_ENTRIES; i++) {
        std::cout << "Введите запись автобиографии " << (i + 1) << ": ";
        std::string entry;
        std::getline(is, entry);
        member.autobiography[member.autobiographyCount++] = entry;
    }
    return is;
}