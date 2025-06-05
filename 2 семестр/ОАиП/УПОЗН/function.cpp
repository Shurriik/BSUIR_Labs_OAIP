#include "transport.h"


// Проверка високосного года
int isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Проверка корректности даты
int isValidDate(int day, int month, int year)
{
    time_t t = time(NULL);
    struct tm current_time;

    if (localtime_s(&current_time, &t) != 0)
    {
        printf("Error getting current date\n");
        return 0;
    }

    int current_year = current_time.tm_year + 1900;
    int current_month = current_time.tm_mon + 1;
    int current_day = current_time.tm_mday;

    // Проверка года
    if (year < current_year || year > 2100)
    {
        printf("Error: Invalid year (%d). Year must be between %d and 2100.\n",
            year, current_year);
        return 0;
    }

    // Проверка месяца
    if (month < 1 || month > 12)
    {
        printf("Error: Invalid month (%d). Must be between 1 and 12.\n", month);
        return 0;
    }

    // Количество дней в месяцах
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Корректировка для високосного года
    if (isLeapYear(year))
    {
        daysInMonth[1] = 29;
    }

    // Проверка дня
    if (day < 1 || day > daysInMonth[month - 1])
    {
        printf("Error: Invalid day (%d) for month %d.\n", day, month);
        return 0;
    }

    // Проверка, что дата не в прошлом
    if (year == current_year)
    {
        if (month < current_month || (month == current_month && day < current_day))
        {
            printf("Error: Date %02d.%02d.%04d cannot be earlier than the current date.\n",
                day, month, year);
            return 0;
        }
    }

    return 1;
}


// Проверка корректности времени
int isValidTime(int hour, int minute)
{
    if (hour < 0 || hour > 23)
    {
        printf("Error: Invalid hour (%d). Must be between 0 and 23.\n", hour);
        return 0;
    }
    if (minute < 0 || minute > 59)
    {
        printf("Error: Invalid minute (%d). Must be between 0 and 59.\n", minute);
        return 0;
    }
    return 1;
}


//Меню
void menu()
{
    int choice;
    do {
        printf("\nTransport Management System\n");
        printf("1. Add Transport\n");
        printf("2. Book Transport\n");
        printf("3. Cancel Booking\n");
        printf("4. Edit Booking\n");
        printf("5. Update Availability\n");
        printf("6. Check Status\n");
        printf("7. Filter Transport\n");
        printf("8. Count Available by Date\n");
        printf("9. Print Statistics\n");
        printf("10. Print All Transports\n");
        printf("11. Search Transport\n");
        printf("12. Edit Transport\n");
        printf("13. Delete Transport\n");
        printf("14. Export to Text File\n");
        printf("15. Load from Export File\n");
        printf("16. Exit\n");
        printf("Enter your choice: ");

        if (scanf_s("%d", &choice) != 1)
        {
            while (getchar() != '\n');
            printf("Invalid input\n");
            continue;
        }
        while (getchar() != '\n');

        switch (choice)
        {

        case 1: addTransport(); break;

        case 2: orderTransport(); break;

        case 3: cancelBooking(); break;

        case 4: editBooking(); break;

        case 5: updateAvailability(); break;

        case 6: checkStatus(); break;

        case 7: filterTransport(); break;

        case 8: countAvailableByDate(); break;

        case 9: printStatistics(); break;

        case 10: printTransports(); break;

        case 11: searchTransport(); break;

        case 12: editTransport(); break;

        case 13: deleteTransport(); break;

        case 14: exportToTextFile(); break;

        case 15:

            if (loadFromExportFile())
            {
                printf("Data loaded from export file\n");
            }
            break;

        case 16:

            printf("Exiting...\n");
            break;

        default:

            printf("Invalid choice\n");
        }

    } while (choice != 16);
}

// Повтор программы
int againf()
{
    int again, x;
    printf("Enter 1 to continue or any other key to exit: ");
    while (1)
    {
        x = scanf_s("%d", &again);
        if (x != 1 || again != 1)
        {
            printf("\n");
            printf("Program is terminating.\n");
            again = 0;
            return again;
        }
        else
        {
            printf("Restarting the program\n");
            break;
        }
    }
    return again;
}