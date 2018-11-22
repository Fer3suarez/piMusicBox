/*
 *  File name	: piMusicBox_1.c
 *  Authors		: Fernando Ruano Crespo y Fernando Suarez Menendez
 *  Description	: Programa principal
 */

/* Includes */

#include "piMusicBox_1.h"
#include <string.h>
#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "tmr.h"


//Las distintas melodias, con sus arrays de tiempos y de frecuencias


int frecuenciaDespacito[160] = {0,1175,1109,988,740,740,740,740,740,740,988,988,988,988,880,988,784,0,784,784,784,784,784,988,988,988,988,1109,1175,880,0,880,880,880,880,880,1175,1175,1175,1175,1318,1318,1109,0,1175,1109,988,740,740,740,740,740,740,988,988,988,988,880,988,784,0,784,784,784,784,784,988,988,988,988,1109,1175,880,0,880,880,880,880,880,1175,1175,1175,1175,1318,1318,1109,0,1480,1318,1480,1318,1480,1318,1480,1318,1480,1318,1480,1568,1568,1175,0,1175,1568,1568,1568,0,1568,1760,1568,1480,0,1480,1480,1480,1760,1568,1480,1318,659,659,659,659,659,659,659,659,554,587,1480,1318,1480,1318,1480,1318,1480,1318,1480,1318,1480,1568,1568,1175,0,1175,1568,1568,1568,1568,1760,1568,1480,0,1480,1480,1480,1760,1568,1480,1318};
int tiempoDespacito[160] = {1200,600,600,300,300,150,150,150,150,150,150,150,150,300,150,300,343,112,150,150,150,150,150,150,150,150,300,150,300,300,150,150,150,150,150,150,150,150,150,300,150,300,800,300,600,600,300,300,150,150,150,150,150,150,150,150,300,150,300,343,112,150,150,150,150,150,150,150,150,300,150,300,300,150,150,150,150,150,150,150,150,150,300,150,300,450,1800,150,150,150,150,300,150,300,150,150,150,300,150,300,450,450,300,150,150,225,75,150,150,300,450,800,150,150,300,150,150,300,450,150,150,150,150,150,150,150,150,300,300,150,150,150,150,150,150,450,150,150,150,300,150,300,450,450,300,150,150,150,300,150,300,450,800,150,150,300,150,150,300,450};
int frecuenciaGOT[518] = {1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,1175,0,1397,0,932,0,1244,0,1175,0,1397,0,932,0,1244,0,1175,0,1046,0,831,0,698,0,523,0,349,0,784,0,523,0,523,0,587,0,622,0,698,0,784,0,523,0,622,0,698,0,784,0,523,0,622,0,698,0,587,0,698,0,466,0,622,0,587,0,698,0,466,0,622,0,587,0,523,0,523,0,587,0,622,0,698,0,784,0,523,0,622,0,698,0,784,0,523,0,622,0,698,0,587,0,698,0,466,0,622,0,587,0,698,0,466,0,622,0,587,0,523,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1175,0,587,0,622,0,587,0,523,0,587,0,784,0,880,0,932,0,1046,0,1175,0,0,1397,0,0,932,0,0,1244,0,0,1175,0,0,1397,0,0,932,0,0,1244,0,0,1175,0,0,1046,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1568,0,0,1046,0,0,1244,0,0,1397,0,0,1175,0,880,0,784,0,932,0,1244,0,0,1397,0,0,932,0,0,1175,0,0,1244,0,0,1175,0,0,932,0,0,1046,0,0,2093,0,622,0,831,0,932,0,1046,0,622,0,831,0,1046,0,0,1865,0,622,0,784,0,831,0,932,0,622,0,784,0,932,0,0,1661,0,523,0,698,0,784,0,831,0,523,0,698,0,831,0,0,1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,0,0,1661,0,1046,0,1175,0,1244,0,831,0,1175,0,1244,0,0,0,0,2489,0,0,0,0,2794,0,0,0,0,3136,0,0,2093,0,622,0,831,0,932,0,1046,0,622,0,831,0,1046,0,0,1865,0,622,0,784,0,831,0,932,0,622,0,784,0,932,0,0,1661,0,523,0,698,0,784,0,831,0,523,0,698,0,831,0,0,1568,0,1046,0,1244,0,1397,0,1568,0,1046,0,1244,0,1397,0,0,0,1661,0,1046,0,1175,0,1244,0,831,0,1175,0,1244,0,0,0,0,2489,0,1397,0,0,0,2350,0,0,0,2489,0,0,0,2350,0,0,0,0,2093,0,392,0,415,0,466,0,523,0,392,0,415,0,466,0,523,0,392,0,415,0,466,0,2093,0,1568,0,1661,0,1865,0,2093,0,1568,0,1661,0,1865,0,2093,0,1568,0,1661,0,1865};
int tiempoGOT[518] = {900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1400,1400,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,116,267,28,267,28,267,28,900,89,900,89,1400,89,69,7,69,7,69,7,69,7,900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1800,1800,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,2400,69,7,69,7,69,7,69,7,900,89,900,89,133,13,133,13,600,59,600,59,133,13,133,13,1800,1800,900,89,900,89,133,13,133,13,600,59,900,89,133,13,133,13,1200,2400,3600,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,600,59,600,133,13,150,133,13,150,1200,400,69,7,69,7,69,7,69,7,267,28,400,45,133,13,267,28,267,28,267,28,300,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,900,89,900,133,13,150,133,13,150,1200,1800,3600,900,89,900,900,89,900,133,13,150,133,13,150,600,59,600,600,59,600,133,13,150,133,13,150,1200,400,267,28,1200,400,133,13,133,13,150,900,89,900,900,89,900,600,59,600,267,28,300,600,59,600,267,28,300,1200,2400,3600,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,133,13,267,28,267,28,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,150,600,59,133,13,133,13,267,28,267,28,133,13,133,13,150,150,150,900,89,900,900,900,900,89,900,900,900,1200,2400,3600,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,150,150,600,59,133,13,133,13,267,28,267,28,133,13,133,13,150,150,150,600,212,133,13,150,150,267,28,300,300,400,45,450,450,133,13,150,150,150,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,267,28,267,28,133,13,2400,116,267,28,267,28,133,13,133,13,267,28,267,28,133,13,133,13,267,28,267,28,133,13,2400};
int frecuenciaTetris[55] = {1319,988,1047,1175,1047,988,880,880,1047,1319,1175,1047,988,988,1047,1175,1319,1047,880,880,0,1175,1397,1760,1568,1397,1319,1047,1319,1175,1047,988,988,1047,1175,1319,1047,880,880,0,659,523,587,494,523,440,415,659,523,587,494,523,659,880,831};
int tiempoTetris[55] = {450,225,225,450,225,225,450,225,225,450,225,225,450,225,225,450,450,450,450,450,675,450,225,450,225,225,675,225,450,225,225,450,225,225,450,450,450,450,450,450,900,900,900,900,900,900,1800,900,900,900,900,450,450,900,1800};
int frecuenciaStarwars[59] = {523,0,523,0,523,0,698,0,1046,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,784,0,1397,0,523,0,1760,0,0,880,0,1760,0,0,784,0,523,0,0,523,0,0,523,0};
int tiempoStarwars[59] = {134,134,134,134,134,134,536,134,536,134,134,134,134,134,134,536,134,402,134,134,429,357,134,134,134,134,536,134,402,134,134,429,357,134,134,134,134,536,134,402,134,134,429,357,134,134,134,429,357,1071,268,67,67,268,67,67,67,67,67};


//Variables globales
//Variables de control de flags

volatile int flags = 0;
volatile int flagsinterrupt = 1;

/*
 * Funcion:  delay_until
 * --------------------
 * Anade un tiempo de espera al temporizador
 *
 * el tiempo en milisegundos
 *
 */


void delay_until (unsigned int next) {
	unsigned int now = millis();

	if (next > now) {
		delay (next - now);
    }
}

//------------------------------------------------------------------
// COLECCION DE FUNCIONES DE LA MAQUINA DE ESTADOS DE REPRODUCCION
//------------------------------------------------------------------


// FUNCIONES DE PASO O DE COMPROBACI�N --



/*
 * Function:  compruebaPlayerStart
 * --------------------
 * Informa de la activacion del flag FLAG_PLAYER_START
 *
 *  this: puntero a la maquina de estados en la que se comprueba el flag
 *
 *  returns: devuelve 1 si se ha activado FLAG_PLAYER_START o 0 en caso contrario
 */

int compruebaPlayerStart (fsm_t* this) { //Comprueba si el FLAG_PLAYER_START está activo
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_START);
	piUnlock (FLAGS_KEY);

	return result;
}

/*
 * Function:  compruebaNotaNueva
 * --------------------
 * Informa de la activacion del flag FLAG_PLAYER_END siempre que el numero de lanota actual sea menor que el numero
 * total de notas de la melodia
 *
 *  this: puntero a la maquina de estados en la que se comprueba el flag
 *
 *  returns: devuelve 1 si se ha activado FLAG_PLAYER_END o 0 en caso contrario
 */


int compruebaNotaNueva (fsm_t* this) {//Comprueba si el FLAG_PLAYER_END está activo, si todavia quedan más notas
	TipoPlayer *p_player;
	p_player = (TipoPlayer*)(this->user_data);
	int result;
	if(p_player->posicion_nota_actual<p_player->melodia->num_notas){
		piLock (FLAGS_KEY);
		result = (flags & FLAG_PLAYER_END);
		piUnlock (FLAGS_KEY);
	}else{
		result= 0;
	}
	return result;
}

/*
 * Function:  compruebaNotaTiemout
 * --------------------
 * Informa de la activacion del flag FLAG_NOTA_TIEMOUT
 *
 *  this: puntero a la maquina de estados en la que se comprueba el flag
 *
 *  returns: devuelve 1 si se ha activado FLAG_NOTA_TIEMOUT o 0 en caso contrario
 */

int compruebaNotaTimeout (fsm_t* this) {//Comprueba si el FLAG_NOTA_TIMEOUT está activo
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_NOTA_TIMEOUT);
	piUnlock (FLAGS_KEY);

	return result;
}

/*
 * Function:  compruebaFinalMelodia
 * --------------------
 * Informa de la activacion del flag FLAG_PLAYER_END siempre que el numero de la nota actual sea igual al numero total de notas
 *
 *  this: puntero a la maquina de estados en la que se comprueba el flag
 *
 *  returns: devuelve 1 si se ha activado FLAG_PLAYER_END o 0 en caso contrario
 */


int compruebaFinalMelodia (fsm_t* this) {//Comprueba si el FLAG_PLAYER_END está activo, si ya no quedan más notas
	TipoPlayer *p_player;
	p_player = (TipoPlayer*)(this->user_data);
	int result;
	if(p_player->posicion_nota_actual==p_player->melodia->num_notas){
	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_END);
	piUnlock (FLAGS_KEY);
	}else{
		result=0;
	}
	return result;
}

/*
 * Function:  compruebaPlayerSopt
 * --------------------
 * Informa de la activacion del flag FLAG_PLAYER_STOP
 *
 *  this: puntero a la maquina de estados en la que se comprueba el flag
 *
 *  returns: devuelve 1 si se ha activado FLAG_PLAYER_STOP o 0 en caso contrario
 */

int compruebaPlayerStop (fsm_t* this) {//Comprueba si el FLAG_PLAYER_STOP está activo
	int result;

	piLock (FLAGS_KEY);
	result = (flags & FLAG_PLAYER_STOP);
	piUnlock (FLAGS_KEY);

	return result;
}

//------------------------------
 // FUNCIONES DE INICIALIZACION
 //-----------------------------

 /*
  * Function:  InicializaMelodia
  * --------------------
  * Metodo de inicializacion de la melodia pasada como parametro
  *
  *  this: puntero a la maquina de estados en la que se comprueba el flag
  *
  *  returns: devuelve el numero total de la melodia pasada como parametro
  */

int InicializaMelodia (TipoMelodia *melodia, char *nombre, int *array_frecuencias, int *array_duraciones, int num_notas) { 
	strcpy(melodia->nombre,nombre); 
	int i;
	int j;
	for(i=0;i<num_notas;i++){
		melodia -> frecuencias[i] = array_frecuencias[i];
	}
	for(j=0;j<num_notas;j++){
		melodia->duraciones[j]=array_duraciones[j];
	}
	melodia->num_notas=num_notas;
	return melodia->num_notas;
}

/*
 * Function:  InicializaPlayer
 * --------------------
 * Metodo de inicializacion del player
 *
 *  this: puntero a la maquina de estados en la que se comprueba el flag
 *
 */

void InicializaPlayer(fsm_t* this){ //Inicializa la nota, frecuencia y duración
	TipoPlayer *p_player;
	p_player = (TipoPlayer*)(this->user_data);

	piLock (FLAGS_KEY);
		flags &= ~FLAG_PLAYER_START;
		flags &= ~FLAG_PLAYER_STOP;
		flags &= ~FLAG_PLAYER_END;
		flags &= ~FLAG_NOTA_TIMEOUT; //Desactiva los flags
		flags |= FLAG_NOTA_TIMEOUT; //Activa el FLAG_NOTA_TIMEOUT
	piUnlock (FLAGS_KEY);

	p_player->posicion_nota_actual = -1; //Al incrementarse, la primera nota que se toca es la 0(la primera posición del array)
	p_player->frecuencia_nota_actual=p_player->melodia->frecuencias[0];
	p_player->duracion_nota_actual=p_player->melodia->duraciones[0];
	softToneWrite(18, p_player->frecuencia_nota_actual);

	piLock (STD_IO_BUFFER_KEY);
		printf("[PLAYER][INICIALIZA PLAYER][NOTA %d][FREC %d][DURA %d]\n", p_player->posicion_nota_actual+1,p_player->frecuencia_nota_actual,p_player->duracion_nota_actual);
	piUnlock (STD_IO_BUFFER_KEY);
}

// FUNCIONES DE REPRODUCCION

 /*
     * Function:  ActualizaPlayer
     * --------------------
     * Actualiza las notas del player(sumando una posicion en tiempo y frecuencias)
     *
     *  fsm: puntero a la maquina de estados
     *
     */

void ActualizaPlayer(fsm_t* this){ //Va actualizando las notas, sumando 1, y pasando a la siguiente
	TipoPlayer *p_player;
	p_player = (TipoPlayer*)(this->user_data);

	piLock (FLAGS_KEY);
		flags &= ~FLAG_PLAYER_START;
		flags &= ~FLAG_PLAYER_STOP;
		flags &= ~FLAG_PLAYER_END; //Desactiva los flags
		flags &= ~FLAG_NOTA_TIMEOUT;
		flags |= FLAG_PLAYER_END; //Activa FLAG_PLAYER_END

	piUnlock (FLAGS_KEY);

	p_player->posicion_nota_actual++;
	p_player->frecuencia_nota_actual=p_player->melodia->frecuencias[p_player->posicion_nota_actual];
	p_player->duracion_nota_actual=p_player->melodia->duraciones[p_player->posicion_nota_actual];

	piLock (STD_IO_BUFFER_KEY);
		printf("[PLAYER][ACTUALIZA PLAYER][NUEVA NOTA (%d DE %d)]\n",p_player->posicion_nota_actual+1,p_player->melodia->num_notas);
	piUnlock (STD_IO_BUFFER_KEY);
}

/*
    * Function:  StopPlayer
    * --------------------
    * Finalizaci�n del player(llevando la posicion de las notas a la ultima
    *
    *  fsm: puntero a la maquina de estados
    *
    */

void StopPlayer(fsm_t* this){ //Cuando se produce se acaba la melodia
	TipoPlayer *p_player;
	p_player = (TipoPlayer*)(this->user_data);

	piLock (FLAGS_KEY);
		flags &= ~FLAG_PLAYER_START;
		flags &= ~FLAG_PLAYER_STOP; //Desactiva los flags
		flags &= ~FLAG_PLAYER_END;
		flags &= ~FLAG_NOTA_TIMEOUT;

	piUnlock (FLAGS_KEY);
	softToneWrite(18, 0);
	p_player->posicion_nota_actual=p_player->melodia->num_notas; //La nota actual pasa a ser la ultima, cuando incrementa es como si hubiese acabado la melodia

	piLock (STD_IO_BUFFER_KEY);
		printf("[PLAYER][STOP PLAYER]\n");
	piUnlock (STD_IO_BUFFER_KEY);
}

/*
    * Function:  ComienzaNuevaNota
    * --------------------
    * Saca la frecuencia de la nota actual por el pin 18 de la rapsberry e inicia el temporizador con la duracion de la nota
    *
    *  fsm: puntero a la maquina de estados
    *
    */

void ComienzaNuevaNota(fsm_t* this){
	TipoPlayer *p_player;
	p_player = (TipoPlayer*)(this->user_data);

	piLock (FLAGS_KEY);
		flags &= ~FLAG_PLAYER_START;
		flags &= ~FLAG_PLAYER_STOP; //Desactiva los flags
		flags &= ~FLAG_PLAYER_END;
		flags &= ~FLAG_NOTA_TIMEOUT;
	piUnlock (FLAGS_KEY);

	softToneWrite(18, p_player->frecuencia_nota_actual); //Muestra en el osciloscopio la frecuencia de la nota actual

	piLock (STD_IO_BUFFER_KEY);
		printf("[PLAYER][COMIENZA NUEVA NOTA][NOTA %d][FREC %d][DURA %d]\n", p_player->posicion_nota_actual+1,p_player->frecuencia_nota_actual,p_player->duracion_nota_actual);
	piUnlock (STD_IO_BUFFER_KEY);

	tmr_startms((tmr_t*)(this->user_data2), p_player->duracion_nota_actual); //activa el temporizador
}
/*
    * Function:  FinalizaMelodia
    * --------------------
    * Se produce cuando se ha acabado la melodia
    *
    *  fsm: puntero a la maquina de estados
    *
    */

void FinalMelodia(fsm_t* this){ //Simplemente saca por pantalla que se ha acabado la melodia
	piLock (FLAGS_KEY);
		flags &= ~FLAG_PLAYER_START;
		flags &= ~FLAG_PLAYER_STOP; //Desactiva los flags
		flags &= ~FLAG_PLAYER_END;
		flags &= ~FLAG_NOTA_TIMEOUT;
	piUnlock (FLAGS_KEY);

	softToneWrite(18, 0);

	piLock (STD_IO_BUFFER_KEY);
		printf("[PLAYER][FINAL MELODIA]\n");
		printf("[FINAL MELODIA][FLAG_PLAYER_END]\n");
	piUnlock (STD_IO_BUFFER_KEY);
}
//---------------------------------------------------------------------------
 // FUNCION DE CONTROL DE DETECCION DE TARJETAS
 //---------------------------------------------------------------------------

void startFlag(){

	static int debounceTime = 0;

	if(millis() < debounceTime) {
		debounceTime = millis() + DEBOUNCE_TIME;
		return;
	}
	piLock (FLAGS_KEY);
	if(flagsinterrupt==1){
		flags |= FLAG_PLAYER_START;
		flagsinterrupt=0;

	}else{
		flags |= FLAG_PLAYER_STOP;
		flagsinterrupt=1;
	}
	piUnlock (FLAGS_KEY);

	debounceTime = millis() + DEBOUNCE_TIME;

}
/*
  * Function:  system_setup
  * --------------------
  * Inicializa el sistema(parametros)
  *
  *  returns: 1 si ha funcionado todo
  */

int system_setup (void) {
	int x = 0;
	wiringPiSetupGpio();
	pinMode(20,INPUT);
	pinMode(18, OUTPUT);
	softToneCreate(18);
	softToneCreate(20);
	piLock (STD_IO_BUFFER_KEY);

	// sets up the wiringPi library
	if (wiringPiSetupGpio () < 0) {
		printf ("Unable to setup wiringPi\n");
		piUnlock (STD_IO_BUFFER_KEY);
		return -1;
    }

	// Lanzamos thread para exploracion del teclado convencional del PC
	x = piThreadCreate (thread_explora_teclado);

	if (x != 0) {
		printf ("it didn't start!!!\n");
		piUnlock (STD_IO_BUFFER_KEY);
		return -1;
    }

	piUnlock (STD_IO_BUFFER_KEY);

	return 1;
}

/*
 * Function:  timer_isr
 * --------------------
 *
 *	 Activa la FLAG_NOTA_TIMEOUT
 *
 *
 */

void timer_isr (union sigval value) {
	flags |= FLAG_NOTA_TIMEOUT; // Activa el FLAG_NOTA_TIMEOUT
}

/*
    * Function:  fsm_setup
    * --------------------
    * Funcion que inicializa la maquina de estados poneindo el FLAG_SYSTEM_START a 1
    *
    */

void fsm_setup(fsm_t* pi_fsm) {
	piLock (FLAGS_KEY);
	flags = 0;
	piUnlock (FLAGS_KEY);

	InicializaPlayer(pi_fsm);

	piLock (STD_IO_BUFFER_KEY);
	printf("\nInserte la tarjeta para comenzar\n");
	piUnlock (STD_IO_BUFFER_KEY);
}

//-------------------------------------------------------------------------------------
// PI_THREAD (thread_explora_teclado): Deteccion y manejo de pulsaciones en el teclado
//-------------------------------------------------------------------------------------


PI_THREAD (thread_explora_teclado) {
	int teclaPuls;

	while (1) {
		delay(10); // Wiring Pi function: pauses program execution for at least 10 ms

		piLock (STD_IO_BUFFER_KEY);
	if(kbhit()) { // Funcion que detecta si se ha producido pulsacion de tecla alguna
			teclaPuls = kbread(); // Funcion que devuelve la tecla pulsada

			printf("\n[KBHIT][%c]\n", teclaPuls);

			switch(teclaPuls) {
					case 's':
						piLock (FLAGS_KEY);
							flags |= FLAG_PLAYER_START; //si se pulsa la s, se activa el FLAG_PLAYER_START

						piUnlock (FLAGS_KEY);
						break;

					case 't':
					piLock (FLAGS_KEY);
							flags |= FLAG_PLAYER_STOP; //si se pulsa la s, se activa el FLAG_PLAYER_STOP
						piUnlock (FLAGS_KEY);
						break;

					case 'q':
						exit(0); //si se pulsa la s, se abandona el programa
						break;

					default:
						printf("INVALID KEY!!!\n"); //cualquier pulsacion de otra tecla no interrumpe nada
						break; //se muestra por pantalla un aviso de que la tecla pulsada es inválida
			}
		}
	piUnlock (STD_IO_BUFFER_KEY);
	}
}

/*
     * Function:  main
     * --------------------
     * Funcion principal del programa. Inicializa el sistema y comienza a funcionar en un bucle infinito
     *
     */

int main ()
{
	TipoSistema sistema;
	TipoMelodia melodiaV1;
	sistema.player.melodia=&(sistema.tarjetas_activas[0].melodia);
	InicializaMelodia(&melodiaV1,"Despacito",frecuenciaDespacito,tiempoDespacito,160); //Inicializa una melodía determinada
	sistema.player.melodia=&melodiaV1;

	tmr_t* tmr = tmr_new (timer_isr);


	unsigned int next;

	// Maquina de estados: lista de transiciones
	// {EstadoOrigen,FunciónDeEntrada,EstadoDestino,FunciónDeSalida}
	fsm_trans_t pi_tabla[] = {
			{WAIT_START ,   compruebaPlayerStart,  WAIT_PUSH, InicializaPlayer },
			{WAIT_PUSH, compruebaNotaTimeout, WAIT_END,   ActualizaPlayer },
			{WAIT_PUSH, compruebaPlayerStop, WAIT_START,   StopPlayer},
			{WAIT_END, compruebaFinalMelodia, WAIT_START,   FinalMelodia},
			{WAIT_END, compruebaNotaNueva, WAIT_PUSH,   ComienzaNuevaNota},
			{ -1, NULL, -1, NULL },
	};

	fsm_t* pi_fsm = fsm_new (WAIT_START, pi_tabla, &(sistema.player), tmr);

	// Configuracion e inicializacion del sistema
	system_setup();
	fsm_setup (pi_fsm);
	wiringPiISR (20, INT_EDGE_BOTH, startFlag);
	next = millis();
	while (1) {
		fsm_fire (pi_fsm);
		next += CLK_MS;
		delay_until (next);
	}
	tmr_destroy ((tmr_t*)(pi_fsm->user_data));

	fsm_destroy (pi_fsm);
}
