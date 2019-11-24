#include <ncurses.h>
#include <wiringPi.h>
#include "../headers/deteccionTecla.h"
#include "../headers/rs232.h"

int controlVelocidad(int periodo, int puertochar)
{
	if(periodo < 1)
		periodo = 1;

	if(periodo > 100)
		periodo = 99;

	if((deteccionTecla(KEY_UP, 1) || puertochar=='s' ) && periodo>1){
		periodo = periodo - 1;
	}
	if((deteccionTecla(KEY_DOWN, 1) || puertochar=='b' ) && periodo<100){
		periodo = periodo + 1;
	}
	return periodo;
}
