#include "processcommand.h"
#include "linearsensor.h"
#include "debounce.h"

int main(void) {
	boardConfig();
	configuraUart();
	//configInterruptIRQ();

	printf("Inicia el Firmware...\n");
	delay_t myDelay;
	delayInit(&myDelay, 10);
	fsmPulseInit(&debounce, GPIO6);
	stepperMotorInit(&stepper, 100, GPIO2, GPIO1, GPIO0, GPIO3, GPIO4, GPIO5,
			1.8);
	//0.5 cm por cada pulsos
	linearSensorInit(&ls,0,0,0, 0.5);

	while (TRUE) {
		if (delayRead(&myDelay)) {
			processCommandBufferAux();
		}
		//linearSensorSetPosition(&ls, &stepper);
		fsmPulseUpdate(&debounce);
	}
	return 0;
}
