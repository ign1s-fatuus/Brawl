//#include <ncurses.h>
//#include <stdlib.h>
//#include <string.h>
#include "brawl.h"
//#include <time.h>
#include "level.h"
#include "world.h"

int printData(Level * newLevel);
int testPrintMask(Level * newLevel);
int testHeightMap(Level * newLevel);

Level * allocateMemory(Level * newLevel);
int freeMemory(Level * newLevel);

int main()
{
    initNcurses();
    srand(time(0));

    start_color();
    int background = COLOR_BLUE;
    init_color(background, 1000, 0, 0);
    init_pair(1, COLOR_RED, background);
    init_pair(2, COLOR_RED, COLOR_BLUE);
    attron(COLOR_PAIR(1));
    printw("this is a test");
    attroff(COLOR_PAIR(1));

    getch();
    init_color(background, 0, 500, 1000);
    attron(COLOR_PAIR(1));
    printw("this is a test");
    attroff(COLOR_PAIR(1));
    getch();


    Level * newLevel;
    newLevel = malloc(sizeof(Level));

    newLevel = generateWorld(newLevel);
    
    newLevel = allocateMemory(newLevel);

    newLevel = generateLevel(newLevel, 1);
    //newLevel->levelMask = createLevelMask(newLevel); 
    
    //Windows * gameWindows = malloc(sizeof(Windows));             // rewrtie to malloc Windows in main and not in function
    //gameWindows = drawBorders();
    //refreshWindows(gameWindows);

    clear();
    printData(newLevel);
    testPrintMask(newLevel);
    getch();
    testHeightMap(newLevel);
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
            newLevel->levelMask[y][x].tileContents = (TileContents *) malloc(sizeof(TileContents));
            newLevel->levelMask[y][x].terrain = (Terrain *) malloc(sizeof(Terrain));
            newLevel->levelMask[y][x].lgObject = (LgObject *) malloc(sizeof(Terrain));
            newLevel->levelMask[y][x].smObject = (SmObject *) malloc(sizeof(Terrain));
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
    mvprintw(4, newLevel->levelWidth + 4, "Level number is: %d",newLevel->levelNumber);
    mvprintw(5, newLevel->levelWidth + 4, "Level size is: %d",newLevel->levelSize);
    mvprintw(6, newLevel->levelWidth + 4, "Level biome is: %s", newLevel->levelBiome);
    mvprintw(7, newLevel->levelWidth + 4, "Level biome density is: %d", newLevel->biomeDensity);
    mvprintw(8, newLevel->levelWidth + 4, "Level biome min seed is: %d", newLevel->biomeMinSeed);
    mvprintw(9, newLevel->levelWidth + 4, "Level biome max seed is: %d", newLevel->biomeMaxSeed);
    
    mvprintw(11, newLevel->levelWidth + 4, "Bar building height is: %d", newLevel->bar->buildingHeight);
    mvprintw(12, newLevel->levelWidth + 4, "Bar building width is: %d", newLevel->bar->buildingWidth);
    mvprintw(13, newLevel->levelWidth + 4, "Bar starting position is: %d, %d", newLevel->bar->start_pos.y, newLevel->bar->start_pos.x);
    mvprintw(14, newLevel->levelWidth + 4, "Bar Gravity is: %d",newLevel->bar->barWallGravity);
    mvprintw(15, newLevel->levelWidth + 4, "Bar type is: %d",newLevel->bar->barType);
    mvprintw(16, newLevel->levelWidth + 4, "Number of rooms is: %d",newLevel->bar->numOfRooms);
    mvprintw(17, newLevel->levelWidth + 4, "Numbe of enrances: %d",newLevel->bar->numOfEntrances);
    mvprintw(18, newLevel->levelWidth + 4, "Number of windows: %d",newLevel->bar->numOfWindows);
    mvprintw(19, newLevel->levelWidth + 4, "Number of activity areas: %d",newLevel->bar->numOfActAreas);
    mvprintw(20, newLevel->levelWidth + 4, "envPriTrnObjDensity is: %d", newLevel->envPriTrnObjDensity);
    mvprintw(21, newLevel->levelWidth + 4, "envSecTrnObjDensity is: %d", newLevel->envSecTrnObjDensity);
    mvprintw(22, newLevel->levelWidth + 4, "envPriTrnDensity is: %d", newLevel->envPriTrnDensity);
    mvprintw(23, newLevel->levelWidth + 4, "envPriTrnDensity is: %d", newLevel->envSecTrnDensity);

    int counterMax;
    counterMax = ((newLevel->biomeDensity * .01) * (newLevel->levelWidth * newLevel->levelHeight));

    mvprintw(24, newLevel->levelWidth + 4, "Biome counter is: %d", counterMax);

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

int testHeightMap(Level * newLevel)
{
    clear();
    int x, y;
    for (y = 0; y <= newLevel->levelHeight; y++)
    {
        for (x = 0; x <= newLevel->levelWidth; x++)
        {
            mvprintw(y, x , "%d", newLevel->levelMask[y][x].terrain->height);
        }
    }

    return 0;
}
