#include <ncurses.h>
#include <wiringPi.h>
#include "../headers/deteccionTecla.h"
#include "../headers/rs232.h"

int controlVelocidad(int periodo, int puertochar)
{
	if(periodo < 0)
		periodo = 3;

	if(periodo > 201)
		periodo = 198;

	if((deteccionTecla(KEY_UP, 1) || puertochar=='s' ) && periodo>1){
		periodo = periodo - 2;
	}
	if((deteccionTecla(KEY_DOWN, 1) || puertochar=='b' ) && periodo<200){
		periodo = periodo + 2;
	}
	return periodo;
}
