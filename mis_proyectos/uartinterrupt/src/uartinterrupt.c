#include "uartinterrupt.h"

void onRx(void *noUsado){

	char dato =	uartRxRead(UART_USB);
printf("Recibimos un dato:%c por la UART\r\n",dato);

}
