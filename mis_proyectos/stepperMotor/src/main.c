//#include "stepmotor.h"
//#include "uartinterr.h"
//#include "menu.h"
#include "processcommand.h"
int main(void) {
	boardConfig();
	configuraUart();

	delay_t myDelay;
	delayInit(&myDelay,10);


	stepperMotorInit(&stepper, 100, GPIO1, GPIO0, GPIO3, GPIO4, GPIO5, 1.8);

	while (TRUE) {
		if(delayRead(&myDelay)){
			processCommandBufferAux();
		}
	}
	return 0;
}
