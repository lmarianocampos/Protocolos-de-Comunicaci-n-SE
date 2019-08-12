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
#include "operaciones.h"
///*=====[Inclusiones de dependencias de funciones privadas]===================*/
#include <sapi.h>
///*=====[Macros de definicion de constantes privadas]=========================*/

///*=====[Macros estilo funcion privadas]======================================*/

///*=====[Definiciones de tipos de datos privados]=============================*/

///*=====[Definiciones de Variables globales publicas externas]================*/


///*=====[Definiciones de Variables globales publicas]=========================*/

///*=====[Definiciones de Variables globales privadas]=========================*/

///*=====[Prototipos de funciones privadas]====================================*/

///*=====[Implementaciones de funciones publicas]==============================*/

void operacion0(void* taskParmPtr) {
	char *pMayusculizar = NULL;
	uint8_t i=0;
	while (1) {
		if (pdTRUE == xQueueReceive(queueMayusculizar, &pMayusculizar,
		portMAX_DELAY)) {

			while (*(pMayusculizar+i) != '\0') {
				if (*(pMayusculizar+i) >= 'a' && *(pMayusculizar+i) <= 'z') {
					*(pMayusculizar+i) = *(pMayusculizar+i) - 32;
				}
				i++;
			}
			i=0;

			xQueueSend(queueTransmitir,&pMayusculizar,portMAX_DELAY);
		}
	}
}
void operacion1 (void* taskParmPtr){
	char *pMinusculizar = NULL;
	uint8_t i=0;
		while (1) {
			if (pdTRUE == xQueueReceive(queueMinusculizar, &pMinusculizar,
			portMAX_DELAY)) {
				//pMinusculizarAux = pMinusculizar;
				while (*(pMinusculizar+i) != '\0') {
					if (*(pMinusculizar+i) >= 'A' && *(pMinusculizar+i) <= 'Z') {
						*(pMinusculizar+i) = *(pMinusculizar+i) + 32;

					}
					i++;
				}
				i=0;
				xQueueSend(queueTransmitir,&pMinusculizar,portMAX_DELAY);
			}
		}

}

// Implementacion de funcion de la tarea
void myTask(void* taskParmPtr) {
	// ---------- CONFIGURACIONES ------------------------------
	// Tarea periodica cada 1000 ms
	portTickType xPeriodicity = 1000 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();

	// ---------- REPETIR POR SIEMPRE --------------------------
	while (TRUE) {
		gpioToggle(LEDB);
		// Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
		vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}
///*=====[Implementaciones de funciones de interrupcion publicas]==============*/

///*=====[Implementaciones de funciones privadas]==============================*/


