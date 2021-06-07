#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <stdlib.h>

#include <unistd.h>
#include<poll.h>
 
//int poll(struct poll_fd *fds, nfds_t  nfds, int timeout)

#define UP    1
#define DOWN   -1
#define LEFT  2
#define RIGHT  -2

#define KEYCODE_R 0x43
#define KEYCODE_L 0x44
#define KEYCODE_U 0x41
#define KEYCODE_D 0x42

//初始位置
#define LINE0 1 
#define LIST0 1

struct Snake
{
	int line;
	int list;
	struct Snake *next;
};

struct Snake food ;
struct Snake *head = NULL;
struct Snake *tail = NULL;
int dir;

void initNcurses()
{		
	initscr();
	keypad(stdscr,1);
	noecho();
}

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

int hasFoodNode(int i,int j)
{
	if(food.line == i&& food.list == j){
		return 1;
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
			printw("                            ~By HaHaHa!\n");

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
	p = NULL;
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
	} 
	else{
		deleNode();
	}
	if(ifSnakeDie()){
		initSnake();
	}
}

void funSnake()
{
	moveSnake();
	gameMap();
	refresh();
	usleep(108000);
}

void turn(int direction)
{
	if(abs(dir) != abs(direction))
	{
		dir = direction;
	}
}

void sys_err(const char *str)
{
    perror(str);
    exit(-1);
}

int main(void)
{
	int ret;
	int kfd = STDIN_FILENO;
	char keycode;
	struct timeval tv;

	initNcurses(); 	//curses初始化
	initSnake(); 	
	gameMap();  

	struct pollfd pfd[1];
	pfd[0].fd = kfd;
	pfd[0].events = POLLIN;
	while(1)
	{
		funSnake(); //贪吃蛇前进
		//int poll(struct poll_fd *fds, nfds_t  nfds, int timeout)
		if(poll(pfd, 1, 80) > 0)
		{
			if(pfd[0].revents & POLLIN)
        	{
				if(read(kfd, &keycode, 1) < 0)
				{
					sys_err("read:");
				}
				switch(keycode)
				{
					case KEYCODE_L:
						turn(LEFT);
						break;
					case KEYCODE_R:
						turn(RIGHT);
						break;
					case KEYCODE_U:
						turn(UP);
						break;
					case KEYCODE_D:
						turn(DOWN);
						break;
				}
			}

		}

	}
	getch();
	endwin();
	return 0;
}
