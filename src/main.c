#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "brawl.h"
#include <time.h>
#include "level.h"


/* Dclaration of functions */
Level * createLevel(Level * newLevel);
int main()
{
    initNcurses();
    
    Level * newLevel;
    newLevel = malloc(sizeof(Level));
    newLevel = createLevel(newLevel);
    

    printw("Level number is: %d\n",newLevel->levelNumber);
    printw("Level size is: %d\n",newLevel->levelSize);
    printw("Number of rooms is: %d\n",newLevel->numOfRooms);
    printw("Numbe of enrances: %d\n",newLevel->numOfEntrances);
    printw("Number of windows: %d\n",newLevel->numOfWindows);
    printw("Number of activity areas: %d\n",newLevel->numOfActAreas);
    getch();

    endwin();
    return 0;
}
