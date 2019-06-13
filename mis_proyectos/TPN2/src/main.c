/* Copyright 2016, Eric Pernia.
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

/*
 * Date: 2016-04-26
 */

/*==================[inclusions]=============================================*/

#include "sapi.h"       // <= sAPI header
#include "biblioteca.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();
   uint8_t opcion = 3;
   gpioMap_t secuencia []= {LEDB,LED1,LED2,LED3};
   gpioMap_t secuencia_bis [] ={LEDB,LED1,LED2,LED3,LEDB,LED1,LED2,LED3,LEDB,LED1};
   gpioMap_t* psecuencia = secuencia;
   /* ------------- REPETIR POR SIEMPRE ------------- */

   gpioWrite(LEDG,OFF);
   delay(100);
   while(1)
   {
	   switch(opcion){
	   case 1 :
		   	   	  LED_parpadear(LED1,450);
				  break;
	   case 2:
		   	   	  LED_parpadear_n_veces(LEDG, 400, 4);
                  opcion=0;
		          break;
	   case 3:  gpioWrite(LEDB,ON);
	            LED_secuencia_fija(100);
	            gpioWrite(LEDB,OFF);
	            LED_secuencia_fija(100);

	            gpioWrite(LED1,ON);
				LED_secuencia_fija(500);
				gpioWrite(LED1,OFF);
				LED_secuencia_fija(500);

				gpioWrite(LED2,ON);
				LED_secuencia_fija(150);
				gpioWrite(LED2,OFF);
				LED_secuencia_fija(150);

				gpioWrite(LED3,ON);
				LED_secuencia_fija(250);
				gpioWrite(LED3,OFF);
				LED_secuencia_fija(250);
	   		      break;
	   case 4:
		       LED_secuencia_arbitraria(250,psecuencia);
		       LED_secuencia_arbitraria(300,psecuencia+1);
		       LED_secuencia_arbitraria(350,psecuencia+2);
		       LED_secuencia_arbitraria(400,psecuencia+3);
	   		      break;
	   case 5:
		       LED_secuencia_arbitraria_bis(250,psecuencia,3);
	   		      break;


	   }
   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/*==================[end of file]============================================*/
