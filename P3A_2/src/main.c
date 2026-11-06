#include "riscv_types.h"
#include "dispatch.h"
#include "clinc.h"

#include "log.h"

uint32_t cnt_1=10, cnt_2=50;
uint32_t flag_1=0, flag_2=0;

void timer_handler(void)
{
	cnt_1--;
	cnt_2--;

	if (cnt_1 == 0)
	{
		cnt_1 = 10;
		flag_1 = 1;
	}

	if (cnt_2 == 0)
	{
		cnt_2 = 50;
		flag_2 = 1;
	}
}

int main()
{
	printf("----------TIMER IRQ---------\n");
	install_local_timer_handler( timer_handler );
	local_timer_set_gap( 1000000 ); // CLINT timer clock is 10Mhz

	enable_timer_clinc_irq();
	enable_irq();	          // Global interrupt enable

	while(1)
	{
		if ( flag_1 )
		{
			printf("---> Msg 1\n");
			flag_1 = 0;
		}

		if ( flag_2 )
		{
			printf("     ---> Msg 2\n");
			flag_2 = 0;
		}
	}
}
