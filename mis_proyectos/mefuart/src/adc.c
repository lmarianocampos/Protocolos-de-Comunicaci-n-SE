#include "adc.h"

void lecturaDatos(adc_t * adc){

	if(adc!=NULL){
		adc->valor = adcRead(CH1);
	}

}
