#include "linearsensor.h"

void configInterruptIRQ() {
	Chip_PININT_Init(LPC_GPIO_PIN_INT);
	Chip_SCU_GPIOIntPinSel(CANAL3, PORT3, PIN6);
	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH3);
	Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH3);
	NVIC_EnableIRQ(PIN_INT3_IRQn);

}
//defino mi handler de interrupción
void GPIO3_IRQHandler(void) {
	static uint32_t pulseCount = 0;
//identificamos que la interrupción es por un flanco ascendente
	if (Chip_PININT_GetRiseStates(LPC_GPIO_PIN_INT) & PININTCH3) {
		//limpiamos el flag de interrupción correspondiente al canal 3
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH3);
		//if (stepper.isMoveAxis == STEPPER_AXIS_IN_MOVE) {
		//contamos los pulsos tanto en sentido horario como antihorario
		switch (stepper.direction) {
		case STEPPER_RIGHT:
			linearSensorIncreaseClockWisePulses(&ls);

			//ls.pcClockwise++;
			printf("Cantidad de Pulsos Horario:%d\n",linearSensorGetPulsesClockWise(& ls));

			break;
		case STEPPER_LEFT:
			//ls.pcCounterClockWise++;
			linearSensorIncreasePulsesCounterClockWise (&ls);
			printf("Cantidad de Pulsos Antihorario:%d\n",linearSensorGetPulsesCounterClockWise(& ls));
			break;
		default: // llamar a una función de error
			break;
		}
		//	}
	}
}

void linearSensorInit(linearSensor_t* ls, uint32_t pcCounterClockWise,
		uint32_t pcClockwise, float position, float dPerPulse) {
	if (dPerPulse > 0) {
		ls->pcCounterClockWise = pcCounterClockWise;
		ls->pcClockwise = pcClockwise;
		ls->position = position;
		ls->distancePerPulse = dPerPulse;
	} else {
		printf("La distancia por pulso es igual o menor a cero\n");
	}

}

void linearSensorSetPosition(linearSensor_t* ls, stepperMotor_t* stepper) {
	//controlo que el eje del motor
	if (stepper->isMoveAxis == STEPPER_AXIS_LAST_MOVE) {
		printf("Entro en LinearSensorSetPosition......\n");
		//printf("Cantidad de Pulsos Horario:%d\n", ls->pcClockwise);
		//printf("Cantidad de Pulsos Antihorario:%d\n", ls->pcCounterClockWise);
		/*if (ls->pcHorario > ls->pcAntihorario)
		 ls->position = ls->distancePerPulse
		 * (ls->pcHorario - ls->pcAntihorario);
		 if (ls->pcHorario < ls->pcAntihorario)
		 ls->position = ls->distancePerPulse
		 * (ls->pcAntihorario - ls->pcHorario);
		 if (ls->pcHorario == ls->pcAntihorario)
		 ls->position = 0;*/
		stepper->isMoveAxis = STEPPER_AXIS_NO_MOVE;
		//ls->pcAntihorario = 0;
		//ls->pcHorario = 0;
	}

}

void linearSensorSetDistancePerPulse(linearSensor_t* ls, float dPerPulse) {

	if (dPerPulse > 0)
		ls->distancePerPulse = dPerPulse;
	else
		printf("Valor invalido: distancia por pulso\n ");
}

float linearSensorGetDistancePerPulse(linearSensor_t* ls) {
	return ls->distancePerPulse;
}

uint32_t linearSensorGetPulsesClockWise(linearSensor_t* ls){
	return ls->pcClockwise;

}

uint32_t linearSensorGetPulsesCounterClockWise(linearSensor_t* ls){
	return ls->pcCounterClockWise;
}

void linearSensorIncreaseClockWisePulses(linearSensor_t* ls){
	ls->pcClockwise++;
}

void linearSensorIncreasePulsesCounterClockWise (linearSensor_t*ls){
	ls->pcCounterClockWise++;
}

