#include "esp8266_server_http.h"
#include<string.h>

// comandos AT
//Para establecer el modo
char send_AT_MODE[] = "CWMODE?";
char send_AT_SET_MODE[] = "CWMODE=3"; //mode softAp
//para conectarse a una red
char send_AT_QUERY_JOIN_ACCESSPOINT[] = "CWJAP?";
char send_AT_JOIN_ACCESSPOINT[] = { 'C', 'W', 'J', 'A', 'P', '_', 'C', 'U', 'R',
		'=', '"', 'T', 'P', '-', 'L', 'I', 'N', 'K', '"', ',', '"', 'n', 'a',
		'n', 'o', 'r', 'i', 'o', '2', '0', '1', '4', '"', '\0' };
//para desconectarse del AP
char send_AT_DISCONNECT[] = "CWQAP";
//para configurar el tipo de conexion
char send_AT_QUERY_TCP_UDP_CONNECTIONS[] = "CIPMUX?";
char send_AT_TCP_UDP_CONNECTIONS[] = "CIPMUX=1";
//comando que devuele la ip que tiene asignado el modulo
char send_AT_CHECKIP[] = "CIFSR";
//comando que lista las redes wifi
char send_AT_LISTA_ACCESS_POINT[] = "CWLAP";
char send_AT_SET_MODE_With_FAIL[] = "CWMODE'=3";
//comando que cofigura elmodulo como servidor y abre el puerto 80
char send_AT_AS_SERVER_AND_OPEN_PORT[] = "CIPSERVER=1,80";
//comando que devuelve las conexiones
char send_AT_TCP_UDP_CONNECTIONS_STATUS[] = "CIPSTATUS";
//envio el id conection y la cantidad de caracteres
char send_AT_SEND_DATA[]="CIPSEND=0,30";
//este comando restaura los valores del modulo de fabrica
char send_AT_TCP_RESTORE[]="RESTORE";
char send_FORM_A[] ="<h1>TEC1 : PRESIONADA</h1>";
char send_FORM_B[] ="<h1>TEC1 : NO PRESIONADA</h1>";
char send_CONNECTION_CLOSED_0[]="CIPCLOSE=0";
char send_CONNECTION_CLOSED_1[]="CIPCLOSE=1";

//char responseWait[SIZE_RESPONSE_WAIT];
//uint32_t responseWaitSize = SIZE_RESPONSE_WAIT;

void esp8266Init(esp8266_t * espWifi, gpioMap_t pinVcc,
		bool_t isConectedToNetworkWifi, bool_t isOn, bool_t IsConnectionAT,
		char * ssid, char * password) {

	espWifi->pinVcc = pinVcc;
	espWifi->isConnectedToNetworkWifi = isConectedToNetworkWifi;
	espWifi->isOn = isOn;
	espWifi->isConnectionAT = IsConnectionAT;
	espWifi->ssid = ssid; //igualo los punteros. el puntero apunta a un string
	espWifi->password = password;

}
void esp8266SetOn(esp8266_t * espWifi) {

	gpioWrite(espWifi->pinVcc, ON);
	espWifi->isOn = TRUE;

}

void esp8266Setoff(esp8266_t * espWifi) {

	gpioWrite(espWifi->pinVcc, LOW);
	espWifi->isOn = FALSE;

}

bool_t esp8266IsOn(esp8266_t * espWifi) {

	return espWifi->isOn;

}
bool_t esp8266TestAT(esp8266_t * espWifi) {

	bool_t valueResponse;

	esp8266SendCommandAT(NULL, COMMAND_TEST_AT);
	valueResponse = waitForReceiveStringOrTimeoutBlocking( UART_ESP8266,

	"AT\r\r\n\r\nOK\r\n", strlen("AT\r\r\n\r\nOK\r\n"), 5000);
	/*valueResponse = receiveBytesUntilReceiveStringOrTimeoutBlocking(
	 UART_ESP8266,
	 "AT\r\r\n\r\nOK\r\n",12,
	 responseWait, &responseWaitSize,
	 5000
	 );*/
	return valueResponse;
}
void esp8266TestATWithFail(esp8266_t *espWifi) {
	bool_t valueResponse;

	esp8266SendCommandAT(NULL, COMMAND_TEST_AT_FAIL);
	valueResponse = waitForReceiveStringOrTimeoutBlocking( UART_ESP8266,

	"ERROR\r\n", strlen("ERROR\r\n"), 5000);
	if (valueResponse) {
		printf("El Comando AT FALLO\n\r");
	} else {
		printf("El Comando AT NO FALLO\n\r");
	}

}
void esp8266SetMode(esp8266_t * espWifi) {
	bool_t valueResponse;

	esp8266SendCommandAT(send_AT_SET_MODE, COMMAND_AT);
	valueResponse = waitForReceiveStringOrTimeoutBlocking( UART_ESP8266,

	"\r\nOK\r\n", strlen("\r\nOK\r\n"), 5000);
	/*	valueResponse = receiveBytesUntilReceiveStringOrTimeoutBlocking(
	 UART_ESP8266,"\r\r\n\r\nOK\r\n",10, responseWait, &responseWaitSize, 5000);*/

	if (valueResponse) {
		printf("Modo establecido correctamente\n\r");
	} else {
		printf("No se pudo establecer el Modo Intentar nuevamente\n\r");
	}

}

void esp8266SetModeWithFail(esp8266_t * espWifi) {
	bool_t valueResponse;

	esp8266SendCommandAT(send_AT_SET_MODE_With_FAIL, COMMAND_AT);
	valueResponse = waitForReceiveStringOrTimeoutBlocking( UART_ESP8266,

	"ERROR\r\n", strlen("ERROR\r\n"), 5000);
	/*	valueResponse = receiveBytesUntilReceiveStringOrTimeoutBlocking(
	 UART_ESP8266,"\r\r\n\r\nOK\r\n",10, responseWait, &responseWaitSize, 5000);*/

	if (valueResponse) {
		printf("No se pudo establecer el Modo Intentar nuevamente\n\r");
	} else {
		printf("Modo establecido correctamente\n\r");
	}

}
void esp8266ConnectToAP(esp8266_t * espWifi) {
	bool_t valueResponse;

	esp8266SendCommandAT(send_AT_JOIN_ACCESSPOINT, COMMAND_AT);
	valueResponse = waitForReceiveStringOrTimeoutBlocking( UART_ESP8266,

	"WIFI CONNECTED", strlen("WIFI CONNECTED"), 5000);

	if (valueResponse) {
		printf("Se conecto satisfactoriamente\n\r");
	} else {
		printf("No se conecto\n\r");
	}

}
void esp8266Disconnect(esp8266_t * espWifi) {
	bool_t valueResponse;

	esp8266SendCommandAT(send_AT_DISCONNECT, COMMAND_AT);
	valueResponse = waitForReceiveStringOrTimeoutBlocking( UART_ESP8266,

	"WIFI DISCONNECT", strlen("WIFI DISCONNECT"), 8000);
	if (valueResponse) {
		printf("Se desconecto satisfactoriamente\n\r");
	} else {
		printf("No se desconecto\n\r");
	}
}
bool_t esp8266IsConected(esp8266_t * espWifi) {
	bool_t valueResponse;
	esp8266SendCommandAT(send_AT_QUERY_JOIN_ACCESSPOINT, COMMAND_AT);
	valueResponse = waitForReceiveStringOrTimeoutBlocking( UART_ESP8266,

	"No AP", strlen("No AP"), 5000);

	return valueResponse;
}
void esp8266TypeConection(esp8266_t * espWifi) {
	bool_t valueResponse;
	esp8266SendCommandAT(send_AT_TCP_UDP_CONNECTIONS, COMMAND_AT);
	valueResponse = waitForReceiveStringOrTimeoutBlocking( UART_ESP8266,

	"AT+CIPMUX=1\r\r\n\r\nOK\r\n", strlen("AT+CIPMUX=1\r\r\n\r\nOK\r\n"), 5000);
	if (valueResponse) {
		printf("Tipo de Conexion Multiple\n\r");
	} else {
		printf("No se Establecio el tipo de Conexion\n\r");
	}
}
void esp8266OpenPortAndEnableServer(esp8266_t * espWifi) {
	bool_t valueResponse;
	esp8266SendCommandAT(send_AT_AS_SERVER_AND_OPEN_PORT, COMMAND_AT);
	valueResponse = waitForReceiveStringOrTimeoutBlocking( UART_ESP8266,

	"AT+CIPSERVER=1,80\r\r\n\r\nOK\r\n",
			strlen("AT+CIPSERVER=1,80\r\r\n\r\nOK\r\n"), 5000);
	if (valueResponse) {
		printf("Se configuro como Servidor y se abrio el puerto 80\n\r");
	} else {
		printf("No Se configuro como Servidor y se abrio el puerto 80\n\r");
	}

}
void esp8266ReturnSofAPIP(esp8266_t * espWifi) {
	bool_t valueResponse;
	char loadIP[20];
	uint8_t dato;
	uint8_t i;
	uint8_t count = 0;
	esp8266SendCommandAT(send_AT_CHECKIP, COMMAND_AT);
	valueResponse = waitForReceiveStringOrTimeoutBlocking( UART_ESP8266,

	"+CIFSR:STAIP,", strlen("+CIFSR:STAIP,"), 5000);
	if (valueResponse) {
		delay(4);
		for (i = 0; i < 20; i++) {
			if (uartReadByte( UART_ESP8266, &dato)) {
				/* Se reenvía el dato a la UART_USB realizando un puente entre ambas */
				//uartWriteByte( UART_USB, dato );
				loadIP[i] = dato;
				delayInaccurateUs(45);

			}
		}
		printf("IP del Servidor:\n\r");
		for (i = 0; i < 15; i++) {
			if (loadIP[i] == '"') {
				count++;
				i++;
			}
			if (count == 1) {
				uartWriteByte(UART_USB, loadIP[i]);
			}


		}
		printf("\n\r");
	}
	else {
		printf("verificar el envio del comando CIFSR\n\r");
	}
}
bool_t esp8266CheckConnections(){
	bool_t valueResponse;
	uint8_t idConnection;
		valueResponse = waitForReceiveStringOrTimeoutBlocking( UART_ESP8266,

		 "+IPD", strlen("+IPD"), 3000);
		 if (valueResponse) {
			 printf("Vino una solicitud\n\r");
			 idConnection=0;
			 esp8266SendData();
		 }
		else {
		 //printf("No hay Conexiones pendiente\n\r");

		 }
    return valueResponse;
}
void esp8266CheckStatus(esp8266_t * espWifi){
	//bool_t valueResponse;
			esp8266SendCommandAT(send_AT_TCP_UDP_CONNECTIONS_STATUS, COMMAND_AT);

}
void esp8266SendData(){
	bool_t valueResponse;

		esp8266SendCommandAT(send_AT_SEND_DATA, COMMAND_AT);
			valueResponse = waitForReceiveStringOrTimeoutBlocking( UART_ESP8266,

			 "SEND OK", strlen("SEND OK"), 3000);
			if(valueResponse){
				esp8266SendForm();
			}
}
void esp8266SendForm(){
	if(gpioRead(TEC1)){
	esp8266SendCommandAT(send_FORM_B, FORM);

	}
	else{
		esp8266SendCommandAT(send_FORM_A, FORM);
	}
	esp8266SendCommandAT(send_CONNECTION_CLOSED_0, COMMAND_AT);
	esp8266SendCommandAT(send_CONNECTION_CLOSED_1, COMMAND_AT);
}


void esp8266Restore(esp8266_t * espWifi) {
	bool_t valueResponse;
	esp8266SendCommandAT(send_AT_TCP_RESTORE, COMMAND_AT);
	valueResponse = waitForReceiveStringOrTimeoutBlocking( UART_ESP8266,

	 "Ai-Thinker Technology Co. Ltd.", strlen("Ai-Thinker Technology Co. Ltd."), 10000);
	 if (valueResponse) {
	 printf("Se restauro de fabrica satisfactoriamente\n\r");
	 } else {
	 printf("No se restauro de fabrica\n\r");
	 }

}
void esp8266SendCommandAT(char *command, comandAT_t test) {
	uint8_t cr = 0x0D;
	uint8_t le = 0x0A;

	switch (test) {

	case COMMAND_AT:
		uartWriteByte( UART_ESP8266, 'A');
		uartWriteByte( UART_ESP8266, 'T');
		uartWriteByte( UART_ESP8266, '+');
		while (*command != '\0') {
			uartWriteByte( UART_ESP8266, *command);
			command++;
		}
		uartWriteByte( UART_ESP8266, cr);
		uartWriteByte( UART_ESP8266, le);
		break;
	case COMMAND_TEST_AT:
		uartWriteByte( UART_ESP8266, 'A');
		uartWriteByte( UART_ESP8266, 'T');
		uartWriteByte( UART_ESP8266, cr);
		uartWriteByte( UART_ESP8266, le);

		break;
	case COMMAND_TEST_AT_FAIL:
		uartWriteByte( UART_ESP8266, 'A');
		uartWriteByte( UART_ESP8266, 'T');
		uartWriteByte( UART_ESP8266, 'T');
		uartWriteByte( UART_ESP8266, cr);
		uartWriteByte( UART_ESP8266, le);

		break;
	case FORM:
		while (*command != '\0') {
					uartWriteByte( UART_ESP8266, *command);
					command++;
				}
			uartWriteByte( UART_ESP8266, cr);
			uartWriteByte( UART_ESP8266, le);
				break;

	}

}


