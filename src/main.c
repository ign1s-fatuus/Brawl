//#include <ncurses.h>
//#include <stdlib.h>
//#include <string.h>
#include "brawl.h"
//#include <time.h>
#include "level.h"
#include "world.h"

int printData(Level * newLevel);
int testPrintMask(Level * newLevel);

Level * allocateMemory(Level * newLevel);
int freeMemory(Level * newLevel);

int main()
{
    initNcurses();
    srand(time(0));
    
    Level * newLevel;
    newLevel = malloc(sizeof(Level));

    newLevel = generateWorld(newLevel);
    
    newLevel = allocateMemory(newLevel);

    newLevel = generateLevel(newLevel, 1);
    //newLevel->levelMask = createLevelMask(newLevel); 
    
    //Windows * gameWindows = malloc(sizeof(Windows));             // rewrtie to malloc Windows in main and not in function
    //gameWindows = drawBorders();
    //refreshWindows(gameWindows);
    
    printData(newLevel);
    getch();
    clear();
    testPrintMask(newLevel);
    getch();

    endwin();

    freeMemory(newLevel);
    return 0;
}

Level * allocateMemory(Level * newLevel)
{
    int x, y;
    
    newLevel->bar = malloc(sizeof(Bar));
    
    newLevel->levelMask = (Tile **) malloc(sizeof(Tile) * newLevel->levelHeight);
    for (y = 0; y <= newLevel->levelHeight; y++)
    {
        newLevel->levelMask[y] = (Tile *)malloc(sizeof(Tile) * newLevel->levelWidth);
        for (x = 0; x <= newLevel->levelWidth; x++)
        {
            newLevel->levelMask[y][x].building = (Building *) malloc(sizeof(Building));
            newLevel->levelMask[y][x].world = (World *) malloc(sizeof(World));
            //strcpy(newLevel->levelMask[y][x].building->maskID, "e");
        }
    }
    return newLevel;
}

int freeMemory(Level * newLevel)
{
    int x, y;
    for (y = 0; y <= newLevel->levelHeight; y++)
    {
        for(x = 0; x <= newLevel->levelWidth; x++)
        {
            //free(newLevel->levelMask[y][x].building);
            //free(newLevel->levelMask[y][x].world);
        }
        //free(newLevel->levelMask[y]);
    }
    //free(newLevel->levelMask);
    //free(newLevel->bar);
    free(newLevel);

    return 0;
}

int printData(Level * newLevel)
{
    printw("Level number is: %d\n",newLevel->levelNumber);
    printw("Level size is: %d\n",newLevel->levelSize);
    printw("Level biome is: %s\n", newLevel->levelBiome);
    printw("Level biome density is: %d\n", newLevel->biomeDensity);
    printw("Level biome min seed is: %d\n", newLevel->biomeMinSeed);
    printw("Level biome max seed is: %d\n\n", newLevel->biomeMaxSeed);
    
    printw("Bar building height is: %d\n", newLevel->bar->buildingHeight);
    printw("Bar building width is: %d\n", newLevel->bar->buildingWidth);
    printw("Bar starting position is: %d, %d\n", newLevel->bar->start_pos.y, newLevel->bar->start_pos.x);
    printw("Bar Gravity is: %d\n",newLevel->bar->barWallGravity);
    printw("Bar type is: %d\n",newLevel->bar->barType);
    printw("Number of rooms is: %d\n",newLevel->bar->numOfRooms);
    printw("Numbe of enrances: %d\n",newLevel->bar->numOfEntrances);
    printw("Number of windows: %d\n",newLevel->bar->numOfWindows);
    printw("Number of activity areas: %d\n",newLevel->bar->numOfActAreas);

    int counterMax;
    counterMax = ((newLevel->biomeDensity * .01) * (newLevel->levelWidth * newLevel->levelHeight));

    printw("Biome counter is: %d", counterMax);

    return 0;
}

int testPrintMask(Level * newLevel)
{
    int x, y;
    for (y = 0; y <= newLevel->levelHeight; y++)
    {
        for (x = 0; x <= newLevel->levelWidth; x++)
        {
            mvprintw(y, x , "%s", newLevel->levelMask[y][x].world->maskID);
            mvprintw( y, x,"%s",newLevel->levelMask[y][x].building->maskID);
            //getch();
        }
    }
    return 0;
}
