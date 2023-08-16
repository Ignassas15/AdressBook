#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * enter_adress_menu() - Handles entering new address by hand
 * @param address_list: pointer to first linked list element
 */
void enter_adress_menu(struct address **address_list){
    char line[100];
    printf("Enter address in .csv format: \n");
    fgets(line,sizeof(line),stdin);
    if(check_if_csv(line,3) == 0){
        printf("Wrong .csv format or the data is too long\n");
        clear_newline();
        return;
    }

    struct address *new_addr;
    new_addr = create_address(line);
    printf("Enter the position for the new address: \n");
    int pos = read_menu_digit();
    
    int success_code = insert_to_position(address_list,new_addr,pos);
    if(success_code){
        printf("Couldn't insert address \n");
        free(new_addr);
    }else{
        printf("Action succesful \n");
    }

}

/**
 * print_address_list_menu() - Handles printing of all addresses
 * @param address_list: pointer to first linked list element
 */
void print_address_records_menu(struct address **address_list){
    printf("All addresses: \n");
    print_addresses(address_list);
}

/**
 * delete_selected_menu() - Handles deletion of selected linked list element
 * @param address_list: pointer to first linked list element
 */
void delete_selected_menu(struct address **address_list){
    printf("Enter the position of the address to delete: \n");
    int pos = read_menu_digit();
    int success_code = delete_position(address_list,pos);
    if(success_code){
        printf("Couldn't delete address \n");
    }else{
        printf("Action succesful \n");
    }
}

/**
 * find_by_position_menu()) - Handles search by position
 * @param address_list: pointer to first linked list element
 */
void find_by_position_menu(struct address **address_list){
    printf("Enter the address position: \n");
    int pos = read_menu_digit();
    struct address *found = find_by_position(address_list, pos);
    if(found == NULL){
        printf("Couldn't find address\n");
    }else{
        printf("Found address info: \n");
        print_address(found);
    }
}


/**
 * find_by_param_menu() - Handles search by parameter
 * @param address_list: pointer to first linked list element
 */
void find_by_param_menu(struct address **address_list){
            struct address *search_matches = NULL;
            print_search_submenu();
            char query[100];
            int selection = read_menu_digit();
            enum search_param param = get_selected_param(selection);
            printf("Enter the search query: \n");
            scanf("%99[^\n]",query);
            clear_newline();
            find_by_param(address_list,&search_matches,param,query);
            printf("Search results: \n");
            print_addresses(&search_matches);
            delete_addresses(&search_matches);
}

/**
 * get_selected_param() - Selects search parameter from selection number
 * @param selection: Which parameter option the user selected
 * @return: Selected parameters enum or name parameter as default
 */
enum search_param get_selected_param(int selection){
    enum search_param param;
    switch (selection)
    {
    case 1:
        param = name;
        break;
    case 2:
        param = surname;
        break;

    case 3:
        param = email;
        break;

    case 4:
        param = phone;
        break;
    
    default:
        param = name;
        break;
    
    } 
    return param;
}


/**
 * check_if_csv() - Checks if provided line has required amount of commas
 * @param line: Line to check.
 * @param needed_commas: Description of the second argument.
 * @return: 1 if correct 0 if not.
 */
int check_if_csv(char *line, int needed_commas){
    if(line == NULL){
        return 0;
    }

    int comma_count = 0;
    for(int i = 0; i < strlen(line); i++){
        if(line[i] == ','){
            comma_count++;
            //check for two consecutive commas
            if(i > 0 && line[i-1] == ','){
                return 0;
            }
        }
    }

    //Empty at front or back
    if(line[strlen(line-1)] == ',' || line[0] == ','){
        return 0;
    }

    if(comma_count == needed_commas){
        return 1;
    }else{
        return 0;
    }

}

int read_menu_digit(){
    int sel = 0;
    scanf("%d", &sel);
    clear_newline();
    return sel;
}

/**
 * clear_newline() - Clears remaining characters and new line symbol from buffer
 */
void clear_newline(){
    int c;
    while ( (c = getchar()) != EOF && c != '\n') { }
}

/**
 * print_menu_commands() - prints menu points to console
 */
void print_menu_commands(){
    printf("Here are the available actions: \n");
    printf("1. Read address from console and insert to position \n");
    printf("2. Display all adress book records \n");
    printf("3. Delete address \n");
    printf("4. Find address by position \n");
    printf("5. Find addresses by criteria \n");
    printf("6. Exit \n");
    printf("Enter your command: \n");

}

/**
 * print_search_submenu() - prints search submenu points to console
 */
void print_search_submenu(){
    printf("Here are the available search criteria: \n");
    printf("1. By name or part of it \n");
    printf("2. By surname or part of it \n");
    printf("3. By email or part of it \n");
    printf("4. By phone or part of it \n");
    printf("Enter the selected criteria: \n");
}

/**
 * print_address - Prints data of passed address to console
 * @param to_print: Address to print
 */
void print_address(struct address *to_print){
    if(to_print != NULL){
        printf("%s %s %s %s", to_print->name,to_print->surname,to_print->email, to_print->phone);
    }
}
