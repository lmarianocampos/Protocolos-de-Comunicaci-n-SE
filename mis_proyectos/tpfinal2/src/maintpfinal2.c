#include "stepper_uart.h"
#include "stepper_fsmbutton.h"

int main(void) {
	boardConfig();
	uartConfig(UART_USB, 115200);

	delay_t myDelay;
	delayConfig(&myDelay, 500);

	stepperButtonStart();

	while (TRUE) {
		stepperReadUart();
		stepperExecuteButton();

		if (delayRead(&myDelay)) {
			stepperButtonPrint();
		}

	} //end while
	return 0;
} //end main
