#include "stepmotor.h"
//uint32_t pulseCount = 0;

static void stepperMotorCycle() {

	if (pulseCount != 0) {
		gpioWrite(PULSE_PIN, ON);
		pulseCount--;
	}
}
static void stepperMotorDutyCycle() {
	gpioWrite(PULSE_PIN, OFF);
}
void stepperMotorInit(stepperMotor_t *stepper, uint32_t stepsPerRevolution,
		gpioMap_t directionPin, gpioMap_t enablePin, gpioMap_t microStepsM0Pin,
		gpioMap_t microStepsM1Pin, gpioMap_t microStepsM2Pin, float stepAngle) {

	stepper->stepsPerRevolution = stepsPerRevolution;
	stepper->directionPin = directionPin;
	stepper->enablePin = enablePin;
	stepper->microStepsM0Pin = microStepsM0Pin;
	stepper->microStepsM1Pin = microStepsM1Pin;
	stepper->microStepsM2Pin = microStepsM2Pin;
	stepper->stepAngle = stepAngle;

	// configuro el sentidos de los GPIO'S
	gpioConfig(PULSE_PIN, GPIO_OUTPUT);
	gpioConfig(stepper->directionPin, GPIO_OUTPUT);
	gpioConfig(stepper->enablePin, GPIO_OUTPUT);
	gpioConfig(stepper->microStepsM0Pin, GPIO_OUTPUT);
	gpioConfig(stepper->microStepsM1Pin, GPIO_OUTPUT);
	gpioConfig(stepper->microStepsM2Pin, GPIO_OUTPUT);

	//Debo configurar el timer para poder generar el ciclo
	Timer_Init(TIMER0, Timer_microsecondsToTicks(CYCLE_PULSE),
			stepperMotorCycle);
	Timer_EnableCompareMatch(TIMER0, TIMERCOMPAREMATCH1,
			Timer_microsecondsToTicks(DUTY_CYCLE), stepperMotorDutyCycle);

}

void stepperMotorSetSpeed(stepperMotor_t * stepper, float rpm) {
	stepper->rpm = rpm;
}

float stepperMotorGetSpeed(stepperMotor_t * stepper) {
	return stepper->rpm;
}
void stepperMotorSetDirection(stepperMotor_t * stepper,
		stepperMotorDirection_t dir) {

	switch (dir) {
	case STEPPER_RIGHT:
		gpioWrite(stepper->directionPin, TRUE);
		stepper->direction = dir;
		break;
	case STEPPER_LEFT:
		gpioWrite(stepper->directionPin, FALSE);
		stepper->direction = dir;
		break;
	}
}

stepperMotorDirection_t stepperMotorGetDirection(stepperMotor_t *stepper) {
	//debo controlar que el eje del motor este girando y luego enviar el dato
	return stepper->direction;
}
void stepperMotorEnable(stepperMotor_t *stepper, stepperMotorEnable_t enable) {
	switch (enable) {
	case STEPPER_ENABLE:
		gpioWrite(stepper->enablePin, FALSE); //activo en bajo
		stepper->isEnable = enable;
		break;
	case STEPPER_DISABLE:
		gpioWrite(stepper->enablePin, TRUE);
		stepper->isEnable = enable;
	}
}

stepperMotorEnable_t stepperMotorGetEnable(stepperMotor_t *stepper) {
	return stepper->isEnable;
}

void stepperMotorMoveSteps(stepperMotor_t *stepper, uint32_t numberOfSteps) {
	// debemos generar la cantidad de pulsos...
	//controlar si el motor se encuentra habilitado para generar los pulsos
	if (stepper->isEnable == STEPPER_ENABLE)
		pulseCount = numberOfSteps;

}

void stepperMotorMoveTurns(stepperMotor_t *stepper, uint32_t numberOfTurns) {
	stepperMotorMoveSteps(stepper, stepper->stepsPerRevolution * numberOfTurns);
}

void stepperMotorMoveAngle(stepperMotor_t *stepper, float angle) {
	if (stepper->stepAngle != 0.000) {
		stepperMotorMoveSteps(stepper, angle / stepper->stepAngle);
	} else {
		printf("No se puede realizar una división por 0");
	}
}

void stepperMotorSetMicroSteps(stepperMotor_t *stepper, bool_t m0MicroStep,
		bool_t m1MicroStep, bool_t m2MicroStep) {
	//controlar que el eje del motor no este girando para poder establecer un microsteps....
	//podemos preguntar si pulseCount=0
	if (pulseCount == 0) {
		gpioWrite(stepper->microStepsM0Pin, m0MicroStep);
		gpioWrite(stepper->microStepsM1Pin, m1MicroStep);
		gpioWrite(stepper->microStepsM2Pin, m2MicroStep);
	}
}
