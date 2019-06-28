#include "serie_uart.h"
#include "stepper_motor.h"

static xQueueHandle cola_rec;
static SemaphoreHandle_t sinsynchronizeTasks;
static char message[20];
static TimerHandle_t xAutoReloadTimer;
stepperMotor_t motor;
int32_t pulse;
void initSerie(void) {

	uartCallbackSet(UART_USB, UART_RECEIVE, onRx, NULL);
	uartInterrupt(UART_USB, TRUE);
	printf("freeRTOS y sAPI.\n\r");
	cola_rec = xQueueCreate(TAM_COLA, sizeof(char));

	if (cola_rec == NULL) {
		/*llamo a una función que prende un led para advertir un error al crear la cola*/
		gpioWrite(LED2, ON);
		printf("No se pudo crear la cola \n\r");
		while (1)
			;/*   Se queda bloqueado el sistema hasta
			 que venga el técnico de mantenimiento*/

	}
}
void initSemaphore(void) {
	sinsynchronizeTasks = xSemaphoreCreateBinary();
	if (sinsynchronizeTasks == NULL) {
		/*llamo a una función que prende un led para advertir un error al crear la cola*/
		gpioWrite(LED1, ON);
		printf("No se pudo crear el semaforo \n\r");

		while (1)
			;/*   Se queda bloqueado el sistema hasta
			 que venga el técnico de mantenimiento*/
	}

}

void initTimers(void) {
	xAutoReloadTimer = xTimerCreate("AutoReload", AUTO_RELOAD_TIMER_PERIOD,
	pdTRUE, 0, pvrAutoReloadTimerCallback);
	if (xAutoReloadTimer == NULL) {
		gpioWrite(LEDR, ON);
		printf("No se pudo crear el controlador del Timer \n\r");
		while (TRUE)
			;
		/*   Se queda bloqueado el sistema hasta
		 que venga el técnico de mantenimiento*/

	}

}
void initStepperMotor(void) {
	stepperInit(&motor, 200, GPIO0, GPIO1, GPIO2, 7.5);

	printf("Se inicializo el motor\n\r");

}
void onRx(void *noUsado) {
	BaseType_t xHigherpriorityTaskWoken = pdFALSE;
	char data = uartRxRead(UART_USB);

	xQueueSendFromISR(cola_rec, &data, &xHigherpriorityTaskWoken);

	if (xHigherpriorityTaskWoken == pdTRUE) {
		portYIELD_FROM_ISR(xHigherpriorityTaskWoken);
	}

}

void processRxSerieTask(void * taskParmPtr) {

	static uint8_t index = 0;
	char car_rec;
	while (TRUE) {
		if (xQueueReceive(cola_rec, &car_rec, portMAX_DELAY) == pdTRUE) {
			message[index] = car_rec;
			if (message[index] == '\n') {
				message[index + 1] = '\0';
				index = 0;
				xSemaphoreGive(sinsynchronizeTasks);/*cuando libera el semaforo significa que ya hay un comando en la cola de recepción*/
			} else {
				index++;
			}

		}
	}

}
void processCommndTask(void * taskParmPtr) {
	int32_t angle;
	while (TRUE) {
		/*si se obtuvo el semaforosignifica que hay un comando por procesar*/
		if (xSemaphoreTake(sinsynchronizeTasks, portMAX_DELAY) == pdTRUE) {

			switch (message[1]) {
			case 'L': /*Establecer el sentido de giro a la izquierda*/
				stepperDirectionSet(&motor, STEPPER_LEFT);

				break;
			case 'R': /*Establecer el sentido de giro a la derecha*/

				stepperDirectionSet(&motor, STEPPER_RIGHT);
				break;
			case 'E':/*habilitar el Motor*/
				stepperEnable(&motor); //habilito el motor
				printf("Se habilito el motor\n\r");
				break;
			case 'D':/*Deshabilitar el motor*/
				stepperDisable(&motor);
				printf("Se deshabilito el motor\n\r");
				break;
			}
			switch (message[2]) {
			case 'P':
				printf(" genera tren de pulsos\n\r");
				/*llamar a la funcion que genera un tren de pulso*/
				pulse = convertir_caracter_a_decimal(&message[3], 4);
				if (xTimerStart(xAutoReloadTimer,0) != pdPASS) {
					printf(" no se pudo iniciar el temporizador\n\r");
				}
				break;
			case 'A':
				printf(" gira un cierto angulo\n\r");
				/*llamar a la funcion que mueve el eje u cierto ańgulo*/
				angle = convertir_caracter_a_decimal(&message[3], 4);
				pulse = angle / motor.stepAngle;
				if (xTimerStart(xAutoReloadTimer,0) != pdPASS) {
					printf(" no se pudo iniciar el temporizador\n\r");
				}

				break;

			}
		}

	}

}

int32_t convertir_caracter_a_decimal(char * puntero, uint8_t longitud) {

	uint32_t num = 0;
	uint32_t digito = 0;
	uint32_t tam = longitud;
	int32_t expo = 0;
	uint32_t pot = 1;
	int32_t i;

	for (i = tam; i > 0; --i) {

		digito = (uint32_t)(*(puntero + (i - 1)) - 48);

		expo = tam - i;
		pot = 1;
		while (expo > 0) { //para sacar la potencia

			pot = pot * 10;
			expo = expo - 1;
		}
		num = num + digito * pot;
	}
	return num;
}

static void pvrAutoReloadTimerCallback(TimerHandle_t xTimer) {
	static uint32_t i = 0;
	static bool_t flag = TRUE;
	if (i < pulse) {
		if (flag == TRUE) {
			gpioWrite(motor.pulsePin, TRUE);
			flag = FALSE;

		} else {
			gpioWrite(motor.pulsePin, FALSE);
			flag = TRUE;
			i++;
		}
	} else {
		i = 0;
		xTimerStop(xTimer, 0);
	}

}
