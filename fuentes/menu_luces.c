#include <stdio.h>
#include <curses.h>
#include <string.h>


void menu_luces()
{

	initscr();
	noecho();                    /* turn off echoing*/

	start_color();
	init_pair(1, COLOR_RED, 	COLOR_BLACK);
	init_pair(2, COLOR_GREEN, 	COLOR_BLACK);
	init_pair(3, COLOR_YELLOW,	COLOR_BLACK);

	curs_set(0);

}	



void center(int row, char *title)
{
	int len,indent,y,width;
		
	getmaxyx(stdscr,y,width);	/* get screen width */

	len = strlen(title);		/* get title's length */
	indent = width - len;		/* subtract it from screen width */
	indent /= 2;			/* divide result into two */

	mvaddstr(row,indent,title);
	refresh();
}

