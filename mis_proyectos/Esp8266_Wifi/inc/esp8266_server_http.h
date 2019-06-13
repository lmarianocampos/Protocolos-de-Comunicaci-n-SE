#ifndef ESP8266_SERVER_HTTP
#define ESP8266_SERVER_HTTP

#include "sapi.h"
#define UART_ESP8266 UART_232
#define SIZE_RESPONSE_WAIT  256
#define RECONNECTION 	3    //CANTIDAD DE REINTENTOS PARA RECONECTAR ALA RED

typedef struct {
	gpioMap_t pinVcc;
	bool_t isConnectedToNetworkWifi;
	bool_t isOn;
	bool_t isConnectionAT;
	char * ssid;
	char * password;
} esp8266_t;

typedef enum {
	COMMAND_AT, COMMAND_TEST_AT
} comandAT_t;


//esta función inicializa la estructura correspondiente al módulo
void esp8266Init(esp8266_t * espWifi, gpioMap_t pinVcc,
		bool_t isConectedToNetworkWifi, bool_t isOn, bool_t IsConnectionAT,
		char * const ssid, char * const password); //
//esta función enciende el módulo esp8266
void esp8266SetOn(esp8266_t * espWifi);
//esta función apaga el módulo
void esp8266SetOff(esp8266_t * espWifi);
//esta función obtiene el estado de energía del modulo:encendido o apagado. TRUE:Encendido, FALSE:Apagado
bool_t esp8266IsOn(esp8266_t * espWifi);
//esta Función monitorea si se establecío la comunicación entre placa edu-ciaa-nxp y el modulo wifi
//TRUE: Comunicación establecida FALSE:No se establecio la Comunicación
bool_t Esp8266TestAT(esp8266_t * espWifi);
// esta función configura el modo del modulo: ap, sta o ambos
void esp8266SetMode(esp8266_t * espWifi);
//esta función conecta el módulo esp8266 a una red determinada
void esp8266Connect(esp8266_t * espWifi);
//esta función desconecta el módulo esp8266 de una red determinada
void esp8266DisConnect(esp8266_t * espWifi);
// esta función devuele si esta conectada a una red deerminada
bool_t esp8266IsConected(esp8266_t * espWifi);
//esta función envía comandos AT al módulo
void Esp8266sendCommandAT(char *command, comandAT_t test);

#endif
