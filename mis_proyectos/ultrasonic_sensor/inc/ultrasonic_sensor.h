/*=====[Module Name]===========================================================
 * Copyright 2020 Author Luis Mariano Campos <lmarianocampos@gmail.com>
 * All rights reserved.
 * License: license text or at least name and link
         (example: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 1.0.0
 * Creation Date: 2020/06/04
 */

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef _ULTRASONIC_SENSOR_H_
#define _ULTRASONIC_SENSOR_H_

/*=====[Inclusions of public function dependencies]==========================*/

//#include "dependency.h"
//#include <dependency.h>

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

//#define PI 3.14

/*=====[Public function-like macros]=========================================*/

//#define printInt(printer,number) printIntFormat((printer),(number),(DEC_FORMAT))

//#define printlnString(printer,string);   {printString((printer),(string));\
                                          printEnter((printer));}

/*=====[Definitions of public data types]====================================*/

// Data type that renames an elementary data type
//typedef uint8_t bool_t;

// Function pointer data type
//typedef void (*callBackFuncPtr_t)(void *);

// Enumerated data type
typedef enum {
	U_SENSOR__0,
    U_SENSOR_1,
} uSensorMap_t;

typedef enum {
   U_SENSOR_DISABLE,
   U_SENSOR_ENABLE
} uSensorInit_t;

typedef enum{
	 RAISING_EDGE,
	 FALLING_EDGE
 }uSensorEdge_t;

 typedef struct{
	 uint8_t irqChannel;
	 gpioInitLpc4337_t gpioInterrupt;
 }uSensorInterruptIrq_t;
typedef struct {
	uSensorMap_t ultrasonicSensor;	 /*sensor ID */
   uint32_t  signalEchoRisetime;     /*Ticks of echo pulse rise edge */
   uint32_t  signalEchoFallTime;	 /* Ticks of echo pulse falling edge   */
   uint32_t  lastEchoPulseWidth;     /* Echo pulse width in ticks*/
   gpioMap_t inPutSignalEcho;	    /* GPIO Input signal echo*/
   uSensorInit_t enabled;			/*Enable or disable sensor*/
   gpioMap_t outPutSignalTrigger;   /*GPIO Output signal Trigger*/
   //uSensorInterruptIrq_t

} uSensor_t;

/*=====[Prototypes (declarations) of public functions]=======================*/

//bool_t rtcInit( rtc_t* rtc );

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

//void UART0_IRQHandler(void);

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* _ULTRASONIC_SENSOR_H_ */
