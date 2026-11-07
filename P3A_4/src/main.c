#include "riscv_types.h"
#include "dispatch.h"
#include "log.h"
#include "clinc.h"
#include "riscv_monotonic_clock.h"

int main() {
    printf("----------MONOTONIC TIME (DELAY)---------\n");

    // Time set: 12/10/2026 12:40
    InitMonotonicClock(date_time_to_Y2K(12, 10, 26, 12, 40, 0 ));

    uint32_t current = 0;
    // uint64_t target_ticks = get_ticks_from_reset(); para el wait_until

    // Print universal time each second using delay
    do {
        current = GetUniversalTime_Y2K();
        print_date_time_from_Y2K( current );

        // Esperar 1 segundo (10.000.000 ticks a 10 MHz)
        delay(10000000);

        //con wait_until:
        // Incrementar el objetivo en 1 segundo (10.000.000 ticks)
        // target_ticks += 10000000;
        // wait_until( target_ticks );

    } while ( 1 );

    printf("\n----------END---------\n");
}
