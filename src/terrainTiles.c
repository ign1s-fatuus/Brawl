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
                newLevel->levelMask[y][x].terrain->objectID = 1001;
                strcpy(newLevel->levelMask[y][x].terrain->description, "Add description");
                strcpy(newLevel->levelMask[y][x].terrain->maskID, "d");
                strcpy(newLevel->levelMask[y][x].terrain->symbol, ".");
                strcpy(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD");
                newLevel->levelMask[y][x].tileContents->terrain = true;
                newLevel->levelMask[y][x].tileProperties->impass = false;
                newLevel->levelMask[y][x].terrain->bold = true;
                newLevel->levelMask[y][x].terrain->dim = false;
                newLevel->levelMask[y][x].terrain->symColor = 94;
                //newLevel->levelMask[y][x].terrain->speedMod = add speed mod
                newLevel->levelMask[y][x].terrain->damage = 0;
                newLevel->levelMask[y][x].terrain->fammable = false;
                break;
            case 1002:
                strcpy(newLevel->levelMask[y][x].terrain->name, "grass");
                newLevel->levelMask[y][x].terrain->objectID = 1001;
                strcpy(newLevel->levelMask[y][x].terrain->description, "Add description");
                strcpy(newLevel->levelMask[y][x].terrain->maskID, "g");
                strcpy(newLevel->levelMask[y][x].terrain->symbol, ",");
                strcpy(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD");
                newLevel->levelMask[y][x].terrain->bold = true;
                newLevel->levelMask[y][x].terrain->dim = false;
                newLevel->levelMask[y][x].tileContents->terrain = true;
                newLevel->levelMask[y][x].tileProperties->impass = false;
                newLevel->levelMask[y][x].terrain->symColor = 22;
                //newLevel->levelMask[y][x].terrain->speedMod = add speed mod
                newLevel->levelMask[y][x].terrain->damage = 0;
                newLevel->levelMask[y][x].terrain->fammable = false;
                break;
            case 1003:
                strcpy(newLevel->levelMask[y][x].terrain->name, "sand");
                newLevel->levelMask[y][x].terrain->objectID = 1003;
                strcpy(newLevel->levelMask[y][x].terrain->description, "Add description");
                strcpy(newLevel->levelMask[y][x].terrain->maskID, "s");
                strcpy(newLevel->levelMask[y][x].terrain->symbol, ".");
                strcpy(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD");
                newLevel->levelMask[y][x].terrain->bold = true;
                newLevel->levelMask[y][x].terrain->dim = false;
                newLevel->levelMask[y][x].tileContents->terrain = true;
                newLevel->levelMask[y][x].tileProperties->impass = false;
                newLevel->levelMask[y][x].terrain->symColor = 172;
                //newLevel->levelMask[y][x].terrain->speedMod = add speed mod
                newLevel->levelMask[y][x].terrain->damage = 0;
                newLevel->levelMask[y][x].terrain->fammable = false;
                break;
            case 1004:
                strcpy(newLevel->levelMask[y][x].terrain->name, "snow");
                newLevel->levelMask[y][x].terrain->objectID = 1004;
                strcpy(newLevel->levelMask[y][x].terrain->description, "Add description");
                strcpy(newLevel->levelMask[y][x].terrain->maskID, "o");
                strcpy(newLevel->levelMask[y][x].terrain->symbol, ".");
                //strcpy(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD");
                newLevel->levelMask[y][x].terrain->bold = true;
                newLevel->levelMask[y][x].terrain->dim = true;
                newLevel->levelMask[y][x].tileContents->terrain = true;
                newLevel->levelMask[y][x].tileProperties->impass = false;
                newLevel->levelMask[y][x].terrain->symColor = 229;
                //newLevel->levelMask[y][x].terrain->speedMod = add speed mod
                newLevel->levelMask[y][x].terrain->damage = 0;
                newLevel->levelMask[y][x].terrain->fammable = false;
                break;
            case 1005:
                strcpy(newLevel->levelMask[y][x].terrain->name, "swamp");
                newLevel->levelMask[y][x].terrain->objectID = 1005;
                strcpy(newLevel->levelMask[y][x].terrain->description, "Add description");
                strcpy(newLevel->levelMask[y][x].terrain->maskID, "w");
                strcpy(newLevel->levelMask[y][x].terrain->symbol, ",");
                strcpy(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD");
                newLevel->levelMask[y][x].terrain->bold = true;
                newLevel->levelMask[y][x].terrain->dim = false;
                newLevel->levelMask[y][x].tileContents->terrain = true;
                newLevel->levelMask[y][x].tileProperties->impass = false;
                newLevel->levelMask[y][x].terrain->symColor = 61;
                //newLevel->levelMask[y][x].terrain->speedMod = add speed mod
                newLevel->levelMask[y][x].terrain->damage = 0;
                newLevel->levelMask[y][x].terrain->fammable = false;
                break;
            case 1006:
                strcpy(newLevel->levelMask[y][x].terrain->name, "desert");
                newLevel->levelMask[y][x].terrain->objectID = 1006;
                strcpy(newLevel->levelMask[y][x].terrain->description, "Add description");
                strcpy(newLevel->levelMask[y][x].terrain->maskID, "D");
                strcpy(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD");
                strcpy(newLevel->levelMask[y][x].terrain->symbol, ".");
                newLevel->levelMask[y][x].terrain->bold = true;
                newLevel->levelMask[y][x].terrain->dim = true;
                newLevel->levelMask[y][x].tileContents->terrain = true;
                newLevel->levelMask[y][x].tileProperties->impass = false;
                newLevel->levelMask[y][x].terrain->symColor = 94;
                //newLevel->levelMask[y][x].terrain->speedMod = add speed mod
                newLevel->levelMask[y][x].terrain->damage = 0;
                newLevel->levelMask[y][x].terrain->fammable = false;
                break;
            case 1007:
                strcpy(newLevel->levelMask[y][x].terrain->name, "water");
                newLevel->levelMask[y][x].terrain->objectID = 1007;
                strcpy(newLevel->levelMask[y][x].terrain->description, "Add description");
                strcpy(newLevel->levelMask[y][x].terrain->maskID, "~");
                strcpy(newLevel->levelMask[y][x].terrain->symbol, "~");
                strcpy(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD");
                newLevel->levelMask[y][x].terrain->bold = false;
                newLevel->levelMask[y][x].terrain->dim = false;
                newLevel->levelMask[y][x].tileContents->terrain = true;
                newLevel->levelMask[y][x].tileProperties->impass = true;
                newLevel->levelMask[y][x].terrain->symColor = 21;
                //newLevel->levelMask[y][x].terrain->speedMod = add speed mod
                newLevel->levelMask[y][x].terrain->damage = 0;
                newLevel->levelMask[y][x].terrain->fammable = false;
                break;
            case 1008:
                strcpy(newLevel->levelMask[y][x].terrain->name, "deep water");
                newLevel->levelMask[y][x].terrain->objectID = 1008;
                strcpy(newLevel->levelMask[y][x].terrain->description, "Add description");
                strcpy(newLevel->levelMask[y][x].terrain->maskID, "~");
                strcpy(newLevel->levelMask[y][x].terrain->symbol, "~");
                strcpy(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD");
                newLevel->levelMask[y][x].terrain->bold = false;
                newLevel->levelMask[y][x].terrain->dim = false;
                newLevel->levelMask[y][x].tileContents->terrain = true;
                newLevel->levelMask[y][x].tileProperties->impass = true;
                newLevel->levelMask[y][x].terrain->symColor = 20;
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
        newLevel->levelMask[y][x].tileProperties->impass = false;
        newLevel->levelMask[y][x].terrain->symColor = 0;
        //newLevel->levelMask[y][x].terrain->speedMod = add speed mod
        newLevel->levelMask[y][x].terrain->damage = 0;
        newLevel->levelMask[y][x].terrain->fammable = false;
    }
    return newLevel;
}
