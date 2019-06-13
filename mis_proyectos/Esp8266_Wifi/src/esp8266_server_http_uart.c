#include "esp8266_server_http_uart.h"


esp8266_t esp8266Wifi;
char * const networkSsid = "myWifi";
char * const networkPassword = "password";

void esp8266ReadUartUSB(){
	uint8_t rxData;
	bool_t connection;

	uartReadByte( UART_USB, &rxData );

	switch(rxData){
	case 'A':
		esp8266Init(&esp8266Wifi, GPIO0,
			FALSE, FALSE, FALSE,
			networkSsid, networkPassword);
		break;
	case 'B':
		     connection = Esp8266TestAT(&esp8266Wifi);
		     if(connection == TRUE){
		    	 printf("Conexión establecida con el Modulo WIFI\n\r");
		     }
		     else{
		    	 printf("NO se establecío la comunicación con el Modulo WIFI\n\r");
		     }
		break;
	}
}
