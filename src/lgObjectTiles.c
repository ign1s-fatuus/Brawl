#include "brawl.h"
#include "level.h"

/* define and return terrain tiles  */

Level * updateLgObject(int y, int x, bool hasLgObject, int objectID, Level * newLevel)
{
    if(hasLgObject)
    {
        switch(objectID)
        {
            case 2001:
                newLevel->levelMask[y][x].tileContents->lgObject = true;
                newLevel->levelMask[y][x].lgObject->objectID =  2001;
                strcpy(newLevel->levelMask[y][x].lgObject->name, "small tree");
                strcpy(newLevel->levelMask[y][x].lgObject->description, "Add description");
                strcpy(newLevel->levelMask[y][x].lgObject->maskID, "t");
                strcpy(newLevel->levelMask[y][x].lgObject->symbol, "t");
                newLevel->levelMask[y][x].lgObject->symColor = 64;
                newLevel->levelMask[y][x].lgObject->bold = false;
                newLevel->levelMask[y][x].lgObject->dim = false;
                //newLevel->levelMask[y][x].lgObject->speedMod = add speed mod
                newLevel->levelMask[y][x].lgObject->storageCap = 0;
                //newLevel->levelMask[y][x].lgObject->toughness = add toughness
                //newLevel->levelMask[y][x].lgObject->maxHealth = add health
                //newLevel->levelMask[y][x].lgObject->curHealth = add curHealth
                newLevel->levelMask[y][x].lgObject->destructable = true;
                newLevel->levelMask[y][x].lgObject->destroyed = false;    
                newLevel->levelMask[y][x].lgObject->fammable = true;
                break;
            case 2002:
                newLevel->levelMask[y][x].tileContents->lgObject = true;
                newLevel->levelMask[y][x].lgObject->objectID =  2002;
                strcpy(newLevel->levelMask[y][x].lgObject->name, "large tree");
                strcpy(newLevel->levelMask[y][x].lgObject->description, "Add description");
                strcpy(newLevel->levelMask[y][x].lgObject->maskID, "T");
                strcpy(newLevel->levelMask[y][x].lgObject->symbol, "T");
                newLevel->levelMask[y][x].lgObject->symColor = 64;
                newLevel->levelMask[y][x].lgObject->bold = true;
                newLevel->levelMask[y][x].lgObject->dim = false;
                //newLevel->levelMask[y][x].lgObject->speedMod = add speed mod
                newLevel->levelMask[y][x].lgObject->storageCap = 0;
                //newLevel->levelMask[y][x].lgObject->toughness = add toughness
                //newLevel->levelMask[y][x].lgObject->maxHealth = add health
                //newLevel->levelMask[y][x].lgObject->curHealth = add curHealth
                newLevel->levelMask[y][x].lgObject->destructable = true;
                newLevel->levelMask[y][x].lgObject->destroyed = false;    
                newLevel->levelMask[y][x].lgObject->fammable = true;
                break;
            case 2003:
                newLevel->levelMask[y][x].tileContents->lgObject = true;
                newLevel->levelMask[y][x].lgObject->objectID =  2003;
                strcpy(newLevel->levelMask[y][x].lgObject->name, "small bush");
                strcpy(newLevel->levelMask[y][x].lgObject->description, "Add description");
                strcpy(newLevel->levelMask[y][x].lgObject->maskID, "b");
                strcpy(newLevel->levelMask[y][x].lgObject->symbol, "#");
                newLevel->levelMask[y][x].lgObject->symColor = 106;
                newLevel->levelMask[y][x].lgObject->bold = false;
                newLevel->levelMask[y][x].lgObject->dim = false;
                //newLevel->levelMask[y][x].lgObject->speedMod = add speed mod
                newLevel->levelMask[y][x].lgObject->storageCap = 0;
                //newLevel->levelMask[y][x].lgObject->toughness = add toughness
                //newLevel->levelMask[y][x].lgObject->maxHealth = add health
                //newLevel->levelMask[y][x].lgObject->curHealth = add curHealth
                newLevel->levelMask[y][x].lgObject->destructable = true;
                newLevel->levelMask[y][x].lgObject->destroyed = false;    
                newLevel->levelMask[y][x].lgObject->fammable = true;
                break;
            case 2004:
                newLevel->levelMask[y][x].tileContents->lgObject = true;
                newLevel->levelMask[y][x].lgObject->objectID =  2004;
                strcpy(newLevel->levelMask[y][x].lgObject->name, "large bush");
                strcpy(newLevel->levelMask[y][x].lgObject->description, "Add description");
                strcpy(newLevel->levelMask[y][x].lgObject->maskID, "B");
                strcpy(newLevel->levelMask[y][x].lgObject->symbol, "#");
                newLevel->levelMask[y][x].lgObject->symColor = 106;
                newLevel->levelMask[y][x].lgObject->bold = true;
                newLevel->levelMask[y][x].lgObject->dim = false;
                //newLevel->levelMask[y][x].lgObject->speedMod = add speed mod
                newLevel->levelMask[y][x].lgObject->storageCap = 0;
                //newLevel->levelMask[y][x].lgObject->toughness = add toughness
                //newLevel->levelMask[y][x].lgObject->maxHealth = add health
                //newLevel->levelMask[y][x].lgObject->curHealth = add curHealth
                newLevel->levelMask[y][x].lgObject->destructable = true;
                newLevel->levelMask[y][x].lgObject->destroyed = false;    
                newLevel->levelMask[y][x].lgObject->fammable = true;
                break;
            case 2005:
                newLevel->levelMask[y][x].tileContents->lgObject = true;
                newLevel->levelMask[y][x].lgObject->objectID =  2005;
                strcpy(newLevel->levelMask[y][x].lgObject->name, "Boulder");
                strcpy(newLevel->levelMask[y][x].lgObject->description, "Add description");
                strcpy(newLevel->levelMask[y][x].lgObject->maskID, "D");
                strcpy(newLevel->levelMask[y][x].lgObject->symbol, "o");
                newLevel->levelMask[y][x].lgObject->symColor = 232;
                newLevel->levelMask[y][x].lgObject->bold = false;
                newLevel->levelMask[y][x].lgObject->dim = false;
                //newLevel->levelMask[y][x].lgObject->speedMod = add speed mod
                newLevel->levelMask[y][x].lgObject->storageCap = 0;
                //newLevel->levelMask[y][x].lgObject->toughness = add toughness
                //newLevel->levelMask[y][x].lgObject->maxHealth = add health
                //newLevel->levelMask[y][x].lgObject->curHealth = add curHealth
                newLevel->levelMask[y][x].lgObject->destructable = false;
                newLevel->levelMask[y][x].lgObject->destroyed = false;    
                newLevel->levelMask[y][x].lgObject->fammable = false;
                break;
            /* add damage  */
            case 2006:
                newLevel->levelMask[y][x].tileContents->lgObject = true;
                newLevel->levelMask[y][x].lgObject->objectID =  2006;
                strcpy(newLevel->levelMask[y][x].lgObject->name, "cactus");
                strcpy(newLevel->levelMask[y][x].lgObject->description, "Add description");
                strcpy(newLevel->levelMask[y][x].lgObject->maskID, "c");
                strcpy(newLevel->levelMask[y][x].lgObject->symbol, "t");
                newLevel->levelMask[y][x].lgObject->symColor = 28;
                newLevel->levelMask[y][x].lgObject->bold = false;
                newLevel->levelMask[y][x].lgObject->dim = false;
                //newLevel->levelMask[y][x].lgObject->speedMod = add speed mod
                newLevel->levelMask[y][x].lgObject->storageCap = 0;
                //newLevel->levelMask[y][x].lgObject->toughness = add toughness
                //newLevel->levelMask[y][x].lgObject->maxHealth = add health
                //newLevel->levelMask[y][x].lgObject->curHealth = add curHealth
                newLevel->levelMask[y][x].lgObject->destructable = true;
                newLevel->levelMask[y][x].lgObject->destroyed = false;    
                newLevel->levelMask[y][x].lgObject->fammable = false;
                break;
            default:
                break;
        }
    }
    else
    {
        newLevel->levelMask[y][x].tileContents->lgObject = false;
        newLevel->levelMask[y][x].lgObject->objectID =  0;
        strcpy(newLevel->levelMask[y][x].lgObject->name, "\0");
        strcpy(newLevel->levelMask[y][x].lgObject->description, "\0");
        strcpy(newLevel->levelMask[y][x].lgObject->maskID, "\0");
        strcpy(newLevel->levelMask[y][x].lgObject->symbol, "\0");
        //newLevel->levelMask[y][x].lgObject->symColor = add color
        //newLevel->levelMask[y][x].lgObject->speedMod = add speed mod
        newLevel->levelMask[y][x].lgObject->storageCap = 0;
        //newLevel->levelMask[y][x].lgObject->toughness = add toughness
        //newLevel->levelMask[y][x].lgObject->maxHealth = add health
        //newLevel->levelMask[y][x].lgObject->curHealth = add curHealth
        newLevel->levelMask[y][x].lgObject->destructable = false;
        newLevel->levelMask[y][x].lgObject->destroyed = false;    
        newLevel->levelMask[y][x].lgObject->fammable = false;
    }
    return newLevel;
}
