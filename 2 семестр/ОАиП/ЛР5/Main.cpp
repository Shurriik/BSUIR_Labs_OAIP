#include <locale.h>
#include "solution.h"

int main() 
{

    setlocale(LC_ALL, "RUS");

    int again = 1;
    while (again)
    {

        allocateMemory();  // ��������� ������

        menu();            // ������ ����������

        again = againf();
        freeTree();        // ������� ������

    }
    return 0;
}
