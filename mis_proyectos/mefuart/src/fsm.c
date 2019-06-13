/* Copyright 2018, Eric Pernia.
 * All rights reserved.
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

#include "fsm.h"
#include "gpio.h"
#include "adc.h"
#include "imprimir.h"

#define DOSCIENTOSMS   4

void fsmconvertirDecimalCaracter(adc_t * );
  boton_t tec1 = {TEC1,"TEC1:\t","Released\n\r",TRUE};
  boton_t tec2 = {TEC2,"TEC2:\t","Released\n\r",TRUE};
  boton_t tec3 = {TEC3,"TEC3:\t","Released\n\r",TRUE};
  boton_t tec4 = {TEC4,"TEC4:\t","Released\n\r",TRUE};
  adc_t adc1 ={0};

// Variable that hold the current state

uint8_t message[]= "*******Bienvenidos al Menú Principal*****\n\r";
uint8_t menu1[]=" Prisione 1 para ver el Estado de las Teclas\n\r";
uint8_t menu2[]=" Presione 2 para ver valores del ADC\n\r ";
fsmState_t fsmState;
// FSM Error Handler Function
void fsmError( void )
{
   // Error handler, example, restart FSM:
    //fsmState = STATE_DEFAULT;
    fsmInit();
}

// FSM Initialize Function
void fsmInit( void )
{
   // Example:
   // boardInit();          // Initialize hardwaree
   boardConfig();
   uartConfig(UART_USB,115200);
   uartWriteByte(UART_USB,27);
   uartWriteString(UART_USB,"[2J");
   uartWriteByte(UART_USB,27);
   uartWriteString(UART_USB,"[H");
   delay(1);
   uartWriteString(UART_USB,message);
   uartWriteString(UART_USB,menu1);
   uartWriteString(UART_USB,menu2);
}

// FSM Update Sate Function
void fsmUpdate( fsmState_t fsmState )
{

   switch( fsmState ){

      case STATE_GPIO:
         botonPresionado(&tec1);
         botonPresionado(&tec2);
         botonPresionado(&tec3);
         botonPresionado(&tec4);

      break;
      case STATE_ADC:
    	  lecturaDatos(&adc1);
    	  fsmconvertirDecimalCaracter(&adc1);

      break;

      case STATE_DEFAULT:
    	  break;
      default:
         fsmError();
      break;
   }
}

void fsmImprimir(void){
	static uint8_t time=0;
	if(time == DOSCIENTOSMS){
		if(fsmState == STATE_GPIO){
		imprimirClearScreem();
		imprimirTec(&tec1);
		imprimirTec(&tec2);
		imprimirTec(&tec3);
		imprimirTec(&tec4);
		}
		if(fsmState==STATE_ADC){
		imprimirClearScreem();
		imprimirAdc(&adc1);
		}
		time=0;
	}
	else time++;


}
void fsmconvertirDecimalCaracter(adc_t * adcCh1){
	uint16_t num=0;
	uint8_t i=0;
	 char c=0;
	 char temp;
	 num = adcCh1->valor;
	 //aux = num;
	 while(num>0){
		 c = (num%10)+48;
		 adcCh1->stringValor[i] = c;
		 num = num/10;
		 i++;
	 }
	 switch(i){
	 case 0: 	 adcCh1->stringValor[i] = '0';
	 	 	 	 adcCh1->stringValor[i+1] = '0';
	 	 	 	 adcCh1->stringValor[i+2] = '0';
	 	 	 	adcCh1->stringValor[i+3] = '0';
	 	 	 	break;
	 case 1:	 adcCh1->stringValor[i] = '0';
	 	 	 	 adcCh1->stringValor[i+1] = '0';
	 	 	 	 adcCh1->stringValor[i+2] = '0';
	 	 	 	 break;
	 case 2:	 adcCh1->stringValor[i]='0';
	 	 	 	 adcCh1->stringValor[i+1]='0';
	 	 	 	 break;
	 case 3:	 adcCh1->stringValor[i]='0';
	 	 	 	 break;
	 }

    	 for (i=0;i<=1;i++){
    		 	 temp=adcCh1->stringValor[i];
    		 	 adcCh1->stringValor[i]=adcCh1->stringValor[3-i];
    		 	 adcCh1->stringValor[3-i]=temp;
    	 }
		 for(i=0;i<4;i++){
			 adcCh1->printValor[i] = adcCh1->stringValor[i];
		 }

}
