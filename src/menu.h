#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/linkedlist.h"

void print_menu_commands();
void print_search_submenu();
void clear_newline();
void enter_adress_menu(struct address **address_list);
void print_address_records_menu(struct address **address_list);
void delete_selected_menu(struct address **address_list);
void find_by_position_menu(struct address **address_list);
void find_by_param_menu(struct address **address_list);
void print_address(struct address *to_print);
int check_if_csv(char *line, int needed_commas);
int read_menu_digit();
enum search_param get_selected_param(int selection);

#endif