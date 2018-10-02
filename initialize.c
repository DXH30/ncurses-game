#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
WINDOW *create_building(int height, int width, int posy, int posx);
void destroy_win(WINDOW *local_win);
void rigidbody2dbuilding(WINDOW *local_win, int posy, int posx);

int main(int argc, char *argv[])
{
	WINDOW *my_win;
	WINDOW *my_building;
	int startx, starty, width, height;
	int buildx, buildy, widthb, heightb;
	int ch;

	initscr();
	cbreak();

	keypad(stdscr, TRUE);
	heightb = 5;
	widthb = 5;
	buildy = (LINES - heightb) / 2;
	buildx = (LINES - widthb) / 2;
	height = 1;
	width = 1;
	starty = (LINES - height) / 2;
	startx = (LINES - width) / 2;
	printw("Press F1 to exit");
	refresh();
	my_building = create_building(heightb, widthb, buildy, buildx);
	my_win = create_newwin(height, width, starty, startx);

	while((ch = getch()) != KEY_F(1))
	{
		switch(ch)
		{
			case KEY_LEFT:
				destroy_win(my_win);
				my_win = create_newwin(height, width, starty, --startx);
				break;
			case KEY_RIGHT:
				destroy_win(my_win);
				my_win = create_newwin(height, width, starty, ++startx);
				break;
			case KEY_UP:
				destroy_win(my_win);
				my_win = create_newwin(height, width, --starty, startx);
				break;
			case KEY_DOWN:
				destroy_win(my_win);
				my_win = create_newwin(height, width, ++starty, startx);
				break;
		}
	}

	endwin();
	rigidbody2dbuilding(my_building, 3, 3);
	return 0;
}
WINDOW *create_building(int height, int width, int posy, int posx)
{
	WINDOW *local_building;
	local_building = newwin(height, width, posy, posx);
	wborder(local_building, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(local_building);
	return local_building;
}
void destroy_building(WINDOW *local_win)
{
	wrefresh(local_win);
	delwin(local_win);
}

void rigidbody2dbuilding(WINDOW *local_win, int posy, int posx)
{	
	int mx, my;
	int r = mx*my;
	int hole = (mx-2)*(my-2);
	int c = 2;
	getmaxyx(local_win, mx, my);
	int i, j, **tembok;
	tembok = malloc(mx*my*sizeof(int *));
	for (i = 0; i < mx*my; i++)
		tembok[i] = malloc(c*sizeof(int));
	int x = 0, y = 0, count = 0;
	for (i = 0; i < mx; i++)
		for (j = 0; j < my; j++)
		{
		       tembok[count][0] = i;
		       tembok[count][1] = j;
		       count++;
		}
	count = 0;
	for (i = 0; i < mx; i++)
		for (j = 0; j < my; j++)
		{
			printf("%d %d\n", tembok[count][0],tembok[count][1]);
			count++;
		}
}
WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	
//box(local_win, 0, 0);
	
	wborder(local_win, '|', '|', '-', '-', '+', '+', '+', '+');

	wrefresh(local_win);

	return local_win;
}

void destroy_win(WINDOW *local_win)
{
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
}
