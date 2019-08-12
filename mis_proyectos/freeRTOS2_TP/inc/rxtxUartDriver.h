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

/*=====[Evitar inclusion multiple comienzo]==================================*/

#ifndef _RX_TX_UART_DRIVER_H_
#define _RX_TX_UART_DRIVER_H_

#define SIZE_QUEUE_RECEIVE 50
/*=====[Inclusiones de dependencias de funciones publicas]===================*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"			//API de control de tareas y temporizacion
#include "queue.h"			//API de Colas
#include "sapi.h"


///*=====[C++ comienzo]========================================================*/
//
#ifdef __cplusplus
extern "C" {
#endif
//
///*=====[Macros de definicion de constantes publicas]=========================*/
//
#define TAMANIO_MAXIMO_PAQUETE 104
#define SIZE_QUEUE_SEND    50
#define SIZE_QUEUE_RECEIVE 50
#define SIZE_QUEUE_DELETE_POINTER 50
///*=====[Macros estilo funcion publicas]======================================*/

///*=====[Definiciones de tipos de datos publicos]=============================*/
QueueHandle_t colaReceive;
QueueHandle_t queueSend;
QueueHandle_t queueDeletePointer;
////Funcion de inicializacion de interrupciones
void IRQ_Init(void);
//Esta funcion se ejecuta a traves de una Interrupcion cuando se detecta un dato en la buffer de RX de la cola de la UART_USB

// Funcion Handler de ISR UART_USB de recepcion
void datoRecibido(void *noUsado);
//Esta Función corresponde a la interrupción de buffer transmisor tx vacío
void uartUsbSendCallback(void * noUsado);
void taskDeletePoint(void* taskParmPtr);
///*=====[Prototipos de funciones publicas]====================================*/

///*=====[Prototipos de funciones publicas de interrupcion]====================*/

///*=====[C++ fin]=============================================================*/
//
//#ifdef __cplusplus
//}
//#endif
//
///*=====[Evitar inclusion multiple fin]=======================================*/
//
#endif /* _RX_TX_UART_DRIVER_H_ */
