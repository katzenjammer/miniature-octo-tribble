//
//  main.c
//  curses_rocket
//
//  Created by Hal Phillips on 11/9/13.
//  Copyright (c) 2013 Hal Phillips. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>


#define MvAddCh (void) mvaddch
#define MvWAddCh (void) mvwaddch
#define MvAddStr (void) mvaddstr
#define MvWAddStr (void) mvwaddstr
#define MvWAddChStr (void) mvwaddchstr
#define MvPrintw (void) mvprintw
#define MvWPrintw (void) mvwprintw
#define MvHLine (void) mvhline
#define MvWHLine (void) mvwhline
#define MvVLine (void) mvvline
#define MvWVLine (void) mvwvline

#define ExitProgram(code) _nc_free_tinfo(code)

static void showit(int ms);
static void cleanup(void);
static void draw_rocket(void);
static void draw_background(void);
static void animate_truck(void);


int main(int argc, const char * argv[])
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
   
    draw_background();
    draw_rocket();
   
   for (;;)
   {
      MvPrintw((LINES/1.5)-5, (COLS/2)+10, "LIFTOFF!!!");
      showit(1000);
   }
   
    cleanup();
    
    return 0;
}

static void animate_truck(void)
{
   int i = 0;
   
   for (i = -7; i < (COLS/2) - 20; i++)
   {
      MvPrintw(LINES-5,i,  " ,_!p\\_");
      MvPrintw(LINES-4,i,  " ;0---0`");
      showit(100);
   }

   showit(1000);
   
   for (i = (COLS/2) - 13; i < (COLS/2)+1; i++)
   {
      if(i%2)
      {
         MvPrintw(LINES-5,i,  " O");
         MvPrintw(LINES-4,i,  " ^");
         showit(500);
      }
      else
      {
         MvPrintw(LINES-5,i,  " O");
         MvPrintw(LINES-4,i,  " |");
         showit(500);
      }
   }
   return;
}

static void draw_background(void)
{

   int horizon = LINES/1.5;
   int row = 0;
   int i,j = 0;
   int density = 3;
   int feature_length = 8;
   time_t t;

   srand((unsigned) time(&t));

   const char *hills[10] = {
      ".  .  ..",
      "_  _..  ",
      ". .. . ,",
      ".~. ~ ._",
      ".  .,  ,",
      "__   _._",
      " ..  ,   ",
      ",_ . .  ",
      "   ,  . ",
      ".  __  _"};

   
   const char *foreground[10] = {
      "   !    ",
      "      . ",
      "   .    ",
      "        ",
      "  ,    .",
      "     ;  ",
      "+       ",
      "    `   ",
      "       ,",
      "     ^  "};
   
   MvPrintw(3,5, "    _..._    ");
   MvPrintw(4,5, "  .'  o ::.  ");
   MvPrintw(5,5, " : O     ::: ");
   MvPrintw(6,5, " :   .   ::: ");
   MvPrintw(7,5, " `. .   .::' ");
   MvPrintw(8,5, "   `-..:''   ");

   for (i=0; i < COLS; i=i+10)
   {
      j = rand() % 10;
      MvPrintw(horizon, i, "%s", hills[j]);
   }
   
   for (row = horizon+1; row < LINES; row++)
   {
      for (i = 0; i < density; i++)
      {
         j = rand() % COLS-feature_length;
         MvPrintw(row, j, "%s", foreground[j%10]);
 
      }
   }
   
   return;
   
}

static void draw_rocket(void)
{
   int platform_offset = 3;
   int platform = LINES - platform_offset;
   int row = 0;
   int top = 1;
   int center = (COLS/2)-1;
   int liftoff = 0;
   int ms = 200;
    
    for (row = platform; row > top-2 ; row--)
    {
       MvPrintw(row-9, (center - 2), "    .    ");
       MvPrintw(row-8, (center - 2), "   / \\   ");
       MvPrintw(row-7, (center - 2), "   |||   ");
       MvPrintw(row-6, (center - 2), "   |o|   ");
       MvPrintw(row-5, (center - 2), "   |||   ");
       MvPrintw(row-4, (center - 2), "   |o|   ");
       MvPrintw(row-3, (center - 2), "  /|||\\  ");
       MvPrintw(row-2, (center - 2), " --===-- ");
       MvPrintw(row-1, (center - 2), "   ^^^   ");
       
       if (platform == row)
       {
          MvPrintw(row,(center - 2), " ||   || ");
          animate_truck();
          MvPrintw(row-2, (center - 2), " --===-- ");
          MvPrintw(row-1, (center - 2), "   ^^^   ");
          showit(10);
          showit(3000);
          for (liftoff = 10; liftoff > 0; liftoff--)
          {
             switch(liftoff)
             {
                case 10 :
                   MvPrintw(row,   (center - 2),     " || + || ");
                   showit(ms*3);
                   break;
                case 9 :
                   MvPrintw(row,   (center - 2),     " ||+*+|| ");
                   showit(ms*3);
                   break;
                case 8 :
                   MvPrintw(row,   (center - 2),     " ||*#*|| ");
                   showit(ms*3);
                   break;
                case 7 :
                   MvPrintw(row,   (center - 2),     " ||#*#|| ");
                   showit(ms*2);
                   break;
                case 6 :
                   MvPrintw(row,   (center - 2),     "&||*#*||&");
                   showit(ms*2);
                   break;
                case 5 :
                   MvPrintw(row,   (center - 3),    "&&||#*#||&&");
                   showit(ms*2);
                   break;
                case 4 :
                   MvPrintw(row,   (center - 4),   "&&&||*#*||&&&");
                   showit(ms*2);
                   break;
                case 3 :
                   MvPrintw(row,   (center - 5),  "&&&&||#*#||&&&&");
                   showit(ms*2);
                   break;
                case 2 :
                   MvPrintw(row,   (center - 6), "&&&&&||*#*||&&&&&");
                   showit(ms*2);
                   break;
                case 1 :
                   MvPrintw(row,   (center - 7),"&&&&&&||#*#||&&&&&&");
                   showit(ms*2);
                   break;
                default :
                   showit(ms);
                   break;
             }
          }
        
       }
       else if (row % 2)
       {
          MvPrintw(row, (center - 2), "   #*#  ");
       }
       else
       {
          MvPrintw(row, (center - 2), "   *#*  ");
       }
       showit(ms);
    }
    
    return;
}

static void showit(int ms)
{
    int ch;
    napms(ms);
    if ((ch = getch()) != ERR)
    {
#ifdef KEY_RESIZE
        if (ch == KEY_RESIZE)
        {
            erase();
        } else
#endif
            if (ch == 'q')
            {
                cleanup();
                exit(EXIT_SUCCESS);
            } else if (ch == 's') {
                nodelay(stdscr, FALSE);
            } else if (ch == ' ') {
                nodelay(stdscr, TRUE);
            }
    }
}



static void cleanup(void)
{
    curs_set(1);
    endwin();
}

