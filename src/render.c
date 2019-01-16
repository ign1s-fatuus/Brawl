#include "brawl.h"
#include "level.h"

Level * updateMapWindow(int moveDir, Level * newLevel)
{
    int y, x;

    /* Movent Dir handles as:
     *  0 1 2
     *  7   3
     *  6 5 4 */

    switch (moveDir)
    {
        case 0:     //up-left
            if (((newLevel->drawWinCorner->x -1) >= 0) && ((newLevel->drawWinCorner->y -1) >= 0))
            {
                newLevel->drawWinCorner->y--;
                newLevel->drawWinCorner->x--;
                for (y = 0; y < newLevel->drawWinMaxY; y++)
                {
                    for (x = 0; x < newLevel->drawWinMaxX; x++)
                    {
                        newLevel->drawWindowCoords[y][x].y = y + newLevel->drawWinCorner->y;
                        newLevel->drawWindowCoords[y][x].x = x + newLevel->drawWinCorner->x;
                    }
                }
            }
            break;
        case 1:     //up
            if (((newLevel->drawWinCorner->y -1) >= 0))
            {
                newLevel->drawWinCorner->y--;
                for (y = 0; y < newLevel->drawWinMaxY; y++)
                {
                    for (x = 0; x < newLevel->drawWinMaxX; x++)
                    {
                        newLevel->drawWindowCoords[y][x].y = y + newLevel->drawWinCorner->y;
                        newLevel->drawWindowCoords[y][x].x = x + newLevel->drawWinCorner->x;
                    }
                }
            }
            break;
        case 2:     //up-right
            if (((newLevel->drawWinCorner->x + newLevel->drawWinMaxX +1) < newLevel->levelWidth) && ((newLevel->drawWinCorner->y - 1) >= 0))
            {
                newLevel->drawWinCorner->y--;
                newLevel->drawWinCorner->x++;
                for (y = 0; y < newLevel->drawWinMaxY; y++)
                {
                    for (x = 0; x < newLevel->drawWinMaxX; x++)
                    {
                        newLevel->drawWindowCoords[y][x].y = y + newLevel->drawWinCorner->y;
                        newLevel->drawWindowCoords[y][x].x = x + newLevel->drawWinCorner->x;
                    }
                }
            }
            break;
        case 3:     //right
            if (((newLevel->drawWinCorner->x + newLevel->drawWinMaxX +1) < newLevel->levelWidth))
            {
                newLevel->drawWinCorner->x++;
                for (y = 0; y < newLevel->drawWinMaxY; y++)
                {
                    for (x = 0; x < newLevel->drawWinMaxX; x++)
                    {
                        newLevel->drawWindowCoords[y][x].y = y + newLevel->drawWinCorner->y;
                        newLevel->drawWindowCoords[y][x].x = x + newLevel->drawWinCorner->x;
                    }
                }
            }
            break;
        case 4:     //down-right
            if (((newLevel->drawWinCorner->x + newLevel->drawWinMaxX + 1) < newLevel->levelWidth) && ((newLevel->drawWinCorner->y + newLevel->drawWinMaxY  + 1) < newLevel->levelHeight))
            {
                newLevel->drawWinCorner->y++;
                newLevel->drawWinCorner->x++;
                for (y = 0; y < newLevel->drawWinMaxY; y++)
                {
                    for (x = 0; x < newLevel->drawWinMaxX; x++)
                    {
                        newLevel->drawWindowCoords[y][x].y = y + newLevel->drawWinCorner->y;
                        newLevel->drawWindowCoords[y][x].x = x + newLevel->drawWinCorner->x;
                    }
                }
            }
            break;
        case 5:     //down
            if (((newLevel->drawWinCorner->y + newLevel->drawWinMaxY + 1) < newLevel->levelHeight))
            {
                newLevel->drawWinCorner->y++;
                for (y = 0; y < newLevel->drawWinMaxY; y++)
                {
                    for (x = 0; x < newLevel->drawWinMaxX; x++)
                    {
                        newLevel->drawWindowCoords[y][x].y = y + newLevel->drawWinCorner->y;
                        newLevel->drawWindowCoords[y][x].x = x + newLevel->drawWinCorner->x;
                    }
                }
            }
            break;
        case 6:     //down-left
            if (((newLevel->drawWinCorner->x - 1) >= 0) && ((newLevel->drawWinCorner->y + newLevel->drawWinMaxY + 1) < newLevel->levelHeight))
            {
                newLevel->drawWinCorner->y++;
                newLevel->drawWinCorner->x--;
                for (y = 0; y < newLevel->drawWinMaxY; y++)
                {
                    for (x = 0; x < newLevel->drawWinMaxX; x++)
                    {
                        newLevel->drawWindowCoords[y][x].y = y + newLevel->drawWinCorner->y;
                        newLevel->drawWindowCoords[y][x].x = x + newLevel->drawWinCorner->x;
                    }
                }
            }
            break;
        case 7:     //left
            if (((newLevel->drawWinCorner->x - 1) >= 0))
            {
                newLevel->drawWinCorner->x--;
                for (y = 0; y < newLevel->drawWinMaxY; y++)
                {
                    for (x = 0; x < newLevel->drawWinMaxX; x++)
                    {
                        newLevel->drawWindowCoords[y][x].y = y + newLevel->drawWinCorner->y;
                        newLevel->drawWindowCoords[y][x].x = x + newLevel->drawWinCorner->x;
                    }
                }
            }
            break;
    }
    return newLevel;
}

Level * drawMapInWindow(Windows * newWindows, Level * newLevel)
{
    for (int y = 0; y < newLevel->drawWinMaxY; y++)
    {
        for (int x = 0; x < newLevel->drawWinMaxX; x++)
        {
            drawMapElementInWindow(y, x, newWindows, newLevel);
        }
    }
    return newLevel;
}
/*
int drawMap(Level * newLevel)
{
    int y, x;

    for (y = 0; y <= newLevel->levelHeight; y++)
        {
            for (x = 0; x <= newLevel->levelWidth; x++)
            {
                //drawMapElement(y, x, newLevel);
            }
        }
    return 0;
}
*/
int drawMapElementInWindow(int y, int x, Windows * newWindows, Level * newLevel)
{
    if (newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].tileContents->player)
    {
        if (newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].terrain->bold)
            attron(A_BOLD);
        if (newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].terrain->dim)
            attron(A_DIM);
        wcolor_set(newWindows->mapWindow, newLevel->cPal[newLevel->newPlayer->playerColor][getBGColor(newLevel->drawWindowCoords[y][x].y, newLevel->drawWindowCoords[y][x].x, newLevel)], NULL);
        mvwprintw(newWindows->mapWindow, y, x, "%s", newLevel->newPlayer->playerSymbol);
    }
   /* else if (newLevel->levelMask[y][x].tileContents->npc)
    {
        if (newLevel->levelMask[y][x].terrain->bold)
            attron(A_BOLD);
        if (newLevel->levelMask[y][x].terrain->dim)
            attron(A_DIM);
        color_set(newLevel->cPal[newLevel->levelMask[y][x].terrain->symColor][getBGColor(y, x, newLevel)], NULL);
        if (strcmp(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD") == 0)
            mvaddch(y, x, ACS_CKBOARD);
        else
            mvprintw(y, x, "%s", newLevel->levelMask[y][x].terrain->symbol);
    }*/
    else if (newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].tileContents->lgObject)
    {
        if (newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].lgObject->bold)
            attron(A_BOLD);
        if (newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].lgObject->dim)
            attron(A_DIM);
        wcolor_set(newWindows->mapWindow, newLevel->cPal[newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].lgObject->symColor][getBGColor(newLevel->drawWindowCoords[y][x].y, newLevel->drawWindowCoords[y][x].x, newLevel)], NULL);
        mvwprintw(newWindows->mapWindow, y, x, "%s", newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].lgObject->symbol);
    }
   /* else if (newLevel->levelMask[y][x].tileContents->building)
    {
        if (newLevel->levelMask[y][x].terrain->bold)
            attron(A_BOLD);
        if (newLevel->levelMask[y][x].terrain->dim)
            attron(A_DIM);
        color_set(newLevel->cPal[newLevel->levelMask[y][x].terrain->symColor][(newLevel->levelMask[y][x].terrain->height * 2) + 232], NULL);
        if (strcmp(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD") == 0)
            mvaddch(y, x, ACS_CKBOARD);
        else
            mvprintw(y, x, "%s", newLevel->levelMask[y][x].terrain->symbol);
    }*/
    else if (newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].tileContents->terrain)
    {
        if (newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].terrain->bold)
            attron(A_BOLD);
        if (newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].terrain->dim)
            attron(A_DIM);
        if (strcmp(newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].terrain->ACStype, "none") == 0)
        {
            wcolor_set(newWindows->mapWindow, newLevel->cPal[newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].terrain->symColor][getBGColor(newLevel->drawWindowCoords[y][x].y, newLevel->drawWindowCoords[y][x].x, newLevel)], NULL);
        }
        else
        {
            wcolor_set(newWindows->mapWindow, newLevel->cPal[newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].terrain->symColor][(newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].terrain->height * 2) + 232], NULL);
        }
        if (strcmp(newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].terrain->ACStype, "ACS_CKBOARD") == 0)
            mvwaddch(newWindows->mapWindow, y, x, ACS_CKBOARD);
        else
            mvwprintw(newWindows->mapWindow, y, x, "%s", newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].terrain->symbol);
            //mvwprintw(newWindows->mapWindow, y, x, "%d", newLevel->levelMask[newLevel->drawWindowCoords[y][x].y][newLevel->drawWindowCoords[y][x].x].terrain->height);
    }
    attroff(A_BOLD);
    attroff(A_DIM);

    return 0;
}
