#include "brawl.h"
#include "level.h"
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>

/* setupLevel -- functions for creating various levels  */

 /*  Eventuaally add randomized rooms and features
 *      Rooms: bathrooms, closets, kitchen, illegal gambling den, dance floor, etc.
 *      Features: tables and chairs, pool tables, stools, etc.
  */


/* Generate the level details; size of bar; etc */
Level * generateLevel(Level * newLevel, int levelNumber)
{
    srand(time(0));
    newLevel->levelNumber = levelNumber;

    newLevel->levelSize = ((rand() % 3  ) + 1 );        // 1=small; 2=med; 3=lrg
    newLevel->barWallGravity = (rand() % 3 );           //0=Top; 1=Right; 2=Bottom; 3=Left
    newLevel->barType = (rand() % 2);                   //0=full bar; 1=3/4; etc
    newLevel->numOfEntrances = ((rand() % 4  ) + 1 );   // 1-4 entrances; put prioity on a wall that is not on the side of the bar
    newLevel->numOfWindows = (rand() % 8 );             // 0-8 windows
    switch(newLevel->levelSize)
    {
        case 1:     //small
            newLevel->numOfActAreas = ((rand() % 2  ) + 1 ); // 1-2 Activity Areas
            newLevel->numOfRooms = (rand() % 1 );            // 0-1 extra rooms
            break;
        case 2:     //medium
            newLevel->numOfActAreas = ((rand() % 3  ) + 2 ); // 2-3 Activity Areas
            newLevel->numOfRooms = (rand() % 2 );            // 0-2 extra rooms
            break;
        case 3:     //large
            newLevel->numOfActAreas = ((rand() % 4  ) + 3 ); // 3-4 Activity Areas
            newLevel->numOfRooms = ((rand() % 3 ) + 1 );     // 1-3 extra rooms
            break;
    }
    
    return newLevel;
}


/* Generate the leval mask to store data for map elements  */
int createLevelMask(Level * newLevel)
{

    return 0;
}

