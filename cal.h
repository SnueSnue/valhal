#include <ncurses.h>

#ifndef CAL_H
#define CAL_H

typedef struct {
    WINDOW *win;
} Calendar;

Calendar new_cal();

int print_cal(Calendar *cal);

#endif // CAL_H
