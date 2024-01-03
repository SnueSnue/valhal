#include <ncurses.h>

#ifndef TODO_H
#define TODO_H

typedef struct {
    char string[100];
} todo_item;

typedef struct {
    int todo_max;
    int current_item;
    WINDOW *win;
    todo_item item[10];
} Todo_list;

Todo_list new_list();

int print_todo_list(Todo_list *list);

int todo_list_move_to(Todo_list *list, int target);

int todo_list_move_up(Todo_list *list);

int todo_list_move_down(Todo_list *list);

int todo_handle_input(Todo_list *list, char ch);

#endif // TODO_H
