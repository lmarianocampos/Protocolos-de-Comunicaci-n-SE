#include "processcommand.h"
#include "linearsensor.h"

int main(void) {
	char c;
	boardConfig();
	configuraUart();
	configInterruptIRQ();

	delay_t myDelay;
	delayInit(&myDelay, 10);

	printf("inicia el Firmware...\n");

	stepperMotorInit(&stepper, 100, GPIO2, GPIO1, GPIO0, GPIO3, GPIO4, GPIO5,
			1.8);
	//0.5 cm por cada pulsos
	linearSensorInit(&ls,0,0,0, 0.5);

	while (TRUE) {
		if (delayRead(&myDelay)) {
			processCommandBufferAux();
		}
		//linearSensorSetPosition(&ls, &stepper);
	}
	return 0;
}
