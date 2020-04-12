#include "stepmotor.h"
#include "uartinterr.h"
#include "menu.h"
int main(void) {
	boardConfig();
	configuraUart();
	delay_t myDelay;
	delayInit(&myDelay,500);
	stepperMotor_t step;
	stepperMotorInit(&step, 100, GPIO1, GPIO0, GPIO3, GPIO4, GPIO5, 1.8);
	stepperMotorMoveSteps(&step, 15);
	while (TRUE) {
		if(delayRead(&myDelay)){
			menu();
		}
	}
	return 0;
}
