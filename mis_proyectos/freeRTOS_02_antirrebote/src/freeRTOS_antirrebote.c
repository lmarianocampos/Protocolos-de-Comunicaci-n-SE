/* Copyright 2017-2018, Eric Pernia
 * All rights reserved.
 *
 * This file is part of sAPI Library.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*==================[inlcusiones]============================================*/

// Includes de FreeRTOS
#include "../../freeRTOS_02_antirrebote/inc/FreeRTOSConfig.h"
#include "FreeRTOS.h"    //motor del Sistema Operativo
#include "task.h"        //API de control de tareas y temporización
#include "semphr.h"  	 //API de sincronización (semaforos y mutex)

// sAPI header
#include "sapi.h"

/*==================[definiciones y macros]==================================*/
typedef enum {
	STATE_BUTTON_UP,
	STATE_BUTTON_DOWN,
	STATE_BUTTON_FALLING,
	STATE_BUTTON_RISING

} FsmButtonState_t;
typedef enum {
	WITH_ERROR, WITHOUT_ERROR

} ErrState_t;
/*==================[definiciones de datos internos]=========================*/
SemaphoreHandle_t releasedEvent; // declaro un puntero a una estructura de datos de control del tipo semáforo
SemaphoreHandle_t pressedEvent; // es decir que me reserva memoria en tiempo de comilación
/*==================[definiciones de datos externos]=========================*/

DEBUG_PRINT_ENABLE
;

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

// Prototipo de funcion de la tarea
void teclaTask(void* taskParmPtr);
void ledTask(void * taskParmPtr);

/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main(void) {
	// ---------- CONFIGURACIONES ------------------------------
	// Inicializar y configurar la plataforma
	boardConfig();
	ErrState_t errorState;
	errorState = WITHOUT_ERROR;
	// UART for debug messages
	debugPrintConfigUart( UART_USB, 115200 );
	debugPrintlnString("Antirrebote  con freeRTOS y sAPI.");

	// Led para dar se�al de vida
	gpioWrite(LED3, ON);
	releasedEvent = xSemaphoreCreateBinary();
	if (releasedEvent == NULL) {
		errorState = WITH_ERROR;
	}
	pressedEvent = xSemaphoreCreateBinary();
	if (releasedEvent == NULL) {
		errorState = WITH_ERROR;
	}

	// Crear tarea en freeRTOS
	xTaskCreate(teclaTask,                  // Funcion de la tarea a ejecutar
			(const char *) "teclaTask", // Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE * 2, // Cantidad de stack de la tarea
			0,                          // Parametros de tarea
			tskIDLE_PRIORITY + 1,         // Prioridad de la tarea
			0                         // Puntero a la tarea creada en el sistema
			);
	xTaskCreate(ledTask,                     // Funcion de la tarea a ejecutar
			(const char *) "ledTask", // Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE * 2, // Cantidad de stack de la tarea
			0,                          // Parametros de tarea
			tskIDLE_PRIORITY + 1,         // Prioridad de la tarea
			0                         // Puntero a la tarea creada en el sistema
			);

	if (errorState == WITHOUT_ERROR) { //nos aseguramos que nuestro sistema no va arrancar si no se crearon los semáforos
		// Iniciar scheduler
		vTaskStartScheduler();
		printf("Se inicio el scheduler!!");

	} else {
		printf(
				"Error al iniciar crear la estructura de control del Semáforo!!");
	}

	// ---------- REPETIR POR SIEMPRE --------------------------
	while ( TRUE) {
		// Si cae en este while 1 significa que no pudo iniciar el scheduler
	}

	// NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
	// directamenteno sobre un microcontroladore y no es llamado por ningun
	// Sistema Operativo, como en el caso de un programa para PC.
	return 0;
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

// Implementacion de funcion de la tarea
void teclaTask(void* taskParmPtr) {
	// ---------- CONFIGURACIONES ------------------------------
	//printf("Antirrebote con freeRTOS y sAPI.\r\n");

	FsmButtonState_t buttomCurrentState;
	buttomCurrentState = STATE_BUTTON_UP;
	portTickType startTime; //variable que guardara el valor de tick en el momento
							// que detecte el inicio de presionado

	// Tarea periodica cada 5 ms
	portTickType xPeriodicity = 5/ portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();

	// ---------- REPETIR POR SIEMPRE --------------------------
	while (TRUE) {

		switch (buttomCurrentState) {
		case STATE_BUTTON_UP:
			if (!gpioRead(TEC1)) {
				buttomCurrentState = STATE_BUTTON_FALLING;
				startTime = xTaskGetTickCount();
			}

			break;
		case STATE_BUTTON_FALLING:
			if (!gpioRead(TEC1)) {
				if (((xTaskGetTickCount() - startTime) * portTICK_RATE_MS)
						>= 20) {
					buttomCurrentState = STATE_BUTTON_DOWN;
					xSemaphoreGive(pressedEvent);

				}
			} else {
				buttomCurrentState = STATE_BUTTON_UP;
			}

			break;
		case STATE_BUTTON_DOWN:
			if (gpioRead(TEC1)) {
				buttomCurrentState = STATE_BUTTON_RISING;
				startTime = xTaskGetTickCount();
			}
			break;

		case STATE_BUTTON_RISING:
			if (gpioRead(TEC1)) {
				if (((xTaskGetTickCount() - startTime) * portTICK_RATE_MS)
						>= 20) {
					buttomCurrentState = STATE_BUTTON_UP;
					xSemaphoreGive(releasedEvent);
				}

			} else {
				buttomCurrentState = STATE_BUTTON_DOWN;
			}
			break;

		}

		// Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
		vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}

void ledTask(void * taskparmPtr) {

	while (TRUE) {
		xSemaphoreTake(pressedEvent, portMAX_DELAY);
		//evento de boton pulsado
		gpioWrite(LEDB, ON);

		xSemaphoreTake(releasedEvent, portMAX_DELAY);
		// evento de boton liberado
		gpioWrite(LEDB, OFF);
	}

}

/*==================[fin del archivo]========================================*/
