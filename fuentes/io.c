#include <wiringPi.h>	// -lwiringPi
#include <ncurses.h>	// -lncurses
#include "../headers/deteccionTecla.h"

int copia(int leds[8], int pulsadores[2], int llaves[4], int periodo){

	mvaddstr(0,0,"Presione cualquier tecla para finalizar"); // Le indico al usuario como cortar secuencia de luces

	int demora = periodo;


	bool valores[8] = {0,0,0,0,0,0,0,0}; // Cadena que guarda estados de los leds

	while(1){
		if(!deteccionTecla('q', 0)){	// Si el usuario no decidio terminar todavia
			// Primero leo todos los switches, e igualo los valores a lo que corresponda
			valores[0] = digitalRead(llaves[0]) & digitalRead(pulsadores[0]);
			valores[4] = digitalRead(llaves[0]) & digitalRead(pulsadores[1]);
			valores[1] = digitalRead(llaves[1]) & digitalRead(pulsadores[0]);
			valores[5] = digitalRead(llaves[1]) & digitalRead(pulsadores[1]);
			valores[2] = digitalRead(llaves[2]) & digitalRead(pulsadores[0]);
			valores[6] = digitalRead(llaves[2]) & digitalRead(pulsadores[1]);
			valores[3] = digitalRead(llaves[3]) & digitalRead(pulsadores[0]);
			valores[7] = digitalRead(llaves[3]) & digitalRead(pulsadores[1]);
			// Igualo todos los pines a sus respectivos valores
			digitalWrite(leds[0], valores[0]);
			digitalWrite(leds[1], valores[1]);
			digitalWrite(leds[2], valores[2]);
			digitalWrite(leds[3], valores[3]);
			digitalWrite(leds[4], valores[4]);
			digitalWrite(leds[5], valores[5]);
			digitalWrite(leds[6], valores[6]);
			digitalWrite(leds[7], valores[7]);
		}else{
			// Cuando termina el programa apagado todos los pines
			digitalWrite(leds[0],LOW);
			digitalWrite(leds[1],LOW);
			digitalWrite(leds[2],LOW);
			digitalWrite(leds[3],LOW);
			digitalWrite(leds[4],LOW);
			digitalWrite(leds[5],LOW);
			digitalWrite(leds[6],LOW);
			digitalWrite(leds[7],LOW);

			mvaddstr(2,0,"Finalizo la ejecucion, presione cualquier tecla para cerrar el programa.");
			//getch(); // El primer getch es para recibir el caracter que triggereo la funcion finalizar
			//getch(); // El segundo getch es para esperar otro caracter, 
				 //   para que el usuario pueda cortar la ejecucion
			break;
		}
	}
	return demora;	// Esto no hace falta, queda asi solo para mantener consistencia entre funciones
}
