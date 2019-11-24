#include <ncurses.h>
#include <string.h>

#define MENUMAXY 10
#define MENUMAXX 26

int ch;
int height, width;
int indent_x, indent_y, len;

WINDOW *frame_menu, *str_menu;

void ledmenu(int remoto, char *program, int speed);

void ledmenu(int remoto, char *program, int speed)
{
char title[] 	= "PROYECTO FINAL DE TECNICAS DIGITALES II";
char str1[]	= "Ejecutando:";
char str2[]	= "Presione \"Q\" para terminar.";
char str3[]	= "Presione \"KEY_UP\" para aumentar la velocidad.";
char str4[]	= "Presione \"KEY_DOWN\" para disminuir la velocidad.";
char str5[]	= "MODO LOCAL";
char str6[]	= "MODO REMOTO";

	clear();

	if(remoto == 0)
	{
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
		init_pair(2, COLOR_YELLOW, COLOR_BLACK);
		init_pair(3, COLOR_RED, COLOR_BLACK);
		init_pair(4, COLOR_GREEN, COLOR_BLACK);
		init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(6, COLOR_CYAN, COLOR_BLACK);
	}

	else if(remoto == 1)
	{
		init_pair(1, COLOR_WHITE, COLOR_BLUE);
		init_pair(2, COLOR_YELLOW, COLOR_BLUE);
		init_pair(3, COLOR_RED, COLOR_BLUE);
		init_pair(4, COLOR_GREEN, COLOR_BLUE);
		init_pair(5, COLOR_MAGENTA, COLOR_BLUE);
		init_pair(6, COLOR_CYAN, COLOR_BLUE);
	}

	
	bkgd(COLOR_PAIR(1));


	getmaxyx(stdscr, height, width);
	len = strlen(title);	
	indent_x = ((width  - len) >> 1);
	wattron(stdscr,A_BOLD | COLOR_PAIR(2));
	mvwaddstr(stdscr, 2,indent_x, title);
	wattroff(stdscr,A_BOLD | COLOR_PAIR(2));

	indent_x = ((width  - MENUMAXX) >> 1);
	indent_y = ((height - MENUMAXY) >> 1);

	frame_menu = subwin(stdscr , MENUMAXY, MENUMAXX, indent_y-1, indent_x-1);

	box(stdscr,0,0);
	box(frame_menu,0,0);

	len = strlen(program);
	indent_x = ((MENUMAXX) - len) >> 1;
	
	wattron(frame_menu, A_BLINK | A_BOLD | COLOR_PAIR(5));
	mvwaddstr(frame_menu,2,indent_x, program);
	wattroff(frame_menu,A_BLINK | A_BOLD | COLOR_PAIR(5));

	wattron(frame_menu,A_BOLD | COLOR_PAIR(6));
	mvwprintw(frame_menu,6,5, "Velocidad = %d %%", speed);
	wattroff(frame_menu,A_BOLD | COLOR_PAIR(6));
	
	len = strlen(str1);
	indent_x = ((width  - len) >> 1);
	indent_y = ((height - MENUMAXY) >> 1) -2 ;

   	mvaddstr(indent_y, indent_x , str1);

	wattron(stdscr,A_BLINK | A_STANDOUT | COLOR_PAIR(3));
   	mvaddstr(height-5, 3, str2);
   	mvaddstr(height-4, 3, str3);
   	mvaddstr(height-3, 3, str4);
	wattroff(stdscr,A_BLINK | A_STANDOUT | COLOR_PAIR(3));


	wattron(stdscr, A_BOLD | COLOR_PAIR(4));
	if(remoto == 0)
	{
		len=strlen(str5);
   		mvaddstr(height-4, width-len-12, str5);

	}
	
	else if(remoto == 1)
	{
		len=strlen(str6);
		mvaddstr(height-4, width-len-11, str6); }
	wattroff(stdscr, A_BOLD |  COLOR_PAIR(4));


	refresh();
	wrefresh(frame_menu);
}
