#include "esp8266_server_http_uart.h"


esp8266_t esp8266Wifi;
char * const networkSsid = "myWifi";
char * const networkPassword = "password";

void esp8266ReadUartUSB(){
	uint8_t rxData;
	bool_t connection,isConnected;
if(uartReadByte( UART_USB, &rxData ))
{

	switch(rxData){
	case 'A':
		esp8266Init(&esp8266Wifi, GPIO0,
			FALSE, FALSE, FALSE,
			networkSsid, networkPassword,WAIT_QUERY);
		break;
	case 'B':
		     connection = esp8266TestAT(&esp8266Wifi);
		     if(connection == TRUE){
		    	 printf("Conexion establecida entre la placa y el Modulo WIFI\n\r");
		     }
		     else{
		    	 printf("NO se establecio la comunicacion entre la placa y el Modulo WIFI\n\r");
		     }
		break;
	case 'C': esp8266SetMode(&esp8266Wifi);
		          break;
	case 'D': esp8266TestATWithFail(&esp8266Wifi);

		          break;
	case 'E': esp8266SetModeWithFail(&esp8266Wifi);

			          break;
	case 'F':esp8266ConnectToAP(&esp8266Wifi);
				break;
	case 'G':esp8266Disconnect(&esp8266Wifi);
	break;
	case 'H':isConnected=esp8266IsConected(&esp8266Wifi);
	 if(isConnected == TRUE){
			    	 printf("El Modulo WIFI no esta conectado a la red local\n\r");
			     }
			     else{
			    	 printf("El Modulo WIFI  esta conectado a la red local\n\r");
			     }
	 	 break;
	case 'I':esp8266ReturnSofAPIP(&esp8266Wifi);
	          break;
	case 'J':esp8266TypeConection(&esp8266Wifi); //AT+ CIPMUX=1
              break;
	case 'K':esp8266OpenPortAndEnableServer(&esp8266Wifi);//AT+CIPSERVER=1,80
             break;
	case 'L':esp8266CheckStatus(&esp8266Wifi);
	break;
	case 'M':esp8266SetOn(&esp8266Wifi);
			break;
	case 'N':esp8266SetOff(&esp8266Wifi);
	break;

	case 'Z':esp8266Restore(&esp8266Wifi);//AT+RESTORE pone al modulo wifi de fabrica
	         break;

    	}
}
}
void esp8266CheckConnections(){
	esp8266CheckConnectionsFSM(&esp8266Wifi);
}

