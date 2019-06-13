#ifndef _IMPRIMIR_H
#define _IMPRIMIR_H

	#include "gpio.h"
    #include "fsm.h"
    #include "adc.h"

	void imprimirTec(boton_t*);
	void imprimirAdc(adc_t*);
	void imprimirClearScreem(void);

#endif
