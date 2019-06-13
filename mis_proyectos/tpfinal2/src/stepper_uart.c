#include "stepper_uart.h"

stepperMotor_t motor;

uint8_t command;

void stepperReadUart(void) {
	if (uartReadByte(UART_USB, &command)) {
		switch (command) {
		case 'A':
			stepperInit(&motor, 200, GPIO0, GPIO1, GPIO2, 7.5); //
			break;
		case 'B':
			stepperEnable(&motor);
			stepperDirectionSet(&motor, STEPPER_RIGHT);
			break;
		case 'C':
			stepperMoveSteps(&motor, 150); // Genero 150 pulsos
			break;

		case 'D':
			stepperMoveAngle(&motor, 180); // 180°/7.5° = Genero 24 pulsos
			break;
		}
	}

}
