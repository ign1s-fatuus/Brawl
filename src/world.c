#include "brawl.h"
#include "world.h"
#include "level.h"

Level * generateWorld(Level * newLevel)
{
    newLevel->levelHeight = 500;
    newLevel->levelWidth = 700;

    newLevel = gnerateBiome(newLevel);

    return newLevel;
}

Level * gnerateBiome(Level * newLevel)
{
    int rndBiome, biomeDensityMax, biomeDensityMin, biomeMinSeedMin, biomeMinSeedMax, biomeMaxSeedMin, biomeMaxSeedMax;
    int envPriTrnObjMin, envPriTrnObjMax, envSecTrnObjMin, envSecTrnObjMax, envPriTrnMin, envPriTrnMax, envSecTrnMin, envSecTrnMax;

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
            newLevel->levelBiomeID = 0;
            envPriTrnObjMin = 10;
            envPriTrnObjMax = 30;
            envSecTrnObjMin = 10;
            envSecTrnObjMax = 20;
            envPriTrnMin = 60;
            envPriTrnMax = 70;
            envSecTrnMin = 20;
            envSecTrnMax = 30;
            newLevel->perlinFreq = 0.03;
            newLevel->perlinPersist = 0.2;
            break;
        case 1:
            strcpy(newLevel->levelBiome, "forest");
            newLevel->levelBiomeID = 1;
            envPriTrnObjMin = 30;
            envPriTrnObjMax = 60;
            envSecTrnObjMin = 10;
            envSecTrnObjMax = 20;
            envPriTrnMin = 40;
            envPriTrnMax = 60;
            envSecTrnMin = 20;
            envSecTrnMax = 40;
            newLevel->perlinFreq = 0.025;
            newLevel->perlinPersist = 0.4;
            break;
        case 2:
            strcpy(newLevel->levelBiome, "tundra");
            newLevel->levelBiomeID = 2;
            envPriTrnObjMin = 10;
            envPriTrnObjMax = 20;
            envSecTrnObjMin = 10;
            envSecTrnObjMax = 20;
            envPriTrnMin = 50;
            envPriTrnMax = 70;
            envSecTrnMin = 20;
            envSecTrnMax = 30;
            newLevel->perlinFreq = 0.05;
            newLevel->perlinPersist = 0.35;
            break;
        case 3:
            strcpy(newLevel->levelBiome, "prairie");
            newLevel->levelBiomeID = 3;
            envPriTrnObjMin = 10;
            envPriTrnObjMax = 20;
            envSecTrnObjMin = 10;
            envSecTrnObjMax = 20;
            envPriTrnMin = 60;
            envPriTrnMax = 70;
            envSecTrnMin = 20;
            envSecTrnMax = 30;
            newLevel->perlinFreq = 0.02;
            newLevel->perlinPersist = 0.425;
            break;
        case 4:
            strcpy(newLevel->levelBiome, "swamp");
            newLevel->levelBiomeID = 4;
            envPriTrnObjMin = 10;
            envPriTrnObjMax = 20;
            envSecTrnObjMin = 10;
            envSecTrnObjMax = 20;
            envPriTrnMin = 30;
            envPriTrnMax = 40;
            envSecTrnMin = 40;
            envSecTrnMax = 60;
            newLevel->perlinFreq = 0.07;
            newLevel->perlinPersist = 0.225;
            break;
        case 5:
            strcpy(newLevel->levelBiome, "mountain");
            newLevel->levelBiomeID = 5;
            envPriTrnObjMin = 30;
            envPriTrnObjMax = 40;
            envSecTrnObjMin = 10;
            envSecTrnObjMax = 20;
            envPriTrnMin = 60;
            envPriTrnMax = 70;
            envSecTrnMin = 20;
            envSecTrnMax = 30;
            newLevel->perlinFreq = 0.03;
            newLevel->perlinPersist = 0.7;
            break;
        default:
            break;
    }

    newLevel->envPriTrnObjDensity = (rand () % (envPriTrnObjMax + 1 - envPriTrnObjMin) + envPriTrnObjMin);
    newLevel->envSecTrnObjDensity = (rand () % (envSecTrnObjMax + 1 - envSecTrnObjMin) + envSecTrnObjMin);
    newLevel->envPriTrnDensity = (rand () % (envPriTrnMax + 1 - envPriTrnMin) + envPriTrnMin);
    newLevel->envSecTrnDensity = (rand () % (envSecTrnMax + 1 - envSecTrnMin) + envSecTrnMin);

    return newLevel;
}
