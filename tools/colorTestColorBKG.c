#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

//#define MY_A_COLOR NCURSES_BITS(((1U) << 16) - 1U, 0)
//#define MY_COLOR_PAIR(n) (NCURSES_BITS((n), 0) & MY_A_COLOR)

int main()
{
	initscr();
	
    start_color();
    setlocale(LC_ALL,"");
    curs_set(0);
    
    int counter, f, b;
    counter = 1;
   
    int pair[256][256];

    init_pair(259, 172, 255);
    color_set(259, NULL);
    printw("THIS IS A TEST %d", COLOR_PAIRS);
    getch();
    //attroff(MY_COLOR_PAIR(259));

    for (f = 0; f < 256; f++)
    {
        for (b = 0; b < 100; b++)
        {
            pair[f][b] = counter;
            init_pair(pair[f][b], f, b);
            counter++;
        }
    }

    counter = 0;
    for (f = 0; f < 40; f++)
    {
        for (b = 0; b < 150; b++)
        {
            if (pair[f][b] != 0)
            {
                color_set(pair[f][b], NULL);
                mvaddch(f, b, ACS_CKBOARD);
                getch();

                counter++;
                if (counter == 10)
                {
                    counter = 0;
                    printw("\n");
                }
            }
        }
    }

    refresh();
    
    getch();
	endwin();
    return 0;
}
