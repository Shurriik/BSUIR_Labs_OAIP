#include "solution.h"

int main()
{
    setlocale(LC_ALL, "RUS");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);


    int again = 1;
    Cube* cubes = NULL;
    int numCubes = 0;

    while (again)
    {
        Cube* cubes = allocateCubes(numCubes);

        menu();

        again = againf();

        freeCubes(cubes);




    }
    return 0;

}