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
    newLevel->levelNumber = levelNumber;                //FIX THIS

    newLevel->levelSize = (rand() % 3);        // 0=small; 1=med; 2=lrg
    newLevel->levelHeight = 40;
    newLevel->levelWidth = 140;

    newLevel = generateRandom(newLevel, 50);
    newLevel = generateBar(newLevel);
    newLevel->levelMask = addBarMask(newLevel);
    
    return newLevel;
}


Level * generateBar(Level * newLevel)
{
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

    newLevel->bar->barWallGravity = (rand() % 4 );           //0=Top; 1=Right; 2=Bottom; 3=Left
    newLevel->bar->barType = (rand() % 3);                   //0=full bar; 1=3/4; etc
    newLevel->bar->numOfEntrances = ((rand() % 2  ) + 1 );   // 1-2 entrances; put prioity on a wall that is not on the side of the bar
    newLevel->bar->numOfWindows = (rand() % 7 );             // 0-8 windows
    switch(newLevel->levelSize)
    {
        case 0:     //small
            newLevel->bar->numOfActAreas = ((rand() % 2  ) + 1 ); // 1-2 Activity Areas
            newLevel->bar->numOfRooms = (rand() % 1 );            // 0-1 extra rooms
            newLevel->bar->buildingHeight = ((rand() % (smallMaxHeight - smallMinHeight + 1)) + smallMinHeight);
            newLevel->bar->buildingWidth = ((rand() % (smallMaxWidth - smallMinWidth + 1)) + smallMinWidth);

            break;
        case 1:     //medium
            newLevel->bar->numOfActAreas = ((rand() % 3  ) + 2 ); // 2-3 Activity Areas
            newLevel->bar->numOfRooms = (rand() % 2 );            // 0-2 extra rooms
            newLevel->bar->buildingHeight = ((rand() % (medMaxHeight - medMinHeight + 1)) + medMinHeight);
            newLevel->bar->buildingWidth = ((rand() % (medMaxWidth -medMinWidth + 1)) + medMinWidth);
            break;
        case 2:     //large
            newLevel->bar->numOfActAreas = ((rand() % 4  ) + 3 ); // 3-4 Activity Areas
            newLevel->bar->numOfRooms = ((rand() % 3 ) + 1 );     // 1-3 extra rooms
            newLevel->bar->buildingHeight = ((rand() % (largeMaxHeight - largeMinHeight + 1)) + largeMinHeight);
            newLevel->bar->buildingWidth = ((rand() % (largeMaxWidth - largeMinWidth + 1)) + largeMinWidth);
            break;
    }
    newLevel->bar->start_pos.y = ((newLevel->levelHeight - newLevel->bar->buildingHeight) / 2);
    newLevel->bar->start_pos.x = ((newLevel->levelWidth - newLevel->bar->buildingWidth) / 2);
    
    return newLevel;
}

Level * generateRandom(Level * newLevel, int percentCover)
{
    int i, y, x, rndY, rndX, counter, counterMax, rndDir, rndSeedPts;
    counterMax = ((newLevel->biomeDensity * .01) * (newLevel->levelWidth * newLevel->levelHeight));
    rndSeedPts = ((rand() % (newLevel->biomeMaxSeed - newLevel->biomeMinSeed + 1)) + newLevel->biomeMinSeed);
    counter = 0;
    /* Seed pts for nadomization  */
    for(i =0; i < rndSeedPts; i++)
    {
        rndY = (rand() % newLevel->levelHeight);
        rndX = (rand() % newLevel->levelWidth);
        //newLevel->levelMask[rndY][rndX].tileContents->envmnt = true;      //######## FIX THIS #########
        strcpy(newLevel->levelMask[rndY][rndX].world->maskID, "B"); 
    }
    /*  0 1 2
     *  7 R 3
     *  6 5 4
     * */
    while (counter < counterMax)
    {
        for (y = 0; y < newLevel->levelHeight; y++)
        {
            for(x = 0; x < newLevel->levelWidth; x++)
            {
                if (strcmp(newLevel->levelMask[y][x].world->maskID, "B") == 0)
                {
                    mvprintw(0, newLevel->levelWidth + 4, "%d", counter);
                    rndDir = (rand() % 8);
                    switch(rndDir)
                    {
                        case 0:  
                            if(((y - 1) >= 0) && ((x - 1 ) >= 0) && (strcmp(newLevel->levelMask[y - 1][x - 1].world->maskID, "B") != 0))
                            {
                                strcpy(newLevel->levelMask[y-1][x-1].world->maskID, "B"); 
                                strcpy(newLevel->levelMask[y-1][x-1].world->biome, newLevel->levelBiome); 
                                counter++;
                                //mvprintw(y-1,x-1,"X");
                            }
                        case 1:
                            if(((y - 1) >= 0) && (strcmp(newLevel->levelMask[y - 1][x].world->maskID, "B") != 0))
                            {
                                strcpy(newLevel->levelMask[y-1][x].world->maskID, "B"); 
                                strcpy(newLevel->levelMask[y-1][x].world->biome, newLevel->levelBiome); 
                                counter++;
                                //mvprintw(y-1,x,"X");
                            }
                            break;
                        case 2:
                            if(((y - 1) >= 0) && ((x + 1 ) <= newLevel->levelWidth) && (strcmp(newLevel->levelMask[y - 1][x + 1].world->maskID, "B") != 0))
                            {
                                strcpy(newLevel->levelMask[y-1][x+1].world->maskID, "B"); 
                                strcpy(newLevel->levelMask[y-1][x+1].world->biome, newLevel->levelBiome); 
                                counter++;
                                //mvprintw(y-1,x+1,"X");
                            }
                            break;
                        case 3:
                            if(((x + 1 ) <= newLevel->levelWidth) && (strcmp(newLevel->levelMask[y][x + 1].world->maskID, "B") != 0))
                            {
                                strcpy(newLevel->levelMask[y][x+1].world->maskID, "B"); 
                                strcpy(newLevel->levelMask[y][x+1].world->biome, newLevel->levelBiome); 
                                counter++;
                                //mvprintw(y,x+1,"X");
                            }
                            break;
                        case 4:
                            if(((y + 1) >= newLevel->levelHeight) && ((x + 1 ) <= newLevel->levelWidth) && (strcmp(newLevel->levelMask[y + 1][x + 1].world->maskID, "B") != 0))
                            {
                                strcpy(newLevel->levelMask[y+1][x+1].world->maskID, "B"); 
                                strcpy(newLevel->levelMask[y+1][x+1].world->biome, newLevel->levelBiome); 
                                counter++;
                                //mvprintw(y+1,x+1,"X");
                            }
                            break;
                        case 5:
                            if(((y + 1) >= newLevel->levelHeight) && (strcmp(newLevel->levelMask[y + 1][x].world->maskID, "B") != 0))
                            {
                                strcpy(newLevel->levelMask[y+1][x].world->maskID, "B"); 
                                strcpy(newLevel->levelMask[y+1][x].world->biome, newLevel->levelBiome); 
                                counter++;
                                //mvprintw(y+1,x,"X");
                            }
                            break;
                        case 6:
                            if(((y + 1) >= newLevel->levelHeight) && ((x - 1 ) >= 0) && (strcmp(newLevel->levelMask[y + 1][x - 1].world->maskID, "B") != 0))
                            {
                                strcpy(newLevel->levelMask[y+1][x-1].world->maskID, "B"); 
                                strcpy(newLevel->levelMask[y+1][x-1].world->biome, newLevel->levelBiome); 
                                counter++;
                                //mvprintw(y+1,x-1,"X");
                            }
                            break;
                        case 7:
                            if(((x - 1 ) >= 0) && (strcmp(newLevel->levelMask[y][x - 1].world->maskID, "B") != 0))
                            {
                                strcpy(newLevel->levelMask[y][x-1].world->maskID, "B"); 
                                strcpy(newLevel->levelMask[y][x-1].world->biome, newLevel->levelBiome); 
                                counter++;
                                //mvprintw(y,x-1,"X");
                            }
                            break;
                        default:
                            break;
                    }
                    //getch();
                }
            }
        }
    }
    return newLevel;
}

Level * updateWorldTile(Level * newLevel)
{

}
