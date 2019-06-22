/* Copyright 2016, Marcelo Vieytes.
 * Copyright 2017, Pablo Gomez - Agustin Bassi.
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/* Date: 2017-14-11 */

/*
ESP01 (ESP8266) connections:

   +--------------------------------------+
   |  |          +----+                   |
   |  +--+  |    |    |      RX o o VCC   |
   |     |  |    +----+   GPIO0 o o RST   |
   |  +--+  |    +----+   GPIO2 o o CH_PD |
   |  |     |    |    |     GND o o TX    |
   |  +-----+    +----+                   |
   +--------------------------------------+

   VCC ESP8266 <--> +3.3V EDU-CIAA-NXP
   RST ESP8266 <--> (SIN CONEXION)
 CH_PD ESP8266 <--> +3.3V EDU-CIAA-NXP
    TX ESP8266 <--> RX EDU-CIAA-NXP

    RX ESP8266 <--> TX EDU-CIAA-NXP
 GPIO0 ESP8266 <--> (SIN CONEXION)
 GPIO0 ESP8266 <--> (SIN CONEXION)
   GND ESP8266 <--> GND EDU-CIAA-NXP

  AT commands: http://www.pridopia.co.uk/pi-doc/ESP8266ATCommandsSet.pdf
*/

/*==================[inclusions]=============================================*/

#include "sapi.h"
#include "esp8266_server_http_uart.h"
#include <string.h>

/*==================[macros and definitions]=================================*/



/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/




/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/


/*==================[external functions definition]==========================*/

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */


int main(void){
	boardConfig();
uartConfig(UART_USB,115200);
uartConfig(UART_232,115200);

gpioConfig(GPIO0,GPIO_OUTPUT);
delay_t dalayReceiveResponse;
uint8_t dato;

delayConfig(&dalayReceiveResponse, 500);// cada 1 segundo monitoreo si hay solicitud de clientes
while(TRUE){
    esp8266ReadUartUSB();//verifica si hay datos por el puerto UART USB

	if(delayRead(&dalayReceiveResponse)){
		esp8266CheckConnections();
	}


	/* Si recibe un byte de la UART_USB lo guardarlo en la variable dato. */
//if( uartReadByte( UART_USB, &dato ) ){
	         /* Se reenvía el dato a la UART_232 realizando un puente entre ambas */
  //uartWriteByte( UART_232, dato );
	//   }

	/* Si recibe un byte de la UART_232 lo guardarlo en la variable dato. */
	  //  if( uartReadByte( UART_ESP8266, &dato ) ){
	         /* Se reenvía el dato a la UART_USB realizando un puente entre ambas */
	    //   uartWriteByte( UART_USB, dato );
	     //}



}

	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
	      por ningun S.O. */
	   return 0 ;
}


