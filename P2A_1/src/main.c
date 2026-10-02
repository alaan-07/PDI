#include "riscv_types.h"
#include "riscv_uart.h"
#include "log.h"

int main()
{
	// TX enable
	riscv_uart_enable_TX();

	// First test, console output
	riscv_putchar('P');
	riscv_putchar('2');
	riscv_putchar('\n');

	// Wait until TX fifo is empty
	do {
		// do nothing
	} while( !riscv_uart_tx_fifo_is_empty() );


    return 0;
}

