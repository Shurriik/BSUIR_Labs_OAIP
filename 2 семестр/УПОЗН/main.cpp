#include "transport.h"


int main()
{

    setlocale(LC_ALL, "RUS");

    int again = 1;
    while (again)
    {

        TransportSystem();

        menu();

        again = againf();

        cleanupTransportSystem();

    }
    return 0;
}