#include "solution.h"


int main()
{

    setlocale(LC_ALL, "RUS");
    Cube* cubes = NULL;
    int numCubes = 0;
    int again = 1;
    while (again)
    {
        Cube* cubes = allocateCubes(numCubes);

        menu(&cubes, &numCubes);

        again = againf();

        freeCubes(cubes);
    }



    return 0;
}