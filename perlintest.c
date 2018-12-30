#include <stdio.h>
#include <time.h>
#include "perlin.h"
#include <stdlib.h>
#include <ncurses.h>

int main() {
    int i = 0, j = 0, c = 0;
    double n[40][140];
    int newArray[40][140];
    double freq = 0.07;
    double persistance = 0.07;
    int octaves = 8;

    srand(time(NULL));
    int str;
    
    initscr();
    noecho;
    start_color();
    
    while ((str = getch()) != 'q')
    {
        clear();
        switch (str)
        {
            case 'a':
                freq -= 0.001;
                if (freq < 0.001)
                    freq = 0.001;
                break;
            case 's':
                freq += 0.001;
                break;
            case 'z':
                persistance -= 0.001;
                if (persistance < 0.001)
                    persistance = 0.001;
                break;
            case 'x':
                persistance += 0.001;
                break;
            case 'o':
                octaves -= 1;
                if (octaves < 1)
                    octaves = 1;
                break;
            case 'p':
                octaves += 1;
                if (octaves > 8)
                    octaves = 8;
                break;
        }
        
        mvprintw(41, 0, "freq is: %f, perisitance is: %f, octaves is: %d", freq, persistance, octaves);
        refresh();

        int rndSeed = (rand() % (99999 + 1 - 10000) + 10000);
        for(i = 0; i < 40; i++) {
            for(j = 0; j < 140; j++) {
                n[i][j] = pnoise2d(j * freq, i * freq, persistance, octaves, rndSeed);
                newArray[i][j] = (int)((n[i][j] + 1) * 4);
                if(newArray[i][j] < 0)
                    newArray[i][j] = 0;
                if(newArray[i][j] > 9)
                    newArray[i][j] = 9;
            }
        }

        mvprintw(10, 10, "help me");
        for (int p = 0; p <= 9; p++ )
        {
            init_pair(p, 0, (231 + (p + 2)));
        }

        for (int y = 0; y < 40; y++)
        {
            for (int x = 0; x < 140; x++)
            {
                mvprintw(y, x, "%d", newArray[y][x]);
                switch (newArray[y][x])
                {
                    case 0:
                        attron(COLOR_PAIR(0));
                        mvprintw(y, x, " " );
                        attroff(COLOR_PAIR(0));
                        break;
                    case 1:
                        attron(COLOR_PAIR(1));
                        mvprintw(y, x, "1" );
                        attroff(COLOR_PAIR(1));
                        break;
                    case 2:
                        attron(COLOR_PAIR(2));
                        mvprintw(y, x, "2" );
                        attroff(COLOR_PAIR(2));
                        break;
                    case 3:
                        attron(COLOR_PAIR(3));
                        mvprintw(y, x, "3" );
                        attroff(COLOR_PAIR(3));
                        break;
                    case 4:
                        attron(COLOR_PAIR(4));
                        mvprintw(y, x, "4" );
                        attroff(COLOR_PAIR(4));
                        break;
                    case 5:
                        attron(COLOR_PAIR(5));
                        mvprintw(y, x, "5" );
                        attroff(COLOR_PAIR(5));
                        break;
                    case 6:
                        attron(COLOR_PAIR(6));
                        mvprintw(y, x, "6" );
                        attroff(COLOR_PAIR(6));
                        break;
                    case 7:
                        attron(COLOR_PAIR(7));
                        mvprintw(y, x, "7" );
                        attroff(COLOR_PAIR(7));
                        break;
                    case 8:
                        attron(COLOR_PAIR(8));
                        mvprintw(y, x, "8" );
                        attroff(COLOR_PAIR(8));
                        break;
                    case 9:
                        attron(COLOR_PAIR(9));
                        mvprintw(y, x, "9" );
                        attroff(COLOR_PAIR(9));
                        break;
                    default:
                        break;
                }
            }
        }
    }
    getch();
    refresh();
    endwin();
    return 0;
}
