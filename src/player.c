#include "brawl.h"
#include "level.h"

Level * setUpPlayer(Level * newLevel)
{
    //newLevel->newPlayer->playerCoordinates.x = 0;
    //newLevel->newPlayer->playerCoordinates.y = 0;
    strcpy(newLevel->newPlayer->playerSymbol, "@");
    newLevel->newPlayer->playerColor = 229;
    //newLevel->levelMask[0][0].tileContents->player = true;

    return newLevel;
}
