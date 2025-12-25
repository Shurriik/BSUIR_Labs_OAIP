#include "FileBin.h"
#include "List.h"
#include "List.cpp"
#include "University_teacher.h"
#include "Commission_member.h"
#include "Teacher_commission_member.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <type_traits>

template <class T>
FileBin<T>::FileBin(const std::string& name) : File(name) {}

template <class T>
void FileBin<T>::writeLinkedList(const List<T>& list)
{
    std::ofstream file(filename, std::ios::binary);
    FileExp fileExp;

    if (!fileExp.isOpenFile(file))
    {
        return;
    }

    int size = list.getSize();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));

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

            file.write(reinterpret_cast<const char*>(&type), sizeof(type));

            // Записываем данные объекта
            if (type == 1)
            {
                Human* h = item;
                // Записываем строки
                size_t len = h->getFirstName().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(h->getFirstName().c_str(), len);

                len = h->getLastName().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(h->getLastName().c_str(), len);

                len = h->getPatronymic().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(h->getPatronymic().c_str(), len);

                int year = h->getBirthYear();
                file.write(reinterpret_cast<const char*>(&year), sizeof(year));
            }
            else if (type == 2)
            {
                UniversityTeacher* t = dynamic_cast<UniversityTeacher*>(item);
                // Базовые данные
                size_t len = t->getFirstName().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(t->getFirstName().c_str(), len);

                len = t->getLastName().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(t->getLastName().c_str(), len);

                len = t->getPatronymic().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(t->getPatronymic().c_str(), len);

                int year = t->getBirthYear();
                file.write(reinterpret_cast<const char*>(&year), sizeof(year));

                // Данные UniversityTeacher
                len = t->getPosition().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(t->getPosition().c_str(), len);

                len = t->getAcademicDegree().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(t->getAcademicDegree().c_str(), len);

                len = t->getSpecialty().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(t->getSpecialty().c_str(), len);

                int worksCount = t->getScientificWorksCount();
                file.write(reinterpret_cast<const char*>(&worksCount), sizeof(worksCount));
                for (int j = 0; j < worksCount; j++)
                {
                    len = t->getScientificWork(j).length();
                    file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                    file.write(t->getScientificWork(j).c_str(), len);
                }
            }
            else if (type == 3)
            {
                CommissionMember* cm = dynamic_cast<CommissionMember*>(item);
                // Базовые данные
                size_t len = cm->getFirstName().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(cm->getFirstName().c_str(), len);

                len = cm->getLastName().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(cm->getLastName().c_str(), len);

                len = cm->getPatronymic().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(cm->getPatronymic().c_str(), len);

                int year = cm->getBirthYear();
                file.write(reinterpret_cast<const char*>(&year), sizeof(year));

                // Данные CommissionMember
                len = cm->getCommissionName().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(cm->getCommissionName().c_str(), len);

                int appointmentYear = cm->getAppointmentYear();
                file.write(reinterpret_cast<const char*>(&appointmentYear), sizeof(appointmentYear));

                len = cm->getCertificateNumber().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(cm->getCertificateNumber().c_str(), len);

                int entriesCount = cm->getAutobiographyCount();
                file.write(reinterpret_cast<const char*>(&entriesCount), sizeof(entriesCount));
                for (int j = 0; j < entriesCount; j++)
                {
                    len = cm->getAutobiographyEntry(j).length();
                    file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                    file.write(cm->getAutobiographyEntry(j).c_str(), len);
                }
            }
            else if (type == 4)
            {
                TeacherCommissionMember* tcm = dynamic_cast<TeacherCommissionMember*>(item);
                // Базовые данные
                size_t len = tcm->getFirstName().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(tcm->getFirstName().c_str(), len);

                len = tcm->getLastName().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(tcm->getLastName().c_str(), len);

                len = tcm->getPatronymic().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(tcm->getPatronymic().c_str(), len);

                int year = tcm->getBirthYear();
                file.write(reinterpret_cast<const char*>(&year), sizeof(year));

                // Данные UniversityTeacher
                len = tcm->getPosition().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(tcm->getPosition().c_str(), len);

                len = tcm->getAcademicDegree().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(tcm->getAcademicDegree().c_str(), len);

                len = tcm->getSpecialty().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(tcm->getSpecialty().c_str(), len);

                int worksCount = tcm->getScientificWorksCount();
                file.write(reinterpret_cast<const char*>(&worksCount), sizeof(worksCount));
                for (int j = 0; j < worksCount; j++)
                {
                    len = tcm->getScientificWork(j).length();
                    file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                    file.write(tcm->getScientificWork(j).c_str(), len);
                }

                // Данные CommissionMember
                len = tcm->getCommissionName().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(tcm->getCommissionName().c_str(), len);

                int appointmentYear = tcm->getAppointmentYear();
                file.write(reinterpret_cast<const char*>(&appointmentYear), sizeof(appointmentYear));

                len = tcm->getCertificateNumber().length();
                file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                file.write(tcm->getCertificateNumber().c_str(), len);

                int entriesCount = tcm->getAutobiographyCount();
                file.write(reinterpret_cast<const char*>(&entriesCount), sizeof(entriesCount));
                for (int j = 0; j < entriesCount; j++)
                {
                    len = tcm->getAutobiographyEntry(j).length();
                    file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                    file.write(tcm->getAutobiographyEntry(j).c_str(), len);
                }

                // Данные TeacherCommissionMember
                int commissionWorksCount = tcm->getCommissionWorksCount();
                file.write(reinterpret_cast<const char*>(&commissionWorksCount), sizeof(commissionWorksCount));
                for (int j = 0; j < commissionWorksCount; j++)
                {
                    len = tcm->getCommissionWork(j).length();
                    file.write(reinterpret_cast<const char*>(&len), sizeof(len));
                    file.write(tcm->getCommissionWork(j).c_str(), len);
                }
            }
        }
    }

    file.close();
    std::cout << "Данные успешно записаны в бинарный файл: " << filename << std::endl;
}

template <class T>
void FileBin<T>::readLinkedList(List<T>& list)
{
    std::ifstream file(filename, std::ios::binary);
    FileExp fileExp;

    if (!fileExp.isOpenFile(file))
    {
        return;
    }

    list.clear();
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));

    for (int i = 0; i < size; i++)
    {
        if (std::is_same<T, Human*>::value)
        {
            int type;
            file.read(reinterpret_cast<char*>(&type), sizeof(type));

            Human* item = nullptr;

            if (type == 1)
            {
                item = new Human();
                // Читаем строки
                size_t len;
                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                char* buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                item->setFirstName(std::string(buffer));
                delete[] buffer;

                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                item->setLastName(std::string(buffer));
                delete[] buffer;

                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                item->setPatronymic(std::string(buffer));
                delete[] buffer;

                int year;
                file.read(reinterpret_cast<char*>(&year), sizeof(year));
                item->setBirthYear(year);
            }
            else if (type == 2)
            {
                item = new UniversityTeacher();
                UniversityTeacher* t = dynamic_cast<UniversityTeacher*>(item);

                // Базовые данные
                size_t len;
                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                char* buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                t->setFirstName(std::string(buffer));
                delete[] buffer;

                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                t->setLastName(std::string(buffer));
                delete[] buffer;

                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                t->setPatronymic(std::string(buffer));
                delete[] buffer;

                int year;
                file.read(reinterpret_cast<char*>(&year), sizeof(year));
                t->setBirthYear(year);

                // Данные UniversityTeacher
                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                t->setPosition(std::string(buffer));
                delete[] buffer;

                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                t->setAcademicDegree(std::string(buffer));
                delete[] buffer;

                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                t->setSpecialty(std::string(buffer));
                delete[] buffer;

                int worksCount;
                file.read(reinterpret_cast<char*>(&worksCount), sizeof(worksCount));
                t->clearScientificWorks();
                for (int j = 0; j < worksCount; j++)
                {
                    file.read(reinterpret_cast<char*>(&len), sizeof(len));
                    buffer = new char[len + 1];
                    file.read(buffer, len);
                    buffer[len] = '\0';
                    t->addScientificWork(std::string(buffer));
                    delete[] buffer;
                }
            }
            else if (type == 3)
            {
                item = new CommissionMember();
                CommissionMember* cm = dynamic_cast<CommissionMember*>(item);

                // Базовые данные
                size_t len;
                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                char* buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                cm->setFirstName(std::string(buffer));
                delete[] buffer;

                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                cm->setLastName(std::string(buffer));
                delete[] buffer;

                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                cm->setPatronymic(std::string(buffer));
                delete[] buffer;

                int year;
                file.read(reinterpret_cast<char*>(&year), sizeof(year));
                cm->setBirthYear(year);

                // Данные CommissionMember
                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                cm->setCommissionName(std::string(buffer));
                delete[] buffer;

                int appointmentYear;
                file.read(reinterpret_cast<char*>(&appointmentYear), sizeof(appointmentYear));
                cm->setAppointmentYear(appointmentYear);

                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                cm->setCertificateNumber(std::string(buffer));
                delete[] buffer;

                int entriesCount;
                file.read(reinterpret_cast<char*>(&entriesCount), sizeof(entriesCount));
                cm->clearAutobiography();
                for (int j = 0; j < entriesCount; j++)
                {
                    file.read(reinterpret_cast<char*>(&len), sizeof(len));
                    buffer = new char[len + 1];
                    file.read(buffer, len);
                    buffer[len] = '\0';
                    cm->addAutobiographyEntry(std::string(buffer));
                    delete[] buffer;
                }
            }
            else if (type == 4)
            {
                item = new TeacherCommissionMember();
                TeacherCommissionMember* tcm = dynamic_cast<TeacherCommissionMember*>(item);

                // Базовые данные
                size_t len;
                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                char* buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                tcm->setFirstName(std::string(buffer));
                delete[] buffer;

                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                tcm->setLastName(std::string(buffer));
                delete[] buffer;

                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                tcm->setPatronymic(std::string(buffer));
                delete[] buffer;

                int year;
                file.read(reinterpret_cast<char*>(&year), sizeof(year));
                tcm->setBirthYear(year);

                // Данные UniversityTeacher
                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                tcm->setPosition(std::string(buffer));
                delete[] buffer;

                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                tcm->setAcademicDegree(std::string(buffer));
                delete[] buffer;

                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                tcm->setSpecialty(std::string(buffer));
                delete[] buffer;

                int worksCount;
                file.read(reinterpret_cast<char*>(&worksCount), sizeof(worksCount));
                tcm->clearScientificWorks();
                for (int j = 0; j < worksCount; j++)
                {
                    file.read(reinterpret_cast<char*>(&len), sizeof(len));
                    buffer = new char[len + 1];
                    file.read(buffer, len);
                    buffer[len] = '\0';
                    tcm->addScientificWork(std::string(buffer));
                    delete[] buffer;
                }

                // Данные CommissionMember
                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                tcm->setCommissionName(std::string(buffer));
                delete[] buffer;

                int appointmentYear;
                file.read(reinterpret_cast<char*>(&appointmentYear), sizeof(appointmentYear));
                tcm->setAppointmentYear(appointmentYear);

                file.read(reinterpret_cast<char*>(&len), sizeof(len));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                tcm->setCertificateNumber(std::string(buffer));
                delete[] buffer;

                int entriesCount;
                file.read(reinterpret_cast<char*>(&entriesCount), sizeof(entriesCount));
                tcm->clearAutobiography();
                for (int j = 0; j < entriesCount; j++)
                {
                    file.read(reinterpret_cast<char*>(&len), sizeof(len));
                    buffer = new char[len + 1];
                    file.read(buffer, len);
                    buffer[len] = '\0';
                    tcm->addAutobiographyEntry(std::string(buffer));
                    delete[] buffer;
                }

                // Данные TeacherCommissionMember
                int commissionWorksCount;
                file.read(reinterpret_cast<char*>(&commissionWorksCount), sizeof(commissionWorksCount));
                tcm->clearCommissionWorks();
                for (int j = 0; j < commissionWorksCount; j++)
                {
                    file.read(reinterpret_cast<char*>(&len), sizeof(len));
                    buffer = new char[len + 1];
                    file.read(buffer, len);
                    buffer[len] = '\0';
                    tcm->addCommissionWork(std::string(buffer));
                    delete[] buffer;
                }
            }

            if (item != nullptr)
            {
                list.addToEnd(item);
            }
        }
    }

    file.close();
    std::cout << "Данные успешно загружены из бинарного файла: " << filename << std::endl;
}

template <class T>
FileBin<T>& FileBin<T>::operator<<(const List<T>& list)
{
    writeLinkedList(list);
    return *this;
}

template <class T>
FileBin<T>& FileBin<T>::operator>>(List<T>& list)
{
    readLinkedList(list);
    return *this;
}

// Явная инстанциация для Human*
template class FileBin<Human*>;

