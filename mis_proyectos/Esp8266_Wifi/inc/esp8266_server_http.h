#ifndef ESP8266_SERVER_HTTP
#define ESP8266_SERVER_HTTP

#include "sapi.h"
#define UART_ESP8266 UART_232
#define SIZE_RESPONSE_WAIT  30
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
	COMMAND_AT, COMMAND_TEST_AT,
	COMMAND_TEST_AT_FAIL,
	FORM
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
bool_t esp8266TestAT(esp8266_t * espWifi);
//función que prueba el envio incorrecto de un comando AT
void esp8266TestATWithFail(esp8266_t *espWifi);
// esta función configura el modo del modulo: ap, sta o ambos
void esp8266SetMode(esp8266_t * espWifi);

void esp8266SetModeWithFail(esp8266_t * espWifi);
//Muestra por pantalla el modo de funcionamiento del módulo WIFI
//void esp8266GetMode(esp8266_t * espWifi);
//esta función conecta el módulo esp8266 a una red determinada
void esp8266ConnectToAP(esp8266_t * espWifi);
//esta función desconecta el módulo esp8266 de una red determinada
void esp8266Disconnect(esp8266_t * espWifi);
// esta función devuele si esta conectada a una red deerminada
bool_t esp8266IsConected(esp8266_t * espWifi);
//esta función establece el tipo de conexión TCP o UDP: Multiple
void esp8266TypeConection(esp8266_t * espWifi);
//esta función esta función abre e puerto http :80 y estable al moculo como servidor
void esp8266OpenPortAndEnableServer(esp8266_t * espWifi);
//Esta Funcion devuelve la ip del modulo WIFI
void esp8266ReturnSofAPIP(esp8266_t * espWifi);
//Es función chekea si hay peticiones de clientes
bool_t esp8266CheckConnections(void);
//est función verifica el status del modulo WIFI
void esp8266CheckStatus(esp8266_t * espWifi);//AT+CIPSTATUS
void esp8266SendData(void);//AT+CIPSEND=0,30
//esta función asigna un id la conexión
void esp8266SendForm(void);
//Esta función establece el modulo WIFI de fabrica
void esp8266Restore(esp8266_t * espWifi);
//esta función envía comandos AT al módulo
void esp8266SendCommandAT(char *command, comandAT_t test);

#endif
