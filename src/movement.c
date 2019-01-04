#include "brawl.h"
#include "level.h"

Level * handleInput(int keyPress, Level * newLevel)
{
    switch (keyPress)
    {
        case 'h':         //left
            if ((newLevel->newPlayer->playerCoordinates.x - 1 >= 0) && (!newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x - 1].tileProperties->impass))
            {
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = false;
                redrawMapElement(newLevel->newPlayer->playerCoordinates.y, newLevel->newPlayer->playerCoordinates.x, newLevel);
                newLevel->newPlayer->playerCoordinates.x--;
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = true;
                redrawMapElement(newLevel->newPlayer->playerCoordinates.y, newLevel->newPlayer->playerCoordinates.x, newLevel);
            }
            break;
        case 'l':         //right
            if ((newLevel->newPlayer->playerCoordinates.x + 1 <= newLevel->levelWidth) && (!newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x + 1].tileProperties->impass))
            {
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = false;
                redrawMapElement(newLevel->newPlayer->playerCoordinates.y, newLevel->newPlayer->playerCoordinates.x, newLevel);
                newLevel->newPlayer->playerCoordinates.x++;
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = true;
                redrawMapElement(newLevel->newPlayer->playerCoordinates.y, newLevel->newPlayer->playerCoordinates.x, newLevel);
            }
            break;
        case 'j':         //down
            if ((newLevel->newPlayer->playerCoordinates.y + 1 <= newLevel->levelHeight) && (!newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y + 1][newLevel->newPlayer->playerCoordinates.x].tileProperties->impass))
            {
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = false;
                redrawMapElement(newLevel->newPlayer->playerCoordinates.y, newLevel->newPlayer->playerCoordinates.x, newLevel);
                newLevel->newPlayer->playerCoordinates.y++;
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = true;
                redrawMapElement(newLevel->newPlayer->playerCoordinates.y, newLevel->newPlayer->playerCoordinates.x, newLevel);
            }
            break;
        case 'k':         //up
            if ((newLevel->newPlayer->playerCoordinates.y - 1 >= 0) && (!newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y - 1][newLevel->newPlayer->playerCoordinates.x].tileProperties->impass))
            {
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = false;
                redrawMapElement(newLevel->newPlayer->playerCoordinates.y, newLevel->newPlayer->playerCoordinates.x, newLevel);
                newLevel->newPlayer->playerCoordinates.y--;
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = true;
                redrawMapElement(newLevel->newPlayer->playerCoordinates.y, newLevel->newPlayer->playerCoordinates.x, newLevel);
            }
            break;
        case 'y':         //up-left
            if ((newLevel->newPlayer->playerCoordinates.y - 1 >= 0) && (newLevel->newPlayer->playerCoordinates.x - 1 >= 0) && (!newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y - 1][newLevel->newPlayer->playerCoordinates.x - 1].tileProperties->impass))
            {
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = false;
                redrawMapElement(newLevel->newPlayer->playerCoordinates.y, newLevel->newPlayer->playerCoordinates.x, newLevel);
                newLevel->newPlayer->playerCoordinates.y--;
                newLevel->newPlayer->playerCoordinates.x--;
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = true;
                redrawMapElement(newLevel->newPlayer->playerCoordinates.y, newLevel->newPlayer->playerCoordinates.x, newLevel);
            }
            break;
        case 'u':         //up-right
            if ((newLevel->newPlayer->playerCoordinates.y - 1 >= 0) && (newLevel->newPlayer->playerCoordinates.x + 1 <= newLevel->levelWidth) && (!newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y - 1][newLevel->newPlayer->playerCoordinates.x + 1].tileProperties->impass))
            {
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = false;
                redrawMapElement(newLevel->newPlayer->playerCoordinates.y, newLevel->newPlayer->playerCoordinates.x, newLevel);
                newLevel->newPlayer->playerCoordinates.y--;
                newLevel->newPlayer->playerCoordinates.x++;
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = true;
                redrawMapElement(newLevel->newPlayer->playerCoordinates.y, newLevel->newPlayer->playerCoordinates.x, newLevel);
            }
            break;
        case 'b':         //down-left
            if ((newLevel->newPlayer->playerCoordinates.y + 1 <= newLevel->levelHeight) && (newLevel->newPlayer->playerCoordinates.x - 1 >= 0) && (!newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y + 1][newLevel->newPlayer->playerCoordinates.x - 1].tileProperties->impass))
            {
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = false;
                redrawMapElement(newLevel->newPlayer->playerCoordinates.y, newLevel->newPlayer->playerCoordinates.x, newLevel);
                newLevel->newPlayer->playerCoordinates.y++;
                newLevel->newPlayer->playerCoordinates.x--;
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = true;
                redrawMapElement(newLevel->newPlayer->playerCoordinates.y, newLevel->newPlayer->playerCoordinates.x, newLevel);
            }
            break;
        case 'n':         //down-right
            if ((newLevel->newPlayer->playerCoordinates.y + 1 <= newLevel->levelHeight) && (newLevel->newPlayer->playerCoordinates.x + 1 <= newLevel->levelWidth) && (!newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y + 1][newLevel->newPlayer->playerCoordinates.x + 1].tileProperties->impass))
            {
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = false;
                redrawMapElement(newLevel->newPlayer->playerCoordinates.y, newLevel->newPlayer->playerCoordinates.x, newLevel);
                newLevel->newPlayer->playerCoordinates.y++;
                newLevel->newPlayer->playerCoordinates.x++;
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = true;
                redrawMapElement(newLevel->newPlayer->playerCoordinates.y, newLevel->newPlayer->playerCoordinates.x, newLevel);
            }
            break;
        default:
            break;
    }

    return newLevel;
}

