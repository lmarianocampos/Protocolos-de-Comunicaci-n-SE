#include "processcommand.h"

void processComandBufferAux(void) {

	if (buffer == BUFFER_FULL) {
		char bufferAux[SIZE_TOTAL_BUFFER];
		for (uint8_t i = 0; bufferRx[i] != '\0'; i++) {
			bufferAux[i] = bufferRx[i];
			buffer = BUFFER_EMPTY;
		}
		switch (*bufferAux) {
		case 'M':
			switch (*bufferAux + 1) {
			case 'E': // habilitar el motor.
				break;
			case 'D': //deshabilitar.
				break;
			case 'M': //establece los micropasos.
				break;
			case 'T': //establece el sentido de dirección horario y antihorario.
				break;
			case 'S': //establece la cantidad de pasos.
				break;
			case 'A': // establece el ángulo de giro.
				break;
			case 'F': //establece la cantidad de vueltas que debe realizar el eje del motor.
				break;
			default: // llamar a la función Error1();
				break;
			}
			break;
		default: // llamar a la función Error2()
			break;
		}
	}
}
