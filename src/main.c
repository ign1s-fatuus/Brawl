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

    //newLevel->levelMask = createLevelMask(newLevel); 
    
    //Windows * gameWindows = malloc(sizeof(Windows));
    //gameWindows = drawBorders();
    //refreshWindows(gameWindows);
    
    printData(newLevel);
    getch();

    endwin();
    return 0;
}

int printData(Level * newLevel)
{
    printw("Level number is: %d\n",newLevel->levelNumber);
    printw("Level size is: %d\n\n",newLevel->levelSize);
    
    printw("Bar building height is: %d\n", newLevel->bar->buildingHeight);
    printw("Bar building width is: %d\n", newLevel->bar->buildingWidth);
    printw("Bar starting position is: %d, %d\n", newLevel->bar->start_pos.y, newLevel->bar->start_pos.x);
    printw("Bar Gravity is: %d\n",newLevel->bar->barWallGravity);
    printw("Bar type is: %d\n",newLevel->bar->barType);
    printw("Number of rooms is: %d\n",newLevel->bar->numOfRooms);
    printw("Numbe of enrances: %d\n",newLevel->bar->numOfEntrances);
    printw("Number of windows: %d\n",newLevel->bar->numOfWindows);
    printw("Number of activity areas: %d\n",newLevel->bar->numOfActAreas);

    return 0;
}
