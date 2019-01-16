#include "brawl.h"
#include "level.h"

/* define and return terrain tiles  */

Level * updateSmObject(int y, int x, bool hasSmObject, int objectID, Level * newLevel)
{
    if(hasSmObject)
    {
        switch(objectID)
        {
            case 3001:
                newLevel->levelMask[y][x].tileContents->smObject = true;
                newLevel->levelMask[y][x].smObject->objectID =  3001;
                strcpy(newLevel->levelMask[y][x].smObject->name, "rock");
                strcpy(newLevel->levelMask[y][x].smObject->description, "Add description");
                strcpy(newLevel->levelMask[y][x].smObject->maskID, "r");
                strcpy(newLevel->levelMask[y][x].smObject->symbol, "*");
                //newLevel->levelMask[y][x].smObject->symColor = add color
                //newLevel->levelMask[y][x].smObject->speedMod = add speed mod
                newLevel->levelMask[y][x].smObject->storageCap = 0;
                //newLevel->levelMask[y][x].smObject->toughness = add toughness
                //newLevel->levelMask[y][x].smObject->maxHealth = add health
                //newLevel->levelMask[y][x].smObject->curHealth = add curHealth
                newLevel->levelMask[y][x].smObject->destructable = false;
                newLevel->levelMask[y][x].smObject->destroyed = false;    
                newLevel->levelMask[y][x].smObject->fammable = false;
                break;
            case 3002:
                newLevel->levelMask[y][x].tileContents->smObject = true;
                newLevel->levelMask[y][x].smObject->objectID =  3002;
                strcpy(newLevel->levelMask[y][x].smObject->name, "stick");
                strcpy(newLevel->levelMask[y][x].smObject->description, "Add description");
                strcpy(newLevel->levelMask[y][x].smObject->maskID, "/");
                strcpy(newLevel->levelMask[y][x].smObject->symbol, "/");
                //newLevel->levelMask[y][x].smObject->symColor = add color
                //newLevel->levelMask[y][x].smObject->speedMod = add speed mod
                newLevel->levelMask[y][x].smObject->storageCap = 0;
                //newLevel->levelMask[y][x].smObject->toughness = add toughness
                //newLevel->levelMask[y][x].smObject->maxHealth = add health
                //newLevel->levelMask[y][x].smObject->curHealth = add curHealth
                newLevel->levelMask[y][x].smObject->destructable = true;
                newLevel->levelMask[y][x].smObject->destroyed = false;    
                newLevel->levelMask[y][x].smObject->fammable = true;
                break;
            default:
                break;
        }
    }
    else
    {
        newLevel->levelMask[y][x].tileContents->smObject = false;
        newLevel->levelMask[y][x].smObject->objectID =  0;
        strcpy(newLevel->levelMask[y][x].smObject->name, "\0");
        strcpy(newLevel->levelMask[y][x].smObject->description, "\0");
        strcpy(newLevel->levelMask[y][x].smObject->maskID, "\0");
        strcpy(newLevel->levelMask[y][x].smObject->symbol, "\0");
        //newLevel->levelMask[y][x].smObject->symColor = add color
        //newLevel->levelMask[y][x].smObject->speedMod = add speed mod
        newLevel->levelMask[y][x].smObject->storageCap = 0;
        //newLevel->levelMask[y][x].smObject->toughness = add toughness
        //newLevel->levelMask[y][x].smObject->maxHealth = add health
        //newLevel->levelMask[y][x].smObject->curHealth = add curHealth
        newLevel->levelMask[y][x].smObject->destructable = false;
        newLevel->levelMask[y][x].smObject->destroyed = false;    
        newLevel->levelMask[y][x].smObject->fammable = false;
    }
    return newLevel;
}
