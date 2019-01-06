#include "brawl.h"
#include <ncurses.h>
#include <stdlib.h>
#include "level.h"

/* Basic setup for ncurses  */
int initNcurses()
{
    initscr();
    noecho();
    refresh();
    
    return 0;
}

/* If termminal is too small exit with an error code */
int checkTermSize()
{

}

/* Draw the borders for the map, stats, etc. */
Windows * drawBorders(Windows * newWindows)
{
    int y, x;
    getmaxyx(stdscr, y, x);
    
    /* Print map border  */
    newWindows->mapBorder = newwin((y / 5) * 4, (x / 5) * 4, 0, 0);
    box(newWindows->mapBorder, 0, 0);
        
    newWindows->mapWindow = derwin(newWindows->mapBorder, (y / 5) * 4 - 2, (x / 5) * 4 - 2, 1, 1);

    /* Print stats border  */
    newWindows->statsBorder = newwin(y, (x / 5) - 1, 0, (x / 5) * 4 + 1 );
    box(newWindows->statsBorder, 0, 0);

    newWindows->statsWindow = derwin(newWindows->statsBorder, y - 2, (x / 5) - 3, 1, 1);
    
    /* Print printout border  */
    newWindows->printoutBorder = newwin((y / 5) + 4, (x / 5) * 4, (y / 5) * 4, 0);
    box(newWindows->printoutBorder, 0, 0);

    newWindows->printoutWindow = derwin(newWindows->printoutBorder, (y / 5) + 4, (x / 5) * 4, (y / 5) * 4, 0);

    return newWindows;
}

int refreshWindows(Windows *newWindows)
{
    //wprintw(newWindows->mapWindow, "debug");

    wrefresh(newWindows->mapBorder);
    wrefresh(newWindows->statsBorder);
    wrefresh(newWindows->printoutBorder);
    wrefresh(newWindows->mapWindow);
    wrefresh(newWindows->statsWindow);
    wrefresh(newWindows->printoutWindow);

    return 0;
}
