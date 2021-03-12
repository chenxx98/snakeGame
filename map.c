#include <curses.h>

void initNcurses()
{
		
	initscr();
	keypad(stdscr,1);
}

void  gameMap()
{
	int line;
	int list;
	
	for(line=0;line<20;line++){
		if(line==0){
			for(list = 0; list <20;list++){
				printw("--");
			}
			printw("\n");
		}


		if(line>=0 && line<=19){

			for(list=0;list<=20;list++){
				
				if(list ==0 || list==20){
					printw("|");
				}
				else{
					
					printw("  ");
				}

			}
			printw("\n");
		
		}
		if(line == 19){
			for(list=0;list<20;list++){
				printw("--");
			}
			printw("\n");
			printw("By ChenChen!\n");
		
		}

	}

}

int main()
{
	
	initNcurses();
	gameMap();	
	

		
	getch();
	endwin();
	return 0;

	
}
