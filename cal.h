#include <ncurses.h>

#ifndef CAL_H
#define CAL_H

typedef struct {
    WINDOW *win;
} Calendar;

Calendar new_cal();

int print_cal(Calendar *cal);

int cal_handle_input(Calendar *cal, char ch);

#endif // CAL_H
