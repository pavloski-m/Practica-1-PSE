/*=============================================================================
 * Author: pablo <pablomorzan@gmail.com>
 * Date: 2021/06/14
 * Version: 1.0
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "Leds.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/
bool_t sequence = 0;
/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/


int main(void){


   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Variable de Retardo no bloqueante */
   delay_t delayLed;

   /* Inicializar Retardo no bloqueante con tiempo en milisegundos
      (500ms = 0,5s) */
   delayConfig( &delayLed, 500 );

   /* Declaración de variables locales */
   int8_t i = 3;
   uint8_t cant = 0;

//----------SECUENCIAS---------------------------------

    gpioMap_t secuencia1[] = {LED1, LED2, LED3, LEDB};
    gpioMap_t secuencia2[] = {LED2, LEDB, LED1, LED3, LEDG};



//----------SELECCIÓN DE SECUENCIAS------------------------------

    cant = sizeof(secuencia1)/sizeof(gpioMap_t);                 // Se calcula cantidad de items de secuencia

    punteroSecuencias ptrSec1 = {.pDesplaza = secuencia1, .pInicio = &secuencia1[0], .pFinal = &secuencia1[cant-1]}; // Se instancia el struct con valores de punteros


    /* ------------- REPETIR POR SIEMPRE ------------- */

    while(1) {


//-----------------LECTURA DE TECLAS Y ACCIÓN DE TECLAS -----------------------
	int8_t tecla = 0;

	for (int j=1; j<5; j++){
		tecla += j * leerTecla(TEC1 + j - 1);
		if (tecla > 0){                                         //Se pone para evitar el error de presionar "TEC1" y "TEC2" juntas y que entienda "TEC3"
			break;
		}
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

	  activarSecuencia(&ptrSec1);

	}

   }


 /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */

    return 0 ;
}


//================================FUNCICONES=================================

bool_t  encenderLed(gpioMap_t led){

	if (led >= 40 || led <= 45){
		gpioWrite(led, ON);

		if(gpioRead(led)){
		  return 1;
	    } else {return 0;}
	}else {return 0;}

}


bool_t  apagarLeds(){     /* apagar todos los leds */

	gpioWrite( LEDB, OFF );
    gpioWrite( LED1, OFF );
    gpioWrite( LED2, OFF );
    gpioWrite( LED3, OFF );

    if( gpioRead(LEDB) == 0 && gpioRead(LED1) == 0 && gpioRead(LED2) == 0 && gpioRead(LED3) == 0){
    	return 1;
    } else {return 0;}

}


void activarSecuencia(punteroSecuencias *ptr_seq1){       /* psecuencia apunta a una secuencia de leds o arreglo de gpioMap_t */


	if ( !sequence ){
	 ptr_seq1->pDesplaza++;
	}
	else{
	 ptr_seq1->pDesplaza--;
	}

	if ( ptr_seq1->pDesplaza < ptr_seq1->pInicio ){
	 ptr_seq1->pDesplaza = ptr_seq1->pFinal;
	}
	if ( ptr_seq1->pDesplaza > ptr_seq1->pFinal ){
	 ptr_seq1->pDesplaza = ptr_seq1->pInicio;
	}

	apagarLeds();
	encenderLed(*(ptr_seq1->pDesplaza));


}


