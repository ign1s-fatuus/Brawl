#ifndef BRAWL_H
#define BRAWL_H
#endif

#include <ncurses.h>

/* Declarations for data types  */

typedef struct Windows
{
    WINDOW * mapBorder;
    WINDOW * mapWindow;
    WINDOW * statsBorder;
    WINDOW * statsWindow;
    WINDOW * printoutBorder;
    WINDOW * printoutWindow;
} Windows;


/* Function Declarations */

int initNcurses();
Windows * drawBorders();
int checkTermSize();
int refreshWindows(Windows * newWindows);
