#include "brawl.h"
#include "level.h"
#include <time.h>
#include <stdlib.h>

/* setupLevel -- functions for creating various levels  */

/*
 *  -----------------------------------------
 *  |................B......................|
 *  |=============b================..=======|
 *  |.......................................|
 *  |.........@.............................|
 *  |........_....................o___o.....|
 *  |......h(b)h..................|...|.....|
 *  |.............................o...o.....|
 *  |.............................|...|.....|
 *  |.............................o---o.....|
 *  |.......................................|
 *  ---------------------..-----;----;-------
 *  
 *  Eventuaally add randomized rooms and features
 *      Rooms: bathrooms, closets, kitchen, illegal gambling den, dance floor, etc.
 *      Features: tables and chairs, pool tables, stools, etc.
 * */

Level * createLevel(Level * newLevel)
{

    srand(time(0));
    int levelCounter = 0;
    //newLevel->levelNumber = levelCounter++;
    //num = (rand() % (upper – lower + 1)) + lower
    newLevel->levelSize = ((rand() % 3  ) + 1 );        // 1=small; 2=med; 3=lrg
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
        defualt:
            break;
    }
    
    return newLevel;
}
