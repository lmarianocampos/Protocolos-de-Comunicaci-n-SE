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
#define AUTO_RELOAD_TIMER_PERIOD   pdMS_TO_TICKS(500)
/*esta función crea la cola e inicializa el puerto Serie USB*/
void initSerie(void);
void initSemaphore(void);
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

/**/
int32_t convertir_caracter_a_decimal(char * puntero, uint8_t longitud);
#endif
