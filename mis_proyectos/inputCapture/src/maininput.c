#include "sapi.h"



int main(void){
	boardConfig();

	gpioConfig(GPIO0,GPIO_OUTPUT);


	timerTickerConfig(TIMER1,10);
	timerTickerSetTickEvent(TIMER1,tickCallback);


	timerInputCaptureConfig(TIMER0,TIMER_CAPTURE2,10,TRUE,FALSE);
	timerInputCaptureSetCaptureEvent(TIMER0,TIMER_CAPTURE2,T0CaptureCallBack);

	timerSetPower(TIMER0,ON);
	timerSetPower(TIMER1,ON);
	while(TRUE){
		sleepUntilNextInterrupt();

	}
	return 0;
}
