#include <wiringPi.h>	// -lwiringPi
#include <stdint.h>	// Necesario para usar uint8_t y asegurar portabilidad de tamaño de variable
#include <ncurses.h>	// -lncurses
#include "../headers/deteccionTecla.h"
#include "../headers/controlVelocidad.h"
#include "../headers/rs232.h"

int choque(int pines[8], int periodo, int fdpuerto, bool remoto){
	int posC, filas, columnas;

	static const uint8_t lut[8] =	// La LUT se implementa con static y const para permitir optimizaciones
	{
		// Valores calculados manualmente, es simplemente pasar del binario de 8 leds al hexa correspondiente
		0x81U,
		0x42U,
		0x24U,
		0x18U,
		0x18U,
		0x24U,
		0x42U,
		0x81U
	};

	for(int i=0; i<8; i++){	// Recorro los 8 valores de mi LUT
		if(!remoto){
			(lut[i] & 0x01) ? digitalWrite(pines[0], HIGH) : digitalWrite(pines[0], LOW);
			(lut[i] & 0x02) ? digitalWrite(pines[1], HIGH) : digitalWrite(pines[1], LOW);
			(lut[i] & 0x04) ? digitalWrite(pines[2], HIGH) : digitalWrite(pines[2], LOW);
			(lut[i] & 0x08) ? digitalWrite(pines[3], HIGH) : digitalWrite(pines[3], LOW);
			(lut[i] & 0x10) ? digitalWrite(pines[4], HIGH) : digitalWrite(pines[4], LOW);
			(lut[i] & 0x20) ? digitalWrite(pines[5], HIGH) : digitalWrite(pines[5], LOW);
			(lut[i] & 0x40) ? digitalWrite(pines[6], HIGH) : digitalWrite(pines[6], LOW);
			(lut[i] & 0x80) ? digitalWrite(pines[7], HIGH) : digitalWrite(pines[7], LOW);
		}
		for(int d=0; d<periodo; d++){
			int puertochar;
			if(remoto) rs232escribo(fdpuerto);
			puertochar = rs232rx(fdpuerto);
			periodo = controlVelocidad(periodo, puertochar);
			if(deteccionTecla('q', 0) || puertochar=='q'){
				ungetch('q');
			       	i=18; break;
			}
 			getmaxyx(stdscr, filas, columnas); // Guardo en mis variables las filas 
			wclear(stdscr);
 			mvprintw(0	, 0	, "Presione la tecla \"q\" para finalizar", filas, columnas);
 			mvprintw(filas-1, 0	, "[DEBUG] La terminal tiene %d filas y %d columnas", filas, columnas);
			(columnas/2-16)<0 ? (posC=0) : (posC = columnas/2-16);
			mvaddstr(filas/2-1, posC, "Ejecutando la secuencia \"El choque\"");
			(columnas/2-14)<0 ? (posC=0) : (posC = columnas/2-14);
			mvprintw(filas/2, posC, "El periodo actual es %4d ms", periodo);
			wrefresh(stdscr);

			delay(1);
		}
	}	

	// Pongo todos los leds a 0
	digitalWrite(pines[0], LOW);
	digitalWrite(pines[1], LOW);
	digitalWrite(pines[2], LOW);
	digitalWrite(pines[3], LOW);
	digitalWrite(pines[4], LOW);
	digitalWrite(pines[5], LOW);
	digitalWrite(pines[6], LOW);
	digitalWrite(pines[7], LOW);

	return periodo;
}
