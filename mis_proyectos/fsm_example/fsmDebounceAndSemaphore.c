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

typedef enum{
   BUTTON_UP,
   BUTTON_DOWN,
   BUTTON_FALLING,
   BUTTON_RISING
} fsmButtonState_t;

void fsmButtonError( void );
void fsmButtonInit( void );
void fsmButtonUpdate( gpioMap_t tecla );
void buttonPressed( void );
void buttonReleased( void );

fsmButtonState_t fsmButtonState;


int main(void){     
   boardConfig();
   fsmButtonInit();
   fsmSemaphoreInit();
   while(TRUE){
      fsmButtonUpdate(TEC1);
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




void buttonPressed( void )
{
   static uint8_t cont = 0;
   gpioWrite(LEDR, OFF);
   gpioWrite(LEDG, OFF);
   gpioWrite(LEDB, ON);
   if(cont>5){
      gpioWrite(LEDR, OFF);
      gpioWrite(LEDG, ON);
      gpioWrite(LEDB, OFF);
   }
   cont++;
}

void buttonReleased( void )
{
   static uint8_t cont = 0;
   gpioWrite(LEDR, ON);
   gpioWrite(LEDG, OFF);
   gpioWrite(LEDB, OFF);
   if(cont>10){
      gpioWrite(LEDR, OFF);
      gpioWrite(LEDG, OFF);
      gpioWrite(LEDB, OFF);
   }
   cont++;
}

void fsmButtonError( void )
{
   fsmButtonState = BUTTON_UP;
}

void fsmButtonInit( void )
{
   fsmButtonState = BUTTON_UP;  // Set initial state
}

// FSM Update Sate Function
void fsmButtonUpdate( gpioMap_t tecla )
{
   static bool_t flagFalling = FALSE;
   static bool_t flagRising = FALSE;
   
   static uint8_t contFalling = 0;
   static uint8_t contRising = 0;

   switch( fsmButtonState ){

      case BUTTON_UP: 
         /* CHECK TRANSITION CONDITIONS */
         if( !gpioRead(tecla) ){
            fsmButtonState = BUTTON_FALLING;
         }
      break;

      case BUTTON_DOWN:
         /* CHECK TRANSITION CONDITIONS */
         if( gpioRead(tecla) ){
            fsmButtonState = BUTTON_RISING;
         }
      break;

      case BUTTON_FALLING:      
         /* ENTRY */
         if( flagFalling == FALSE ){
            flagFalling = TRUE;
         }      
         /* CHECK TRANSITION CONDITIONS */
         if( contFalling >= 40 ){
            if( !gpioRead(tecla) ){
               fsmButtonState = BUTTON_DOWN;
               buttonPressed();
            } else{
               fsmButtonState = BUTTON_UP;
            }
            contFalling = 0;
         }
         contFalling++;
         /* LEAVE */
         if( fsmButtonState != BUTTON_FALLING ){
            flagFalling = FALSE;
         }
      break;

      case BUTTON_RISING:      
         /* ENTRY */
         if( flagRising == FALSE ){
            flagRising = TRUE;
         }    
         /* CHECK TRANSITION CONDITIONS */
         
         if( contRising >= 40 ){
            if( gpioRead(tecla) ){
               fsmButtonState = BUTTON_UP;
               buttonReleased();
            } else{
               fsmButtonState = BUTTON_DOWN;
            }
            contRising = 0;
         }
         contRising++;
         
         /* LEAVE */
         if( fsmButtonState != BUTTON_RISING ){
            flagRising = FALSE;
         }
      break;

      default:
         fsmButtonError();
      break;
   }
}
