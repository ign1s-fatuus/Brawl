#include "brawl.h"
#include "level.h"

Level * buildColorPalette(Level * newLevel)
{
    int counter, f, b;
    counter = 1;

    for (f = 0; f < 256; f++)
    {
        for (b = 0; b < 256; b++)
        {
            if ((b == 232) || (b == 234) || (b == 236) || (b == 238) || (b == 240) || (b == 242) || (b == 244) || (b == 246) || (b == 248) || (b == 250))
            {
                if ((f == 20) || (f == 21) || (f == 22) || (f == 28) || (f == 33) || (f == 45) || (f == 52) || (f == 56) || (f == 61) || (f == 62) || (f == 64) || (f == 94) || (f == 106) || (f == 124) || (f == 161) || (f == 166) || (f == 172) || (f == 198) || (f == 202) || (f == 208) || (f == 220) || (f == 226) || (f == 229) || (f == 232))
                {
                    newLevel->cPal[f][b] = counter;
                    init_pair(newLevel->cPal[f][b], f, b);
                    counter++;
                }
            }
            else
            {
                newLevel->cPal[f][b] = 0;
            }
        }
    }

    return newLevel;
}

