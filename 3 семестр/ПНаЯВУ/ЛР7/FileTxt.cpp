#include "FileTxt.h"
#include "List.h"
#include "List.cpp"
#include "University_teacher.h"
#include "Commission_member.h"
#include "Teacher_commission_member.h"
#include <fstream>
#include <iostream>
#include <type_traits>



template <class T>
void FileTxt<T>::writeLinkedList(const List<T>& list)
{
    std::ofstream file(filename);
    FileExp fileExp;

    if (!fileExp.isOpenFile(file))
    {
        return;
    }

    int size = list.getSize();
    file << size << std::endl;

    for (int i = 0; i < size; i++)
    {
        T item = list.get(i);

        // Определяем тип объекта для Human*
        if (std::is_same<T, Human*>::value)
        {
            int type = 0;
            if (dynamic_cast<TeacherCommissionMember*>(item))
            {
                type = 4;
            }
            else if (dynamic_cast<UniversityTeacher*>(item))
            {
                type = 2;
            }
            else if (dynamic_cast<CommissionMember*>(item))
            {
                type = 3;
            }
            else
            {
                type = 1;
            }

            file << type << std::endl;

            // Записываем данные объекта
            if (type == 1)
            {
                Human* h = item;
                file << h->getFirstName() << std::endl;
                file << h->getLastName() << std::endl;
                file << h->getPatronymic() << std::endl;
                file << h->getBirthYear() << std::endl;
            }
            else if (type == 2)
            {
                UniversityTeacher* t = dynamic_cast<UniversityTeacher*>(item);
                // Базовые данные
                file << t->getFirstName() << std::endl;
                file << t->getLastName() << std::endl;
                file << t->getPatronymic() << std::endl;
                file << t->getBirthYear() << std::endl;

                // Данные UniversityTeacher
                file << t->getPosition() << std::endl;
                file << t->getAcademicDegree() << std::endl;
                file << t->getSpecialty() << std::endl;

                int worksCount = t->getScientificWorksCount();
                file << worksCount << std::endl;
                for (int j = 0; j < worksCount; j++)
                {
                    file << t->getScientificWork(j) << std::endl;
                }
            }
            else if (type == 3)
            {
                CommissionMember* cm = dynamic_cast<CommissionMember*>(item);
                // Базовые данные
                file << cm->getFirstName() << std::endl;
                file << cm->getLastName() << std::endl;
                file << cm->getPatronymic() << std::endl;
                file << cm->getBirthYear() << std::endl;

                // Данные CommissionMember
                file << cm->getCommissionName() << std::endl;
                file << cm->getAppointmentYear() << std::endl;
                file << cm->getCertificateNumber() << std::endl;

                int entriesCount = cm->getAutobiographyCount();
                file << entriesCount << std::endl;
                for (int j = 0; j < entriesCount; j++)
                {
                    file << cm->getAutobiographyEntry(j) << std::endl;
                }
            }
            else if (type == 4)
            {
                TeacherCommissionMember* tcm = dynamic_cast<TeacherCommissionMember*>(item);
                // Базовые данные
                file << tcm->getFirstName() << std::endl;
                file << tcm->getLastName() << std::endl;
                file << tcm->getPatronymic() << std::endl;
                file << tcm->getBirthYear() << std::endl;

                // Данные UniversityTeacher
                file << tcm->getPosition() << std::endl;
                file << tcm->getAcademicDegree() << std::endl;
                file << tcm->getSpecialty() << std::endl;

                int worksCount = tcm->getScientificWorksCount();
                file << worksCount << std::endl;
                for (int j = 0; j < worksCount; j++)
                {
                    file << tcm->getScientificWork(j) << std::endl;
                }

                // Данные CommissionMember
                file << tcm->getCommissionName() << std::endl;
                file << tcm->getAppointmentYear() << std::endl;
                file << tcm->getCertificateNumber() << std::endl;

                int entriesCount = tcm->getAutobiographyCount();
                file << entriesCount << std::endl;
                for (int j = 0; j < entriesCount; j++)
                {
                    file << tcm->getAutobiographyEntry(j) << std::endl;
                }

                // Данные TeacherCommissionMember
                int commissionWorksCount = tcm->getCommissionWorksCount();
                file << commissionWorksCount << std::endl;
                for (int j = 0; j < commissionWorksCount; j++)
                {
                    file << tcm->getCommissionWork(j) << std::endl;
                }
            }
        }
    }

    file.close();
    std::cout << "Данные успешно записаны в текстовый файл: " << filename << std::endl;
}

template <class T>
void FileTxt<T>::readLinkedList(List<T>& list)
{
    std::ifstream file(filename);
    FileExp fileExp;

    if (!fileExp.isOpenFile(file))
    {
        return;
    }

    list.clear();
    int size;
    file >> size;
    file.ignore();

    for (int i = 0; i < size; i++)
    {
        if (std::is_same<T, Human*>::value)
        {
            int type;
            file >> type;
            file.ignore();

            Human* item = nullptr;

            if (type == 1)
            {
                item = new Human();
                std::string firstName, lastName, patronymic;
                int year;
                std::getline(file, firstName);
                std::getline(file, lastName);
                std::getline(file, patronymic);
                file >> year;
                file.ignore();
                item->setFirstName(firstName);
                item->setLastName(lastName);
                item->setPatronymic(patronymic);
                item->setBirthYear(year);
            }
            else if (type == 2)
            {
                item = new UniversityTeacher();
                UniversityTeacher* t = dynamic_cast<UniversityTeacher*>(item);

                std::string firstName, lastName, patronymic;
                int year;
                std::getline(file, firstName);
                std::getline(file, lastName);
                std::getline(file, patronymic);
                file >> year;
                file.ignore();
                t->setFirstName(firstName);
                t->setLastName(lastName);
                t->setPatronymic(patronymic);
                t->setBirthYear(year);

                // Данные UniversityTeacher
                std::string position, degree, specialty;
                std::getline(file, position);
                std::getline(file, degree);
                std::getline(file, specialty);
                t->setPosition(position);
                t->setAcademicDegree(degree);
                t->setSpecialty(specialty);

                int worksCount;
                file >> worksCount;
                file.ignore();
                t->clearScientificWorks();
                for (int j = 0; j < worksCount; j++)
                {
                    std::string work;
                    std::getline(file, work);
                    t->addScientificWork(work);
                }
            }
            else if (type == 3)
            {
                item = new CommissionMember();
                CommissionMember* cm = dynamic_cast<CommissionMember*>(item);

                std::string firstName, lastName, patronymic;
                int year;
                std::getline(file, firstName);
                std::getline(file, lastName);
                std::getline(file, patronymic);
                file >> year;
                file.ignore();
                cm->setFirstName(firstName);
                cm->setLastName(lastName);
                cm->setPatronymic(patronymic);
                cm->setBirthYear(year);

                // Данные CommissionMember
                std::string commissionName, certNumber;
                int appointmentYear;
                std::getline(file, commissionName);
                file >> appointmentYear;
                file.ignore();
                std::getline(file, certNumber);
                cm->setCommissionName(commissionName);
                cm->setAppointmentYear(appointmentYear);
                cm->setCertificateNumber(certNumber);

                int entriesCount;
                file >> entriesCount;
                file.ignore();
                cm->clearAutobiography();
                for (int j = 0; j < entriesCount; j++)
                {
                    std::string entry;
                    std::getline(file, entry);
                    cm->addAutobiographyEntry(entry);
                }
            }
            else if (type == 4)
            {
                item = new TeacherCommissionMember();
                TeacherCommissionMember* tcm = dynamic_cast<TeacherCommissionMember*>(item);

                std::string firstName, lastName, patronymic;
                int year;
                std::getline(file, firstName);
                std::getline(file, lastName);
                std::getline(file, patronymic);
                file >> year;
                file.ignore();
                tcm->setFirstName(firstName);
                tcm->setLastName(lastName);
                tcm->setPatronymic(patronymic);
                tcm->setBirthYear(year);

                // Данные UniversityTeacher
                std::string position, degree, specialty;
                std::getline(file, position);
                std::getline(file, degree);
                std::getline(file, specialty);
                tcm->setPosition(position);
                tcm->setAcademicDegree(degree);
                tcm->setSpecialty(specialty);

                int worksCount;
                file >> worksCount;
                file.ignore();
                tcm->clearScientificWorks();
                for (int j = 0; j < worksCount; j++)
                {
                    std::string work;
                    std::getline(file, work);
                    tcm->addScientificWork(work);
                }

                // Данные CommissionMember
                std::string commissionName, certNumber;
                int appointmentYear;
                std::getline(file, commissionName);
                file >> appointmentYear;
                file.ignore();
                std::getline(file, certNumber);
                tcm->setCommissionName(commissionName);
                tcm->setAppointmentYear(appointmentYear);
                tcm->setCertificateNumber(certNumber);

                int entriesCount;
                file >> entriesCount;
                file.ignore();
                tcm->clearAutobiography();
                for (int j = 0; j < entriesCount; j++)
                {
                    std::string entry;
                    std::getline(file, entry);
                    tcm->addAutobiographyEntry(entry);
                }

                // Данные TeacherCommissionMember
                int commissionWorksCount;
                file >> commissionWorksCount;
                file.ignore();
                tcm->clearCommissionWorks();
                for (int j = 0; j < commissionWorksCount; j++)
                {
                    std::string work;
                    std::getline(file, work);
                    tcm->addCommissionWork(work);
                }
            }

            if (item != nullptr)
            {
                list.addToEnd(item);
            }
        }
    }

    file.close();
    std::cout << "Данные успешно загружены из текстового файла: " << filename << std::endl;
}

template <class T>
FileTxt<T>& FileTxt<T>::operator<<(const List<T>& list)
{
    writeLinkedList(list);
    return *this;
}

template <class T>
FileTxt<T>& FileTxt<T>::operator>>(List<T>& list)
{
    readLinkedList(list);
    return *this;
}



