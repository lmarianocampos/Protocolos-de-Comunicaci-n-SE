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
#include "fsmbutton.h"


// FSM Error Handler Function
void fsmButtonError( void )
{
   // Error handler, example, restart FSM:
    fsmButtonState = STATE_BUTTON_UP;
}

// FSM Initialize Function
void fsmButtonInit( void )
{
   // Example:
   // boardInit();          // Initialize hardwaree
   fsmButtonState = STATE_BUTTON_UP;   // Set initial state
}

// FSM Update Sate Function
void fsmButtonUpdate( dbn_t* debounce )
{ static bool_t flagFalling = FALSE;
  static bool_t flagRising = FALSE;

   switch( debounce->state ){

      case STATE_BUTTON_UP:
         if(!gpioRead(debounce->tec)){
        	 fsmButtonState=STATE_BUTTON_FALLING;
         }
      break;

      case STATE_BUTTON_DOWN:
    	  if(gpioRead(debounce->state)){
    		  fsmButtonState=STATE_BUTTON_RISING;
    	  }
      break;
      case STATE_BUTTON_FALLING:
        if (flagFalling==FALSE){
    	  delayConfig(&(debounce->delay),40);
    	  flagFalling = TRUE;
        }
               if(delayRead(&(debounce->delay))){// se cumple los 40ms
            	   if(!gpioRead(debounce->tec)){
            		   fsmButtonState = STATE_BUTTON_DOWN;
            	   }
            	   else{
            		   fsmButtonState = STATE_BUTTON_UP;
            	   }
            	   flagFalling = FALSE;
               }
            break;
      case STATE_BUTTON_RISING:
    	  if(flagRising==FALSE){
    		  delayConfig(&(debounce->delay),40);
    		  flagRising=TRUE;
    	  }
               if(delayRead(&(debounce->delay))){
            	   if(gpioRead(debounce->tec)){
            		   fsmButtonState = STATE_BUTTON_UP;
            	   }
            	   else{
            		   fsmButtonState = STATE_BUTTON_DOWN;

            	   }
            	   flagRising=TRUE;
               }
            break;
      default:
         fsmButtonError();
      break;
   }
}
