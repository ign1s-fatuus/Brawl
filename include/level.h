#ifndef LEVEL_H
#define LEVEL_H
#endif

/* Declaration of data types  */

typedef struct Level
{
    int levelNumber;        // i.e. 1, 2...10
    int levelSize;          // 1 = small, 2 = medium, 3 = large
    int numOfRooms;        // number of additional rooms; 0 = only the bar
    int numOfEntrances;     // number of doors leading into the bar
    int numOfWindows;       // number of windows
    int numOfActAreas;      // number of activity areas; i.e. tables and seeating, dart boards, arcade
} Level;


/* Dclaration of functions */
Level * createLevel(Level * newLevel);
