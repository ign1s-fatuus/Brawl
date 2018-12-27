#include "brawl.h"
#include "world.h"
#include "level.h"

Level * generateWorld(Level * newLevel)
{
    newLevel->levelHeight = 40;
    newLevel->levelWidth = 150;

    newLevel = gnerateBiome(newLevel);

    return newLevel;
}

Level * gnerateBiome(Level * newLevel)
{
    int rndBiome, biomeDensityMax, biomeDensityMin, biomeMinSeedMin, biomeMinSeedMax, biomeMaxSeedMin, biomeMaxSeedMax;

    biomeDensityMin = 40;
    biomeDensityMax = 90;
    biomeMinSeedMin = 5;
    biomeMinSeedMax = 10;
    biomeMaxSeedMin = 25;
    biomeMaxSeedMax = 45;
    
    newLevel->biomeDensity = (rand() % (biomeDensityMax + 1 - biomeDensityMin) + biomeDensityMin);         
    newLevel->biomeMinSeed = (rand() % (biomeMinSeedMax + 1 - biomeMinSeedMin) + biomeMinSeedMin);    
    newLevel->biomeMaxSeed = (rand() % (biomeMaxSeedMax + 1 - biomeMaxSeedMin) + biomeMaxSeedMin);      
    rndBiome = (rand() % 6);

    switch(rndBiome)
    {
        case 0:
            strcpy(newLevel->levelBiome, "desert");
            break;
        case 1:
            strcpy(newLevel->levelBiome, "forest");
            break;
        case 2:
            strcpy(newLevel->levelBiome, "tundra");
            break;
        case 3:
            strcpy(newLevel->levelBiome, "prairie");
            break;
        case 4:
            strcpy(newLevel->levelBiome, "swamp");
            break;
        case 5:
            strcpy(newLevel->levelBiome, "mountain");
            break;
        default:
            break;
    }

    return newLevel;
}
