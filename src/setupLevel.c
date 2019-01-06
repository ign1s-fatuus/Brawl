#include "brawl.h"
#include "level.h"
#include "build_bar.h"
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include <string.h>
#include "perlin.h"

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

    newLevel = generateHeightMap(newLevel);
    newLevel = generateBiome2(newLevel);
    //newLevel = generateBiome(newLevel);
    //newLevel = generateTerrain(newLevel);
    newLevel = generateBar(newLevel);
    newLevel->levelMask = addBarMask(newLevel);
    newLevel = getStartingPosition(newLevel);
    
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

Level * generateHeightMap(Level * newLevel)
{
    int y, x;
    double tempArray[newLevel->levelHeight + 1][newLevel->levelWidth + 1];
    
    int rndSeed = (rand() % (99999 + 1 - 10000) + 10000);

    for(y = 0; y <= newLevel->levelHeight; y++) 
    {
        for(x = 0; x <= newLevel->levelWidth; x++) 
        {
            tempArray[y][x] = pnoise2d(x * newLevel->perlinFreq, y * newLevel->perlinFreq, newLevel->perlinPersist, 8, rndSeed);
            //tempArray[y][x] = pnoise2d(x * 0.07, y * 0.07, 0.7, 8, rndSeed);
            //printw("%f", tempArray[y][x]);
            //getch();
            newLevel->levelMask[y][x].terrain->height = (int)((tempArray[y][x] + 1) * 4);
            if(newLevel->levelMask[y][x].terrain->height < 0)
                newLevel->levelMask[y][x].terrain->height = 0;
            if(newLevel->levelMask[y][x].terrain->height > 9)
                newLevel->levelMask[y][x].terrain->height = 9;
        }
    }

    return newLevel;
}

Level * generateBiome2(Level * newLevel)
{
    int y, x, b, rndDir;
    
    /* default all tiles to dirt -- rethink this to come up with a more dynamic option  */
    for (y = 0; y <= newLevel->levelHeight; y++)
    {
        for (x = 0; x <= newLevel->levelWidth; x++)
        {
            newLevel = updateTerrain(y, x, true, 1001, newLevel);
        }
    }

    /* populate terrain via height map  */
    for (b = 9; b  >= 0; b--)
    {
        for (y = 0; y <= newLevel->levelHeight; y++)
        {
            for (x = 0; x <= newLevel->levelWidth; x++)
            {
                    if (newLevel->levelMask[y][x].terrain->height == b)
                    switch (newLevel->levelBiomeID)
                    {
                        case 0:         // dersert
                            switch (b)
                            {
                                case 9:
                                    newLevel = updateTerrain(y, x, true, 1003, newLevel);    
                                    break;
                                case 8:
                                    newLevel = updateTerrain(y, x, true, 1003, newLevel);   
                                    break;
                                case 7:
                                    newLevel = updateTerrain(y, x, true, 1003, newLevel);  
                                    break;
                                case 6:
                                    newLevel = weightedRandomTerrain(y, x, 90, 50, 1003, 1003, newLevel);
                                    break;
                                case 5:
                                    newLevel = weightedRandomTerrain(y, x, 80, 40, 1003, 1003, newLevel);
                                    break;
                                case 4:
                                    newLevel = weightedRandomTerrain(y, x, 70, 30, 1003, 1003, newLevel);
                                    break;
                                case 3:
                                    newLevel = weightedRandomTerrain(y, x, 40, 20, 1006, 1006, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.006, 0.001, 1006, 2006, newLevel);
                                    break;
                                case 2:
                                    newLevel = weightedRandomTerrain(y, x, 60, 30, 1006, 1006, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.007, 0.001, 1006, 2006, newLevel);
                                    break;
                                case 1:
                                    newLevel = weightedRandomTerrain(y, x, 80, 50, 1006, 1006, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.0085, 0.002, 1006, 2006, newLevel);
                                    break;
                                case 0:
                                    newLevel = weightedRandomTerrain(y, x, 90, 60, 1006, 1006, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.009, 0.003, 1006, 2006, newLevel);
                                    break;
                            }
                            break;
                        case 1:         // forest
                            switch (b)
                            {
                                case 9:
                                    newLevel = weightedRandomTerrain(y, x, 30, 20, 1004, 1004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.001, 0.001, 1001, 2005, newLevel);
                                    break;
                                case 8:
                                    newLevel = weightedRandomTerrain(y, x, 20, 10, 1004, 1004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.001, 0.001, 1001, 2005, newLevel);
                                    break;
                                case 7:
                                    newLevel = weightedRandomTerrain(y, x, 10, 5, 1004, 1004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.001, 0.001, 1001, 2005, newLevel);
                                    break;
                                case 6:
                                    newLevel = weightedRandomTerrain(y, x, 20, 10, 1001, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.03, 0.02, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.03, 0.02, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.001, 0.001, 1001, 2005, newLevel);
                                    break;
                                case 5:
                                    newLevel = weightedRandomTerrain(y, x, 30, 20, 1001, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.03, 0.02, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.03, 0.02, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.001, 0.001, 1001, 2005, newLevel);
                                    break;
                                case 4:
                                    newLevel = weightedRandomTerrain(y, x, 40, 30, 1001, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.001, 0.001, 1001, 2005, newLevel);
                                    break;
                                case 3:
                                    newLevel = weightedRandomTerrain(y, x, 50, 35, 1001, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.001, 0.001, 1001, 2005, newLevel);
                                    break;
                                case 2:
                                    newLevel = weightedRandomTerrain(y, x, 60, 40, 1001, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.006, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.006, 1001, 2004, newLevel);
                                    break;
                                case 1:
                                    newLevel = weightedRandomTerrain(y, x, 70, 50, 1001, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.005, 0.0025, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.005, 0.0025, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.005, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.005, 1001, 2004, newLevel);
                                    break;
                                case 0:
                                    newLevel = weightedRandomTerrain(y, x, 80, 60, 1001, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.002, 0.001, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.002, 0.001, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2004, newLevel);
                                    break;
                            }
                            break;
                        case 2:         // tundra
                            switch (b)
                            {
                                case 9:
                                    newLevel = weightedRandomTerrain(y, x, 99, 80, 1004, 1004, newLevel);
                                    break;
                                case 8:
                                    newLevel = weightedRandomTerrain(y, x, 99, 80, 1004, 1004, newLevel);
                                    break;
                                case 7:
                                    newLevel = weightedRandomTerrain(y, x, 90, 80, 1004, 1004, newLevel);
                                    break;
                                case 6:
                                    newLevel = weightedRandomTerrain(y, x, 90, 75, 1004, 1004, newLevel);
                                    break;
                                case 5:
                                    newLevel = weightedRandomTerrain(y, x, 80, 65, 1004, 1004, newLevel);
                                    break;
                                case 4:
                                    newLevel = weightedRandomTerrain(y, x, 75, 55, 1004, 1004, newLevel);
                                    break;
                                case 3:
                                    newLevel = weightedRandomTerrain(y, x, 10, 5, 1004, 1004, newLevel);
                                    break;
                                case 2:
                                    newLevel = weightedRandomTerrain(y, x, 5, 1, 1004, 1004, newLevel);
                                    break;
                                case 1:
                                    newLevel = weightedRandomTerrain(y, x, 1, 1, 1004, 1004, newLevel);
                                    break;
                                case 0:
                                    newLevel = weightedRandomTerrain(y, x, 0, 0, 1004, 1004, newLevel);
                                    break;
                            }
                            break;
                        case 3:         // prairie
                            switch (b)
                            {
                                case 9:
                                    newLevel = weightedRandomTerrain(y, x, 99, 80, 1002, 1002, newLevel);
                                    break;
                                case 8:
                                    newLevel = weightedRandomTerrain(y, x, 95, 80, 1002, 1002, newLevel);
                                    break;
                                case 7:
                                    newLevel = weightedRandomTerrain(y, x, 85, 70, 1002, 1002, newLevel);
                                    break;
                                case 6:
                                    newLevel = weightedRandomTerrain(y, x, 80, 60, 1002, 1002, newLevel);
                                    break;
                                case 5:
                                    newLevel = weightedRandomTerrain(y, x, 75, 50, 1002, 1002, newLevel);
                                    break;
                                case 4:
                                    newLevel = weightedRandomTerrain(y, x, 70, 40, 1002, 1002, newLevel);
                                    break;
                                case 3:
                                    newLevel = weightedRandomTerrain(y, x, 65, 35, 1002, 1002, newLevel);
                                    break;
                                case 2:
                                    newLevel = weightedRandomTerrain(y, x, 60, 30, 1002, 1002, newLevel);
                                    break;
                                case 1:
                                    newLevel = weightedRandomTerrain(y, x, 35, 15, 1002, 1002, newLevel);
                                    break;
                                case 0:
                                    newLevel = weightedRandomTerrain(y, x, 30, 10, 1002, 1002, newLevel);
                                    break;
                            }
                            break;
                        case 4:         // swamp
                            switch (b)
                            {
                                case 9:
                                    newLevel = weightedRandomTerrain(y, x, 75, 60, 1002, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2001, newLevel);
                                    newLevel = weightedRandomTerrainLlgObj(y , x, 1, 1, 1002, 2003, newLevel);
                                    newLevel = weightedRandomTerrainLlgObj(y , x, 1, 1, 1002, 2004, newLevel);
                                    newLevel = weightedRandomTerrainLlgObj(y , x, 1, 1, 1002, 2001, newLevel);
                                    break;
                                case 8:
                                    newLevel = weightedRandomTerrain(y, x, 70, 55, 1002, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2001, newLevel);
                                    break;
                                case 7:
                                    newLevel = weightedRandomTerrain(y, x, 65, 50, 1002, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2001, newLevel);
                                    break;
                                case 6:
                                    newLevel = weightedRandomTerrain(y, x, 60, 45, 1002, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2001, newLevel);
                                    break;
                                case 5:
                                    newLevel = weightedRandomTerrain(y, x, 55, 40, 1002, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.005, 0.005, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.005, 0.005, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.005, 0.005, 1002, 2001, newLevel);
                                    break;
                                case 4:
                                    newLevel = weightedRandomTerrain(y, x, 30, 20, 1005, 1005, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.005, 0.005, 1005, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.005, 0.005, 1005, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.005, 0.005, 1005, 2001, newLevel);
                                    break;
                                case 3:
                                    newLevel = weightedRandomTerrain(y, x, 50, 30, 1005, 1005, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.003, 0.005, 1005, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.003, 0.005, 1005, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.002, 0.001, 1005, 2001, newLevel);
                                    break;
                                case 2:
                                    newLevel = weightedRandomTerrain(y, x, 75, 40, 1005, 1005, newLevel);
                                    break;
                                case 1:
                                    newLevel = updateTerrain(y, x, true, 1007, newLevel);
                                    break;
                                case 0:
                                    newLevel = updateTerrain(y, x, true, 1008, newLevel);
                                    break;
                            }
                            break;
                        case 5:         // mountain
                            switch (b)
                            {
                                case 9:
                                    newLevel = weightedRandomTerrain(y, x, 90, 70, 1004, 1004, newLevel);
                                    break;
                                case 8:
                                    newLevel = weightedRandomTerrain(y, x, 80, 50, 1004, 1004, newLevel);
                                    break;
                                case 7:
                                    newLevel = weightedRandomTerrain(y, x, 60, 40, 1004, 1004, newLevel);
                                    break;
                                case 6:
                                    newLevel = weightedRandomTerrain(y, x, 50, 30, 1004, 1004, newLevel);
                                    break;
                                case 5:
                                    newLevel = weightedRandomTerrain(y, x, 30, 10, 1004, 1004, newLevel);
                                    break;
                                case 4:
                                    newLevel = weightedRandomTerrain(y, x, 10, 5, 1004, 1004, newLevel);
                                    break;
                                case 3:
                                    newLevel = weightedRandomTerrain(y, x, 5, 5, 1004, 1004, newLevel);
                                    break;
                                case 2:
                                    newLevel = weightedRandomTerrain(y, x, 20, 10, 1001, 1002, newLevel);
                                    break;
                                case 1:
                                    newLevel = weightedRandomTerrain(y, x, 30, 15, 1001, 1002, newLevel);
                                    break;
                                case 0:
                                    newLevel = weightedRandomTerrain(y, x, 60, 20, 1001, 1002, newLevel);
                                    break;
                            }
                            break;
                    }
            }
        }
    }

    return newLevel;
}

Level * weightedRandomTerrain(int y, int x, int wghtpercent, int defpercent, int objectidmatch, int terraintypeadd, Level * newlevel)
{
    if ((y - 1 >= 0) && (y + 1 <= newlevel->levelHeight) && (x - 1 >= 0) && (x + 1 <= newlevel->levelWidth))    //fix this !!! creates a border of dirt around the entire map !!!
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                if ((newlevel->levelMask[y + i][x + j].terrain->objectID == objectidmatch) || (newlevel->levelMask[y - i][x - j].terrain->objectID == objectidmatch) || (newlevel->levelMask[y - i][x + j].terrain->objectID == objectidmatch) || (newlevel->levelMask[y + i][x - j].terrain->objectID == objectidmatch))
                {
                    if ((rand() % 101) < wghtpercent)
                    {
                        newlevel = updateTerrain(y, x, true, terraintypeadd, newlevel); 
                    }
                }
                else
                {
                    if ((rand() % 101) == defpercent)
                    {
                        newlevel = updateTerrain(y, x, true, terraintypeadd, newlevel);
                    }
                }
            }
        }
    }
    return newlevel;
}

/* If terrain == terrainIdMatch then use random percent given, else use other percentage  */
Level * weightedRandomTerrainLlgObj(int y, int x, int wghtPercent, int defPercent, int terrainIdMatch, int objectTypeAdd, Level * newlevel)
{
    int rndNum;
    if (!newlevel->levelMask[y][x].tileContents->lgObject)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                if ((newlevel->levelMask[y][x].terrain->objectID == terrainIdMatch))
                {
                    if ((rndNum =(rand() % 101)) < wghtPercent)
                    {
                        newlevel = updateLgObject(y, x, true, objectTypeAdd, newlevel); 
                        //mvprintw(0, newlevel->levelWidth + 2,"%d",rndNum);
                        //getch();
                    }
                }
                else
                {
                    if ((rand() % 101) == defPercent)
                    {
                        newlevel = updateLgObject(y, x, true, objectTypeAdd, newlevel);
                    }
                }
            }
        }
    }
    return newlevel;
}

/* for instances where percentage is < 1  */
Level * weightedFractTerrainLlgObj(int y, int x, double wghtPercent, double defPercent, int terrainIdMatch, int objectTypeAdd, Level * newlevel)
{
    double rndNum;
    if (!newlevel->levelMask[y][x].tileContents->lgObject)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                if ((newlevel->levelMask[y][x].terrain->objectID == terrainIdMatch))
                {
                    if ((rndNum = (double) rand() / (RAND_MAX)) < wghtPercent)
                    {
                        newlevel = updateLgObject(y, x, true, objectTypeAdd, newlevel); 
                        //mvprintw(0, newlevel->levelWidth + 2,"%f",rndNum);
                        //getch();
                    }
                }
                else
                {
                    if ((rndNum = (double) rand() / (RAND_MAX)) < defPercent)
                    {
                        newlevel = updateLgObject(y, x, true, objectTypeAdd, newlevel);
                    }
                }
            }
        }
    }
    return newlevel;
}

Level * updateBiome(int y, int x, bool hasBiome, Level * newLevel)
{
    if(hasBiome)
    {
        strcpy(newLevel->levelMask[y][x].world->maskID, "B");
        strcpy(newLevel->levelMask[y][x].world->biome, newLevel->levelBiome);
        newLevel->levelMask[y][x].tileContents->biome = true;
    }
    else
    {
        strcpy(newLevel->levelMask[y][x].world->maskID, "\0");
        strcpy(newLevel->levelMask[y][x].world->biome, "\0");
        newLevel->levelMask[y][x].tileContents->biome = false;
    }
    return newLevel;
}

Level * generateTerrain(Level * newLevel)
{
    int y, x, counter, counterPriTrnObj, counterSecTrnObj, counterPriTrn, counterSecTrn, biomeCount;
    counter = 0;

    biomeCount = ((newLevel->biomeDensity * .01) * (newLevel->levelWidth * newLevel->levelHeight));
    
    counterPriTrnObj = ((newLevel->envPriTrnObjDensity * .01) * biomeCount);
    counterSecTrnObj = ((newLevel->envSecTrnObjDensity * .01) * biomeCount);
    counterPriTrn = ((newLevel->envPriTrnDensity * .01) * biomeCount);
    counterSecTrn = ((newLevel->envSecTrnDensity * .01) * biomeCount);
    

    /* Generate Primary Terrain */
    while(counter <= counterPriTrn)
    {
        for(y = 0; y <= newLevel->levelHeight; y++)
        {
            for(x = 0; x <= newLevel->levelWidth; x++)
            {
                if(!(rand() % 5) && (newLevel->levelMask[y][x].tileContents->biome) && (!newLevel->levelMask[y][x].tileContents->terrain) && (counter <= counterPriTrn))
                {
                    mvprintw(y, x, "P");
                    mvprintw(1, newLevel->levelWidth + 4, "biome density is: %d", biomeCount);
                    mvprintw(2, newLevel->levelWidth + 4, "Primary Terrain");
                    mvprintw(3, newLevel->levelWidth + 4, "Counter Max is: %d", counterPriTrn);
                    mvprintw(4, newLevel->levelWidth + 4, "Exit count is: %d", counter);
                    switch(newLevel->levelBiomeID)
                    {
                        case 0:     // desert
                            newLevel = updateTerrain(y, x, true, 1003, newLevel);   // sand
                            counter++;
                            break;
                        case 1:     // forest
                            newLevel = updateTerrain(y, x, true, 1001, newLevel);   // dirt
                            counter++;
                            break;
                        case 2:     // tundra
                            newLevel = updateTerrain(y, x, true, 1004, newLevel);   // snow
                            counter++;
                            break;
                        case 3:     //prairie
                            newLevel = updateTerrain(y, x, true, 1002, newLevel);   // grass
                            counter++;
                            break;
                        case 4:     // swamp
                            newLevel = updateTerrain(y, x, true, 1005, newLevel);   //swamp
                            counter++;
                            break;
                        case 5:     //mountain
                            newLevel = updateTerrain(y, x, true, 1001, newLevel);   // dirt
                            counter++;
                            break;
                    }
                }
            }
        }
    }
    

    getch();
    // Generate Secondary Terrain //

    counter = 0;

    while(counter <= counterSecTrn)
    {
        for(y = 0; y <= newLevel->levelHeight; y++)
        {
            for(x = 0; x <= newLevel->levelWidth; x++)
            {
                if(!(rand() % 5) && (newLevel->levelMask[y][x].tileContents->biome) && (!newLevel->levelMask[y][x].tileContents->terrain) && (counter <= counterSecTrn))
                {
                    mvprintw(y, x, "S");
                    mvprintw(7, newLevel->levelWidth + 4, "Secondary Terrain");
                    mvprintw(8, newLevel->levelWidth + 4, "Counter Max is: %d", counterSecTrn);
                    mvprintw(9, newLevel->levelWidth + 4, "Exit count is: %d", counter);
                    mvprintw(10, newLevel->levelWidth + 4, "Spaces left is: %d", biomeCount - counterPriTrn);
                    //getch();
                    switch(newLevel->levelBiomeID)
                    {
                        case 0:     // desert
                            newLevel = updateTerrain(y, x, true, 1001, newLevel);   // dirt
                            counter++;
                            break;
                        case 1:     // forest
                            newLevel = updateTerrain(y, x, true, 1002, newLevel);   // grass
                            counter++;
                            break;
                        case 2:     // tundra
                            newLevel = updateTerrain(y, x, true, 1001, newLevel);   // dirt
                            counter++;
                            break;
                        case 3:     //prairie
                            newLevel = updateTerrain(y, x, true, 1001, newLevel);   // dirt
                            counter++;
                            break;
                        case 4:     // swamp
                            newLevel = updateTerrain(y, x, true, 1002, newLevel);   // grass
                            counter++;
                            break;
                        case 5:     //mountain
                            newLevel = updateTerrain(y, x, true, 1004, newLevel);   // snow
                            counter++;
                            break;
                    }
                }
            }
        }
    }
    getch();    
    // Generate Primary Terrain objects  //
    
    counter = 0;
    
    while(counter <= counterPriTrnObj)
    {
        for(y = 0; y <= newLevel->levelHeight; y++)
        {
            for(x = 0; x <= newLevel->levelWidth; x++)
            {
                if(!(rand() % 25) && (newLevel->levelMask[y][x].tileContents->biome) && (!newLevel->levelMask[y][x].tileContents->lgObject) && (counter <= counterPriTrnObj))
                {
                    mvprintw(y, x, "O");
                    mvprintw(13, newLevel->levelWidth + 4, "Primary Terrain Obj");
                    mvprintw(14, newLevel->levelWidth + 4, "Counter Max is: %d", counterPriTrnObj);
                    mvprintw(15, newLevel->levelWidth + 4, "Exit count is: %d", counter);
                    //getch();
                    switch(newLevel->levelBiomeID)
                    {
                        case 0:     // desert
                            newLevel = updateLgObject(y, x, true, 2006, newLevel);   // cactus
                            counter++;
                            break;
                        case 1:     // forest
                            if(rand() % 2)
                            {
                                newLevel = updateLgObject(y, x, true, 2001, newLevel);   // sm tree
                            }
                            else
                            {
                                newLevel = updateLgObject(y, x, true, 2002, newLevel);   // lg tree
                            }
                            counter++;
                            break;
                        case 2:     // tundra
                            newLevel = updateLgObject(y, x, true, 2005, newLevel);      //boulder
                            counter++;
                            break;
                        case 3:     //prairie
                            if(rand() % 2)
                            {
                                newLevel = updateLgObject(y, x, true, 2003, newLevel);   // sm bush
                            }
                            else
                            {
                                newLevel = updateLgObject(y, x, true, 2004, newLevel);   // lg bush
                            }
                            counter++;
                            break;
                        case 4:     // swamp
                            if(rand() % 2)
                            {
                                newLevel = updateLgObject(y, x, true, 2003, newLevel);   // sm bush
                            }
                            else
                            {
                                newLevel = updateLgObject(y, x, true, 2004, newLevel);   // lg bush
                            }
                            counter++;
                            break;
                        case 5:     //mountain
                            newLevel = updateLgObject(y, x, true, 2005, newLevel);   // boulder
                            counter++;
                            break;
                    }
                }
            }
        }
    }
    getch();    
    // Generate Secondary Terrain Objects  //

    counter = 0;

    while(counter <= counterSecTrnObj)
    {
        for(y = 0; y <= newLevel->levelHeight; y++)
        {
            for(x = 0; x <= newLevel->levelWidth; x++)
            {
                if(!(rand() % 25) && (newLevel->levelMask[y][x].tileContents->biome) && (!newLevel->levelMask[y][x].tileContents->lgObject) && (counter <= counterSecTrnObj))
                {
                    mvprintw(y, x, "o");
                    mvprintw(17, newLevel->levelWidth + 4, "Secondary Terrain Objects");
                    mvprintw(18, newLevel->levelWidth + 4, "%d", counterSecTrnObj);
                    mvprintw(19, newLevel->levelWidth + 4, "%d", counter);
                    //getch();
                    switch(newLevel->levelBiomeID)
                    {
                        case 0:     // desert
                            if(rand() % 2)
                            {
                                newLevel = updateLgObject(y, x, true, 2003, newLevel);   // sm bush
                            }
                            else
                            {
                                newLevel = updateLgObject(y, x, true, 2004, newLevel);   // lg bush
                            }
                            counter++;
                            break;
                        case 1:     // forest
                            if(rand() % 2)
                            {
                                newLevel = updateLgObject(y, x, true, 2003, newLevel);   // sm bush
                            }
                            else
                            {
                                newLevel = updateLgObject(y, x, true, 2004, newLevel);   // lg bush
                            }
                            counter++;
                            break;
                        case 2:     // tundra
                            if(rand() % 2)
                            {
                                newLevel = updateLgObject(y, x, true, 2003, newLevel);   // sm bush
                            }
                            else
                            {
                                newLevel = updateLgObject(y, x, true, 2004, newLevel);   // lg bush
                            }
                            counter++;
                            break;
                        case 3:     //prairie
                            if(rand() % 2)
                            {
                                newLevel = updateLgObject(y, x, true, 2001, newLevel);   // sm tree
                            }
                            else
                            {
                                newLevel = updateLgObject(y, x, true, 2002, newLevel);   // lg tree
                            }
                            counter++;
                            break;
                        case 4:     // swamp
                            if(rand() % 2)
                            {
                                newLevel = updateLgObject(y, x, true, 2001, newLevel);   // sm tree
                            }
                            else
                            {
                                newLevel = updateLgObject(y, x, true, 2002, newLevel);   // lg tree
                            }
                            counter++;
                            break;
                        case 5:     //mountain
                            if(rand() % 2)
                            {
                                newLevel = updateLgObject(y, x, true, 2001, newLevel);   // sm tree
                            }
                            else
                            {
                                newLevel = updateLgObject(y, x, true, 2002, newLevel);   // lg tree
                            }
                            counter++;
                            break;
                    }
                }
            }
        }
    }
    getch();
    return newLevel;
}

Level * popBiomeTerrain(int y, int x, char terrainType[6], Level * newLevel)
{
    if(strcmp(terrainType, "priFea"))
    {
    }
}

Level * getStartingPosition(Level * newLevel)
{
    int y, x, rndY, rndX;

    while (!(newLevel->drawWinCorner->y) && !(newLevel->drawWinCorner->x))
    {
        rndY = rand() % newLevel->levelHeight;
        rndX = rand() % newLevel->levelWidth;
                
        if ((rndY >= 0) && (rndY + newLevel->drawWinMaxY <= newLevel->levelHeight))
        {
            if ((rndX >= 0) && (rndX + newLevel->drawWinMaxX <= newLevel->levelWidth))
            {
                newLevel->drawWinCorner->y = rndY;
                newLevel->drawWinCorner->x = rndX;
                for (y = 0; y < newLevel->drawWinMaxY; y++)
                {
                    for (x = 0; x < newLevel->drawWinMaxX; x++)
                    {
                        newLevel->drawWindowCoords[y][x].y = y + newLevel->drawWinCorner->y;
                        newLevel->drawWindowCoords[y][x].x = x + newLevel->drawWinCorner->x;
                        //mvprintw(y, x, "%s", newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].terrain->symbol);
                    }
                }
                
            }
        }
    }

    rndY = rand() % newLevel->drawWinMaxY;
    rndX = rand() % newLevel->drawWinMaxX;

    newLevel->newPlayer->playerCoordinates.y = newLevel->drawWindowCoords[rndY][rndX].y;
    newLevel->newPlayer->playerCoordinates.x = newLevel->drawWindowCoords[rndY][rndX].x;

    newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = true;

    return newLevel;
}
