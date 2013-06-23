/******************************************************************************
 *** @file         : snake_processes.c
 *** @author       :timepe
 *** @date         :Sun Jun 23 15:56:56 2013
 *** 
 *** @description  :  process version of snake .
 ***                  compile with gcc : add -lpthread -lcurses
 ***                  set usleep(200),it's too fast that can't show snake 
 ***                  
 *** 

 *** Copyright (c) 2008,VIA Logistics Management, Inc.
 ******************************************************************************/

#include <curses.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include "snake_struct.h"

void* snake_show(void *);

void setup()
{

     initscr();
     clear();
     noecho();
     crmode();
     curs_set(0);
     
     snake_init();
     food_create();
     snake_show_or_hide(SNAKE_BODY);
}

void* snake_show(void* msg)
{
     while(1)
     {
	  usleep(200*1000);
	  snake_show_or_hide(BLANK);
	  if( !snake_move())
	  {
	       endwin();
	       exit(0);
	  }
	  if(is_touch_food(&food)){
	       snake_eat(&food);
	       food_create();
	  }
	  snake_show_or_hide(SNAKE_BODY);
     }
}

int main(void)
{
     char c;
     pthread_t msg_thread;
     setup();
     if(pthread_create(&msg_thread,NULL,snake_show,NULL)){
	  endwin();
	  exit(1);
     }
     while(1)
     {
	  c= getch();
	  if(c== 'q') break;
	  if(c== 's' && dir_y == DIR_DEFAULT) {

	       dir_x = DIR_DEFAULT;
	       dir_y = DIR_POSITIVE;
	  }
	  if(c== 'w' && dir_y == DIR_DEFAULT){
	       dir_x = DIR_DEFAULT;
	       dir_y = DIR_NEGATIVE;   
	  }
	  if(c == 'a' && dir_x == DIR_DEFAULT){
	       dir_x = DIR_NEGATIVE;
	       dir_y = DIR_DEFAULT;
	  }
	  if(c == 'd' && dir_x == DIR_DEFAULT){
	       dir_x = DIR_POSITIVE;
	       dir_y = DIR_DEFAULT;
	  }
	  
     }
     pthread_cancel(msg_thread);
     endwin();
     return 0;
}


