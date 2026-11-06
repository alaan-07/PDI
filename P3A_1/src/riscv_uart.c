#include "riscv_uart.h"

struct UART_regs
{
	/** \brief UART  Data Register */
	volatile uint32_t Data;   	/* 0xFC001000 */
	/** \brief UART  Status Register */
	volatile uint32_t Status; 	/* 0xFC001004 */
	/** \brief UART  Control Register */
	volatile uint32_t Ctrl; 	/* 0xFC001008 */
	/** \brief UART  Scaler Register */
	volatile uint32_t Scaler; 	/* 0xFC00100C */
};

volatile struct UART_regs * const pUART_REGS= (struct UART_regs *)0xFC001000;

//***************************
#define riscv_UART_TF_IS_FULL() (RISCV_UART_TF & pUART_REGS->Status)

//***************************
int8_t riscv_putchar(char c)
{
	uint32_t write_timeout=0;

	while( (riscv_UART_TF_IS_FULL()) && (write_timeout < 0xAAAAA))
	{
		write_timeout++;
	}

	if(write_timeout <  0xAAAAA)
		pUART_REGS->Data=c;

	// return 1 (true) if write_timeout reach maximun value
	// 0 (false) otherwise
	return (write_timeout >= 0xAAAAA);
}


//***************************
int8_t riscv_uart_tx_fifo_is_empty()
{
	return (RISCV_UART_TE & pUART_REGS->Status);
}

//***************************
void riscv_uart_enable_TX()
{
	pUART_REGS->Ctrl |= RISCV_UART_TXE;
}

//***************************
void riscv_uart_disable_TX()
{
	pUART_REGS->Ctrl &= ~RISCV_UART_TXE;
}

//***************************
void riscv_uart_enable_RX()
{
	pUART_REGS->Ctrl |= RISCV_UART_RXE;
}

//***************************
void riscv_uart_disable_RX()
{
	pUART_REGS->Ctrl &= ~RISCV_UART_RXE;
}

//***************************
void riscv_uart_enable_RI() {
	pUART_REGS->Ctrl |= RISCV_UART_RI;
}

//***************************
void riscv_uart_disable_RI() {
    pUART_REGS->Ctrl &= ~RISCV_UART_RI;
}

int8_t riscv_print_string(char* str)
{

    int8_t error=0;
    uint32_t i = 0;

    while( str[i] != '\0' && (!error) )
    {
        error = riscv_putchar( str[i] );
        i++;
    }

    while(!riscv_uart_tx_fifo_is_empty())
		;  // empty statement

return error;
}

int32_t riscv_getchar()
{
	int32_t uart_rx_data;

	if ( RISCV_UART_DR & pUART_REGS->Status)
	{
		uart_rx_data = pUART_REGS->Data;
	} else {
		uart_rx_data = -1;
	}

	return uart_rx_data;
}
