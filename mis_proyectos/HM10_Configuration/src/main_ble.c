#include "sapi.h"
#include <string.h>

#define UART_PC 		UART_USB
#define UART_BLUETOOTH  UART_232

bool_t hm10BleTest(int32_t uart);
void hm10BlePrintATCommands(int32_t uart);

	int main(void) {
	boardConfig();
	uartConfig(UART_PC, 9600);
	uartWriteString(UART_PC, "Programa Ejecutandose.\n\r");
	uartWriteString(UART_PC, "UART_PC Configurada.\n\r");

	gpioWrite(LEDB, OFF);
	uartConfig(UART_BLUETOOTH, 9600);
	uartWriteString(UART_PC,
			"UART_BLUETOOTH para modulo bluetooth Configurada.\n\r");

	uint8_t data = 0;

	uartWriteString(UART_PC,
			"Testeo si el modulo esta conectado enviando:AT.\n\r ");

	if (hm10BleTest(UART_BLUETOOTH)) {
		uartWriteString(UART_PC, "modulo conectado correctamente.\n\r");
	}
	while (TRUE) {

		if (uartReadByte(UART_PC, &data)) {
			uartWriteByte(UART_BLUETOOTH, data);
		}

		if (uartReadByte(UART_BLUETOOTH, &data)) {
			if (data == 'h') {
				gpioWrite(LEDB, ON);
			}
			if (data == 'l') {
				gpioWrite(LEDB, OFF);
			}
			uartWriteByte(UART_PC, data);
		}
		//si presiono TEC1 imprime la lista de comandos AT
		if (!gpioRead(TEC1)) {
			hm10BlePrintATCommands(UART_BLUETOOTH);
		}
		//si presiono la TEC3 enciende el led de la pantalla de la app
		if (!gpioRead(TEC3)) {
			uartWriteString(UART_PC, "LED_ON\r\n");
			delay(500);
		}
		//si presiono TEC4 apaga el led de la pantalla de la app
		if (!gpioRead(TEC4)) {
			uartWriteString(UART_PC, "LED_OFF\r\n");
			delay(500);
		}

	}
	return 0;
}

bool_t hm10BleTest(int32_t uart) {
	uartWriteString(uart, "AT\r\n");
	return waitForReceiveStringOrTimeoutBlocking(uart, "OK",
			strlen("OK\r\n"), 50);
}

void hm10BlePrintATCommands(int32_t uart) {
	delay(500);
	uartWriteString(uart,"AT+HELP");

}
