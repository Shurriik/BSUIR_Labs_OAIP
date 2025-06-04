#include <locale.h>
#include "solution.h"

int main() 
{

    setlocale(LC_ALL, "RUS");

    int again = 1;
    while (again)
    {

        allocateMemory();  // Выделение памяти

        menu();            // Запуск интерфейса

        again = againf();
        freeTree();        // Очистка дерева

    }
    return 0;
}
