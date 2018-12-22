#include "brawl.h"
#include <ncurses.h>

/* Basic setup for ncurses  */
int initNcurses()
{
    initscr();
    noecho();
    refresh();
    
    return 0;
}
