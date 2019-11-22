#include <ncurses.h>
#include <wiringPi.h>
#include "../headers/deteccionTecla.h"
#include "../headers/rs232.h"

int controlVelocidad(int periodo, int puertochar){
	if((deteccionTecla(KEY_UP, 1) || puertochar=='s' ) && periodo>5){
		periodo = periodo - 5;
	}
	if((deteccionTecla(KEY_DOWN, 1) || puertochar=='b' ) && periodo<9995){
		periodo = periodo + 5;
	}
	return periodo;
}
