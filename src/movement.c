#include "brawl.h"
#include "level.h"

Level * handleInput(int keyPress, Windows * newWindows, Level * newLevel)
{
    switch (keyPress)
    {
        case 'h':         //left
            if ((newLevel->newPlayer->playerCoordinates.x - 1 >= 0) && (!newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x - 1].tileProperties->impass))
            {
                if (newLevel->newPlayer->playerCoordinates.x - 1 <= newLevel->drawWinCorner->x + 20)
                    newLevel = updateMapWindow(7, newLevel);
                    
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = false;
                newLevel->newPlayer->playerCoordinates.x--;
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = true;
            }
            break;
        case 'l':         //right
            if ((newLevel->newPlayer->playerCoordinates.x + 1 < newLevel->levelWidth) && (!newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x + 1].tileProperties->impass))
            {
                if (newLevel->newPlayer->playerCoordinates.x + 1 >= newLevel->drawWinCorner->x + newLevel->drawWinMaxX - 20)
                    newLevel = updateMapWindow(3, newLevel);
                    
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = false;
                newLevel->newPlayer->playerCoordinates.x++;
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = true;
            }
            break;
        case 'j':         //down
            if ((newLevel->newPlayer->playerCoordinates.y + 1 < newLevel->levelHeight) && (!newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y + 1][newLevel->newPlayer->playerCoordinates.x].tileProperties->impass))
            {
                if (newLevel->newPlayer->playerCoordinates.y + 1 >= newLevel->drawWinCorner->y + newLevel->drawWinMaxY - 8)
                    newLevel = updateMapWindow(5, newLevel);
                    
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = false;
                newLevel->newPlayer->playerCoordinates.y++;
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = true;
            }
            break;
        case 'k':         //up
            if ((newLevel->newPlayer->playerCoordinates.y - 1 >= 0) && (!newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y - 1][newLevel->newPlayer->playerCoordinates.x].tileProperties->impass))
            {
                if (newLevel->newPlayer->playerCoordinates.y - 1 <= newLevel->drawWinCorner->y + 8)
                    newLevel = updateMapWindow(1, newLevel);
                    
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = false;
                newLevel->newPlayer->playerCoordinates.y--;
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = true;
            }
            break;
        case 'y':         //up-left
            if ((newLevel->newPlayer->playerCoordinates.y - 1 >= 0) && (newLevel->newPlayer->playerCoordinates.x - 1 >= 0) && (!newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y - 1][newLevel->newPlayer->playerCoordinates.x - 1].tileProperties->impass))
            {
                if ((newLevel->newPlayer->playerCoordinates.x - 1 <= newLevel->drawWinCorner->x + 20) || (newLevel->newPlayer->playerCoordinates.y - 1 <= newLevel->drawWinCorner->y + 8))
                    newLevel = updateMapWindow(0, newLevel);
                    
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = false;
                newLevel->newPlayer->playerCoordinates.y--;
                newLevel->newPlayer->playerCoordinates.x--;
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = true;
            }
            break;
        case 'u':         //up-right
            if ((newLevel->newPlayer->playerCoordinates.y - 1 >= 0) && (newLevel->newPlayer->playerCoordinates.x + 1 < newLevel->levelWidth) && (!newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y - 1][newLevel->newPlayer->playerCoordinates.x + 1].tileProperties->impass))
            {
                if ((newLevel->newPlayer->playerCoordinates.x + 1 >= newLevel->drawWinCorner->x + newLevel->drawWinMaxX - 20) || (newLevel->newPlayer->playerCoordinates.y - 1 <= newLevel->drawWinCorner->y + 8))
                    newLevel = updateMapWindow(2, newLevel);
                    
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = false;
                newLevel->newPlayer->playerCoordinates.y--;
                newLevel->newPlayer->playerCoordinates.x++;
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = true;
            }
            break;
        case 'b':         //down-left
            if ((newLevel->newPlayer->playerCoordinates.y + 1 < newLevel->levelHeight) && (newLevel->newPlayer->playerCoordinates.x - 1 >= 0) && (!newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y + 1][newLevel->newPlayer->playerCoordinates.x - 1].tileProperties->impass))
            {
                if ((newLevel->newPlayer->playerCoordinates.x - 1 <= newLevel->drawWinCorner->x + 20) || (newLevel->newPlayer->playerCoordinates.y + 1 >= newLevel->drawWinCorner->y + newLevel->drawWinMaxY - 8))
                    newLevel = updateMapWindow(6, newLevel);
                    
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = false;
                newLevel->newPlayer->playerCoordinates.y++;
                newLevel->newPlayer->playerCoordinates.x--;
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = true;
            }
            break;
        case 'n':         //down-right
            if ((newLevel->newPlayer->playerCoordinates.y + 1 < newLevel->levelHeight) && (newLevel->newPlayer->playerCoordinates.x + 1 < newLevel->levelWidth) && (!newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y + 1][newLevel->newPlayer->playerCoordinates.x + 1].tileProperties->impass))
            {
                if ((newLevel->newPlayer->playerCoordinates.x + 1 >= newLevel->drawWinCorner->x + newLevel->drawWinMaxX - 20) || (newLevel->newPlayer->playerCoordinates.y - 1 >= newLevel->drawWinCorner->y + newLevel->drawWinMaxY - 8))
                    newLevel = updateMapWindow(4, newLevel);
                    
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = false;
                newLevel->newPlayer->playerCoordinates.y++;
                newLevel->newPlayer->playerCoordinates.x++;
                newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = true;
            }
            break;
        default:
            break;
    }
    return newLevel;
}
