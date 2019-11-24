#include <ncurses.h>			/* ncurses.h includes stdio.h */  
#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
#include <math.h>
#include "../headers/deteccionTecla.h"
#include "../headers/rs232.h"
#include "../headers/auto.h"
#include "../headers/logueo.h"
#include "../headers/carrera.h"
#include "../headers/choque.h"
#include "../headers/apilada.h"
#include "../headers/adcCrudo.h"
#include "../headers/policia.h"
#include "../headers/explosion.h"
#include "../headers/contador.h"
#include "../headers/loteria.h"
#define PUERTO "/dev/serial0"
#define VELOCIDAD 9600

float modifier  = 0.39212;
int leds[] ={4, 5, 6, 26, 27, 28, 29, 25};
int potenciometro, fotocelula, termistor, ADC;
int fdpuerto = 0;
int filas, columnas;
int intentos = 3;
int posC = 0;
int speed, velocidad_ms;

bool remoto = 0;

int main()
{
	led_config(leds);
	initscr();			// Inicializo mi pantalla de ncurses, por defecto llamada stdscr
	noecho(); 			// Deshabilito el echo automatico de los caracteres tipeados
  	keypad(stdscr, TRUE); 		// Deshabilito que se pueda usar el keypad del teclado en la pantalla de ncurses
					//esto es necesario para el correcto uso de la tecla Escape

	adcCrudo(1, &ADC, &fotocelula, &termistor);


	potenciometro = modifier * (ADC+2);
	velocidad_ms 	= 201 - 2 * potenciometro;

	initscr();				// Comienzo la interfaz de ncurses
	curs_set(0);

						// y columnas de la ventana actual
	if(has_colors()){			// Si la terminal soporta colores
 		start_color();			// Arranco ncurses en modo con colores
	}

	
	if(!logueo(intentos))
		return 0;	

	fdpuerto = rs232init(PUERTO,VELOCIDAD);

	while(!deteccionTecla('Q', 0))
	{
		adcCrudo(0, &ADC, &fotocelula, &termistor);

		potenciometro = modifier * (ADC+2.5);
		//velocidad_ms 	= 201 - 2 * potenciometro;
		speed		= 101 - (0.4975 *  velocidad_ms);

		clear();
		mainmenu(potenciometro, speed, remoto);

		int puertochar;
		puertochar = rs232rx(fdpuerto);

		if(!remoto)
		{
			if (deteccionTecla('R',1))
				remoto = 1;
		}
		
		else
		{
			rs232escribo(fdpuerto);
			if (deteccionTecla('R',1))
				remoto = 0;
		}

		if (deteccionTecla('P',1) || puertochar=='P') 
		{
			velocidad_ms 	= 201 - 2 * potenciometro;
		}
		if (deteccionTecla('1',1) || puertochar=='1') 
			while(!deteccionTecla('Q', 1)) velocidad_ms = autoFantastico(leds,   velocidad_ms, fdpuerto, remoto);
		if (deteccionTecla('2',1) || puertochar=='2') 
			while(!deteccionTecla('Q', 1)) velocidad_ms = choque(leds, velocidad_ms, fdpuerto, remoto);
		if (deteccionTecla('3',1) || puertochar=='3')
			while(!deteccionTecla('Q', 1)) velocidad_ms = apilada(leds, velocidad_ms, fdpuerto, remoto);
		if (deteccionTecla('4',1) || puertochar=='4')
			while(!deteccionTecla('Q', 1)) velocidad_ms = carrera(leds, velocidad_ms, fdpuerto, remoto);
		if (deteccionTecla('5',1) || puertochar=='5')
			while(!deteccionTecla('Q', 1)) velocidad_ms = contador(leds, velocidad_ms, fdpuerto, remoto);
		if (deteccionTecla('6',1) || puertochar=='6')
			while(!deteccionTecla('Q', 1)) velocidad_ms = policia(leds, velocidad_ms, fdpuerto, remoto);
		if (deteccionTecla('7',1) || puertochar=='7')
			while(!deteccionTecla('Q', 1)) velocidad_ms = explosion(leds, velocidad_ms, fdpuerto, remoto);
		if (deteccionTecla('8',1) || puertochar=='8')
			while(!deteccionTecla('Q', 1)) velocidad_ms = loteria(leds, velocidad_ms, fdpuerto, remoto);

	}
	
	rs232close(fdpuerto);
	endwin(); // Cierro la pantalla de ncurses
	return 0;
}
