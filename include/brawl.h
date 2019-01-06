#ifndef BRAWL_H
#define BRAWL_H
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/* Declarations for data types  */

typedef struct Coordinates
{
    int x;
    int y;
} Coordinates;

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
Windows * drawBorders(Windows * newWindows);
int checkTermSize();
int refreshWindows(Windows * newWindows);

#endif
