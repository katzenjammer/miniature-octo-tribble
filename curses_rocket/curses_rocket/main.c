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

static void showit(void);
static void cleanup(void);
static void draw_rocket(void);
static short my_bg = COLOR_BLACK;

int main(int argc, const char * argv[])
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    
    draw_rocket();
    cleanup();
    
    return 0;
}

static void draw_rocket(void)
{
    int row = LINES-1;
    int top = 1;
    int left = 1;
    int right = COLS;
    int center = (COLS/2)-1;
    int liftoff = 10;
    
    for (row = LINES-1; row > top-2 ; row--)
    {
       MvPrintw(row-9, (center - 1),  " . ");
       MvPrintw(row-8, (center - 1),  "/ \\");
       MvPrintw(row-7, (center - 1),  ";S:");
       MvPrintw(row-6, (center - 1),  ";P:");
       MvPrintw(row-5, (center - 1),  ";A:");
       MvPrintw(row-4, (center - 1),  ";C:");
       MvPrintw(row-3, (center - 2), " ;E: ");
       MvPrintw(row-2, (center - 2), "-===-");
       MvPrintw(row-1, (center - 1),  "^^^");
       
       if (LINES-1 == row)
       {
          MvPrintw(row,   (center - 2), "|   |");
          for (liftoff = 8; liftoff > 0; liftoff--)
          {
             switch(liftoff)
             {
                case 8 :
                   MvPrintw(row,   (center - 2),       "|   |");
                   showit();
                   break;
                case 7 :
                   MvPrintw(row,   (center - 2),       "|&&&|");
                   showit();
                   break;
                case 6 :
                   MvPrintw(row,   (center - 3),      "&|*#*|&");
                   showit();
                   break;
                case 5 :
                   MvPrintw(row,   (center - 4),     "&&|#*#|&&");
                   showit();
                   break;
                case 4 :
                   MvPrintw(row,   (center - 5),    "&&&|*#*|&&&");
                   showit();
                   break;
                case 3 :
                   MvPrintw(row,   (center - 6),   "&&&&|#*#|&&&&");
                   showit();
                   break;
                case 2 :
                   MvPrintw(row,   (center - 7),  "&&&&&|*#*|&&&&&");
                   showit();
                   break;
                case 1 :
                   MvPrintw(row,   (center - 8), "&&&&&&|#*#|&&&&&&");
                   showit();
                   break;
                default :
                   showit();
                   break;
             }
          }
        
       }
       else if (row % 2)
       {
          MvPrintw(row, (center - 2), " #*# ");
       }
       else
       {
          MvPrintw(row, (center - 2), " *#* ");
       }
       showit();
    }
    
    return;
}

static void showit(void)
{
    int ch;
    napms(300);
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

