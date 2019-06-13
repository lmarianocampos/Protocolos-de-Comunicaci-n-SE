#include "gpio.h"

char statePinPressed[] = "Pressed\n\r";
char statePinReleased[]= "Released\n\r";

void botonPresionado(boton_t * tecla){
	if(!gpioRead(tecla->pin)){     //si esta presionado devuelve 0 ,si no esta presionado devuelve 1
	for(uint8_t i=0;i<11;i++){
		tecla-> printState [i] = statePinPressed[i];
	}
	tecla->state = FALSE;
	}
	else{
		for(uint8_t i=0;i<12;i++){
		tecla-> printState[i]= statePinReleased[i];
		}
			tecla->state = TRUE;
	}

}
