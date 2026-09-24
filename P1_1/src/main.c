#include "riscv_types.h"
#include "gpio_drv.h"
#include "log.h"

int main()
{
    uint32_t input;
    uint32_t dir;

	// Enable output on bits 19..16
	dir = gpio_get_direction();
	dir |= 0x000F0000; // It should be defined as a mask
	gpio_set_direction(dir);

	printf("P1_1\n");

	while(1)
	{
	   // Get GPIO bits
	   input = gpio_read();

	   if (input & SW_0_MASK)
	   {
			// Turns LED0 ON only if it is OFF
			// if ( !(input & LED_0_MASK) )
			if ((input & LED_0_MASK) == 0)
			{
				printf("Turn LED0 on\n");
				input |= LED_0_MASK;
				gpio_write(input);
	   }
	   else
	   {
			// Turns LED0 OFF only if it is ON
			// if ( input & LED_0_MASK )
			if ((input & LED_0_MASK) != 0)
			{
				printf("Turn LED0 off\n");
				input &= ~LED_0_MASK;
				gpio_write(input);
			}
	   }

	} // while(1)

return 0;
}
