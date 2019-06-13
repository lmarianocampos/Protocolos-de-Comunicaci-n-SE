#ifndef _ADC_H
#define _ADC_H

	#include "sapi.h"

	typedef struct{
		uint16_t valor;
		char stringValor[4];
        char printValor[4];
		} adc_t;

		void lecturaDatos(adc_t *);
#endif
