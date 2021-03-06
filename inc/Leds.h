/*=============================================================================
 * Author: pablo <pablomorzan@gmail.com>
 * Date: 2021/06/14
 * Version: 1.0
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __LEDS_H__
#define __LEDS_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>
#include <stddef.h>
#include "sapi.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

#define leerTecla(tecla) !gpioRead(tecla)     //en lugar de leer tecla en la función se hace este #define

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

typedef struct {              // definimos este struct para manejo de los punteros a secuencias
	gpioMap_t *pDesplaza;
	gpioMap_t *pInicio;
	gpioMap_t *pFinal;
}punteroSecuencias;

/*=====[Prototypes (declarations) of public functions]=======================*/

bool_t  encenderLed(gpioMap_t led);

bool_t  apagarLeds();

void activarSecuencia(punteroSecuencias *ptrSeq1);

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __LEDS_H__ */
