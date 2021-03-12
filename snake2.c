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
struct Snake node2 = {2,3,NULL};
struct Snake node3 = {2,4,NULL};
struct Snake node4 = {2,5,NULL};

int SnakeNode(int i,int j)
{
      	struct Snake *p;
        p = &node1;
	
	while(p != NULL){
	
	if(p->line == i&& p->list == j){
		return 1;
	}	
	p = p ->next;
	}
	return 0;
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
				}else if(SnakeNode(line,list)){
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
	node1.next = &node2;
	
	node2.next = &node3;
	
	node3.next = &node4;
		
	getch();
	endwin();
	return 0;

	
}
