#include "brawl.h"
#include "level.h"
#include "build_bar.h"
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include <string.h>

/* setupLevel -- functions for creating various levels  */

 /*  Eventuaally add randomized rooms and features
 *      Rooms: bathrooms, closets, kitchen, illegal gambling den, dance floor, etc.
 *      Features: tables and chairs, pool tables, stools, etc.
  */

/* rand --> int x = (rand() % (upper - lower + 1) - lower)  */

/* Generate the level details; size of bar; etc */
Level * generateLevel(Level * newLevel, int levelNumber)
{
    srand(time(0));
    newLevel->levelNumber = levelNumber;                //FIX THIS

    newLevel->levelSize = (rand() % 3);        // 0=small; 1=med; 2=lrg
    newLevel->levelHeight = 40;
    newLevel->levelWidth = 140;

    newLevel->bar = generateBar(newLevel);
    newLevel->levelMask = createLevelMask(newLevel);
    newLevel->levelMask = addBarMask(newLevel);
    
    return newLevel;
}


Bar * generateBar(Level * newLevel)
{
    Bar * newBar;
    newBar = malloc(sizeof(Bar));

    int smallMinWidth, smallMaxWidth, medMinWidth, medMaxWidth, largeMinWidth, largeMaxWidth;
    int smallMinHeight, smallMaxHeight, medMinHeight, medMaxHeight, largeMinHeight, largeMaxHeight;

    smallMinHeight = 10;
    smallMaxHeight = 16;
    smallMinWidth = 24;
    smallMaxWidth = 40;

    medMinHeight = 17;
    medMaxHeight = 24;
    medMinWidth = 41;
    medMaxWidth = 60;
    
    largeMinHeight = 25;
    largeMaxHeight = 30;
    largeMinWidth = 61;
    largeMaxWidth = 92;
    
    srand(time(0));

    newBar->barWallGravity = (rand() % 4 );           //0=Top; 1=Right; 2=Bottom; 3=Left
    newBar->barType = (rand() % 3);                   //0=full bar; 1=3/4; etc
    newBar->numOfEntrances = ((rand() % 2  ) + 1 );   // 1-2 entrances; put prioity on a wall that is not on the side of the bar
    newBar->numOfWindows = (rand() % 7 );             // 0-8 windows
    switch(newLevel->levelSize)
    {
        case 0:     //small
            newBar->numOfActAreas = ((rand() % 2  ) + 1 ); // 1-2 Activity Areas
            newBar->numOfRooms = (rand() % 1 );            // 0-1 extra rooms
            newBar->buildingHeight = ((rand() % (smallMaxHeight - smallMinHeight + 1)) + smallMinHeight);
            newBar->buildingWidth = ((rand() % (smallMaxWidth - smallMinWidth + 1)) + smallMinWidth);

            break;
        case 1:     //medium
            newBar->numOfActAreas = ((rand() % 3  ) + 2 ); // 2-3 Activity Areas
            newBar->numOfRooms = (rand() % 2 );            // 0-2 extra rooms
            newBar->buildingHeight = ((rand() % (medMaxHeight - medMinHeight + 1)) + medMinHeight);
            newBar->buildingWidth = ((rand() % (medMaxWidth -medMinWidth + 1)) + medMinWidth);
            break;
        case 2:     //large
            newBar->numOfActAreas = ((rand() % 4  ) + 3 ); // 3-4 Activity Areas
            newBar->numOfRooms = ((rand() % 3 ) + 1 );     // 1-3 extra rooms
            newBar->buildingHeight = ((rand() % (largeMaxHeight - largeMinHeight + 1)) + largeMinHeight);
            newBar->buildingWidth = ((rand() % (largeMaxWidth - largeMinWidth + 1)) + largeMinWidth);
            break;
    }
    newBar->start_pos.y = ((newLevel->levelHeight - newBar->buildingHeight) / 2);
    newBar->start_pos.x = ((newLevel->levelWidth - newBar->buildingWidth) / 2);
    
    return newBar;
}

/* Generate the leval mask to store data for map elements  */
Tile ** createLevelMask(Level * newLevel)
{
    Tile ** levelMask;

    int x, y;
    levelMask = (Tile **) malloc(sizeof(Tile) * newLevel->levelHeight);
    for (y = 0; y < newLevel->levelHeight; y++)
    {
        levelMask[y] = (Tile **)malloc(sizeof(Tile) * newLevel->levelWidth);
        for (x = 0; x < newLevel->levelWidth; x++)
        {
            strcpy(levelMask[y][x].maskID, "e");
            //mvprintw(y,x,"%s",levelMask[y][x].maskID);
            //getch();
        }
    }
    //newLevel->levelMask = levelMask;
    return levelMask;
}

