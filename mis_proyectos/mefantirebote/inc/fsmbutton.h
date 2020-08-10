#ifndef _FSMBUTTON_H
#define _FSMBUTTON_H

#include "sapi.h"

#define CANTIDAD_TECLAS 4

 typedef enum{
	 STATE_BUTTON_UP,
	 STATE_BUTTON_DOWN,
	 STATE_BUTTON_FALLING,
	 STATE_BUTTON_RISING
	  }fsmButtonState_t;

typedef struct{
	  			gpioMap_t tec;
	  			fsmButtonState_t state;
	  			delay_t delay;
	  	  	  	}dbn_t;

//fsmButtonState_t fsmButtonState;
dbn_t vectorTeclas[CANTIDAD_TECLAS];

void fsmButtonError( void );
void fsmButtonInit( void );
void fsmButtonUpdate( dbn_t*);
void fsmButtonImprimir(void);



#endif
