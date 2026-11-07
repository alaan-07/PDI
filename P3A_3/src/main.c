#include "riscv_types.h"
#include "dispatch.h"

#include "log.h"

#include "clinc.h"
#include "riscv_monotonic_clock.h"

int main()
{
	printf("----------MONOTONIC TIME---------\n");

	// Time set: 12/10/2023 12:40
	InitMonotonicClock(date_time_to_Y2K(12, 10, 26, 12, 40, 0 ));

	uint32_t previous = 0;
	uint32_t current  = 0;

	do {
		current = GetUniversalTime_Y2K();

		if ( current != previous )
		{
			print_date_time_from_Y2K( current );
			previous = current;
		}
	} while ( 1 );

	printf("\n----------END---------\n");
}

