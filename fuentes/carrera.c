#include <wiringPi.h>	// -lwiringPi
#include <stdint.h>	// Necesario para usar uint8_t y asegurar portabilidad de tamaño de variable
#include <ncurses.h>	// -lncurses
#include "../headers/deteccionTecla.h"
#include "../headers/controlVelocidad.h"
#include "../headers/rs232.h"

int carrera(int pines[8], int periodo, int fdpuerto, bool remoto){
	char programa[] = "La carrera";
	int speed;

	static const uint8_t lut[16] =	// La LUT se implementa con static y const para permitir optimizaciones
	{
		// Valores calculados manualmente, es simplemente pasar del binario de 8 leds al hexa correspondiente
		0x01U, 0x01U,
		0x02U, 0x02U,
		0x04U, 0x04U,
		0x08U, 0x08U,
		0x11U, 0x12U,
		0x24U, 0x28U,
		0x50U, 0x60U,
		0xC0U, 0x80U
	};

	for(int i=0; i<16; i++){	// Recorro los 18 valores de mi LUT
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
			speed = 101 - (0.9900 * periodo);
			if(deteccionTecla('Q', 0) || puertochar=='Q'){
				ungetch('Q');
			       	i=18; break;
			}

			ledmenu(remoto, programa, speed);
			
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
