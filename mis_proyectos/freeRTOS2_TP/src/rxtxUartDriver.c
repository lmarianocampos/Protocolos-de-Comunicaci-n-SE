 /*
 * Copyright 2019 	Mariano Campos <author@mail.com>
 * 					Martin Gambarotta <magambarotta@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * Version: 0.0.1
 * Fecha de creacion: 2019/07/25
 */


/*=====[Inclusion de su propia cabecera]=====================================*/

#include "rxtxUartDriver.h"


void IRQ_Init(void) {
	/* Inicializar la UART_USB junto con las interrupciones de  Rx */
	uartConfig(UART_USB, 115200);
	// Seteo un callback al evento de recepcion y habilito su interrupcion
	uartCallbackSet(UART_USB, UART_RECEIVE, datoRecibido, NULL);
	// Habilito todas las interrupciones de UART_USB
	uartInterrupt(UART_USB, TRUE);

}

// Implementacion de la funcion de Interrupcion datoRecibido activada por un dato en la FIFO de Rx
void datoRecibido(void *noUsado) {

	static uint8_t i = 0;
	static bool_t flag_guardar;
	uint8_t dataReceive;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	dataReceive = uartRxRead(UART_USB);

	switch (dataReceive) {
	case '{':
		flag_guardar = TRUE;
		xQueueSendFromISR(colaReceive, &dataReceive, &xHigherPriorityTaskWoken);
		i++;
		break;
	case '}':
		xQueueSendFromISR(colaReceive, &dataReceive, &xHigherPriorityTaskWoken);
		i = 0;
		flag_guardar = FALSE;
		break;
	default:
		if (flag_guardar == TRUE && i < TAMANIO_MAXIMO_PAQUETE) {
			xQueueSendFromISR(colaReceive, &dataReceive, &xHigherPriorityTaskWoken);
			i++;
		} else {
			i = 0;
			flag_guardar = FALSE;//descartar el paquete
		}
		break;
	}
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
