#ifndef LEVEL_H
#define LEVEL_H

#include "brawl.h"

/* Declaration of data types  */

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


/* Dclaration of functions */
Level * generateLevel(Level * newLevel, int levelNumber);
int ** createLevelMask(Level * newLevel);
Bar * generateBar(Level * newLevel);

#endif
