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
# include "fsmbutton.h"

int main(){
	 boardConfig();
	 fsmButtonInit();
	  uint8_t i=0;

	  delay_t delayTec1;
	  delay_t delayTec2;
	  delay_t delayTec3;
	  delay_t delayTec4;
/*
 dbn_t vectorTeclas[CANTIDAD_TECLAS]={
		.tec = TEC1,.state = STATE_BUTTON_UP,.delay = delayTec1,
		.tec = TEC2,.state = STATE_BUTTON_UP,.delay = delayTec2,
		.tec = TEC3,.state = STATE_BUTTON_UP,.delay = delayTec3,
		.tec = TEC4,.state = STATE_BUTTON_UP,.delay = delayTec4
	 };*/
      //dbn_t * p_dbn;



	  dbn_t dbn1={.tec = TEC1,.state = STATE_BUTTON_UP,.delay=delayTec1};//si inicalizo así me devuelve error de compilación
	  dbn_t dbn2={.tec = TEC2,.state = STATE_BUTTON_UP,.delay=delayTec2};// así no me devuelve error
      dbn_t dbn3={.tec = TEC3,.state = STATE_BUTTON_UP,.delay=delayTec3};
      dbn_t dbn4={.tec = TEC4,.state = STATE_BUTTON_UP,.delay=delayTec4};
    //p_dbn=&vectorTeclas[0];
	while(TRUE){
        	/*fsmButtonUpdate(&dbn1);
        	fsmButtonUpdate(&dbn2);
        	fsmButtonUpdate(&dbn3);
        	fsmButtonUpdate(&dbn4);/*
        // en caso de hacer uso de un vector
        	/*for(i=0;i<CANTIDAD_TECLAS;i++){
        		fsmButtonUpdate(p_dbn);
                 p_dbn++;
        	}*/


	}


}
