/*=====[Nombre del modulo]=====================================================
 * Copyright 2020 Luis Mariano Campos <lmarianocampos@gmail.com>
 * All rights reserved.
 * Licencia: Texto de la licencia o al menos el nombre y un link
         (ejemplo: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 1.0.0
 * Fecha de creacion: 2020/06/29
 */

/*=====[Inclusion de su propia cabecera]=====================================*/
#include "FreeRTOS.h"
//#include "FreeRTOSConfig.h"
//#include "task.h"
#include "sapi.h"
/*=====[Inclusiones de dependencias de funciones privadas]===================*/
/*=====[Macros de definicion de constantes privadas]=========================*/
/*=====[Macros estilo funcion privadas]======================================*/
/*=====[Definiciones de tipos de datos privados]=============================*/
/*=====[Definiciones de Variables globales publicas externas]================*/
/*=====[Definiciones de Variables globales publicas]=========================*/
/*=====[Definiciones de Variables globales privadas]=========================*/
/*=====[Prototipos de funciones privadas]====================================*/
/*==================[funcion principal]======================================*/
int main(void){
	// ---------- CONFIGURACIONES ------------------------------
		// Inicializar y configurar la plataforma
		boardConfig();
	// ---------- REPETIR POR SIEMPRE --------------------------
	while (TRUE ) {
		// Si cae en este while 1 significa que no pudo iniciar el scheduler
	}
	return 0;
}

/*==================[definiciones de funciones internas]=====================*/
/*==================[definiciones de funciones externas]=====================*/
/*==================[fin del archivo]========================================*/

/* @} Final de la definición del modulo para doxygen */

