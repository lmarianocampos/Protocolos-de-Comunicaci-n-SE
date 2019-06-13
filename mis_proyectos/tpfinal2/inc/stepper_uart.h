#ifndef _STEPPER_UART_H
#define _STEPPER_UART_H

#include "sapi.h"
#include "stepper_motor.h"

//Esta función lee si hay datos en el buffer de recepcion de datos, Rx.
void stepperReadUart(void);
#endif
