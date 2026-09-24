#include "riscv_types.h"
#include "gpio_drv.h"
#include "log.h"

void delay(uint64_t ticks)
{
uint64_t cnt = 0;

	do { cnt++; } while (cnt < ticks);
}

int main()
{
   uint32_t mask = LED_0_MASK;
   uint32_t dir;

   printf("P1_2\n");

   // Enable output on bits 19..16
   dir = gpio_get_direction();
   dir |= 0x000F0000;
   gpio_set_direction(dir);

   printf ("Dir: %08X\n", gpio_get_direction() );

   while(1)
   {
	  gpio_write(mask);

	  printf("INPUT VALUE: %08X\n", gpio_read());

   	  mask <<= 1;

   	  if (mask == 0x00100000)
   	  {
   	     mask = LED_0_MASK;
   	  }

   	  delay(10000000);
   }

return 0;
}
