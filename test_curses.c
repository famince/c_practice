// curses 图形化库
// gcc test_curses.c -o test_curses -lcurses
#include<curses.h>
int main()
{
    initscr();

    box(stdscr, ACS_VLINE, ACS_HLINE); /*draw a box*/

    move(LINES/2, COLS/2); /*move the cursor to the center*/

    waddstr(stdscr, "Hello, world!");

    refresh();

    getch();

    endwin();

    return 0;
}
