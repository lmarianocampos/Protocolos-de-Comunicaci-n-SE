#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H

  #include "sapi.h"
  #include "sapi_datatypes.h"
  #include "sapi_peripheral_map.h"


#define MOTOR_TOTALNUMBER 1
#define EMPTY_POSITION    255

void timer1CompareMatch0funcMotor(void *ptr);
void timer1CompareMatch1funcMotor(void* ptr);
void InicializarTimers(void);
void EnableCompareMatchMotor(void);

#endif
