#include "stepper_motor.h"

void stepperInit(stepperMotor_t * stepper, uint32_t stepsPerRovolution,
		gpioMap_t pulsePin, gpioMap_t directionPin, gpioMap_t enablePin,
		float stepAngle) {
	stepper->stepsPerRevolution = stepsPerRovolution;
	stepper->pulsePin = pulsePin;
	stepper->directionPin = directionPin;
	stepper->enablePin = enablePin;
	stepper->stepAngle = stepAngle;
	//establezco el sentido de los pines hacia el controlador

	gpioConfig(stepper->pulsePin, GPIO_OUTPUT);  //pin de salida, tren de pulsos
	gpioConfig(stepper->directionPin, GPIO_OUTPUT); //pin de salida, para establecer el sentido de giro del motor
	gpioConfig(stepper->enablePin, GPIO_OUTPUT); //pins de salida, Habilita/Deshbailita el motor
}

void stepperSpeedSet(stepperMotor_t* stepper, float speedRPM) {
	stepper->rpm = speedRPM;
}

float stepperSpeedGet(stepperMotor_t* stepper) {
	return stepper->rpm;
}
void stepperDirectionSet(stepperMotor_t* stepper, stepperDirection_t direction) {
	switch (direction) {

	case STEPPER_RIGHT:
		gpioWrite(stepper->directionPin, TRUE);
		stepper->turningSense = TRUE;
		break;
	case STEPPER_LEFT:
		gpioWrite(stepper->directionPin, FALSE);
		stepper->turningSense = FALSE;
		break;
	}

}

stepperDirection_t stepperDirectionGet(stepperMotor_t* stepper) {
	stepperDirection_t turn;

	if (!stepper->turningSense) {
		turn = STEPPER_RIGHT;
	} else {
		turn = STEPPER_LEFT;
	}
	return turn;
}

void stepperMoveSteps(stepperMotor_t* stepper, uint32_t numberOfSteps) {

	for (uint32_t countPulse = 0; countPulse < numberOfSteps; countPulse++) {
		gpioWrite(stepper->pulsePin, TRUE);
		delayInaccurateUs(250);
		gpioWrite(stepper->pulsePin, FALSE);
		delayInaccurateUs(250);
	}

}
void stepperMoveTurns(stepperMotor_t* stepper, uint32_t numberOfTurns) {

	stepperMoveSteps(stepper, stepper->stepsPerRevolution * numberOfTurns);
}

void stepperMoveAngle(stepperMotor_t* stepper, float Angle) {
	uint32_t steps;
	if (stepper->stepAngle != 0.000) {
		steps = Angle / stepper->stepAngle;
		stepperMoveSteps(stepper, steps);
	} else {
		printf("No se puede dividir un número en cero");
	}
}

void stepperEnable(stepperMotor_t* stepper) {
	gpioWrite(stepper->enablePin, TRUE);
	stepper->enable_Disable = STEPPER_ENABLE;
}

void stepperDisable(stepperMotor_t* stepper) {
	gpioWrite(stepper->enablePin, FALSE);
	stepper->enable_Disable = STEPPER_DISABLE;
}
