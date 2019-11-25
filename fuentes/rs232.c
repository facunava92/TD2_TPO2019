#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h> // -lwiringPi
#include <wiringSerial.h>
#include <ncurses.h> // -lncurses
#include "../headers/deteccionTecla.h"
#define PUERTO "/dev/AMA0"
#define VELOCIDAD 9600

int rs232init(char *puerto, int velocidad){
	int fd;
	struct termios configuracion;

	fd = serialOpen(puerto, velocidad);

	tcgetattr(fd, &configuracion);
	configuracion.c_cflag &= ~CSIZE;  // Enmascaro el tamaño
	configuracion.c_cflag &= ~PARENB; // Desatcivo la paridad
	configuracion.c_cflag &= ~CSTOPB; // Desactivo el segundo bit de stop
	configuracion.c_cflag |= CS8;	  // 8 bits
	tcsetattr(fd, TCSANOW, &configuracion);

	return fd;
}

void rs232close(int fd){
	serialClose(fd);
}

int rs232rx(int fd){
	if(serialDataAvail(fd)>0){
		return serialGetchar(fd);
	}else{
		return 0;
	}
}

void rs232tx(int fd, int caracter){
	//serialPutchar(fd, caracter);
	//fwrite(&caracter, sizeof(int), 1, fd);
	write(fd, &caracter, 1);
}

void rs232leo(int fd){
	int caracter[1];
	caracter[0] = rs232rx(fd);
	if (caracter[0]!=0){
		//write(2, caracter, 1);
		fwrite(caracter, sizeof(int), 1, stdin);
	}
}

void rs232escribo(int fd){
	int caracter;
	nodelay(stdscr, TRUE);	// Desactivo la espera a que se escriba un caracter,
	caracter = getch();		// Veo si puedo recibir un caracter

	//read(0, &caracter, 1);
	//fread(&caracter, sizeof(int), 1, stdin);
	if(caracter!=ERR){		// Primero me fijo si recibi algun caracter
		if(caracter == 'R') ungetch('R');
//		else if(caracter=='\033'){ 
//			read(0,&caracter,1);
//			read(0,&caracter,1);
//			if (caracter == 'A'){
//				rs232tx(fd, 's');
//				ungetch(KEY_UP);
//			}
//			if (caracter == 'B'){
//				rs232tx(fd, 'b');
//				ungetch(KEY_DOWN);
//			}
		else if(caracter==KEY_UP){ 
				rs232tx(fd, 's');
				ungetch(KEY_UP);
		}else if(caracter==KEY_DOWN){ 
				rs232tx(fd, 'b');
				ungetch(KEY_DOWN);
		}else{
	       		rs232tx(fd, caracter);
			ungetch(caracter);
		}
	}
	nodelay(stdscr, FALSE); // Vuelvo a habilitar que la funcion getch espere a que el usuario teclee
}
