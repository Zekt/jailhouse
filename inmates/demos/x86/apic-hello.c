#include <inmate.h>

#define CMDLINE_BUFFER_SIZE	256
CMDLINE_BUFFER(CMDLINE_BUFFER_SIZE);

#ifdef CONFIG_UART_OXPCIE952
#define UART_BASE		0xe010
#else
#define UART_BASE		0x3f8
#endif
#define UART_LSR		0x5
#define UART_LSR_THRE		0x20
#define UART_IDLE_LOOPS		100


void inmate_main(void)
{
	unsigned int n;

	printk_uart_base = UART_BASE;
	do {
		for (n = 0; n < UART_IDLE_LOOPS; n++)
			if (!(inb(UART_BASE + UART_LSR) & UART_LSR_THRE))
				break;
	} while (n < UART_IDLE_LOOPS);

	comm_region->cell_state = JAILHOUSE_CELL_RUNNING_LOCKED;


	printk("Hello World\n");
	comm_region->cell_state = JAILHOUSE_CELL_SHUT_DOWN;
}
