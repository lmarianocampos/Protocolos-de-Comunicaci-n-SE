#ifndef _FSM_H
#define _FSM_H

#include "sapi.h"
#include "adc.h"

typedef enum{
     STATE_DEFAULT,
	 STATE_GPIO,
	 STATE_ADC

	  }fsmState_t;

fsmState_t fsmState;
//bool_t flagMessage = FALSE ;

void fsmError( void );
void fsmInit( void );
void fsmUpdate( fsmState_t );
void fsmconvertirDecimalCaracter(adc_t *);
void fsmImprimir(void);



#endif
