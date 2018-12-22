#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "brawl.h"

int main()
{
    initNcurses();
    return 0;
}

void initNcurses()
{
    initscr();
    noecho();
    mvprintw(0,0,"Hello World");
    refresh();
    
    getch();

    endwin();
}
