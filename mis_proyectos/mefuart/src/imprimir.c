#include "imprimir.h"


void imprimirTec(boton_t * tec){
	uartWriteString(UART_USB,tec->printTecla);
	uartWriteString(UART_USB,tec->printState);

}
void imprimirAdc(adc_t* adc){
	uartWriteString(UART_USB,adc->printValor);

}
void imprimirClearScreem(){
	uartWriteByte(UART_USB,27);
	uartWriteString(UART_USB,"[2J");
	uartWriteByte(UART_USB,27);
	uartWriteString(UART_USB,"[H");
	delay(1);
}
