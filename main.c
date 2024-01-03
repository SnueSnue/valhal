#include "todo.h"
#include "cal.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum app {call, todo};

int main() {
    Todo_list todo_list;
    Calendar cal;
    WINDOW *todo_win;
    WINDOW *cal_win;
    int rows, cols;
    int ch;

    enum app current_app = todo;

    // int (*handle_input)(void*, char);
    // void *app;

    initscr();
    cbreak();
    // raw();
    keypad(stdscr, TRUE);
    noecho();
    refresh();

    getmaxyx(stdscr, rows, cols);
    cal_win = newwin(rows/2, cols/2, 0, 0);
    cal = new_cal(cal_win);
    // handle_input[0] = cal_handle_input; 
    todo_win = newwin(rows/2, cols/2, 0, cols/2);
    todo_list = new_list(todo_win);
    // handle_input[1] = todo_handle_input;

    print_todo_list(&todo_list);
    print_cal(&cal);

    while ((ch = (char)getch()) != 'q') {
        switch (ch) {
            case 'H':
                if (current_app == call) {
                    current_app = todo;
                    mvwprintw(cal_win, 0, 3, "Calendar");
                    wattron(todo_win, A_BOLD);
                    mvwprintw(todo_win, 0, 3, "todo list");
                    wattroff(todo_win, A_BOLD);
                    wmove(todo_win, 10, 3);
                }
                else {
                    current_app = call;
                    mvwprintw(todo_win, 0, 3, "todo list");
                    wattron(cal_win, A_BOLD);
                    mvwprintw(cal_win, 0, 3, "Calendar");
                    wattroff(cal_win, A_BOLD);
                    wmove(cal_win, 10, 3);
                }
                wrefresh(todo_win);
                wrefresh(cal_win);
                break;
            case 'L':
                if (current_app == call) {
                    current_app = todo;
                    mvwprintw(cal_win, 0, 3, "Calendar");
                    wattron(todo_win, A_BOLD);
                    mvwprintw(todo_win, 0, 3, "todo list");
                    wattroff(todo_win, A_BOLD);
                    wmove(todo_win, 10, 3);
                }
                else {
                    current_app = call;
                    mvwprintw(todo_win, 0, 3, "todo list");
                    wattron(cal_win, A_BOLD);
                    mvwprintw(cal_win, 0, 3, "Calendar");
                    wattroff(cal_win, A_BOLD);
                    wmove(cal_win, 10, 3);
                }
                wrefresh(cal_win);
                wrefresh(todo_win);
                break;
            default:
                if (current_app == call)
                    cal_handle_input(&cal, ch);
                else
                    todo_handle_input(&todo_list, ch);
        }
    }


    endwin();                  // End curses mode

    return 0;
}
