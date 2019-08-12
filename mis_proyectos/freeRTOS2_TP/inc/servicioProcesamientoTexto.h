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

#ifndef _SERVICIO_PROCESAMIENTO_TEXTO_H_
#define _SERVICIO_PROCESAMIENTO_TEXTO_H_

///*=====[Inclusiones de dependencias de funciones publicas]===================*/
//
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"			//API de control de tareas y temporizacion
#include "semphr.h"			//API de sincronizacion (sem y mutex)
#include "queue.h"			//API de Colas
#include <string.h>
#include <stdio.h>

//
///*=====[C++ comienzo]========================================================*/
#ifdef __cplusplus
extern "C" {
#endif

///*=====[Macros de definicion de constantes publicas]=========================*/

///*=====[Macros estilo funcion publicas]======================================*/

///*=====[Definiciones de tipos de datos publicos]=============================*/

///*=====[Prototipos de funciones publicas]====================================*/



//Tarea para el procesamiento de los datos recibidos a traves de UART_USB
void procesamientoDatoRecibido(void* taskParmPtr);

void interruptTx(void * noUsado);
//
///*=====[Prototipos de funciones publicas de interrupcion]====================*/


///*=====[C++ fin]=============================================================*/

#ifdef __cplusplus
}
#endif

///*=====[Evitar inclusion multiple fin]=======================================*/
//
#endif /* _SERVICIO_PROCESAMIENTO_TEXTO_H_ */
