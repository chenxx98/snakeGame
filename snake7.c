#include <curses.h>
#include <stdlib.h>

#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4


struct Snake
{
	int line;
	int list;
	struct Snake *next;

};

struct Snake *head = NULL;
struct Snake *tail = NULL;
int dir;


void initNcurses()
{
		
	initscr();
	keypad(stdscr,1);
}

int SnakeNode(int i,int j)
{
      	struct Snake *p;
        p = head;
	
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
	move(0,0);	
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
			printw("                           ~By ChenChen!\n");
		
		}

	}

}

void addNode()
{
	struct Snake *new = (struct Snake *)malloc(sizeof(struct Snake));

	new->line = tail->line;
	new->list = tail->list+1;

	new->next = NULL;
	
	switch(dir){
		case UP:
			new->line = tail->line-1;
			new->list = tail->list;
			break;
	
		case DOWN:
			new->line = tail->line+1;
			new->list = tail->list;
			break;
	
		case LEFT:
			new->line = tail->line;
			new->list = tail->list-1;
			break;
		case RIGHT:
			new->line = tail->line;
			new->list = tail->list+1;
			break;
	}


	tail->next= new;
	tail = new;

}


void initSnake()
{
	dir = RIGHT;		
	struct Snake *p;
	while(head != NULL){
	
		p = head;
		head = head->next;
		free(p);
	}
	
	head = (struct Snake *)malloc(sizeof(struct Snake));
	head->line =2;
	head->list =2;
	head->next = NULL;	
	

	tail = head;

	addNode();
	addNode();
}

void deleNode()
{
	struct Snake *p;
	p = head;
	head = head->next;
	
	free(p);

}

void moveSnake()
{
	addNode();
        deleNode();
	
	if(tail->line==0 || tail->list ==0 || tail->line==20 || tail->list==20){
	
	initSnake();

	}
	
}
void* fun1()
{
	while(1){
		
			moveSnake();
			gameMap();

			refresh();
			usleep(100000);
		
	}	
}

void* fun2()
{
	int key;
	while(1){
		key = getch();
		switch(key){
			case KEY_DOWN:
				
				dir = DOWN;
				break;
			case KEY_UP:

				dir = UP;
				break;
			case KEY_LEFT:
				
				dir = LEFT;
				break;
			case KEY_RIGHT:
				
				dir = RIGHT;
				break;
		}
	
	
	}



}
int main()
{
	
	initNcurses();
	initSnake();
	gameMap();	
	
	pthread_t th1;
	pthread_t th2;
	pthread_create(&th1,NULL,fun1,NULL);
	pthread_create(&th2,NULL,fun2,NULL);
	

	
	while(1);
	
	
		
	getch();
	endwin();
	return 0;

	
}
