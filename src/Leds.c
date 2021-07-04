/*=============================================================================
 * Author: pablo <pablomorzan@gmail.com>
 * Date: 2021/06/14
 * Version: 1.0
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/


#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

bool_t  encenderLed(gpioMap_t led){

	gpioWrite(led, ON);

	if(gpioRead(led)){
		return 1;
	} else return 0;

}

bool_t  apagarLeds(){     /* apagar todos los leds */
    gpioWrite( LEDB, OFF );
    gpioWrite( LED1, OFF );
    gpioWrite( LED2, OFF );
    gpioWrite( LED3, OFF );

    if( gpioRead(LEDB) == 0 && gpioRead(LED1) == 0 && gpioRead(LED2) == 0 && gpioRead(LED3) == 0){
    	return 1;
    } else return 0;

}

bool_t leerTecla (gpioMap_t tecla){    /* leer el estado de una tecla.  Devuelve por valor el estado de la tecla pulsada (verdadero) o liberada (falso)*/

	return (!gpioRead(tecla));

}

void activarSecuencia(gpioMap_t * psecuencia){ /* psecuencia apunta a una secuencia de leds o arreglo de gpioMap_t */

}

int main(void){


	gpioMap_t secuencia1[] = {LED1, LED2, LED3, LEDB};
	gpioMap_t secuencia2[] = {LED2, LEDB, LED1, LED3};

	gpioMap_t * psecuencia = secuencia1;

	activarSecuencia(psecuencia);

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Variable de Retardo no bloqueante */
   delay_t delayLed;

   /* Inicializar Retardo no bloqueante con tiempo en milisegundos
      (500ms = 0,5s) */
   delayConfig( &delayLed, 500 );

   int8_t i = 3;
   uint8_t sequence = 0;
   bool_t respuesta = 0;



   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

int8_t tecla = 0;

for (int j=1; j<5; j++){
	tecla += j * leerTecla(35 + j);
}

switch(tecla){

	case 1:
		sequence=1;
		break;
	case 2:
		 delayWrite( &delayLed, 150 );
		 break;
	case 3:
		 delayWrite( &delayLed, 500 );
		 break;
	case 4:
		sequence=0;
		break;
}



      /* delayRead retorna TRUE cuando se cumple el tiempo de retardo */
      if ( delayRead( &delayLed ) ){
         if ( !sequence ){
            i--;
         }
         else{
            i++;
         }
      }


      if ( i < 0 ){
         i = 3;
      }
      if ( i > 3 ){
         i = 0;
      }


      respuesta = encenderLed(42 + i);
      delay(100);
      respuesta = apagarLeds();


   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}
