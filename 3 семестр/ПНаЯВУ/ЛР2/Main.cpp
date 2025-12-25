#include "Solution.h"


int main()
{
    setlocale(LC_ALL, "RUS");

    int again = 1;

    while (again)
    {
        menu();

        again = runAgain();
    }
}