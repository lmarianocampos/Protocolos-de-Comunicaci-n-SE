 #include "biblioteca.h"

void LED_parpadear(gpioMap_t led, uint16_t periodo){

	uint16_t periodo_auxiliar = 0;

	if(periodo >=100 && periodo <=1000)
	{

		periodo_auxiliar = periodo/2;

			gpioWrite(led,ON);
			delay(periodo_auxiliar);
			gpioWrite(led,OFF);
			delay(periodo_auxiliar);

	}

}

void LED_parpadear_n_veces(gpioMap_t led, uint16_t periodo,uint8_t n_veces)
{    uint16_t periodo_auxiliar =0;
	if(n_veces>= 1 && n_veces<= 10)
	{  periodo_auxiliar = periodo/2;
		while(n_veces>0)
			{
				gpioWrite(led,ON);
				delay(periodo_auxiliar);
				gpioWrite(led,OFF);
				delay(periodo_auxiliar);
				n_veces--;
			}
	}

}

void LED_secuencia_fija(uint16_t periodo){
	delay_t miDelay;
	delayConfig(&miDelay,periodo);
	while(TRUE){
		if(delayRead(&miDelay)) break;

	}
}
 void LED_secuencia_arbitraria(uint16_t periodo, gpioMap_t *psecuen){
gpioMap_t LED;

	LED = (*psecuen);
	gpioWrite ( LED,ON);
	LED_secuencia_fija(periodo);
	gpioWrite(LED,OFF);
	LED_secuencia_fija(periodo);
 }

void LED_secuencia_arbitraria_bis( uint16_t periodo, gpioMap_t *psecuen,uint8_t n_leds){
  gpioMap_t LED;
  uint8_t led=n_leds;
	while(n_leds> 0){
    LED_secuencia_arbitraria(periodo,psecuen + n_leds);
	n_leds--;
	}



}

