#include <stdio.h>
#include <curses.h>
#include <string.h>
#define MAX_LENGHT      8
#define ENTER           10
#define DEL		127
#define YBOX		10
#define XBOX		60

int ch=0;
int pos=0;
int pass=0, counter=0;
int denied = 1;
int height, width;
int indent_x, indent_y, len;

char mypass[MAX_LENGHT]="facu4692";
char password[MAX_LENGHT];
char title[] 	= "PROYECTO FINAL DE TECNICAS DIGITALES II";
char success[] 	= "Bienvenido al sistema!!";
char failed[] 	= "<<<ACCESO DENEGADO>>>";
char wait[] 	= "Presione cualquier tecla para continuar ...";
char line[]	= "Password=________";
char line2[]	= "Password=________";
WINDOW *pass_frame, *pass_box;

void show_menu (int intentos, int denied);

bool logueo(int intentos)
{


	init_pair(1, COLOR_RED, 	COLOR_BLACK);
	init_pair(2, COLOR_GREEN, 	COLOR_BLACK);
	init_pair(3, COLOR_YELLOW,	COLOR_BLACK);
	

	while(denied==1 && counter < intentos)
	{
		while(1)
		{	
			show_menu(counter, denied);
			ch=getch();
			if(ch == ENTER)
				break;	
			if(ch == KEY_BACKSPACE)
			{
				if(pos >=  MAX_LENGHT)
				{
					pos = 7;
				}

				if(pos == 0)
				{
					password[pos] = '\0';
					line[9]='_';
				}

				if(pos > 0 && pos < MAX_LENGHT)
				{
					line[9+pos]='_';
					pos--;
				
				}
				for(int i=0 ; i < pos ;i++)
					line[9+i]='*';
			}


			else   
			{	


				if(pos < MAX_LENGHT)
				{	
					line[9+pos]='*';
					password[pos] = ch;
					pos++;
				}
			}
		}		
	
		pos=0;
		counter++;	
		
		strcpy(line,line2);
		
		for(int i = 0; i<MAX_LENGHT; i++)
		{
			if(mypass[i] != password[i])
			{
				denied = 1;
				break;
			}

			else
			{	
				denied = 0;
			}
		}
	}	
	if( denied != 1)
	{
		
		show_menu(counter, denied);
		echo();                      // you can turn on echoing now	
		getch();
		endwin();
		return 1;
	}

	else
	{
		show_menu(counter, denied);
		echo();                      // you can turn on echoing now
		getch();
		endwin();
		return 0;
	}
}

void show_menu (int counter, int denied)
{

	clear();
	wclear(pass_box);
	
	getmaxyx(stdscr, height, width);
	len = strlen(title);	
	indent_x = ((width  - len) >> 1);
	wattron(stdscr,A_BOLD | COLOR_PAIR(3));
	mvwaddstr(stdscr, 2,indent_x, title);
	wattroff(stdscr,A_BOLD | COLOR_PAIR(3));

	
	indent_x = ((width  - XBOX) >> 1);
	indent_y = ((height - YBOX) >> 1);

	pass_frame = subwin(stdscr , YBOX, XBOX, indent_y-1, indent_x-1);
	pass_box   = subwin(pass_frame, YBOX-2, XBOX-2, indent_y,indent_x);


	box(stdscr,0,0);
	box(pass_frame,0,0);

	mvwaddstr(pass_box, 1,1, "Ingrese su password de 8 digitos");
	mvwaddstr(pass_box, 4,15 , line);
	if(counter > 0 && denied == 1 && counter < 3)
	{
		wattron(pass_box,A_BOLD | COLOR_PAIR(1));
		mvwaddstr(pass_box, (YBOX/2)+2, 1, "Clave incorrecta!!, intente nuevamente");
		wattroff(pass_box,A_BOLD | COLOR_PAIR(1));
	}

	if(counter == 3 && denied == 1)
	{
		len = strlen(failed);	
		indent_x = ((width  - len) >> 1);
		wattron(stdscr,A_BOLD | COLOR_PAIR(1));
		mvwaddstr(stdscr, 40,indent_x, failed);
	}
	if(denied == 0)
	{	
		len = strlen(success);	
		indent_x = ((width  - len) >> 1);
		wattron(stdscr,A_BOLD | COLOR_PAIR(2));
		mvwaddstr(stdscr, 40,indent_x, success);
		wattroff(stdscr,A_BOLD | COLOR_PAIR(2));

		len = strlen(wait);	
		indent_x = ((width  - len) >> 1);
		wattron(stdscr,A_BOLD | A_BLINK);
		mvwaddstr(stdscr, 45,indent_x, wait);
		wattroff(stdscr,A_BOLD | A_BLINK);
	}
	wrefresh(pass_box);
	wrefresh(stdscr);
}
