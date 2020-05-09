#ifndef LINEARSENSOR_H
#define LINEARSENSOR_H

#include "sapi.h"
#include "stepmotor.h"

#define CANAL3 3
#define PORT2  2 //corresponde al GPIO LCD2
#define PIN5   5 //corresponde al GPIO LCD2

#define PORT3  3
#define PIN6   6

#define PORT0  0 //corresponde a la TEC 1
#define PIN4   4 //corresponde a la TEC 1

typedef struct{

	uint32_t pcClockwise;
	uint32_t pcCounterClockWise;
	float position; //va estar en cm
	//es la distancia que se mueve el filo de la compuerta al girar un paso el eje del motor PaP
	float distancePerPulse; //va estar en cm

}linearSensor_t;

 linearSensor_t ls;

//esta función configura el input capture
void configInterruptIRQ(void);

// inicia el el objeto sensor lineal
void linearSensorInit(linearSensor_t* ls,uint32_t pcAntihorario,uint32_t pcHorario,float position,float dPerPulse);

//esta función establece la posición correspondiente al filo de la compuerta
void linearSensorSetPosition(linearSensor_t* ls,stepperMotor_t* stepper);

//esta función devuelve la posición del filo de la compuerta
uint32_t linearSensorGetPosition(linearSensor_t* ls);

// esta función establece la disctancia que que recorre el filo de la compuerta al girar un paso el eje del Motor PaP
void linearSensorSetDistancePerPulse(linearSensor_t* ls, float dPerPulse);

//esta función retorna la distancia por pulso
float linearSensorGetDistancePerPulse(linearSensor_t* ls);

// esta función retorna el valor de los pulsos que se contaron en sentido horario
uint32_t linearSensorGetPulsosClockwise(linearSensor_t* ls);

// esta función retorna el valor de los pulsos que se contaron en sentido Antihorario
uint32_t linearSensorGetCounterClockWise(linearSensor_t* ls);

#endif