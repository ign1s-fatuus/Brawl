#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>


int main()
{
	initscr();
	start_color();
    setlocale(LC_ALL,"");
    curs_set(0);
    
    int counter, f, b;
    counter = 1;
   
    int pair[256][256];


    for (f = 0; f < 256; f++)
    {
        for (b = 0; b < 256; b++)
        {
            if ((b == 232) || (b == 234) || (b == 236) || (b == 238) || (b == 240) || (b == 242) || (b == 244) || (b == 246) || (b == 248) || (b == 250))
            {
                if ((f == 20) || (f == 21) || (f == 22) || (f == 28) || (f == 33) || (f == 45) || (f == 52) || (f == 56) || (f == 61) || (f == 62) || (f == 64) || (f == 94) || (f == 106) || (f == 124) || (f == 161) || (f == 166) || (f == 172) || (f == 198) || (f == 202) || (f == 208) || (f == 220) || (f == 226) || (f == 229) || (f == 232))
                {
                    pair[f][b] = counter;
                    init_pair(pair[f][b], f, b);
                    counter++;
                }
            }
            else
            {
                pair[f][b] = 0;
            }
        }
    }

    counter = 0;
    for (f = 16; f < 232; f++)
    {
        for (b = 232; b < 256; b++)
        {
            if (pair[f][b] != 0)
            {
                //attron(COLOR_PAIR(pair[f][b]));
                color_set(pair[f][b], NULL);
                addch(ACS_CKBOARD);
                addch(ACS_CKBOARD);
                printw("(%d,%d)", f, b); 
                addch(ACS_CKBOARD);
                addch(ACS_CKBOARD);
                //attroff(COLOR_PAIR(pair[f][b]));

                counter++;
                if (counter == 10)
                {
                    counter = 0;
                    printw("\n");
                }
            }
        }
    }

    /*for (int x = 0; x < 9; x++)
    {
        attron(COLOR_PAIR(pair[20][(x * 2) + 232]));
        printw("(%d,%d)", x, (x * 2) + 232); 
        addch(ACS_CKBOARD);
        attroff(COLOR_PAIR(pair[20][(x * 2) + 232]));
    
    }*/
    refresh();
    
    getch();
	endwin();
    return 0;
}
