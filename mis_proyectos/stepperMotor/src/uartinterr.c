#include "uartinterr.h"

//Interrupción por la recepción de un carácter
void onRx(void *nosado) {

	static uint8_t index = 0;
	char command;
	if (buffer != BUFFER_FULL) {

		command = uartRxRead(UART_USB);
		printf("Se recibio :%c\n", command);
		bufferRx[index] = command;

		if (bufferRx[index] == '\n') {
			bufferRx[index + 1] = '\0';
			index = 0;
			buffer = BUFFER_FULL;
		} else {
			index++;
			buffer = BUFFER_INCOMPLETE;
		}
	} else {
		printf("El buffer de recepcion se encuentra lleno");
	}
	/*switch (command) {
	 case '1':
	 rx = COMMAND_ENABLE_MOTOR;
	 break;
	 case '2':
	 rx = COMMAND_DISABLE_MOTOR;
	 break;
	 case '3':
	 rx = COMMAND_ORIENTATION_HORARIO;
	 break;
	 case '4':
	 rx = COMMAND_ORIENTATION_ANTIHORARIO;
	 break;
	 case '5':
	 rx = COMMAND_MICRO_STEPES;
	 break;
	 case '6':
	 rx = COMMAND_STEPS;
	 break;
	 case '7':
	 rx = COMMAND_ANGLE;
	 break;
	 case '8':
	 rx = COMMAND_ANGLE;
	 break;
	 default:
	 rx = COMMAND_ERROR;
	 }*/
}
void configuraUart(void) {
	uartConfig(UART_USB, 115200);
	uartCallbackSet(UART_USB, UART_RECEIVE, onRx, NULL);
	uartInterrupt(UART_USB, TRUE);
}

