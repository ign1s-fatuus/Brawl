#include "brawl.h"
#include "build_bar.h"
#include "level.h"

/* Add the bar to the level mask along with any other structural features  */

/*
typedef struct Level
{
    int levelNumber;        // i.e. 1, 2...10
    int levelSize;          // 0 = small, 1 = medium, 2 = large --> overal size of map
    int levelHeight;
    int levelWidth;
    int barSize;            // 0 = small, 1 = medium, 2 = large --> size of bar building
    int barClass;           // dive bar, biker bar, gay bar, etc.

    int ** levelMask;       // data map of game area
    struct Bar * bar;
} Level;

typedef struct Bar
{
    int barWallGravity;     // 0 = Top; 1 = Right; 2 = Bottom; 3 = Left
    int barType;            // 0 = full bar; 1 = 3/4 bar; 2 = L-shaped; etc
    int numOfRooms;         // number of additional rooms; 0 = only the bar
    int numOfEntrances;     // number of doors leading into the bar
    int numOfWindows;       // number of windows
    int numOfActAreas;      // number of activity areas; i.e. tables and seeating, dart boards, arcade
    Coordinates start_pos;  // in y, x
    int buildingHeight;
    int buildingWidth;
} Bar;
*/

int ** addBarMask(Level * newLevel)
{
        newLevel->levelMask = addBarWalls(newLevel);

        return newLevel->levelMask;
}

int ** addBarWalls(Level * newLevel)
{
    int y, x;
    /* Build top and bottom  */
    for (x = newLevel->bar->start_pos.x; x < newLevel->bar->start_pos.x + newLevel->bar->buildingWidth; x++)
    {
        newLevel->levelMask[newLevel->bar->start_pos.y][x] = 1;
        newLevel->levelMask[newLevel->bar->start_pos.y + newLevel->bar->buildingHeight - 1][x] = 1;
    }

    /* Build side and fill in middle  */
    for (y = newLevel->bar->start_pos.y + 1; y < newLevel->bar->start_pos.y + newLevel->bar->buildingHeight -1; y++)
    {
        newLevel->levelMask[y][newLevel->bar->start_pos.x] = 2;
        newLevel->levelMask[y][newLevel->bar->start_pos.x + newLevel->bar->buildingWidth - 1] = 2;
    
    }
    return newLevel->levelMask;
}
