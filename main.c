#include "todo.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int ch;
    Todo_list todo_list;
    FILE *p_todo;
    WINDOW *todo_win;
    int rows, cols;

    initscr();
    cbreak();
    // raw();
    keypad(stdscr, TRUE);
    noecho();

    getmaxyx(stdscr, rows, cols);
    todo_win = newwin(rows/2, cols/2, 0, cols/2);
    todo_list = new_list(todo_win);

    move(3, 0);

    print_todo_list(&todo_list);

    int cont = 1;

    while ((ch = (char)getch()) != 'q') {
        todo_handle_input(&todo_list, ch);
        
    }


    endwin();                  // End curses mode

    return 0;
}
