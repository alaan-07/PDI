#include "log.h"
#include "riscv_types.h"
#include "factorial.h"

int main()
{
    uint32_t fact;

    printf("Programación de Dispositivos e Interfaces\n");

    fact = factorial( 5 );
    printf("Factorial: %u\n", fact);

    return 0;
}
