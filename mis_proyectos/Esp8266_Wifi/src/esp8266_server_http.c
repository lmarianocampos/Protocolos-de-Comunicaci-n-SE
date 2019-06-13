#include "esp8266_server_http.h"



// comandos AT
char send_AT[] = "AT";
char send_AT_JOIN_ACCESSPOINT[] = { 'C', 'W', 'J', 'A', 'P', '?' };
char send_AT_CHECKIP[] = { 'C', 'I', 'F', 'S', 'R' };
char send_AT_LISTA_ACCESS_POINT[] = { 'C', 'W', 'L', 'A', 'P' };
char send_AT_MODE[] = { 'C', 'W', 'M', 'O', 'D', 'E', '?' };
char send_AT_TCP_UDP_CONNECTIONS[] = { 'C', 'I', 'P', 'M', 'U', 'X', '?' };
char send_AT_TCP_UDP_CONNECTIONS_STATUS[] = { 'C', 'I', 'P', 'S', 'T', 'A', 'T',
		'U', 'S' };
char responseWait[SIZE_RESPONSE_WAIT];
uint32_t responseWaitSize = SIZE_RESPONSE_WAIT;


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

bool_t esp8266IsOn(esp8266_t * espWifi){

		 return espWifi->isOn;

}
bool_t Esp8266TestAT(esp8266_t * espWifi){

	bool_t valueResponse;

	Esp8266sendCommandAT(NULL, COMMAND_TEST_AT);
	valueResponse = receiveBytesUntilReceiveStringOrTimeoutBlocking(
	               UART_ESP8266,
	               "OK",2,
	               responseWait, &responseWaitSize,
	               10000
	            );
	return valueResponse;
}

void Esp8266sendCommandAT(char *command, comandAT_t test) {
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

		}

}
//void esp8266SetMode();
