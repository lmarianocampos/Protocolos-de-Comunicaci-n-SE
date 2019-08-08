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

#include "servicioProcesamientoTexto.h"
#include "rxtxUartDriver.h"
#include "operaciones.h"

/*=====[Inclusiones de dependencias de funciones privadas]===================*/

typedef enum {
	DATAGRAMA_VALIDO_SOF,
	DATAGRAMA_VALIDO_OP,
	DATAGRAMA_VALIDO_T,
	DATAGRAMA_VALIDO_EOF,
	DATAGRAMA_VALIDO,
	DATAGRAMA_INVALIDO
} validacion_datagrama_t;
char * chainPayloadAux;
char * chainPayload;
// Implementacion de la Tarea  procesamientoDatoRecibido
void procesamientoDatoRecibido(void* taskParmPtr) {
	// ---------- CONFIGURACIONES ------------------------------

	uint8_t data;
	static uint8_t cadenaProcesar[105];
	static uint8_t i = 0;
	uint8_t j;
	bool_t flag_mensaje_finalizado;
	static validacion_datagrama_t datagrama;
	static uint8_t operacion, tamanio_cadena;
	uint32_t digitoUnidad, digitoDecimal, sizeTotal;

	char * chainPayload;

	// ---------- REPETIR POR SIEMPRE --------------------------
	while (TRUE) {

		if (pdTRUE == xQueueReceive(colaReceive, &data, portMAX_DELAY)) { // aquí se bloquea esperando por un caracter
			cadenaProcesar[i] = data;
			if (cadenaProcesar[i] == '}') {
				//cadenaProcesar[i + 1] = '\0';
				i = 0;
				flag_mensaje_finalizado = TRUE;
				datagrama = DATAGRAMA_VALIDO_SOF;
			} else
				i++;
		}

		if (flag_mensaje_finalizado == TRUE) {
//			printf("%s\r\n", cadenaprocesar);
//			flag_mensaje_finalizado = 0;
			//VALIDACION DE LA CADENA/ RESERVA DE MEMORIA /ENVIO A LA OPERACION

			while (flag_mensaje_finalizado == TRUE) {

			switch (datagrama) {
			case DATAGRAMA_VALIDO_SOF:
				if (cadenaProcesar[0] == '{'){
					datagrama = DATAGRAMA_VALIDO_OP;
				}
				else{
					datagrama = DATAGRAMA_INVALIDO;
				}
                break;
			case DATAGRAMA_VALIDO_OP:
				if (cadenaProcesar[1] == '0') {
					operacion = 0;
					datagrama = DATAGRAMA_VALIDO_T;
				} else if (cadenaProcesar[1] == '1') {
					operacion = 1;
					datagrama = DATAGRAMA_VALIDO_T;
				} else
					datagrama = DATAGRAMA_INVALIDO;
				break;

			case DATAGRAMA_VALIDO_T:
				//el tamanio maximo de 104 ya esta validado en rxtxdriver
				//Aqui guardo el tamaño de la cadena para la posterior reserva de memoria

				//TODO Comparar el tamaño de la cadena con los bytes 3 y 4
				digitoUnidad = (uint32_t)(cadenaProcesar[3] - 48);
				digitoDecimal = (uint32_t)(cadenaProcesar[2] - 48) * 10;
				sizeTotal = digitoDecimal + digitoUnidad;

				if (sizeTotal == (strlen(cadenaProcesar) - 5)) {
					tamanio_cadena = strlen(cadenaProcesar);
					//if ((tamanio_cadena - 5) < 100)
					datagrama = DATAGRAMA_VALIDO_EOF;
				} else
					datagrama = DATAGRAMA_INVALIDO;

				break;
			case DATAGRAMA_VALIDO_EOF:
				if (cadenaProcesar[tamanio_cadena - 1] == '}') {
					datagrama = DATAGRAMA_VALIDO;

				} else
					datagrama = DATAGRAMA_INVALIDO;
				break;
			case DATAGRAMA_VALIDO:
				flag_mensaje_finalizado = FALSE;;
				printf("%s\r\n", cadenaProcesar);

				//TODO borrar la cadena para que no queden datos viejos si la nueva cadena es
				//mas chica y no pisa los datos viejos!

				//RESERVAR MEMORIA Y MANDAR a la OPERACION

				break;
			case DATAGRAMA_INVALIDO:
				printf("Dato Invalido!\r\n");
				flag_mensaje_finalizado = FALSE;
				break;

			default:
				break;

			}
			}
			if (datagrama == DATAGRAMA_VALIDO) {
				sizeTotal = sizeTotal + 2;

				chainPayload = pvPortMalloc(sizeTotal * sizeof(char));
				if (chainPayload != NULL) {

					chainPayloadAux = chainPayload;
					*chainPayloadAux = cadenaProcesar[1];

					chainPayloadAux = chainPayloadAux + 1;

					for (j = 0; j < (tamanio_cadena - 5); j++) {

						*chainPayloadAux = cadenaProcesar[4 + j];
						chainPayloadAux = chainPayloadAux + 1;
					}
					*chainPayloadAux = '\0';//con esto indico que hasta donde debe mayusculizar o minusculizar

					//vPortFree(chainPayloadAux);
					if (cadenaProcesar[1] == '0') {
						xQueueSend(queueMayusculizar, &chainPayload,
								portMAX_DELAY);
					}

					if (cadenaProcesar[1] == '1') {
						xQueueSend(queueMinusculizar, &chainPayload,
								portMAX_DELAY);
					}

				}else {
					printf("Error de Asignación de Memoria\n");
				}

			}

		}
	}
}

void taskAddHeaderLayerTwo(void* taskParmPtr) {
	char bufferSend[12];
	uint8_t i;
	char *pSend;
	while (1) {
		if (pdTRUE == xQueueReceive(queueTransmitir, &pSend, portMAX_DELAY)) {
			bufferSend[0] = '{';
			i = 1;
			while (*pSend != '\0') {
				bufferSend[i] = *pSend;
				pSend++;
				i++;
			}
			bufferSend[i] = '}';
			printf("%s\r\n", bufferSend);

			vPortFree((char*)pSend);
			//vPortFree(chainPayload);
		}
	}
}

