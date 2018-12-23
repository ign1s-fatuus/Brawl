#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "brawl.h"
#include <time.h>
#include "level.h"

int printData(Level * newLevel);

int main()
{
    initNcurses();
    
    Level * newLevel;
    newLevel = malloc(sizeof(Level));
    newLevel = generateLevel(newLevel, 1);

    newLevel->levelMask = createLevelMask(newLevel); 
    
    //Windows * gameWindows = malloc(sizeof(Windows));
    //gameWindows = drawBorders();
    //refreshWindows(gameWindows);
    
    getch();

    endwin();
    return 0;
}

int printData(Level * newLevel)
{
    printw("Level number is: %d\n",newLevel->levelNumber);
    printw("Level size is: %d\n",newLevel->levelSize);
    printw("Bar Gravity is: %d\n",newLevel->barWallGravity);
    printw("Bar type is: %d\n",newLevel->barType);
    printw("Number of rooms is: %d\n",newLevel->numOfRooms);
    printw("Numbe of enrances: %d\n",newLevel->numOfEntrances);
    printw("Number of windows: %d\n",newLevel->numOfWindows);
    printw("Number of activity areas: %d\n",newLevel->numOfActAreas);

    return 0;
}
