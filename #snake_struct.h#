/******************************************************************************
 *** @file         : snake_struct.h
 *** @author       :timepe
 *** @date         :Wed Jun 19 21:19:54 2013
 *** 
 *** @description  :  a snake like eat (version 0.1) 
 ***                  some function relate to snake_struct
 *** 
 *** 
 *** 

 *** Copyright (c) 2008,VIA Logistics Management, Inc.
 ******************************************************************************/

#include <curses.h>
#include <stdlib.h>

#define INIT_BODY 4
#define DIR_NEGATIVE -1
#define DIR_POSITIVE 1
#define DIR_DEFAULT 0

#define SNAKE_BODY '*'
#define BLANK      ' '
#define FOOD       '@'

typedef struct Pos{
     int x;
     int y;
} Pos;

typedef struct Snake{
     Pos loc;
     struct Snake *next;
} Snake;

Snake *snake;
Pos food;
int dir_x;
int dir_y;
/*
 * init snake
 */

void snake_init()
{
     int init_x,init_y;
     int i;
     Snake *iter,*new_body;
     init_x = COLS/2;
     init_y = LINES/2;
     
     /* should be carefully with pointer */
     iter = (Snake *)malloc(sizeof(Snake));
     iter->loc.x = init_x;
     iter->loc.y = init_y;
     snake = iter;
     
     for(i=1;i<=INIT_BODY;++i)
     {
	  new_body = (Snake *)malloc(sizeof(Snake));
	  new_body->loc.x = init_x + i;
	  new_body->loc.y = init_y;
	  iter->next=new_body;
	  new_body->next = NULL;
	  iter=new_body;
     }
     dir_x = DIR_NEGATIVE;  //init LEFT
     dir_y = DIR_DEFAULT;
}

void food_create()
{
     int food_posx,food_posy;
     food_posx = rand()%COLS;
     food_posy = rand()%LINES;
     mvaddch(food_posy,food_posx,FOOD);

     food.x = food_posx;
     food.y = food_posy;
     refresh();
}

/*
 * snake eat
 */
void snake_eat(Pos *pos)
{
     Snake *body;
     body=(Snake *)malloc(sizeof(Snake));
     /*put the new node into snake*/
     body->loc.x=pos->x;
     body->loc.y=pos->y;
     body->next=snake;
     snake=body;
}

int snake_move()
{
     Snake *iter,*rear;
     iter = snake;
     while(iter->next->next != NULL)
     {
	  iter = iter->next;
     }
     /* iter: previous node of rear */
     rear = iter->next;
     iter->next = NULL;
     rear->loc.x = snake->loc.x+dir_x;
     rear->loc.y = snake->loc.y+dir_y;

     rear->next = snake;
     snake = rear;
	  
     if(is_collapse_self() || is_collase_wall())
	  return 0;    // collapse;
     else
	  return 1;  //keep moving;
}

void snake_show_or_hide(char c)
{
     Snake *iter;
     iter = snake;
     while(iter != NULL){
	  mvaddch(iter->loc.y,iter->loc.x,c);
	  iter = iter->next;
     }
     refresh();

}
/*
 * snake touch food
 */
int is_touch_food(Pos *food)
{
     Snake *head = snake;
     if(head->loc.x == food->x && head->loc.y == food->y)
	  return 1;
     return 0;
}


/*
 * snake collapse itself
 */

int is_collapse_self()
{
     Snake *iter,*head;
     iter=snake->next; // iteration
     head=snake; // snake head
     while(iter != NULL)
     {
	  /* collapse itself*/
	  if(iter->loc.x == head->loc.x && iter->loc.y == head->loc.y)
	       return 1;
	  iter = iter -> next;
     }
     return 0;
}

/*
 * snake collapse wall
 */

int is_collase_wall()
{
     Snake *head=snake;
     if(head->loc.x >= COLS || head->loc.x <= 0)
	  return 1;
     if(head->loc.y >= LINES || head->loc.y <= 0)
	  return 1;

     return 0;
}
