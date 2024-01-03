#include "todo.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int place_cursor(WINDOW *win) {
    int rows, cols;

    getmaxyx(win, rows, cols);
    wmove(win, rows - 3, 3);

    return 0;
}

int read_todo_file(Todo_list *list) {
    /* This function reads a todo.txt into the memory of list */
    FILE *p_todo;
    char item[100];
    int count = 0;

    if((p_todo = fopen("todo.txt", "r"))  == NULL)
        strcpy(list->item[0].string,"No todo.txt file !");
    else {
        while(fgets(item, 100, p_todo)) {
            strcpy(list->item[count].string, item);
            count = count + 1;
        }
        list->todo_max = count;
    }
    fclose(p_todo);

    return 0;
}

Todo_list new_list(WINDOW *win){
    Todo_list list;
    list.todo_max = 0;
    list.win = win;
    read_todo_file(&list);
    return list;
}

int print_todo_list(Todo_list *list) {
    WINDOW *win = list->win;

    box(win, 0, 0);

    mvwprintw(win, 0, 3,  "todo list");

    for (int i = 0; i < list->todo_max; i++) {
        mvwprintw(win, 3 + i*2, 3, "%s", &list->item[i]);
    }

    wrefresh(win);

    return 0;
}

int todo_list_move_to(Todo_list *list, int target) {
    /* selects new item in list. Removes attributes from prev selection and adds to new selection */
    int current_item;
    WINDOW *win;

    win = list->win;

    current_item = list->current_item;

    mvwprintw(list->win, 3 + current_item*2, 3, "%s", &list->item[current_item]);

    while (target < 0) {
        target = target + list->todo_max;
    }
    current_item = target % list->todo_max;

    wattron(win, A_BOLD);
    mvwprintw(list->win, 3 + current_item*2, 3, "%s", &list->item[current_item]);
    wattroff(win, A_BOLD);

    list->current_item = current_item;

    place_cursor(list->win);
    wrefresh(list->win);
    return 0;
}

int todo_list_move_up(Todo_list *list) {
    return todo_list_move_to(list, list->current_item-1);
}

int todo_list_move_down(Todo_list *list) {
    return todo_list_move_to(list, list->current_item+1);
}

int todo_list_toggle_item(Todo_list *list) {
    WINDOW *win;
    win = list->win;

    if (list->item[list->current_item].string[1] == 'x')
        list->item[list->current_item].string[1] = ' ';
    else
        list->item[list->current_item].string[1] = 'x';

    wattron(win, A_BOLD);
    mvwprintw(list->win, 3 + list->current_item*2, 3, "%s", &list->item[list->current_item].string);
    wattroff(win, A_BOLD);

    place_cursor(win);
    wrefresh(win);
    return 0;
}

int todo_handle_input(Todo_list *list, char ch) {
    switch (ch) {
        case 'j':
            todo_list_move_down(list);
            break;
        case 'k':
            todo_list_move_up(list);
            break;
        case '\t':
            todo_list_toggle_item(list);
            break;
        default:
            waddch(list->win, (int)ch);
            wrefresh(list->win);
            break;
    }
}
