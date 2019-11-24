#include <wiringPi.h>	// -lwiringPi
#include <ncurses.h>	// -lncurses
#include "../headers/deteccionTecla.h"
#include "../headers/controlVelocidad.h"
#include "../headers/rs232.h"

int autoFantastico(int leds[8], int periodo, int fdpuerto, bool remoto){
	bool valores[8] = {0,0,0,0,0,0,0,0}; // Cadena que guarda estados de los leds
	int posC, filas, columnas,speed;
	char programa[] = "El auto fantastico";

	for(int j=0; j<2; j++){	// Realizo dos ciclos, uno de izq. a derecha, otro de derecha a izq.
		for(int i=0; i<8; i++){ // Prendo todos los leds uno a la vez, en orden
			if(j==0){	// El orden sera de derecha a izquierda si j esta en el primer ciclo
				// Asigno a todos los pines a apagarse
				valores[0]=0;
				valores[1]=0;
				valores[2]=0;
				valores[3]=0;
				valores[4]=0;
				valores[5]=0;
				valores[6]=0;
				valores[7]=0;
				// Solo asigno a encender el indicado
				valores[i] = 1;
			}else{	// El orden sera de izquierda a derecha si j esta en el segundo ciclo
				// Asigno a todos los pines a apagarase
				valores[0]=0;
				valores[1]=0;
				valores[2]=0;
				valores[3]=0;
				valores[4]=0;
				valores[5]=0;
				valores[6]=0;
				valores[7]=0;
				// Solo asigno a encender el inidicado
				valores[7-i] = 1;
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
				periodo = controlVelocidad(periodo, puertochar);
				speed = 101 - (0.4975 * periodo);
				puertochar = rs232rx(fdpuerto);
				if(deteccionTecla('Q', 0) || puertochar=='Q'){
					ungetch('Q');
				       	j=2; i=8; break;
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
