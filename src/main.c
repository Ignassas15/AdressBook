#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "linkedlist.h"
#include "menu.h"

volatile sig_atomic_t EXIT_INTERRUPT = 0;

int read_addresses(FILE *file, struct address **head);
FILE *open_address_file(char *file_name);
void signal_handler(int signum);

int main(void){

    signal(SIGINT,signal_handler);

    FILE *address_file;
    struct address *address_list = NULL;

    int exit = 0;
    address_file = open_address_file("addresses.csv");
    
    read_addresses(address_file,&address_list);
    while(!exit && !EXIT_INTERRUPT){
        print_menu_commands();
        
        switch (read_menu_digit())
        {
        case 1:
            enter_adress_menu(&address_list);
            break;
        case 2:
            print_address_records_menu(&address_list);
            break;
        case 3:
            delete_selected_menu(&address_list);
            break;
        case 4:
            find_by_position_menu(&address_list);
            break;
        case 5:
            find_by_param_menu(&address_list);
            break;
        case 6:
            exit = 1;
            break;
        default:
            break;
        }

    }
    
    
    
    delete_addresses(&address_list);
    if (address_file != NULL)
    {
        fclose(address_file);
    }

    return 0;
}


/**
 * read_addresses - Reads addresses from file to linked list
 * @param file: Pointer to opened file
 * @param head: pointer to first element of linked list.
 * @return: 0 if successful 1 if not.
 */
int read_addresses(FILE *file, struct address **head){
    char line[500];

    if(file == NULL){
        return 1;
    }

    while(fgets(line,sizeof(line), file)){
        
        if(strcmp(line,"\n") == 0){
            continue;
        }
        
        if(!check_if_csv(line,3)){
            return 1;
        }

        struct address *new_address = NULL;
        new_address = create_address(line);
        insert_address(head,new_address);
    }

    return 0;
}

/**
 * open_address_file - Opens file which stores addresses
 * @param file_name: Name of the file
 * @return: pointer to the opened file or NULL if it was unable to open
 */
FILE *open_address_file(char *file_name){
    char *home_path = getenv("HOME");
    if(home_path == NULL){
        return NULL;
    }

    char full_path[150];
    strcpy(full_path,home_path);
    strcat(full_path,"/");
    strcat(full_path,file_name);
    FILE *file = fopen(full_path, "r");
    return file;
}

/**
 * signal_handler() - Handles sigint
 * @param signum: signal number
 */
void signal_handler(int signum){
        EXIT_INTERRUPT = 1;
}






