#ifndef _SERIE_UART_H
#define _SERIE_UART_H

#include "sapi.h"
#include "FreeRTOS.h"    //motor del Sistema Operativo
#include "queue.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"

/*Se define el tamaño de la cola*/
#define TAM_COLA 50
/*define el intervalo de periodicidad de la función periodica
 * por los que la recuencia del tren de pulsos de 2 hz */
#define AUTO_RELOAD_TIMER_PERIOD   pdMS_TO_TICKS(500)
/*esta función crea la cola e inicializa el puerto Serie USB
 * y configura como interrupción por recepcion de datos*/
void initSerie(void);
/*esta función crea un semaforo*/
void initSemaphore(void);
/*esta función crea e inicia un temporizador de software */
void initTimers(void);
void initStepperMotor(void);
/*Rutina de Servicio a la interrupción*/
void onRx(void *noUsado);
/*Tarea que procesa los caracteres que llegan por el puerto serie*/
void processRxSerieTask(void * taskParmPtr);
/*Tarea que interpreta los comandos almacenados en la cola*/
void processCommndTask(void * taskParmPtr);
/*Funcion periodica que genera pulsos*/
static void pvrAutoReloadTimerCallback(TimerHandle_t xTimer);

/*esta función convierte un caracter a decimal*/
int32_t convertir_caracter_a_decimal(char * puntero, uint8_t longitud);
#endif
