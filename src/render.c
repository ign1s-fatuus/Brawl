#include "brawl.h"
#include "level.h"

int drawMap(Level * newLevel)
{
    int y, x;

    for (y = 0; y <= newLevel->levelHeight; y++)
        {
            for (x = 0; x <= newLevel->levelWidth; x++)
            {
                if (newLevel->levelMask[y][x].tileContents->player)
                {
                    if (newLevel->levelMask[y][x].terrain->bold)
                    {
                    attron(A_BOLD);
                    }
                    if (newLevel->levelMask[y][x].terrain->dim)
                    {
                        attron(A_DIM);
                    }
                    attron(COLOR_PAIR(newLevel->cPal[newLevel->newPlayer->playerColor][(newLevel->levelMask[y][x].terrain->height * 2) + 232]));
                    mvprintw(y, x, "%s", newLevel->newPlayer->playerSymbol);
                }
                else if (newLevel->levelMask[y][x].tileContents->npc)
                {
                    if (newLevel->levelMask[y][x].terrain->bold)
                    {
                    attron(A_BOLD);
                    }
                    if (newLevel->levelMask[y][x].terrain->dim)
                    {
                        attron(A_DIM);
                    }
                    attron(COLOR_PAIR(newLevel->cPal[newLevel->levelMask[y][x].terrain->symColor][(newLevel->levelMask[y][x].terrain->height * 2) + 232]));
                    if (strcmp(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD") == 0)
                    {
                        mvaddch(y, x, ACS_CKBOARD);
                    }
                    else
                    {
                        mvprintw(y, x, "%s", newLevel->levelMask[y][x].terrain->symbol);
                    }
                }
                else if (newLevel->levelMask[y][x].tileContents->lgObject)
                {
                    if (newLevel->levelMask[y][x].lgObject->bold)
                    {
                    attron(A_BOLD);
                    }
                    if (newLevel->levelMask[y][x].lgObject->dim)
                    {
                        attron(A_DIM);
                    }
                    attron(COLOR_PAIR(newLevel->cPal[newLevel->levelMask[y][x].lgObject->symColor][(newLevel->levelMask[y][x].terrain->height * 2) + 232]));
                    //if (strcmp(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD") == 0)
                    //{
                    //    mvaddch(y, x, ACS_CKBOARD);
                    //}
                    //else
                    //{
                        mvprintw(y, x, "%s", newLevel->levelMask[y][x].lgObject->symbol);
                    //}
                }
                else if (newLevel->levelMask[y][x].tileContents->smObject)
                {
                    if (newLevel->levelMask[y][x].smObject->bold)
                    {
                    attron(A_BOLD);
                    }
                    if (newLevel->levelMask[y][x].smObject->dim)
                    {
                        attron(A_DIM);
                    }
                    attron(COLOR_PAIR(newLevel->cPal[newLevel->levelMask[y][x].smObject->symColor][(newLevel->levelMask[y][x].terrain->height * 2) + 232]));
                    if (strcmp(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD") == 0)
                    {
                        mvaddch(y, x, ACS_CKBOARD);
                    }
                    else
                    {
                        mvprintw(y, x, "%s", newLevel->levelMask[y][x].smObject->symbol);
                    }
                }
                else if (newLevel->levelMask[y][x].tileContents->building)
                {
                    if (newLevel->levelMask[y][x].terrain->bold)
                    {
                    attron(A_BOLD);
                    }
                    if (newLevel->levelMask[y][x].terrain->dim)
                    {
                        attron(A_DIM);
                    }
                    attron(COLOR_PAIR(newLevel->cPal[newLevel->levelMask[y][x].terrain->symColor][(newLevel->levelMask[y][x].terrain->height * 2) + 232]));
                    if (strcmp(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD") == 0)
                    {
                        mvaddch(y, x, ACS_CKBOARD);
                    }
                    else
                    {
                        mvprintw(y, x, "%s", newLevel->levelMask[y][x].terrain->symbol);
                    }
                }
                else if (newLevel->levelMask[y][x].tileContents->terrain)
                {
                    if (newLevel->levelMask[y][x].terrain->bold)
                    {
                    attron(A_BOLD);
                    }
                    if (newLevel->levelMask[y][x].terrain->dim)
                    {
                        attron(A_DIM);
                    }
                    attron(COLOR_PAIR(newLevel->cPal[newLevel->levelMask[y][x].terrain->symColor][(newLevel->levelMask[y][x].terrain->height * 2) + 232]));
                    if (strcmp(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD") == 0)
                    {
                        mvaddch(y, x, ACS_CKBOARD);
                    }
                    else
                    {
                        mvprintw(y, x, "%s", newLevel->levelMask[y][x].terrain->symbol);
                    }
                }
                attroff(COLOR_PAIR(newLevel->cPal[newLevel->levelMask[y][x].terrain->symColor][(newLevel->levelMask[y][x].terrain->height * 2) + 232]));
                attroff(A_BOLD);
                attroff(A_DIM);
            }
            printf("\n");
        }
    return 0;
}

int redrawMapElement(int y, int x, Level * newLevel)
{
    if (newLevel->levelMask[y][x].tileContents->player)
    {
        if (newLevel->levelMask[y][x].terrain->bold)
        {
        attron(A_BOLD);
        }
        if (newLevel->levelMask[y][x].terrain->dim)
        {
            attron(A_DIM);
        }
        attron(COLOR_PAIR(newLevel->cPal[newLevel->newPlayer->playerColor][(newLevel->levelMask[y][x].terrain->height * 2) + 232]));
        mvprintw(y, x, "%s", newLevel->newPlayer->playerSymbol);
    }
    else if (newLevel->levelMask[y][x].tileContents->npc)
    {
        if (newLevel->levelMask[y][x].terrain->bold)
        {
        attron(A_BOLD);
        }
        if (newLevel->levelMask[y][x].terrain->dim)
        {
            attron(A_DIM);
        }
        attron(COLOR_PAIR(newLevel->cPal[newLevel->levelMask[y][x].terrain->symColor][(newLevel->levelMask[y][x].terrain->height * 2) + 232]));
        if (strcmp(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD") == 0)
        {
            mvaddch(y, x, ACS_CKBOARD);
        }
        else
        {
            mvprintw(y, x, "%s", newLevel->levelMask[y][x].terrain->symbol);
        }
    }
    else if (newLevel->levelMask[y][x].tileContents->lgObject)
    {
        if (newLevel->levelMask[y][x].lgObject->bold)
        {
        attron(A_BOLD);
        }
        if (newLevel->levelMask[y][x].lgObject->dim)
        {
            attron(A_DIM);
        }
        attron(COLOR_PAIR(newLevel->cPal[newLevel->levelMask[y][x].lgObject->symColor][(newLevel->levelMask[y][x].terrain->height * 2) + 232]));
        //if (strcmp(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD") == 0)
        //{
        //    mvaddch(y, x, ACS_CKBOARD);
        //}
        //else
        //{
            mvprintw(y, x, "%s", newLevel->levelMask[y][x].lgObject->symbol);
        //}
    }
    else if (newLevel->levelMask[y][x].tileContents->smObject)
    {
        if (newLevel->levelMask[y][x].smObject->bold)
        {
        attron(A_BOLD);
        }
        if (newLevel->levelMask[y][x].smObject->dim)
        {
            attron(A_DIM);
        }
        attron(COLOR_PAIR(newLevel->cPal[newLevel->levelMask[y][x].smObject->symColor][(newLevel->levelMask[y][x].terrain->height * 2) + 232]));
        if (strcmp(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD") == 0)
        {
            mvaddch(y, x, ACS_CKBOARD);
        }
        else
        {
            mvprintw(y, x, "%s", newLevel->levelMask[y][x].smObject->symbol);
        }
    }
    else if (newLevel->levelMask[y][x].tileContents->building)
    {
        if (newLevel->levelMask[y][x].terrain->bold)
        {
        attron(A_BOLD);
        }
        if (newLevel->levelMask[y][x].terrain->dim)
        {
            attron(A_DIM);
        }
        attron(COLOR_PAIR(newLevel->cPal[newLevel->levelMask[y][x].terrain->symColor][(newLevel->levelMask[y][x].terrain->height * 2) + 232]));
        if (strcmp(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD") == 0)
        {
            mvaddch(y, x, ACS_CKBOARD);
        }
        else
        {
            mvprintw(y, x, "%s", newLevel->levelMask[y][x].terrain->symbol);
        }
    }
    else if (newLevel->levelMask[y][x].tileContents->terrain)
    {
        if (newLevel->levelMask[y][x].terrain->bold)
        {
        attron(A_BOLD);
        }
        if (newLevel->levelMask[y][x].terrain->dim)
        {
            attron(A_DIM);
        }
        attron(COLOR_PAIR(newLevel->cPal[newLevel->levelMask[y][x].terrain->symColor][(newLevel->levelMask[y][x].terrain->height * 2) + 232]));
        if (strcmp(newLevel->levelMask[y][x].terrain->ACStype, "ACS_CKBOARD") == 0)
        {
            mvaddch(y, x, ACS_CKBOARD);
        }
        else
        {
            mvprintw(y, x, "%s", newLevel->levelMask[y][x].terrain->symbol);
        }
    }
    attroff(COLOR_PAIR(newLevel->cPal[newLevel->levelMask[y][x].terrain->symColor][(newLevel->levelMask[y][x].terrain->height * 2) + 232]));
    attroff(A_BOLD);
    attroff(A_DIM);

    return 0;
}

