#ifndef PWM_H
#define PWM_H

  #include "sapi.h"



#define MOTOR_TOTALNUMBER 1
#define EMPTY_POSITION    255

void timer1CompareMatch0funcMotor(void *ptr);
void timer1CompareMatch1funcMotor(void* ptr);
void InicializarTimers(void);
void EnableCompareMatchMotor(void);

#endif
