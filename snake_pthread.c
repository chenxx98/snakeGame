#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define UP    1
#define DOWN   -1
#define LEFT  2
#define RIGHT  -2

//initial position
#define LINE0 1 
#define LIST0 1

struct Snake
{
	int line; //行、列
	int list;
	struct Snake *next;
};

struct Snake food ;
struct Snake *head = NULL;
struct Snake *tail = NULL;
int dir;
/* 初始化curses库 */
void initNcurses()
{	
	initscr();
	keypad(stdscr,1);
	noecho();
}
/* 蛇节点检测 */
int hasSnakeNode(int i,int j)
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
/* 食物节点检测 */
int hasFoodNode(int i,int j)
{
	if(food.line == i&& food.list == j){
		return 1;
	}	
	return 0;
}
/* 游戏地图绘制 */
void  gameMap(void)
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
				}else if(hasSnakeNode(line,list)){
							printw("[]");
				}else if(hasFoodNode(line,list)){
						printw("##");
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

void addNode(void)
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


void initFood()
{
	int x = rand()%20;
    int y = rand()%20;	
	food.line = x;
	food.list = y;	
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
	head->line = LINE0;
	
	head->list = LIST0;
	
	initFood();
	
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
int ifSnakeDie()
{
	struct Snake *p;
	p = head;
	
	if(tail->line<0 || tail->list ==0 || tail->line==20 || tail->list==20){
	
	return 1;
	}
	
	while(p->next != NULL){
		if(p->line == tail->line && p->list == tail->list){

		return 1;
	
		}
		p =p->next;
	}
	
	return 0;

}
void moveSnake()
{
	addNode();
        if(hasFoodNode(tail->line,tail->list)){
		initFood();
	} else{
        deleNode();
	}
	
	if(ifSnakeDie()){
	
	initSnake();

	}
	
}
void* fun1()
{
	while(1){
		
			moveSnake();
			gameMap();

			refresh();
			usleep(108000);
		//        sleep(1);
	}	
}

void turn(int direction)
{
	if(abs(dir) != abs(direction)){

		dir = direction;

	}
}

void* fun2()
{
	int key;
	while(1){
		key = getch();
		switch(key){
			case KEY_DOWN:
				
				turn(DOWN);
				break;
			case KEY_UP:

				turn(UP);
				break;
			case KEY_LEFT:
				
				turn(LEFT);
				break;
			case KEY_RIGHT:
				
				turn(RIGHT);
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
