#include <curses.h>
#include <stdlib.h>

struct Snake
{
	int line; //行、列
	int list;
	struct Snake *next;

};

struct Snake *head; //头节点
struct Snake *tail; //尾节点
/* 初始化curses库 */
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

void addNode()
{
	struct Snake *new = (struct Snake *)malloc(sizeof(struct Snake));

	new->li
	ne = tail->line;
	new->list = tail->list+1;
	new->next = NULL;
	tail->next= new;
	tail = new;

}


void initSnake()
{
	head = (struct Snake *)malloc(sizeof(struct Snake));
	head->line =2;
	head->list =2;
	head->next = NULL;	
	tail = head;
	addNode();
	addNode();
	addNode();
}

int main()
{	
	initNcurses();
	initSnake();
	gameMap();
			
	getch();
	endwin();
	return 0;
}
