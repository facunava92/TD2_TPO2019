#include <wiringPi.h>	// -lwiringPi
#include <ncurses.h>	// -lncurses
#include "../headers/deteccionTecla.h"
#include "../headers/controlVelocidad.h"
#include <time.h>
#include <stdlib.h>
#include "../headers/rs232.h"

int loteria(int leds[8],  int periodo, int fdpuerto, bool remoto ){
	bool valores[8] = {0,0,0,0,0,0,0,0}; // Cadena que guarda estados de los leds
	int posC, filas, columnas;
	srand(time(0));
	int ganador = rand()%8;

	for(int i=1; i<50; i++){ // Prendo todos los leds uno a la vez, en orden
		if(i<30){
		valores[0] = (i%2);
		valores[1] = !(i%2);
		valores[2] = (i%2);
		valores[3] = !(i%2);
		valores[4] = (i%2);
		valores[5] = !(i%2);
		valores[6] = (i%2);
		valores[7] = !(i%2);
		}else{
			valores[0] = 0;
			valores[1] = 0;
			valores[2] = 0;
			valores[3] = 0;
			valores[4] = 0;
			valores[5] = 0;
			valores[6] = 0;
			valores[7] = 0;
			valores[ganador] = i%2;
		}

		// Igualo todos los pines a sus respectivos valores
		if(!remoto){
			digitalWrite(leds[0], valores[0]);
			digitalWrite(leds[1], valores[1]);
			digitalWrite(leds[2], valores[2]);
			digitalWrite(leds[3], valores[3]);
			digitalWrite(leds[4], valores[4]);
			digitalWrite(leds[5], valores[5]);
			digitalWrite(leds[6], valores[6]);
			digitalWrite(leds[7], valores[7]);
		}

		for(int d=0; d<periodo; d++){
			int puertochar;
			if(remoto) rs232escribo(fdpuerto);
			puertochar = rs232rx(fdpuerto);
			periodo = controlVelocidad(periodo, puertochar);
			if(deteccionTecla('q', 0) || puertochar=='q'){
				ungetch('q');
			       	i=512; break;
			}
 			getmaxyx(stdscr, filas, columnas); // Guardo en mis variables las filas 
			wclear(stdscr);
 			mvprintw(0	, 0	, "Presione la tecla \"q\" para finalizar", filas, columnas);
 			mvprintw(filas-1, 0	, "[DEBUG] La terminal tiene %d filas y %d columnas", filas, columnas);
			(columnas/2-18)<0 ? (posC=0) : (posC = columnas/2-18);
			mvaddstr(filas/2-1, posC, "Ejecutando la secuencia \"La lotería\"");
			(columnas/2-14)<0 ? (posC=0) : (posC = columnas/2-14);
			mvprintw(filas/2, posC, "El periodo actual es %4d ms", periodo);
			wrefresh(stdscr);

			delay(1);	// Delay entre ciclos
		}
	}
	
	// Cuando termina el programa apagado todos los pines
	digitalWrite(leds[0], LOW);
	digitalWrite(leds[1], LOW);
	digitalWrite(leds[2], LOW);
	digitalWrite(leds[3], LOW);
	digitalWrite(leds[4], LOW);
	digitalWrite(leds[5], LOW);
	digitalWrite(leds[6], LOW);
	digitalWrite(leds[7], LOW);

	return periodo;
}
