#include "brawl.h"
#include "level.h"
#include "build_bar.h"
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include <string.h>
#include "perlin.h"

Level * generateLevel(Level * newLevel, int levelNumber)
{
    newLevel->levelNumber = levelNumber;                //FIX THIS

    newLevel->levelSize = (rand() % 3);        // 0=small; 1=med; 2=lrg

    newLevel = generateHeightMap(newLevel);
    newLevel = interpolateHightMap(newLevel);
    newLevel = interpolateHightMap(newLevel);
    printw("Interpolation ... PASSED\n");
    getch();
    newLevel = generateBiome2(newLevel);
    newLevel = getStartingPosition(newLevel);
    
    return newLevel;
}

Level * generateHeightMap(Level * newLevel)
{
    int y, x;
    double tempArray;
    //double ** tempArray;
    //tempArray = (double **)malloc(sizeof(double) * newLevel->levelHeight);

    //for (y = 0; y < newLevel->levelHeight; y++)
    //{
        //tempArray[y] = (double *)malloc(sizeof(double) * newLevel->levelWidth);
    //}

    int rndSeed = (rand() % (99999 + 1 - 10000) + 10000);

    for(y = 0; y < newLevel->levelHeight; y++) 
    {
        for(x = 0; x < newLevel->levelWidth; x++) 
        {
            switch(newLevel->levelMask[y][x].world->biomeID)
            {
                case 0:
                tempArray = pnoise2d(x * newLevel->desertPerlinFreq, y * newLevel->desertPerlinFreq, newLevel->desertPerlinPersist, 8, rndSeed);
                newLevel->levelMask[y][x].terrain->height = (int)((tempArray + 1) * 4);
                if(newLevel->levelMask[y][x].terrain->height < 0)
                    newLevel->levelMask[y][x].terrain->height = 0;
                if(newLevel->levelMask[y][x].terrain->height > 9)
                    newLevel->levelMask[y][x].terrain->height = 9;
                break;
                case 3:
                tempArray = pnoise2d(x * newLevel->prairiePerlinFreq, y * newLevel->prairiePerlinFreq, newLevel->prairiePerlinPersist, 8, rndSeed);
                newLevel->levelMask[y][x].terrain->height = (int)((tempArray + 1) * 4);
                if(newLevel->levelMask[y][x].terrain->height < 0)
                    newLevel->levelMask[y][x].terrain->height = 0;
                if(newLevel->levelMask[y][x].terrain->height > 9)
                    newLevel->levelMask[y][x].terrain->height = 9;
                break;
                case 4:
                tempArray = pnoise2d(x * newLevel->swampPerlinFreq, y * newLevel->swampPerlinFreq, newLevel->swampPerlinPersist, 8, rndSeed);
                newLevel->levelMask[y][x].terrain->height = (int)((tempArray + 1) * 4);
                if(newLevel->levelMask[y][x].terrain->height < 0)
                    newLevel->levelMask[y][x].terrain->height = 0;
                if(newLevel->levelMask[y][x].terrain->height > 9)
                    newLevel->levelMask[y][x].terrain->height = 9;
                break;
                case 5:
                tempArray = pnoise2d(x * newLevel->mountainPerlinFreq, y * newLevel->mountainPerlinFreq, newLevel->mountainPerlinPersist, 8, rndSeed);
                newLevel->levelMask[y][x].terrain->height = (int)((tempArray + 1) * 4);
                if(newLevel->levelMask[y][x].terrain->height < 0)
                    newLevel->levelMask[y][x].terrain->height = 0;
                if(newLevel->levelMask[y][x].terrain->height > 9)
                    newLevel->levelMask[y][x].terrain->height = 9;
                break;
            }
        }
    }
    //free(tempArray);
    return newLevel;
}

Level * interpolateHightMap(Level * newLevel)
{
    int y, x, x1, x2, y1, y2, q11, q12, q21, q22, p, dist;
    int q00, q01, q02, q03;
    double r1, r2;
    /* Bilinear interpolation
     * R1 = ((x2 – x)/(x2 – x1))*Q11 + ((x – x1)/(x2 – x1))*Q21
     * R2 = ((x2 – x)/(x2 – x1))*Q12 + ((x – x1)/(x2 – x1))*Q22
     *
     * P = ((y2 – y)/(y2 – y1))*R1 + ((y – y1)/(y2 – y1))*R2
     */

    dist = 1;

    for (y = 0; y < newLevel->levelHeight; y++)
    {
        for (x = 0; x < newLevel->levelWidth; x++)
        {
            if ((y + dist < newLevel->levelHeight) && (y - dist >= 0) && (x + dist < newLevel->levelWidth) && (x - dist >= 0))
            {
                x1 = x - dist;
                x2 = x + dist;
                y1 = y + dist;
                y2 = y - dist;

                q00 = newLevel->levelMask[y - dist][x].terrain->height;
                q01 = newLevel->levelMask[y + dist][x - dist].terrain->height;
                q02 = newLevel->levelMask[y][x + dist].terrain->height;
                q03 = newLevel->levelMask[y][x - dist].terrain->height;
                q11 = newLevel->levelMask[y + dist][x - dist].terrain->height;
                q12 = newLevel->levelMask[y - dist][x - dist].terrain->height;
                q21 = newLevel->levelMask[y + dist][x + dist].terrain->height;
                q22 = newLevel->levelMask[y - dist][x + dist].terrain->height;

                //r1 = ((x2 - x)/(x2 - x1)) * q11 + ((x - x1)/(x2 - x1)) * q21;
                //r2 = ((x2 - x)/(x2 - x1)) * q12 + ((x - x1)/(x2 - x1)) * q22;
                //p = (int)((y2 - y)/(y2 - y1)) * r1 + ((y - y1)/(y2 - y1)) * r2;

                //r1 = (q11 / 2) + (q21 / 2); 
                //r2 = (q12 / 2) + (q22 / 2);

                //p = (int)(r1 / 2) + (r2 / 2);
                
                r1 = (q00 + q01 + q02 + q03 + q11 + q12 + q21 + q22) / 8;
                p = ((r1 - newLevel->levelMask[y][x].terrain->height) /2 ) + newLevel->levelMask[y][x].terrain->height;

                newLevel->levelMask[y][x].terrain->height = p;

                //printw("q11 is: %d, q12 is %d: q21 is: %d, q22 is: %d\n", q11, q12, q21, q22);
                //printw("r1 is: %f, r2 is %f, p is: %d", r1, r2, p);
                //getch();
            }
        }
    }
    return newLevel;
}

Level * generateBiome2(Level * newLevel)
{
    int y, x, b;
    
    /* default all tiles to dirt -- rethink this to come up with a more dynamic option  */
    for (y = 0; y < newLevel->levelHeight; y++)
    {
        for (x = 0; x < newLevel->levelWidth; x++)
        {
            newLevel = updateTerrain(y, x, true, 1001, newLevel);
        }
    }

    /* populate terrain via height map  */
    for (b = 9; b  >= 0; b--)
    {
        for (y = 0; y < newLevel->levelHeight; y++)
        {
            for (x = 0; x < newLevel->levelWidth; x++)
            {
                    if (newLevel->levelMask[y][x].terrain->height == b)
                    switch (newLevel->levelMask[y][x].world->biomeID)
                    {
                        case 0:         // dersert
                            switch (b)
                            {
                                case 9:
                                    newLevel = updateTerrain(y, x, true, 1003, newLevel);    
                                    break;
                                case 8:
                                    newLevel = updateTerrain(y, x, true, 1003, newLevel);   
                                    break;
                                case 7:
                                    newLevel = updateTerrain(y, x, true, 1003, newLevel);  
                                    break;
                                case 6:
                                    newLevel = weightedRandomTerrain(y, x, 90, 50, 1003, 1003, newLevel);
                                    break;
                                case 5:
                                    newLevel = weightedRandomTerrain(y, x, 80, 40, 1003, 1003, newLevel);
                                    break;
                                case 4:
                                    newLevel = weightedRandomTerrain(y, x, 70, 30, 1003, 1003, newLevel);
                                    break;
                                case 3:
                                    newLevel = weightedRandomTerrain(y, x, 40, 20, 1006, 1006, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.006, 0.001, 1006, 2006, newLevel);
                                    break;
                                case 2:
                                    newLevel = weightedRandomTerrain(y, x, 60, 30, 1006, 1006, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.007, 0.001, 1006, 2006, newLevel);
                                    break;
                                case 1:
                                    newLevel = weightedRandomTerrain(y, x, 80, 50, 1006, 1006, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.0085, 0.002, 1006, 2006, newLevel);
                                    break;
                                case 0:
                                    newLevel = weightedRandomTerrain(y, x, 90, 60, 1006, 1006, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.009, 0.003, 1006, 2006, newLevel);
                                    break;
                            }
                            break;
                        case 1:         // forest
                            switch (b)
                            {
                                case 9:
                                    newLevel = weightedRandomTerrain(y, x, 30, 20, 1004, 1004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.001, 0.001, 1001, 2005, newLevel);
                                    break;
                                case 8:
                                    newLevel = weightedRandomTerrain(y, x, 20, 10, 1004, 1004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.001, 0.001, 1001, 2005, newLevel);
                                    break;
                                case 7:
                                    newLevel = weightedRandomTerrain(y, x, 10, 5, 1004, 1004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.001, 0.001, 1001, 2005, newLevel);
                                    break;
                                case 6:
                                    newLevel = weightedRandomTerrain(y, x, 20, 10, 1001, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.03, 0.02, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.03, 0.02, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.001, 0.001, 1001, 2005, newLevel);
                                    break;
                                case 5:
                                    newLevel = weightedRandomTerrain(y, x, 30, 20, 1001, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.03, 0.02, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.03, 0.02, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.001, 0.001, 1001, 2005, newLevel);
                                    break;
                                case 4:
                                    newLevel = weightedRandomTerrain(y, x, 40, 30, 1001, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.001, 0.001, 1001, 2005, newLevel);
                                    break;
                                case 3:
                                    newLevel = weightedRandomTerrain(y, x, 50, 35, 1001, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.02, 0.01, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2004, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.001, 0.001, 1001, 2005, newLevel);
                                    break;
                                case 2:
                                    newLevel = weightedRandomTerrain(y, x, 60, 40, 1001, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.006, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.006, 1001, 2004, newLevel);
                                    break;
                                case 1:
                                    newLevel = weightedRandomTerrain(y, x, 70, 50, 1001, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.005, 0.0025, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.005, 0.0025, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.005, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.005, 1001, 2004, newLevel);
                                    break;
                                case 0:
                                    newLevel = weightedRandomTerrain(y, x, 80, 60, 1001, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.002, 0.001, 1001, 2001, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.002, 0.001, 1001, 2002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.001, 1001, 2004, newLevel);
                                    break;
                            }
                            break;
                        case 2:         // tundra
                            switch (b)
                            {
                                case 9:
                                    newLevel = weightedRandomTerrain(y, x, 99, 80, 1004, 1004, newLevel);
                                    break;
                                case 8:
                                    newLevel = weightedRandomTerrain(y, x, 99, 80, 1004, 1004, newLevel);
                                    break;
                                case 7:
                                    newLevel = weightedRandomTerrain(y, x, 90, 80, 1004, 1004, newLevel);
                                    break;
                                case 6:
                                    newLevel = weightedRandomTerrain(y, x, 90, 75, 1004, 1004, newLevel);
                                    break;
                                case 5:
                                    newLevel = weightedRandomTerrain(y, x, 80, 65, 1004, 1004, newLevel);
                                    break;
                                case 4:
                                    newLevel = weightedRandomTerrain(y, x, 75, 55, 1004, 1004, newLevel);
                                    break;
                                case 3:
                                    newLevel = weightedRandomTerrain(y, x, 10, 5, 1004, 1004, newLevel);
                                    break;
                                case 2:
                                    newLevel = weightedRandomTerrain(y, x, 5, 1, 1004, 1004, newLevel);
                                    break;
                                case 1:
                                    newLevel = weightedRandomTerrain(y, x, 1, 1, 1004, 1004, newLevel);
                                    break;
                                case 0:
                                    newLevel = weightedRandomTerrain(y, x, 0, 0, 1004, 1004, newLevel);
                                    break;
                            }
                            break;
                        case 3:         // prairie
                            switch (b)
                            {
                                case 9:
                                    newLevel = weightedRandomTerrain(y, x, 99, 80, 1002, 1002, newLevel);
                                    break;
                                case 8:
                                    newLevel = weightedRandomTerrain(y, x, 95, 80, 1002, 1002, newLevel);
                                    break;
                                case 7:
                                    newLevel = weightedRandomTerrain(y, x, 85, 70, 1002, 1002, newLevel);
                                    break;
                                case 6:
                                    newLevel = weightedRandomTerrain(y, x, 80, 60, 1002, 1002, newLevel);
                                    break;
                                case 5:
                                    newLevel = weightedRandomTerrain(y, x, 75, 50, 1002, 1002, newLevel);
                                    break;
                                case 4:
                                    newLevel = weightedRandomTerrain(y, x, 70, 40, 1002, 1002, newLevel);
                                    break;
                                case 3:
                                    newLevel = weightedRandomTerrain(y, x, 65, 35, 1002, 1002, newLevel);
                                    break;
                                case 2:
                                    newLevel = weightedRandomTerrain(y, x, 60, 30, 1002, 1002, newLevel);
                                    break;
                                case 1:
                                    newLevel = weightedRandomTerrain(y, x, 35, 15, 1002, 1002, newLevel);
                                    break;
                                case 0:
                                    newLevel = weightedRandomTerrain(y, x, 30, 10, 1002, 1002, newLevel);
                                    break;
                            }
                            break;
                        case 4:         // swamp
                            switch (b)
                            {
                                case 9:
                                    newLevel = weightedRandomTerrain(y, x, 75, 60, 1002, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2001, newLevel);
                                    newLevel = weightedRandomTerrainLlgObj(y , x, 1, 1, 1002, 2003, newLevel);
                                    newLevel = weightedRandomTerrainLlgObj(y , x, 1, 1, 1002, 2004, newLevel);
                                    newLevel = weightedRandomTerrainLlgObj(y , x, 1, 1, 1002, 2001, newLevel);
                                    break;
                                case 8:
                                    newLevel = weightedRandomTerrain(y, x, 70, 55, 1002, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2001, newLevel);
                                    break;
                                case 7:
                                    newLevel = weightedRandomTerrain(y, x, 65, 50, 1002, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2001, newLevel);
                                    break;
                                case 6:
                                    newLevel = weightedRandomTerrain(y, x, 60, 45, 1002, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.01, 0.01, 1002, 2001, newLevel);
                                    break;
                                case 5:
                                    newLevel = weightedRandomTerrain(y, x, 55, 40, 1002, 1002, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.005, 0.005, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.005, 0.005, 1002, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.005, 0.005, 1002, 2001, newLevel);
                                    break;
                                case 4:
                                    newLevel = weightedRandomTerrain(y, x, 30, 20, 1005, 1005, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.005, 0.005, 1005, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.005, 0.005, 1005, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.005, 0.005, 1005, 2001, newLevel);
                                    break;
                                case 3:
                                    newLevel = weightedRandomTerrain(y, x, 50, 30, 1005, 1005, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.003, 0.005, 1005, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.003, 0.005, 1005, 2003, newLevel);
                                    newLevel = weightedFractTerrainLlgObj(y, x, 0.002, 0.001, 1005, 2001, newLevel);
                                    break;
                                case 2:
                                    newLevel = weightedRandomTerrain(y, x, 75, 40, 1005, 1005, newLevel);
                                    break;
                                case 1:
                                    newLevel = updateTerrain(y, x, true, 1007, newLevel);
                                    break;
                                case 0:
                                    newLevel = updateTerrain(y, x, true, 1008, newLevel);
                                    break;
                            }
                            break;
                        case 5:         // mountain
                            switch (b)
                            {
                                case 9:
                                    newLevel = weightedRandomTerrain(y, x, 90, 70, 1004, 1004, newLevel);
                                    break;
                                case 8:
                                    newLevel = weightedRandomTerrain(y, x, 80, 50, 1004, 1004, newLevel);
                                    break;
                                case 7:
                                    newLevel = weightedRandomTerrain(y, x, 60, 40, 1004, 1004, newLevel);
                                    break;
                                case 6:
                                    newLevel = weightedRandomTerrain(y, x, 50, 30, 1004, 1004, newLevel);
                                    break;
                                case 5:
                                    newLevel = weightedRandomTerrain(y, x, 30, 10, 1004, 1004, newLevel);
                                    break;
                                case 4:
                                    newLevel = weightedRandomTerrain(y, x, 10, 5, 1004, 1004, newLevel);
                                    break;
                                case 3:
                                    newLevel = weightedRandomTerrain(y, x, 5, 5, 1004, 1004, newLevel);
                                    break;
                                case 2:
                                    newLevel = weightedRandomTerrain(y, x, 20, 10, 1001, 1002, newLevel);
                                    break;
                                case 1:
                                    newLevel = weightedRandomTerrain(y, x, 30, 15, 1001, 1002, newLevel);
                                    break;
                                case 0:
                                    newLevel = weightedRandomTerrain(y, x, 60, 20, 1001, 1002, newLevel);
                                    break;
                            }
                            break;
                    }
            }
        }
    }

    return newLevel;
}

Level * weightedRandomTerrain(int y, int x, int wghtpercent, int defpercent, int objectidmatch, int terraintypeadd, Level * newlevel)
{
    if ((y - 1 >= 0) && (y + 1 < newlevel->levelHeight) && (x - 1 >= 0) && (x + 1 < newlevel->levelWidth))    //fix this !!! creates a border of dirt around the entire map !!!
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                if ((newlevel->levelMask[y + i][x + j].terrain->objectID == objectidmatch) || (newlevel->levelMask[y - i][x - j].terrain->objectID == objectidmatch) || (newlevel->levelMask[y - i][x + j].terrain->objectID == objectidmatch) || (newlevel->levelMask[y + i][x - j].terrain->objectID == objectidmatch))
                {
                    if ((rand() % 101) < wghtpercent)
                    {
                        newlevel = updateTerrain(y, x, true, terraintypeadd, newlevel); 
                    }
                }
                else
                {
                    if ((rand() % 101) == defpercent)
                    {
                        newlevel = updateTerrain(y, x, true, terraintypeadd, newlevel);
                    }
                }
            }
        }
    }
    return newlevel;
}

/* If terrain == terrainIdMatch then use random percent given, else use other percentage  */
Level * weightedRandomTerrainLlgObj(int y, int x, int wghtPercent, int defPercent, int terrainIdMatch, int objectTypeAdd, Level * newlevel)
{
    int rndNum;
    if (!newlevel->levelMask[y][x].tileContents->lgObject)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                if ((newlevel->levelMask[y][x].terrain->objectID == terrainIdMatch))
                {
                    if ((rndNum =(rand() % 101)) < wghtPercent)
                    {
                        newlevel = updateLgObject(y, x, true, objectTypeAdd, newlevel); 
                        //mvprintw(0, newlevel->levelWidth + 2,"%d",rndNum);
                        //getch();
                    }
                }
                else
                {
                    if ((rand() % 101) == defPercent)
                    {
                        newlevel = updateLgObject(y, x, true, objectTypeAdd, newlevel);
                    }
                }
            }
        }
    }
    return newlevel;
}

/* for instances where percentage is < 1  */
Level * weightedFractTerrainLlgObj(int y, int x, double wghtPercent, double defPercent, int terrainIdMatch, int objectTypeAdd, Level * newlevel)
{
    double rndNum;
    if (!newlevel->levelMask[y][x].tileContents->lgObject)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                if ((newlevel->levelMask[y][x].terrain->objectID == terrainIdMatch))
                {
                    if ((rndNum = (double) rand() / (RAND_MAX)) < wghtPercent)
                    {
                        newlevel = updateLgObject(y, x, true, objectTypeAdd, newlevel); 
                        //mvprintw(0, newlevel->levelWidth + 2,"%f",rndNum);
                        //getch();
                    }
                }
                else
                {
                    if ((rndNum = (double) rand() / (RAND_MAX)) < defPercent)
                    {
                        newlevel = updateLgObject(y, x, true, objectTypeAdd, newlevel);
                    }
                }
            }
        }
    }
    return newlevel;
}

Level * updateBiome(int y, int x, bool hasBiome, Level * newLevel)
{
    if(hasBiome)
    {
        //strcpy(newLevel->levelMask[y][x].world->maskID, "B");
        //strcpy(newLevel->levelMask[y][x].world->biome, newLevel->levelBiome);
        newLevel->levelMask[y][x].tileContents->biome = true;
    }
    else
    {
        //strcpy(newLevel->levelMask[y][x].world->maskID, "\0");
        //strcpy(newLevel->levelMask[y][x].world->biome, "\0");
        newLevel->levelMask[y][x].tileContents->biome = false;
    }
    return newLevel;
}

Level * getStartingPosition(Level * newLevel)
{
    int y, x, rndY, rndX;

    while (!(newLevel->drawWinCorner->y) && !(newLevel->drawWinCorner->x))
    {
        rndY = rand() % newLevel->levelHeight;
        rndX = rand() % newLevel->levelWidth;
                
        if ((rndY >= 0) && (rndY + newLevel->drawWinMaxY <= newLevel->levelHeight))
        {
            if ((rndX >= 0) && (rndX + newLevel->drawWinMaxX <= newLevel->levelWidth))
            {
                newLevel->drawWinCorner->y = rndY;
                newLevel->drawWinCorner->x = rndX;
                for (y = 0; y < newLevel->drawWinMaxY; y++)
                {
                    for (x = 0; x < newLevel->drawWinMaxX; x++)
                    {
                        newLevel->drawWindowCoords[y][x].y = y + newLevel->drawWinCorner->y;
                        newLevel->drawWindowCoords[y][x].x = x + newLevel->drawWinCorner->x;
                    }
                }
                
            }
        }
    }

    rndY = rand() % newLevel->drawWinMaxY;
    rndX = rand() % newLevel->drawWinMaxX;

    newLevel->newPlayer->playerCoordinates.y = newLevel->drawWindowCoords[rndY][rndX].y;
    newLevel->newPlayer->playerCoordinates.x = newLevel->drawWindowCoords[rndY][rndX].x;

    newLevel->levelMask[newLevel->newPlayer->playerCoordinates.y][newLevel->newPlayer->playerCoordinates.x].tileContents->player = true;

    return newLevel;
}
