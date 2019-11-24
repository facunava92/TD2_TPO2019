#include <wiringPi.h>	// -lwiringPi
#include <ncurses.h>	// -lncurses
#include "../headers/deteccionTecla.h"
#include "../headers/controlVelocidad.h"
#include "../headers/rs232.h"

int apilada(int leds[8],int periodo, int fdpuerto, bool remoto){
	bool valores[8] = {0,0,0,0,0,0,0,0}; // Cadena que guarda estados de los leds
	char programa[]  = "La apilada";
	int speed;

	for(int j=0; j<8; j++){	// Realizo dos ciclos, uno de izq. a derecha, otro de derecha a izq.
		for(int i=0; i<8-j+2; i++){ // Prendo todos los leds uno a la vez, en orden
			if(i<8-j){
				valores[i] = 1;
				if(i!=0) valores[i-1] = 0;
			}else{
				if(i==8-j) valores[i-1]=0;
				else valores[i-2]=1;
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
				speed = 101 - (0.9900 * periodo);
				periodo = controlVelocidad(periodo, puertochar);
				if(deteccionTecla('Q', 0) || puertochar=='Q'){
					ungetch('Q');
				       	j=8; i=8; break;
				}

				ledmenu(remoto, programa, speed);
				

				delay(1);	// Delay entre ciclos
			}
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
