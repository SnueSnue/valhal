#include "cal.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Calendar new_cal(WINDOW *win){
    Calendar cal;
    cal.win = win;
    return cal;
}

int print_cal(Calendar *cal) {
    WINDOW *win = cal->win;

    box(win, 0, 0);
    mvwprintw(win, 0, 3,  "calendar");

    wrefresh(win);

    return 0;
}


int cal_handle_input(Calendar *cal, char ch) {
    waddch(cal->win, ch);
    wrefresh(cal->win);

    return 0;
}
