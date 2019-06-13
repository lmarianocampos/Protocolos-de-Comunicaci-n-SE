#ifndef _GPIO_H
#define _GPIO_H

#include "sapi.h"

 typedef struct{
	 gpioMap_t pin;
	 char printTecla[11];
	 char printState[12];
	 bool_t state;
 }boton_t;

void botonPresionado(boton_t *);

#endif
