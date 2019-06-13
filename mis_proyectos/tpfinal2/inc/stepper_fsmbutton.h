#ifndef _STEPPER_FSMBUTTON_H
#define _STEPPER_FSMBUTTON_H

#include "sapi.h"

#define ANTI_REBOUND_TIME 40

typedef enum {
	STATE_BUTTON_UP,
	STATE_BUTTON_DOWN,
	STATE_BUTTON_FALLING,
	STATE_BUTTON_RISING

} stepperFsmButtonState_t;

typedef struct {
	gpioMap_t tec;
	stepperFsmButtonState_t state;
	delay_t delay;
	bool_t flagFalling;
	bool_t flagRising;
	uint32_t countPulses;
} stepperDbn_t;
//Esta Función llama a cada una de las funciones que incializan los miembros de la estructura de cada boton
void stepperButtonStart(void);

// Esta función inicializa cada miembro de la estructura de un boton en particular.
void stepperButtonInit(stepperDbn_t* stepperDebounce, gpioMap_t tec,
		stepperFsmButtonState_t state, bool_t flagFalling, bool_t flagRising,
		uint32_t countPulses);

//Esta función llama a las funciones para actualizar el estado de cada boton
void stepperExecuteButton(void);

//Estas funciones Iniciliza el estado de las teclas
void stepperFsmButtonError(stepperDbn_t* stepperDebounce);
void stepperFsmButtonInit(stepperDbn_t* stepperDebounce);

//Esta función actualiza el estado de una boton en particular
void stepperFsmButtonUpdate(stepperDbn_t* stepperDebounce);

//Esta función imprime en pantalla la cantidad de pulso registrado por cada una de los botones
void stepperButtonPrint(void);

#endif
