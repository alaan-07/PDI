#include "riscv_types.h"
#include "riscv_uart.h"
#include "log.h"

int main()
{
	int32_t rec;
	char car;

	riscv_uart_enable_TX();
	riscv_uart_enable_RX();

	riscv_print_string("Type a character string: ");

	do
	{
		do
		{
			rec = riscv_getchar();
		} while (rec == -1);

		car = (char)rec;
		printf("Recibido: [%c:%d]\n", car, car);
	} while (rec != ESC);

	return 0;
}
