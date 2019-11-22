#include <ncurses.h>			/* ncurses.h includes stdio.h */  
#include <stdio.h>
#include <wiringPi.h>
#include <string.h> 
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
 
int main()
{
	wiringPiSetup();	// Inicializo las funciones de wiringPi, necesario segun documentacion
	initscr();	// Inicializo mi pantalla de ncurses, por defecto llamada stdscr
	noecho(); 		// Deshabilito el echo automatico de los caracteres tipeados
  	keypad(stdscr, TRUE); 	// Deshabilito que se pueda usar el keypad del teclado en la pantalla de ncurses
				//	esto es necesario para el correcto uso de la tecla Escape

	int leds[] ={4, 5, 6, 26, 27, 28, 29, 25};
	
	int potenciometro, fotocelula, termistor;

	adcCrudo(1, &potenciometro, &fotocelula, &termistor);

	pinMode(leds[0], OUTPUT);	
	pinMode(leds[1], OUTPUT);
	pinMode(leds[2], OUTPUT);
	pinMode(leds[3], OUTPUT);
	pinMode(leds[4], OUTPUT);
	pinMode(leds[5], OUTPUT);
	pinMode(leds[6], OUTPUT);
	pinMode(leds[7], OUTPUT);


	bool remoto = 0;
	int fdpuerto = 0;
	int filas, columnas;
	int intentos = 3;
	int posC = 0;
	int velocidad, poteCorrecto;

       	potenciometro>5 ? (poteCorrecto = potenciometro - potenciometro%5) : (poteCorrecto = 5);
	velocidad = poteCorrecto;

	initscr();				// Comienzo la interfaz de ncurses

						// y columnas de la ventana actual
	if(has_colors()){			// Si la terminal soporta colores
 		start_color();			// Arranco ncurses en modo con colores
	}

	
	getmaxyx(stdscr, filas, columnas); 	// Guardo en mis variables las filas 

	if(!logueo(intentos))
		return 0;	

	fdpuerto = rs232init(PUERTO,VELOCIDAD);

	while(!deteccionTecla('q', 0)){
		wclear(stdscr);	// Limpio la pantalla al comienzo de cada ciclo
 		getmaxyx(stdscr, filas, columnas); // Guardo en mis variables las filas 
						   // y columnas de la ventana actual
 		mvprintw(0	, 0	, "Presione la tecla \"q\" para finalizar", filas, columnas);
 		mvprintw(filas-1, 0	, "[DEBUG] La terminal tiene %d filas y %d columnas", filas, columnas);
		adcCrudo(0, &potenciometro, &fotocelula, &termistor);
       		potenciometro>5 ? (poteCorrecto = potenciometro - potenciometro%5) : (poteCorrecto = 5);
 		mvprintw(filas-2, 0	, "El valor del potenciometro es %d. Para usar este valor como velocidad presione \"p\"", potenciometro);
		(columnas/2-20)<0 ? (posC=0) : (posC = columnas/2-20);
		mvaddstr(filas/2-4, posC, "Ingrese la secuencia que desea comenzar:");
		mvaddstr(filas/2-3, posC, "1) El auto fantástico");
		mvaddstr(filas/2-2, posC, "2) El choque");
		mvaddstr(filas/2-1, posC, "3) La apilada");
		mvaddstr(filas/2+0, posC, "4) La carrera");
		mvaddstr(filas/2+1, posC, "5) El contador");
		mvaddstr(filas/2+2, posC, "6) El auto policia");
		mvaddstr(filas/2+3, posC, "7) La explosion");
		mvaddstr(filas/2+4, posC, "8) La lotería");
		
		int puertochar;
		puertochar = rs232rx(fdpuerto);


 			mvprintw(2	, 0	, "Para pasar a modo standalone ponga el switch \"1\" en high y presione \"x\"");
			if(!remoto){
 				mvprintw(1	, 0	, "Se encuentra en modo LOCAL, para pasar a remoto presione \"r\"");
				if (deteccionTecla('r',1))
					remoto = 1;
			}else{
 				mvprintw(1	, 0	, "Se encuentra en modo REMOTO, para pasar a local presione \"r\"");
 				wrefresh(stdscr); // Actualizo la pantalla en cada ciclo
				rs232escribo(fdpuerto);
				if (deteccionTecla('r',1))
					remoto = 0;
			}

			if (deteccionTecla('p',1) || puertochar=='p') 
				velocidad = poteCorrecto;
			if (deteccionTecla('1',1) || puertochar=='1') 
				while(!deteccionTecla('q', 1)) velocidad = autoFantastico(leds,   velocidad, fdpuerto, remoto);
			if (deteccionTecla('2',1) || puertochar=='2') 
				while(!deteccionTecla('q', 1)) velocidad = choque(leds, velocidad, fdpuerto, remoto);
			if (deteccionTecla('3',1) || puertochar=='3')
				while(!deteccionTecla('q', 1)) velocidad = apilada(leds, velocidad, fdpuerto, remoto);
			if (deteccionTecla('4',1) || puertochar=='4')
				while(!deteccionTecla('q', 1)) velocidad = carrera(leds, velocidad, fdpuerto, remoto);
			if (deteccionTecla('5',1) || puertochar=='5')
				while(!deteccionTecla('q', 1)) velocidad = contador(leds, velocidad, fdpuerto, remoto);
			if (deteccionTecla('6',1) || puertochar=='6')
				while(!deteccionTecla('q', 1)) velocidad = policia(leds, velocidad, fdpuerto, remoto);
			if (deteccionTecla('7',1) || puertochar=='7')
				while(!deteccionTecla('q', 1)) velocidad = explosion(leds, velocidad, fdpuerto, remoto);
			if (deteccionTecla('8',1) || puertochar=='8')
				while(!deteccionTecla('q', 1)) velocidad = loteria(leds, velocidad, fdpuerto, remoto);
 			wrefresh(stdscr); // Actualizo la pantalla en cada ciclo
	}
	
	rs232close(fdpuerto);
	endwin(); // Cierro la pantalla de ncurses
	return 0;
}
