#ifndef LEVEL_H
#define LEVEL_H

#include "brawl.h"

/* Declaration of data types  */

typedef struct Level
{
    int levelNumber;        // i.e. 1, 2...10
    int levelSize;          // 0 = small, 1 = medium, 2 = large --> overal size of map
    char levelBiome[10];
    int biomeDensity;
    int biomeMinSeed;
    int biomeMaxSeed;
    int levelHeight;
    int levelWidth;
    int barSize;            // 0 = small, 1 = medium, 2 = large --> size of bar building
    int barClass;           // dive bar, biker bar, gay bar, etc.

    struct Tile ** levelMask;       // data map of game area
    struct Bar * bar;
} Level;

typedef struct Tile
{
    struct TileContents * tileContents;
    struct World * world;
    struct Envmnt * envmnt;
    struct Building * building;
} Tile;

typedef struct TileContents
{
    bool player;
    bool npc;
    bool Pobject;
    bool Sobject;
    bool building;
    bool envmnt;
} TileContents;

typedef struct World
{
    char biome[20];
    char maskID[1];
    char terrain[20];
} World;

typedef struct Envmnt
{
    char name[20];
    char description[50];
    char maskID[1];
    char symbol[1];
    int symColor;       // should be an int.
    char symbolDest[1];
    int symDestColor;
    char type;              //i.e. tree
    char subtype;           //i.e maple
    int speedMod;           // Maybe 1 to 10; 5 is narmal 
    int damage;          //i.e. toxic waste, etc.
    int storageCap;
    int storedItems[10];
    int toughness;
    int maxHealth;
    int curHealth;
    bool destructable;
    bool destroyed;
    bool fammable;

} Envmnt;

typedef struct Building
{
    char name[20];
    char description[50];
    char maskID[1];
    char symbol[1];
    int symColor;       // should be an int.
    char symbolDest[1];
    int symDestColor;
    char type;              //i.e. tree
    char subtype;           //i.e maple
    int speedMod;           // Maybe 1 to 10; 5 is narmal 
    int damage;          //i.e. toxic waste, etc.
    int storageCap;
    int storedItems[10];
    int toughness;
    int maxHealth;
    int curHealth;
    bool destructable;
    bool destroyed;
    bool fammable;
    
    char buildType[20];     //i.e. bar, house, garage      
    char tileType[20];      //wall
    char tileSubType[20];   //horizantal/virtical
    struct Corner * corner;
} Building;

typedef struct Corner
{
    char facing[4];          // inside/outside
    bool facingDirN;
    bool facingDirE;
    bool facingDirS;
    bool facingDirW;
} Corner;


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

/*
typedef struct Tile
{
    char name[10];
    char description[100];
    char maskID[1];
    char buildID[6];
    char tileType[6];
    char tileSubType[6];
    char symbol[1];
    char symbolDest[1];
    int health;
    bool destructable;
    bool flammable;
} Tile;
*/

/* Dclaration of functions */
Level * generateLevel(Level * newLevel, int levelNumber);
Tile ** createLevelMask(Level * newLevel);
Level * generateBar(Level * newLevel);
Level * generateRandom(Level * newLevel, int percentCover);
Level * updateWorldTile(Level * newLevel);

#endif
