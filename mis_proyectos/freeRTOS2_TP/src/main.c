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

/*==================[inlcusiones]============================================*/

// Includes de FreeRTOS
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"			//API de control de tareas y temporizacion
#include "queue.h"			//API de Colas
#include "sapi.h"			// sAPI header

#include "servicioProcesamientoTexto.h"
#include "operaciones.h"
#include "rxtxUartDriver.h"

/*==================[definiciones y macros]==================================*/


/*==================[definiciones de datos internos]=========================*/
QueueHandle_t  xQueueTransmision,xQueueProcesada;
/*==================[definiciones de datos externos]=========================*/
/*==================[declaraciones de funciones internas]====================*/
/*==================[declaraciones de funciones externas]====================*/
/*=================[declaraciones de variables privadas globales]=============================*/
/*==================[funcion principal]======================================*/
int main(void) {
	// ---------- CONFIGURACIONES ------------------------------
	// Inicializar y configurar la plataforma
	boardConfig();
	// Inicializacion Interrupciones de la UART_USB
	IRQ_Init();
	// Led para dar senal de vida
	gpioWrite(LED3, ON);
	gpioWrite(LED1, OFF);
	gpioWrite(LED2, OFF);

		//Creacion de la colas
	colaReceive = xQueueCreate(SIZE_QUEUE_RECEIVE,sizeof(char));
	   if(colaReceive == NULL){
		   	  printf("No se pudo crear la COLA de recepcion de caracteres\n");
		   	  gpioWrite(LED1, ON);
		   	  while(1);
		   	  /* se queda bloqueado el sistema hasta
		   	  que venga el técnico de mantenmiento   */

	   }
	   queueSend = xQueueCreate(SIZE_QUEUE_SEND,sizeof(char));


	   	   if(queueSend == NULL){
	   		   printf("No se pudo crear la COLA Envío\n");
	   		   		   	  gpioWrite(LEDB, ON);
	   		   		   	  while(1);
	   		   		   	  /* se queda bloqueado el sistema hasta
	   		   		   	  que venga el técnico de mantenmiento   */
	   	   }
	   queueMayusculizar = xQueueCreate(SIZE_QUEUE_MAYUS,sizeof(char*));
	   if(queueMayusculizar == NULL){
		   printf("No se pudo crear la COLA Mayusculizar\n");
		   		   	  gpioWrite(LED2, ON);
		   		   	  while(1);
		   		   	  /* se queda bloqueado el sistema hasta
		   		   	  que venga el técnico de mantenmiento   */
	   }
	   queueMinusculizar = xQueueCreate(SIZE_QUEUE_MINUS,sizeof(char*));
	   if(queueMinusculizar == NULL){
	   		   printf("No se pudo crear la COLA Minusculizar\n");
	   		   		   	  gpioWrite(LEDR, ON);
	   		   		   	  while(1);
	   		   		   	  /* se queda bloqueado el sistema hasta
	   		   		   	  que venga el técnico de mantenmiento   */
	   	   }

	    queueTransmitir =xQueueCreate(SIZE_QUEUE_TRANSMITIR,sizeof(char*));
		if(queueMinusculizar == NULL){
					printf("No se pudo crear la COLA Transmitir\n");
					gpioWrite(LEDG, ON);
					while(1);
							/* se queda bloqueado el sistema hasta
							que venga el técnico de mantenmiento   */
			}

	// Creacion  tareas en freeRTOS
	xTaskCreate(myTask,                     // Funcion de la tarea a ejecutar
			(const char *) "myTask", // Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE * 2, // Cantidad de stack de la tarea
			0,                          // Parametros de tarea
			tskIDLE_PRIORITY + 1,         // Prioridad de la tarea
			0                         // Puntero a la tarea creada en el sistema
			);

	// Crear tarea en freeRTOS
	xTaskCreate(procesamientoDatoRecibido,     // Funcion de la tarea a ejecutar
			(const char *) "procesamientoDatoRecibido", // Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE * 2, // Cantidad de stack de la tarea
			0,                          // Parametros de tarea
			tskIDLE_PRIORITY + 1,         // Prioridad de la tarea
			0                         // Puntero a la tarea creada en el sistema
			);
	// Creacion  tareas en freeRTOS
	xTaskCreate(operacion0,                     // Funcion de la tarea a ejecutar
					(const char *) "operacion0", // Nombre de la tarea como String amigable para el usuario
					configMINIMAL_STACK_SIZE * 2, // Cantidad de stack de la tarea
					0,                          // Parametros de tarea
					tskIDLE_PRIORITY + 1,         // Prioridad de la tarea
					0                         // Puntero a la tarea creada en el sistema
					);
	// Creacion  tareas en freeRTOS
		xTaskCreate(operacion1,                     // Funcion de la tarea a ejecutar
						(const char *) "operacion1", // Nombre de la tarea como String amigable para el usuario
						configMINIMAL_STACK_SIZE * 2, // Cantidad de stack de la tarea
						0,                          // Parametros de tarea
						tskIDLE_PRIORITY + 1,         // Prioridad de la tarea
						0                         // Puntero a la tarea creada en el sistema
						);

	// Creacion  tareas en freeRTOS
		xTaskCreate(taskAddHeaderLayerTwo,                     // Funcion de la tarea a ejecutar
				(const char *) "myTask", // Nombre de la tarea como String amigable para el usuario
				configMINIMAL_STACK_SIZE * 2, // Cantidad de stack de la tarea
				0,                          // Parametros de tarea
				tskIDLE_PRIORITY + 1,         // Prioridad de la tarea
				0                         // Puntero a la tarea creada en el sistema
				);



	// Iniciar scheduler
	vTaskStartScheduler();

	// ---------- REPETIR POR SIEMPRE --------------------------
	while ( TRUE) {
		// Si cae en este while 1 significa que no pudo iniciar el scheduler
	}
	return 0;
}

/*==================[definiciones de funciones internas]=====================*/


/*==================[definiciones de funciones externas]=====================*/


/*==================[fin del archivo]========================================*/
