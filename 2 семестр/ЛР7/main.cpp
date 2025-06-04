#include "solution.h"

int main()
{
    setlocale(LC_ALL, "RUS");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int choice;
    int search;
    int again = 1;
    
    while (again)
    {
        int n=0;
        Student* students = allocateStudents(n);
        menu();
        again = againf();
        freeStudents(students, n);



    }

    return 0;
}
