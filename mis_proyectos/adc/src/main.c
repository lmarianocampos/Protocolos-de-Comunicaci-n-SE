#include "adc.h"

int main(){
	boardConfig();

	   /* Inicializar UART_USB a 115200 baudios */
	   uartConfig( UART_USB, 115200 );
	   printf("Inicia programa\n");
	   adcConfig( ADC_ENABLE ); /* ADC */
       float muestra=0;
       muestra = adcRead(CH3);
       printf("Muestra=%f",muestra);

       while(TRUE){

       }


}
