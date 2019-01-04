#ifndef LEVEL_H
#define LEVEL_H

#include "brawl.h"

/* Declaration of data types  */

typedef struct Player
{
    //int str;
    //int dex;
    //int health;
    char playerSymbol[1];
    int playerColor;
    Coordinates playerCoordinates;
} Player;

typedef struct Level
{
    Player * newPlayer;
    int levelNumber;        // i.e. 1, 2...10
    int levelSize;          // 0 = small, 1 = medium, 2 = large --> overal size of map
    char levelBiome[10];
    int levelBiomeID;       //0 = desert, 1 = forest, 2 = tundra, 3 = prarie; 4 = swamp; 5 = mountain
    int levelHeight;
    int levelWidth;
    int barSize;            // 0 = small, 1 = medium, 2 = large --> size of bar building
    int barClass;           // dive bar, biker bar, gay bar, etc.
    int biomeDensity;
    int biomeMinSeed;
    int biomeMaxSeed;
    int envPriTrnObjDensity;
    int envSecTrnObjDensity;
    int envPriTrnDensity;
    int envSecTrnDensity;
    double perlinFreq;
    double perlinPersist;
    int cPal[256][256];

    struct Tile ** levelMask;       // data map of game area
    struct Bar * bar;
} Level;

typedef struct Tile
{
    struct TileContents * tileContents;
    struct World * world;
    struct Terrain * terrain;
    struct Building * building;
    struct LgObject * lgObject;
    struct SmObject * smObject;
    struct TileProperties * tileProperties;
} Tile;

typedef struct TileProperties
{
    bool impass;
} TileProperties;

typedef struct TileContents
{
    bool biome;
    bool player;
    bool npc;
    bool lgObject;
    bool smObject;
    bool building;
    bool terrain;
} TileContents;

typedef struct World
{
    char biome[20];
    char maskID[1];
    char terrain[20];
} World;

typedef struct Terrain
{
    char name[20];
    char description[50];
    int objectID;
    char maskID[1];
    char ACStype[30];
    bool bold;
    bool dim;
    int height;
    char symbol[1];
    int symColor;       // should be an int.
    int speedMod;           // Maybe 1 to 10; 5 is narmal 
    int damage;          //i.e. toxic waste, etc.
    bool fammable;
} Terrain;

/* todo: add what replaced if destroyed -- i.e. tree -> stick  */
typedef struct LgObject
{
    char name[20];
    char description[50];
    char maskID[1];
    int objectID;
    char symbol[1];
    int symColor;       // should be an int.
    bool bold;
    bool dim;
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

} LgObject;

/* todo: add used_as_weapon_damage  */
typedef struct SmObject
{
    char name[20];
    char description[50];
    char maskID[1];
    int objectID;
    char symbol[1];
    int symColor;       // should be an int.
    bool bold;
    bool dim;
    int speedMod;           // Maybe 1 to 10; 5 is narmal 
    int damage;          //i.e. toxic waste, etc.
    int storageCap;
    int storedItems[10];
    int toughness;
    int maxHealth;
    int curHealth;
    bool destructable;
    bool destroyed;         //may not need
    bool fammable;

} SmObject;

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
Level * generateBiome(Level * newLevel);
Level * updateWorldTile(Level * newLevel);
Level * updateBiome(int y, int x, bool hasBiome, Level * newLevel);
Level * generateTerrain(Level * newLevel);
/* move to separate tile header file */
Level * updateTerrain(int y, int x, bool hasTerrain, int objectID, Level * newLevel);
Level * updateLgObject(int y, int x, bool hasLgObject, int objectID, Level * newLevel);
Level * updateSmObject(int y, int x, bool hasSmObject, int objectID, Level * newLevel);
Level * generateHeightMap(Level * newLevel);
Level * generateBiome2(Level * newLevel);
Level * weightedRandomTerrain(int y, int x, int wghtPercent, int defPercent, int objectIdMatch, int objectIdAdd, Level * newLevel);
Level * weightedRandomTerrainLlgObj(int y, int x, int wghtPercent, int defPercent, int terrainIdMatch, int objectTypeAdd, Level * newlevel);
Level * weightedFractTerrainLlgObj(int y, int x, double wghtPercent, double defPercent, int terrainIdMatch, int objectTypeAdd, Level * newlevel);
/* Color functions -- move to own header file */
Level * buildColorPalette(Level * newLevel);

/* render and map draw function -- move to own header file  */
int drawMap(Level * newLevel);
int redrawMapElement(int y, int x, Level * newLevel);

/* plaer functions -- move to own header file  */
Level * setUpPlayer(Level * newLevel);

/* movement functions -- move to own header file  */
Level * handleInput(int keyPrss, Level * newLevel);
#endif
