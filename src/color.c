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
            if ((b == 232) || (b == 234) || (b == 236) || (b == 238) || (b == 240) || (b == 242) || (b == 244) || (b == 246) || (b == 248) || (b == 250) ||
                (b == 58 ) || (b == 59 ) || (b == 101) || (b == 102) || (b == 94 ) || (b == 144) || (b == 145) || (b == 180) || (b == 181) || (b == 222) || 
                (b == 223) || (b == 230) || (b == 137) || (b == 61 ) || (b == 68 ) || (b == 104) || (b == 22 ) || (b == 28 ) || (b == 29 ) || (b == 64) ||
                (b == 65 ) || (b == 66 ) || (b == 252) || (b == 254))
            {
                newLevel->cPal[f][b] = counter;
                init_pair(newLevel->cPal[f][b], f, b);
                counter++;
            }
            else
            {
                newLevel->cPal[f][b] = 0;
            }
        }
    }

    return newLevel;
}

int getBGColor(int y, int x, Level * newLevel)
{
    int bgColor;
    switch (newLevel->levelMask[y][x].terrain->symColor)
    {
        case 94:
            switch (newLevel->levelMask[y][x].terrain->height)
            {
                case 0:
                    bgColor = 58;
                    break;
                case 1:
                    bgColor = 58;
                    break;
                case 2:
                    bgColor = 58;
                    break;
                case 3:
                    bgColor = 58;
                    break;
                case 4:
                    bgColor = 59;
                    break;
                case 5:
                    bgColor = 101;
                    break;
                case 6:
                    bgColor = 101;
                    break;
                case 7:
                    bgColor = 102;
                    break;
                case 8:
                    bgColor = 102;
                    break;
                case 9:
                    bgColor = 102;
                    break;
                default:
                    break;
            }
            break;
        case 61:
            switch (newLevel->levelMask[y][x].terrain->height)
            {
                case 0:
                    bgColor = 61;
                    break;
                case 1:
                    bgColor = 61;
                    break;
                case 2:
                    bgColor = 61;
                    break;
                case 3:
                    bgColor = 61;
                    break;
                case 4:
                    bgColor = 61;
                    break;
                case 5:
                    bgColor = 104;
                    break;
                case 6:
                    bgColor = 104;
                    break;
                case 7:
                    bgColor = 104;
                    break;
                case 8:
                    bgColor = 104;
                    break;
                case 9:
                    bgColor = 104;
                    break;
                default:
                    break;
            }
            break;
            case 22:
            switch (newLevel->levelMask[y][x].terrain->height)
            {
                case 0:
                    bgColor = 22;
                    break;
                case 1:
                    bgColor = 22;
                    break;
                case 2:
                    bgColor = 22;
                    break;
                case 3:
                    bgColor = 22;
                    break;
                case 4:
                    bgColor = 22;
                    break;
                case 5:
                    bgColor = 66;
                    break;
                case 6:
                    bgColor = 66;
                    break;
                case 7:
                    bgColor = 66;
                    break;
                case 8:
                    bgColor = 65;
                    break;
                case 9:
                    bgColor = 65;
                    break;
                default:
                    break;
            }
                break;
            case 254:
            switch (newLevel->levelMask[y][x].terrain->height)
            {
                case 0:
                    bgColor = 244;
                    break;
                case 1:
                    bgColor = 244;
                    break;
                case 2:
                    bgColor = 246;
                    break;
                case 3:
                    bgColor = 246;
                    break;
                case 4:
                    bgColor = 248;
                    break;
                case 5:
                    bgColor = 248;
                    break;
                case 6:
                    bgColor = 250;
                    break;
                case 7:
                    bgColor = 250;
                    break;
                case 8:
                    bgColor = 252;
                    break;
                case 9:
                    bgColor = 252;
                    break;
                default:
                    break;
            }
                break;
    }
    return bgColor;
}
