#include "inputinterrupt.h"


volatile uint32_t tCapturadorAnterior = 0;

bool_t tickCallBack(void * ptr){

	gpioToggle(GPIO0);

}

bool_t T0CaptureCallBack(void* ptr){

	gpioToggle(LED1);
	if(tCapturadorAnterior == 0){
		tCapturadorAnterior = timerReadCapture(TIMER0,TIMER_CAPTURE2);
	}
	else{
		uint32_t tCapturadorActual = timerReadCapture(TIMER0,TIMER_CAPTURE2);
		uint32_t result = (tCapturadorActual-tCapturadorAnterior)/(timerGetClock(TIMER0)/1000000);
		tCapturadorAnterior = tCapturadorActual;
	}


}
