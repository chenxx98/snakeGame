#include <curses.h>

int main()
{
	int key;
	initscr();
	keypad(stdscr,1);
	while(1){
	
		key = getch();
		switch(key){
			
			case KEY_DOWN:
				printw("DOWN\n");
				break;
			case KEY_UP:
				printw("UP\n");
				break;
			case KEY_LEFT:
				printw("LEFT\n");
				break;
			case KEY_RIGHT:
				printw("RIGHT\n");
				break;
		}
	}

	endwin();	

	return 0;
}
