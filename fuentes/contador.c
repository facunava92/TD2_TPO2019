#include <wiringPi.h>	// -lwiringPi
#include <ncurses.h>	// -lncurses
#include "../headers/deteccionTecla.h"
#include "../headers/controlVelocidad.h"
#include "../headers/rs232.h"

int contador(int leds[8], int periodo, int fdpuerto, bool remoto){
	bool valores[8] = {0,0,0,0,0,0,0,0}; // Cadena que guarda estados de los leds
	char programa[] = "El contador";
	int speed;

	for(int i=1; i<512; i++){ // Prendo todos los leds uno a la vez, en orden
		valores[0] = (i/2  )%2;
		valores[1] = (i/4  )%2;
		valores[2] = (i/8  )%2;
		valores[3] = (i/16 )%2;
		valores[4] = (i/32 )%2;
		valores[5] = (i/64 )%2;
		valores[6] = (i/128)%2;
		valores[7] = (i/256)%2;

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
			speed = 101 - (0.9900 * periodo);
			if(deteccionTecla('Q', 0) || puertochar=='Q'){
				ungetch('Q');
			       	i=512; break;
			}


			delay(1);	// Delay entre ciclos
		}
			ledmenu(remoto, programa, speed);
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
