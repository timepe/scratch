/******************************************************************************
 *** @file         : snake.c
 *** @author       :timepe
 *** @date         :Wed Jun 19 21:44:46 2013
 *** 
 *** @description  :   a snake like eat (version 0.1)
 ***                   main function
 *** 
 *** 
 *** 

 *** Copyright (c) 2008,VIA Logistics Management, Inc.
 ******************************************************************************/

#include <curses.h>
#include <signal.h>
#include <sys/time.h>
#include "snake_struct.h"


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

int set_ticker(int n_msecs)
{
     struct itimerval new_timeset;
     long n_sec,n_usecs;

     n_sec = n_msecs / 1000;
     n_usecs = (n_msecs % 1000) *1000L;

     new_timeset.it_interval.tv_sec = n_sec;
     new_timeset.it_interval.tv_usec = n_usecs;

     new_timeset.it_value.tv_sec = n_sec;
     new_timeset.it_value.tv_usec = n_usecs;

     return setitimer(ITIMER_REAL,&new_timeset,NULL);
}

void snake_show(int signum)
{
     snake_show_or_hide(BLANK);
     if(!snake_move())
     {
	  endwin();
	  exit(0);
     }

     if(is_touch_food(&food))
     {
	  snake_eat(&food);
	  food_create();
     }
     snake_show_or_hide(SNAKE_BODY);
}

int main(void)
{
     char c;
     setup();
     signal(SIGALRM,snake_show);
     set_ticker(200);
     snake_show_or_hide(BLANK);
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
     endwin();
     return 0;
     
}

