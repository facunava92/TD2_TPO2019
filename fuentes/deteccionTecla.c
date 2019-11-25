#include <ncurses.h>	// -lncurses

bool deteccionTecla(int caracter, bool ug){	// Funcion que detecta si el usuario toco escape, sin retrasar la ejecucion del programa
	int c;	// Caracter a recibir
	bool r; // Valor de retorno, que indica si recibi escape o no

	nodelay(stdscr, TRUE);	// Desactivo la espera a que se escriba un caracter,
				//   esto es lo que hace que no se pause la ejecucion
	c = getch();		// Veo si puedo recibir un caracter

	if(c!=ERR){		// Primero me fijo si recibi algun caracter
		if(c==caracter){	// Me fijo si ese caracter fue un escape
			r=1;
		} else{
			r=0;	
			if(ug && c!=27){
				ungetch(c);	// Lo devuelvo al buffer de caracteres de stdin
			}
		}
	}else{		// En caso de que nisiquiera haya recibido algun caracter
		r = 0;
	}

	nodelay(stdscr, FALSE); // Vuelvo a habilitar que la funcion getch espere a que el usuario teclee

	return(r);	// Devuelvo si recibi, o no, un escape
}
