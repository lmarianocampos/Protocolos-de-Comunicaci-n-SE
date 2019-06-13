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
 
#include "sapi.h"

typedef enum{
   ROJO,
   ROJO_AMARILLO,
   VERDE,
   AMARILLO
} fsmSemaphoreState_t;

void fsmSemaphoreInit( void );
void fsmSemaphoreUpdate( void );

fsmSemaphoreState_t fsmSemaphoreState;

int main(void){     
   boardConfig();
   fsmSemaphoreInit();
   while(TRUE){
      fsmSemaphoreUpdate();
      delay(1);
   }
   return 0;
}


void fsmSemaphoreInit( void )
{
   fsmSemaphoreState = ROJO;
}

void fsmSemaphoreUpdate( void )
{
   static uint16_t contSemaphore = 0;
   
   switch( fsmSemaphoreState ){
   
      case ROJO:
         gpioWrite( LED1, ON );
         gpioWrite( LED2, OFF );
         gpioWrite( LED3, OFF );
         if( contSemaphore >= 1000 ){
            fsmSemaphoreState = ROJO_AMARILLO;
            contSemaphore = 0;
         }
         contSemaphore++;
      break;
         
      case ROJO_AMARILLO:
         gpioWrite( LED1, ON );
         gpioWrite( LED2, ON );
         gpioWrite( LED3, OFF );
         if( contSemaphore >= 500 ){
            fsmSemaphoreState = VERDE;
            contSemaphore = 0;
         }
         contSemaphore++;
      break;
         
      case VERDE:
         gpioWrite( LED1, OFF );
         gpioWrite( LED2, OFF );
         gpioWrite( LED3, ON );
         if( contSemaphore >= 1200 ){
            fsmSemaphoreState = AMARILLO;
            contSemaphore = 0;
         }
         contSemaphore++;
      break;
         
      case AMARILLO:
         gpioWrite( LED1, OFF );
         gpioWrite( LED2, ON );
         gpioWrite( LED3, OFF );
         if( contSemaphore >= 500 ){
            fsmSemaphoreState = ROJO;
            contSemaphore = 0;
         }
         contSemaphore++;
      break;
         
      default:
         fsmSemaphoreState = ROJO;
      break;
   }
}
