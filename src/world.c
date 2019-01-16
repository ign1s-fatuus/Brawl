#include "brawl.h"
#include "world.h"
#include "level.h"
#include "perlin.h"

Level * generateWorld(Level * newLevel)
{
    //newLevel->levelHeight = 1000;
    //newLevel->levelWidth = 1000;


    newLevel->worldHeight = 15;
    newLevel->worldWidth = 35;
    newLevel->worldTileWidth = 100;
    newLevel->worldTileHeight = 100;
    newLevel->levelHeight = newLevel->worldHeight * newLevel->worldTileHeight;
    newLevel->levelWidth = newLevel->worldWidth * newLevel->worldTileWidth;

    newLevel->worldPerlinFreq = 0.008;
    newLevel->worldPerlinPersist = 0.45;

    newLevel = gnerateBiome(newLevel);

    return newLevel;
}

Level * generateWorldHeightMap(Level * newLevel)
{
    int y, x;
    double tempReturnVal;
    int tempBiomeHeight;
    //double ** tempArray; //[newLevel->worldHeight][newLevel->worldWidth];
    int rndSeed = (rand() % (99999 + 1 - 10000) + 10000);
    
    clear();
    //tempArray = (double **)malloc(sizeof(double) * newLevel->worldHeight);
    for(y = 0; y < newLevel->levelHeight; y++) 
    {
        //tempArray[y] = (double *)malloc(sizeof(double) * newLevel->worldWidth);
        for(x = 0; x < newLevel->levelWidth; x++) 
        {
            tempReturnVal = pnoise2d(x * newLevel->worldPerlinFreq, y * newLevel->worldPerlinFreq, newLevel->worldPerlinPersist, 8, rndSeed);
            tempBiomeHeight = (int)((tempReturnVal + 1) * 4);
            if(tempBiomeHeight < 0)
                tempBiomeHeight = 0;
            if(tempBiomeHeight > 9)
                tempBiomeHeight = 9;
            switch(tempBiomeHeight)
            {
                case 0 ... 1:
                    newLevel->levelMask[y][x].world->biomeID = 4;   //swamp
                    break;
                case 2 ... 4:
                    newLevel->levelMask[y][x].world->biomeID = 3;   //prairie
                    break;
                case 5 ... 6:
                    newLevel->levelMask[y][x].world->biomeID = 0;   //desert
                    break;
                case 7 ... 9:
                    newLevel->levelMask[y][x].world->biomeID = 5;   //Mountain
                    break;
            
            }
            //mvprintw(y, x, "%d", newLevel->levelMask[y][x].world->biomeID);
            //getch();
        }
    }
    //printw("\nWorld map genrated");
    //getch();
    //free(tempArray);
    return newLevel;
}

Level * gnerateBiome(Level * newLevel)
{
    newLevel->desertPerlinFreq = 0.03;      //0.03
    newLevel->desertPerlinPersist = 0.2;    //0,2
    newLevel->prairiePerlinFreq = 0.02;     //0.02
    newLevel->prairiePerlinPersist = 0.425; //0.425
    newLevel->swampPerlinFreq = 0.07;       //0.07
    newLevel->swampPerlinPersist = 0.625;   //0.225
    newLevel->mountainPerlinFreq = 0.03;    //0.03
    newLevel->mountainPerlinPersist = 0.7;  //0.7

    return newLevel;
}

Level * generateMiniMap(Level * newLevel)
{
    int y, x, i, j;

    clear();

    newLevel->miniMap = malloc(sizeof(char *) * newLevel->worldHeight);
    for (y = 0; y < newLevel->worldHeight; y++)
    {
        newLevel->miniMap[y] = malloc(sizeof(char) * newLevel->worldWidth);
        //for (x = 0; x < newLevel->worldWidth; x++)
        //{
           // newLevel->miniMap[y][x] = 'x';
           // mvprintw(y, x, "%c", newLevel->miniMap[y][x]);
        //}
    }

    for (y = 0; y < newLevel->worldHeight; y++)
    {
        for (x = 0; x < newLevel->worldWidth; x++)
        {
            int countDesert = 0, countPrairie = 0, countSwamp = 0, countMountain = 0;
            for (i = y * newLevel->worldTileHeight; i < (y * newLevel->worldTileHeight) + newLevel->worldTileHeight; i++)
            {
                for (j = x * newLevel->worldTileWidth; j < (x * newLevel->worldTileWidth) + newLevel->worldTileWidth; j++)
                {
                    //clear();
                    //mvprintw(0, 100, "y is: %d, yMax is %d", y, newLevel->worldHeight);
                    //mvprintw(1, 100, "x is: %d, xMax is %d", x, newLevel->worldWidth);
                    //mvprintw(2, 100, "i is: %d, iMax is %d", i, y * newLevel->worldTileHeight + newLevel->worldTileHeight);
                    //mvprintw(3, 100, "j is: %d, jMax is %d", j, x * newLevel->worldTileWidth + newLevel->worldTileWidth);
                    switch (newLevel->levelMask[i][j].world->biomeID)
                    {
                        case 0:
                            countDesert++;
                            break;
                        case 3:
                            countPrairie++;
                            break;
                        case 4:
                            countSwamp++;
                            break;
                        case 5:
                            countMountain++;
                            break;
                        default:
                            break;
                    }
                }
            }
            if ((countDesert > countPrairie) && (countDesert > countSwamp) && (countDesert > countMountain))
                newLevel->miniMap[y][x] = 'D';
            else if ((countPrairie > countDesert) && (countPrairie > countSwamp) && (countPrairie > countMountain))
                newLevel->miniMap[y][x] = 'P';
            else if ((countSwamp > countDesert) && (countSwamp > countPrairie) && (countSwamp > countMountain))
                newLevel->miniMap[y][x] = 'S';
            else if ((countMountain > countDesert) && (countMountain > countPrairie) && (countDesert > countSwamp))
                newLevel->miniMap[y][x] = 'M';
            else
                newLevel->miniMap[y][x] = '?';

            mvprintw(y, x,"%c", newLevel->miniMap[y][x]);
            //getch();
        }
    }
    return newLevel;
}
