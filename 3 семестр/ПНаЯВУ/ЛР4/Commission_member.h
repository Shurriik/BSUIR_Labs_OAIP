#ifndef COMMISSION_MEMBER_H
#define COMMISSION_MEMBER_H

#include "Human.h"
#include <string>

class CommissionMember : virtual public Human
{
protected:
    std::string commissionName;                 // Название комиссии
    int appointmentYear;                        // Год назначения в комиссию
    std::string certificateNumber;              // Номер свидетельства
    static const int MAX_ENTRIES = 100;         // Максимальное количество записей
    std::string autobiography[MAX_ENTRIES];     // Автобиография 
    int autobiographyCount;                     // Текущее количество записей

public:
    CommissionMember();                                                         // Конструктор по умолчанию
    CommissionMember(const std::string& first, const std::string& last,
        const std::string& pat, int year,
        const std::string& commission, int appointment,
        const std::string& cert);                                               // Конструктор с параметрами
    ~CommissionMember() override = default;                                     // Деструктор

    std::string getCommissionName() const;                          // Получить название комиссии
    int getAppointmentYear() const;                                 // Получить год назначения
    std::string getCertificateNumber() const;                       // Получить номер свидетельства
    int getAutobiographyCount() const;                              // Получить количество записей
    std::string getAutobiographyEntry(int index) const;             // Получить запись автобиографии

    void setCommissionName(const std::string& commission);  // Установить название комиссии
    void setAppointmentYear(int year);                      // Установить год назначения
    void setCertificateNumber(const std::string& cert);     // Установить номер свидетельства
    void addAutobiographyEntry(const std::string& entry);   // Добавить запись в автобиографию
    void removeAutobiographyEntry(int index);               // Удалить запись из автобиографии
    void clearAutobiography();                              // Очистить автобиографию

    void printInfo() const override;                        // Вывод информации о члене комиссии
    Human* clone() const override;                          // Создание копии члена комиссии
    void inputFromStream(std::istream& is) override;        // Ввод данных члена комиссии
    void outputToStream(std::ostream& os) const override;   // Вывод данных члена комиссии
    void printTableHeader() const override;                 // Вывод шапки таблицы
    void printTableRow() const override;                    // Вывод строки таблицы

    friend std::ostream& operator<<(std::ostream& os, CommissionMember& member);
    friend std::istream& operator>>(std::istream& is, CommissionMember& member);
};

#endif