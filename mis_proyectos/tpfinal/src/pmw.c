#include "pwm.h"
#include "sapi_timer.h"
#include "sapi_gpio.h"

#define MOTOR_COMPLETECYCLE_PERIODO   2000  /* value in uSec */
#define DUTY_CYCLE                    1000
#define TOTAL_PULSE                   20

typedef struct{
	uint8_t numMotor;
	uint8_t dutyCycle;
	uint8_t associatedTimer;
	uint8_t associatedCompareMatch;
	uint64_t countPulse;
	callBackFuncPtr_t associatedFunction;

}attachedMotor_t;


static const uint8_t motorMap[ MOTOR_TOTALNUMBER ] = {
   T_FIL1, // MOTOR0
  // T_COL0, // MOTOR1
  //T_FIL2, // MOTOR2
  // T_FIL3, // MOTOR3
  // GPIO8,  // MOTOR4
  //LCD1,   // MOTOR5
  //LCD2,   // MOTOR6
  //LCD3,   // MOTOR7
  //GPIO2   // MOTOR8
};
/*when the user adds a servo with servoAttach the list updates with the motor number*/
static attachedMotor_t AttachedMotorList[ MOTOR_TOTALNUMBER ] =
   /*position |Motor number | value | asociatedTimer | associatedCompareMatch |countPulse | associatedFunction*/
   /*0*/	  { EMPTY_POSITION , 0,  TIMER1 , TIMERCOMPAREMATCH1 ,0, timer1CompareMatch1funcMotor};
   /*1*/	//{ EMPTY_POSITION , 0 , TIMER1 , TIMERCOMPAREMATCH2 ,0, timer1CompareMatch2funcMotor },
   /*2*/	//{ EMPTY_POSITION , 0 , TIMER1 , TIMERCOMPAREMATCH3 ,0, timer1CompareMatch3funcMotor },
   /*3*/	//{ EMPTY_POSITION , 0 , TIMER2 , TIMERCOMPAREMATCH1 ,0, timer2CompareMatch1funcMotor },
   /*4*/	//{ EMPTY_POSITION , 0 , TIMER2 , TIMERCOMPAREMATCH2 ,0, timer2CompareMatch2funcMotor },
   /*5*/	//{ EMPTY_POSITION , 0 , TIMER2 , TIMERCOMPAREMATCH3 ,0, timer2CompareMatch3funcMotor },
   /*6*/	//{ EMPTY_POSITION , 0 , TIMER3 , TIMERCOMPAREMATCH1 ,0, timer3CompareMatch1funcMotor },
   /*7*/	//{ EMPTY_POSITION , 0 , TIMER3 , TIMERCOMPAREMATCH2 ,0, timer3CompareMatch2funcMotor },
   /*8*/	//{ EMPTY_POSITION , 0 , TIMER3 , TIMERCOMPAREMATCH3 ,0, timer3CompareMatch3funcMotor }
//};

void timer1CompareMatch0funcMotor(void * ptr){
	uint8_t index;
	index=0;

	gpioWrite(motorMap[AttachedMotorList[index].numMotor],TRUE);
    AttachedMotorList[index].countPulse++;

	if(AttachedMotorList[index].countPulse++ >= TOTAL_PULSE ){

  Timer_DisableCompareMatch(AttachedMotorList[index].associatedTimer,AttachedMotorList[index].associatedCompareMatch);
		AttachedMotorList[index].countPulse = 0;
	}
	else{
		Timer_SetCompareMatch(AttachedMotorList[index].associatedTimer,AttachedMotorList[index].associatedCompareMatch,
				Timer_microsecondsToTicks(DUTY_CYCLE));

	}


}


void timer1CompareMatch1funcMotor(void* ptr){
	gpioWrite(motorMap[AttachedMotorList[0].numMotor],FALSE);
}

void InicializarTimers(void){
Timer_Init(TIMER1,Timer_microsecondsToTicks(MOTOR_COMPLETECYCLE_PERIODO),timer1CompareMatch0funcMotor);


}
void EnableCompareMatchMotor(void){

	gpioConfig( (gpioMap_t)motorMap[0], GPIO_OUTPUT );

	Timer_EnableCompareMatch(AttachedMotorList[0].associatedTimer,AttachedMotorList[0].associatedCompareMatch,
			Timer_microsecondsToTicks(DUTY_CYCLE),AttachedMotorList[0].associatedFunction);

}
