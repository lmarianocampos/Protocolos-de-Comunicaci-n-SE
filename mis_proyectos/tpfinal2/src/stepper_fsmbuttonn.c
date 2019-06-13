#include "stepper_fsmbutton.h"

stepperDbn_t sDbn1;
stepperDbn_t sDbn2;
stepperDbn_t sDbn3;
stepperDbn_t sDbn4;

void stepperButtonStart() {
	stepperButtonInit(&sDbn1, TEC1, STATE_BUTTON_UP, FALSE, FALSE, 0);
	stepperButtonInit(&sDbn2, TEC2, STATE_BUTTON_UP, FALSE, FALSE, 0);
	stepperButtonInit(&sDbn3, TEC3, STATE_BUTTON_UP, FALSE, FALSE, 0);
	stepperButtonInit(&sDbn4, TEC4, STATE_BUTTON_UP, FALSE, FALSE, 0);
}

void stepperButtonInit(stepperDbn_t* stepperDebounce, gpioMap_t tec,
		stepperFsmButtonState_t state, bool_t flagFalling, bool_t flagRising,
		uint32_t countPulses) {

	stepperDebounce->tec = tec;
	stepperDebounce->state = state;
	stepperDebounce->flagFalling = flagFalling;
	stepperDebounce->flagRising = flagRising;
	stepperDebounce->countPulses = countPulses;
}

void stepperExecuteButton() {
	stepperFsmButtonUpdate(&sDbn1);
	stepperFsmButtonUpdate(&sDbn2);
	stepperFsmButtonUpdate(&sDbn3);
	stepperFsmButtonUpdate(&sDbn4);
}

// FSM Error Handler Function
void stepperFsmButtonError(stepperDbn_t* stepperDebounce) {
	// Error handler, example, restart FSM:
	stepperDebounce->state = STATE_BUTTON_UP;

}

// FSM Initialize Function
void stepperFsmButtonInit(stepperDbn_t* stepperDebounce) {
	// Example:
	// boardInit();          // Initialize hardwaree
	stepperDebounce->state = STATE_BUTTON_UP;
}

void stepperFsmButtonUpdate(stepperDbn_t* stepperDebounce) {
	switch (stepperDebounce->state) {

	case STATE_BUTTON_UP:
		if (!gpioRead(stepperDebounce->tec)) {
			stepperDebounce->state = STATE_BUTTON_FALLING;
		}
		break;
	case STATE_BUTTON_DOWN:
		if (gpioRead(stepperDebounce->tec)) {
			stepperDebounce->state = STATE_BUTTON_RISING;
		}
		break;

	case STATE_BUTTON_FALLING:	//flanco negativo
		if (stepperDebounce->flagFalling == FALSE) {
			delayConfig(&(stepperDebounce->delay), ANTI_REBOUND_TIME);
			stepperDebounce->flagFalling = TRUE;
		}
		if (delayRead(&(stepperDebounce->delay))) {
			if (!gpioRead(stepperDebounce->tec)) {
				stepperDebounce->state = STATE_BUTTON_DOWN;
				stepperDebounce->countPulses++;
			} else {
				stepperDebounce->state = STATE_BUTTON_UP;
			}
		}
		if (stepperDebounce->state != STATE_BUTTON_FALLING) {
			stepperDebounce->flagFalling = FALSE;
		}

		break;
	case STATE_BUTTON_RISING:
		if (stepperDebounce->flagRising == FALSE) {
			delayConfig(&(stepperDebounce->delay), ANTI_REBOUND_TIME);
			stepperDebounce->flagRising = TRUE;
		}
		if (delayRead(&(stepperDebounce->delay))) {
			if (gpioRead(stepperDebounce->tec)) {
				stepperDebounce->state = STATE_BUTTON_UP;
			} else {
				stepperDebounce->state = STATE_BUTTON_DOWN;
			}
		}
		if (stepperDebounce->state != STATE_BUTTON_RISING) {
			stepperDebounce->flagRising = FALSE;
		}
		break;

	}

}

void stepperButtonPrint() {
	uartWriteByte(UART_USB, 27);
	uartWriteString(UART_USB, "[2J");
	uartWriteByte(UART_USB, 27);
	uartWriteString(UART_USB, "[H");
	printf("Pulsos Registrados por la TECLA1:%d\r\n", sDbn1.countPulses);
	printf("Pulsos Registrados por la TECLA2:%d\r\n", sDbn2.countPulses);
	printf("Pulsos Registrados por la TECLA3:%d\r\n", sDbn3.countPulses);
	printf("Pulsos Registrados por la TECLA4:%d\r\n", sDbn4.countPulses);
}
