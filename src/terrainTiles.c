#include "brawl.h"
#include "level.h"

/* define and return terrain tiles  */

Level * updateTerrain(int y, int x, bool hasTerrain, int objectID, Level * newLevel)
{
    if(hasTerrain)
    {
        switch(objectID)
        {
            case 1001:
                strcpy(newLevel->levelMask[y][x].terrain->name, "dirt");
                strcpy(newLevel->levelMask[y][x].terrain->description, "Add description");
                strcpy(newLevel->levelMask[y][x].terrain->maskID, "d");
                strcpy(newLevel->levelMask[y][x].terrain->symbol, ".");
                newLevel->levelMask[y][x].tileContents->terrain = true;
                //newLevel->levelMask[y][x].terrain->symColor = add color
                //newLevel->levelMask[y][x].terrain->speedMod = add speed mod
                newLevel->levelMask[y][x].terrain->damage = 0;
                newLevel->levelMask[y][x].terrain->fammable = false;
                break;
            case 1002:
                strcpy(newLevel->levelMask[y][x].terrain->name, "grass");
                strcpy(newLevel->levelMask[y][x].terrain->description, "Add description");
                strcpy(newLevel->levelMask[y][x].terrain->maskID, "g");
                strcpy(newLevel->levelMask[y][x].terrain->symbol, ".");
                newLevel->levelMask[y][x].tileContents->terrain = true;
                //newLevel->levelMask[y][x].terrain->symColor = add color
                //newLevel->levelMask[y][x].terrain->speedMod = add speed mod
                newLevel->levelMask[y][x].terrain->damage = 0;
                newLevel->levelMask[y][x].terrain->fammable = false;
                break;
            case 1003:
                strcpy(newLevel->levelMask[y][x].terrain->name, "sand");
                strcpy(newLevel->levelMask[y][x].terrain->description, "Add description");
                strcpy(newLevel->levelMask[y][x].terrain->maskID, "s");
                strcpy(newLevel->levelMask[y][x].terrain->symbol, ".");
                newLevel->levelMask[y][x].tileContents->terrain = true;
                //newLevel->levelMask[y][x].terrain->symColor = add color
                //newLevel->levelMask[y][x].terrain->speedMod = add speed mod
                newLevel->levelMask[y][x].terrain->damage = 0;
                newLevel->levelMask[y][x].terrain->fammable = false;
                break;
            case 1004:
                strcpy(newLevel->levelMask[y][x].terrain->name, "snow");
                strcpy(newLevel->levelMask[y][x].terrain->description, "Add description");
                strcpy(newLevel->levelMask[y][x].terrain->maskID, "o");
                strcpy(newLevel->levelMask[y][x].terrain->symbol, ".");
                newLevel->levelMask[y][x].tileContents->terrain = true;
                //newLevel->levelMask[y][x].terrain->symColor = add color
                //newLevel->levelMask[y][x].terrain->speedMod = add speed mod
                newLevel->levelMask[y][x].terrain->damage = 0;
                newLevel->levelMask[y][x].terrain->fammable = false;
                break;
            case 1005:
                strcpy(newLevel->levelMask[y][x].terrain->name, "swamp");
                strcpy(newLevel->levelMask[y][x].terrain->description, "Add description");
                strcpy(newLevel->levelMask[y][x].terrain->maskID, "w");
                strcpy(newLevel->levelMask[y][x].terrain->symbol, ".");
                newLevel->levelMask[y][x].tileContents->terrain = true;
                //newLevel->levelMask[y][x].terrain->symColor = add color
                //newLevel->levelMask[y][x].terrain->speedMod = add speed mod
                newLevel->levelMask[y][x].terrain->damage = 0;
                newLevel->levelMask[y][x].terrain->fammable = false;
                break;
            default:
                break;
        }
    }
    else
    {
        strcpy(newLevel->levelMask[y][x].terrain->name, "\0");
        strcpy(newLevel->levelMask[y][x].terrain->description, "\0");
        strcpy(newLevel->levelMask[y][x].terrain->maskID, "\0");
        strcpy(newLevel->levelMask[y][x].terrain->symbol, "\0");
        newLevel->levelMask[y][x].tileContents->terrain = false;
        //newLevel->levelMask[y][x].terrain->symColor = add color
        //newLevel->levelMask[y][x].terrain->speedMod = add speed mod
        newLevel->levelMask[y][x].terrain->damage = 0;
        newLevel->levelMask[y][x].terrain->fammable = false;
    }
    return newLevel;
}
