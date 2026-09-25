#include "riscv_types.h"
#include "gpio_drv.h"
#include "log.h"

/*
- Push buttons
  BTN[0..3]: GPIO inputs [4..7]

- Switches
  SW[0..3] GPIO inputs [0..3]

- LED[0..3]: GPIO0 outputs [16..19]
*/


int main()
{
	   uint32_t dir, input_current, input_previous;
	   uint32_t button_current, button_previous;
	   uint32_t button_mask, led_mask;

	   printf("P1_EDGE\n");

	   // Enable output on bits 19..16
	   dir = gpio_get_direction();
	   dir |= 0x000F0000;
	   gpio_set_direction( dir );

	   input_current = gpio_read();

	   while(1)
	   {
		  input_previous = input_current;
		  input_current  = gpio_read();

		  button_mask = BT_0_MASK;
		  led_mask = LED_0_MASK;

		  for (int i = 0; i < 4; i++)
		  {

			  button_previous = input_previous & button_mask;
			  button_current  = input_current  & button_mask;

			  // if ( button_current && !button_previous )  // Rising edge
			  if ( !button_current && button_previous ) // Falling edge
			  {
						 if ( input_current & led_mask ) // If LED is on
						 {
							// switch it off
							input_current &= ~led_mask;
							gpio_write( input_current );
						 }
						 else
						 {
							// switch it on
							input_current |= led_mask;
							gpio_write( input_current );
						 }

			  } // if

			  // Desplazar las máscaras para el siguiente botón y LED
			  led_mask <<= 1;
			  button_mask <<= 1;

		  } //for

	   } // while

	return 0;
}
