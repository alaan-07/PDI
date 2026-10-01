#include "riscv_types.h"
#include "riscv_uart.h"
#include "gpio_drv.h"

#include "log.h"

int main()
{
	uint32_t dir, input;
	uint32_t bt0_current, bt0_previous;
	uint32_t bt1_current, bt1_previous;

	printf("P2_3\n");

	// Enable output on bits 19..16
	dir = gpio_get_direction();
	dir |= 0x000F0000;
	gpio_set_direction( dir );

	bt0_current = 0;

	riscv_uart_enable_TX();
	riscv_print_string("Programacíón de Dispositivos\n");

	while(1)
	{
		input = gpio_read();
		bt0_previous = bt0_current;
		bt0_current = input & BT_0_MASK;

		bt1_previous = bt1_current;
		bt1_current = input & BT_1_MASK;

		if ( bt0_current && !bt0_previous )
		// if ( !bt0_current && bt0_previous )
		{
			riscv_print_string("BT0 press...\n");
		}

		//if ( bt0_current && !bt0_previous )
		if ( !bt0_current && bt0_previous )
		{
			riscv_print_string("BT0 release...\n");
		}

		if ( bt1_current && !bt1_previous )
		// if ( !bt1_current && bt1_previous )
		{
			riscv_print_string("BT1 press...\n");
		}
	}

	return 0;
}


