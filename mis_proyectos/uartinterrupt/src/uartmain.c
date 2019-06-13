#include "sapi.h"
#include "uartinterrupt.h"

int main(void){
    boardConfig();
    uartConfig(UART_USB,115200);

    uartCallbackSet(UART_USB,UART_RECEIVE,onRx,NULL);
    uartInterrupt(UART_USB,TRUE);

	while(TRUE){
       sleepUntilNextInterrupt();

	}
return 0;
}
