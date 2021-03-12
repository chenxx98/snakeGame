#include <curses.h>

void initNcurses()
{
		
	initscr();
	keypad(stdscr,1);
}
struct Snake
{
	int line;
	int list;
	struct Snake *next;

};

struct Snake node1 = {2,2,NULL};

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
				}else if(node1.line == line &&node1.list == list){
						printw("[]");
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
