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

    newLevel = generateBiome(newLevel);
    newLevel = generateTerrain(newLevel);
    newLevel = generateBar(newLevel);
    newLevel = generateHeightMap(newLevel);
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

Level * generateBiome(Level * newLevel)
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
        newLevel = updateBiome(rndY, rndX, true, newLevel);
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
                    rndDir = (rand() % 8);
                    switch(rndDir)
                    {
                        case 0:  
                            if(((y - 1) >= 0) && ((x - 1 ) >= 0) && (strcmp(newLevel->levelMask[y - 1][x - 1].world->maskID, "B") != 0))
                            {
                                newLevel = updateBiome(y - 1, x - 1, true, newLevel);
                                counter++;
                            }
                        case 1:
                            if(((y - 1) >= 0) && (strcmp(newLevel->levelMask[y - 1][x].world->maskID, "B") != 0))
                            {
                                newLevel = updateBiome(y - 1, x, true, newLevel);
                                counter++;
                            }
                            break;
                        case 2:
                            if(((y - 1) >= 0) && ((x + 1 ) <= newLevel->levelWidth) && (strcmp(newLevel->levelMask[y - 1][x + 1].world->maskID, "B") != 0))
                            {
                                newLevel = updateBiome(y - 1, x + 1, true, newLevel);
                                counter++;
                            }
                            break;
                        case 3:
                            if(((x + 1 ) <= newLevel->levelWidth) && (strcmp(newLevel->levelMask[y][x + 1].world->maskID, "B") != 0))
                            {
                                newLevel = updateBiome(y, x + 1, true, newLevel);
                                counter++;
                            }
                            break;
                        case 4:
                            if(((y + 1) <= newLevel->levelHeight) && ((x + 1 ) <= newLevel->levelWidth) && (strcmp(newLevel->levelMask[y + 1][x + 1].world->maskID, "B") != 0))
                            {
                                newLevel = updateBiome(y + 1, x + 1, true, newLevel);
                                counter++;
                            }
                            break;
                        case 5:
                            if(((y + 1) >= newLevel->levelHeight) && (strcmp(newLevel->levelMask[y + 1][x].world->maskID, "B") != 0))
                            {
                                newLevel = updateBiome(y + 1, x, true, newLevel);
                                counter++;
                            }
                            break;
                        case 6:
                            if(((y + 1) >= newLevel->levelHeight) && ((x - 1 ) >= 0) && (strcmp(newLevel->levelMask[y + 1][x - 1].world->maskID, "B") != 0))
                            {
                                newLevel = updateBiome(y + 1, x - 1, true, newLevel);
                                counter++;
                            }
                            break;
                        case 7:
                            if(((x - 1 ) >= 0) && (strcmp(newLevel->levelMask[y][x - 1].world->maskID, "B") != 0))
                            {
                                newLevel = updateBiome(y, x - 1, true, newLevel);
                                counter++;
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
    return newLevel;
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

Level * updateWorldTile(Level * newLevel)
{

}
