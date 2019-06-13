#ifndef _STTEPER_MOTOR_H
#define _STTEPER_MOTOR_H

#include"sapi.h"

typedef enum {
	STEPPER_RIGHT, STEPPER_LEFT,
} stepperDirection_t;

typedef enum {
	STEPPER_ENABLE, STEPPER_DISABLE
} stepperEnble_t;

typedef struct {
	uint32_t stepsPerRevolution;     //cantidad de pasos por vuelta

	gpioMap_t pulsePin;               //pin tren de pulso
	gpioMap_t directionPin; // pin de salida, indica la dirección en que girará el motor
	gpioMap_t enablePin;       //pin de salida, habilita o deshabilita el motor.

	bool_t turningSense;
	stepperEnble_t enable_Disable;
	float stepAngle;
	float rpm;            // guarda el valor de rpm en que esta girando el motor

} stepperMotor_t;

//Esta función carga la estructura stepper e incializa todo el Hardware
void stepperInit(stepperMotor_t* stepper, uint32_t stepsPerRovolution,
		gpioMap_t pulsePin, gpioMap_t directionPin, gpioMap_t enable,
		float stepAngle);

//Esta función permite establecer la velocidad en RPM
void stepperSpeedSet(stepperMotor_t* stepper, float speedRPM);

// Esta función Permite leer la velocidad en rpm
float stepperSpeedGet(stepperMotor_t* stepper);

//Esta función permite esablecer el sentido de dirección del giro del motor
void stepperDirectionSet(stepperMotor_t* stepper, stepperDirection_t direction);

//Esta función permite leer el sentido de giro del motor
stepperDirection_t stepperDirectionGet(stepperMotor_t* stepper);

//Esta función permite mover una cierta cantida de pasos, 1paso = angulo de giro del motor especificado
void stepperMoveSteps(stepperMotor_t* stepper, uint32_t numberOfSteps);

//Esta función permite girar el eje del motor una cierta cantidad de vueltas completas
void stepperMoveTurns(stepperMotor_t* stepper, uint32_t numberOfTurns);

// Esta función permite girar el eje del motor un cierto ángulo
void stepperMoveAngle(stepperMotor_t* stepper, float angle);

//Esta función permite habilitar el motor
void stepperEnable(stepperMotor_t* stepper);

//Esta función permite deshabilitar el motor
void stepperDisable(stepperMotor_t* stepper);

//Estaa función permite leer estado del Motor Habilitado/Deshabilitado
stepperEnble_t stepperEnableDisable(stepperMotor_t* stepper);

#endif
