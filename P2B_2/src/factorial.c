#include "riscv_types.h"
#include "factorial.h"

uint32_t factorial(uint32_t num)
{
    if (num == 0)
    	return 1;
    else
    {
        return num * factorial(num - 1);
    }
}
