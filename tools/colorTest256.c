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
   
    int pair[256];


    for (b = 0; b < 256; b++)
    {
        pair[b] = counter;
        init_pair(pair[b], 0, b);
        counter++;
    }

    counter = 0;
    for (b = 0; b < 256; b++)
    {
        color_set(pair[b], NULL);
        addch(ACS_CKBOARD);
        printw("(%d)", b); 
        addch(ACS_CKBOARD);
        counter++;
        if (counter == 10)
        {
            counter = 0;
            printw("\n");
        }
    }

    refresh();
    
    getch();
	endwin();
    return 0;
}
