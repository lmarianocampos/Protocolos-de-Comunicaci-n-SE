# include "sapi.h"
//supongo que una vuelta del eje del motor es necesario 200 pulsos
#define PULSOS_POR_VUELTA  10


int main(void){

	boardConfig( );
	uartConfig(UART_USB,115200);

	gpioConfig(GPIO1,GPIO_OUTPUT);
	uint16_t countPulses=0;
	gpioWrite(GPIO1,FALSE);
    char command;
	while (TRUE){
	if(uartReadByte(UART_USB,&command)){
		if(command=='A')
		countPulses=0;
	}
	if  (countPulses<PULSOS_POR_VUELTA){
        gpioWrite(GPIO1,TRUE);
		delayInaccurateUs(250);
		gpioWrite(GPIO1,FALSE);
		delayInaccurateUs(250);
		countPulses++;

	}


}

return 0;

}
