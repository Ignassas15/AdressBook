#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"



int read_addresses(FILE *file, struct address **head);
int check_if_csv(char *line, int needed_commas);
FILE *open_address_file(char *file_name);
void print_menu_commands();
void print_search_submenu();
void print_address(struct address *to_print);
void print_search_results(struct address **matched_addresses,int matches);
void clear_newline();



int main(void){

    FILE *address_file;
    struct address *address_list = NULL;

    int matched_size = 20;

    struct address **matched_addresses = (struct address**) malloc(sizeof(struct address) * matched_size);
    if(matched_addresses == NULL){
        printf("ERROR: Could not allocate memory \n");
        exit(1);
    }

    address_file = open_address_file("/addresses.csv");
    
    int matches = 0;
    int exit = 0;
    int command = 0;
    int success_code = 0;
    int pos = 0;
    while(!exit){
        print_menu_commands();
        printf("Enter your command: \n");
        scanf("%d", &command);
        clear_newline();
        switch (command)
        {
        case 1:
            success_code = read_addresses(address_file,&address_list);
            if(success_code){
                printf("Couldn't read addresses \n");
            }else{
                printf("Action succesful \n");
            }
            break;
        case 2:
            char line[100];
            printf("Enter address in .csv format: \n");
            fgets(line,sizeof(line),stdin);
            if(check_if_csv(line,3) == 0){
                printf("Wrong .csv format");
                break;
            }
            
            struct address *new_addr;
            new_addr = create_address(line);
            pos = 0;
            printf("Enter the position for the new address: \n");
            scanf("%d", &pos);
            clear_newline();

            
            success_code = insert_to_position(&address_list,new_addr,pos);
            if(success_code){
                printf("Couldn't insert address \n");
                free(new_addr);
            }else{
                printf("Action succesful \n");
            }

            break;
        case 3:
            printf("All addresses: \n");
            print_addresses(&address_list);
            break;
        case 4:
            pos = 0;
            printf("Enter the position of the address to delete: \n");
            scanf("%d", &pos);
            clear_newline();
            success_code = delete_position(&address_list,pos);
            if(success_code){
                printf("Couldn't delete address \n");
            }else{
                printf("Action succesful \n");
            }
            break;
        case 5:
            pos = 0;
            printf("Enter the address position: \n");
            scanf("%d", &pos);
            clear_newline();
            struct address *found = find_by_position(&address_list, pos);
            if(found == NULL){
                printf("Couldn't find address\n");
            }else{
                printf("Found address info: \n");
                print_address(found);
            }
            break;
        case 6:

            matches = 0;
            char query[100];
            int selection = 0;
            print_search_submenu();
            printf("Enter the selected criteria: \n");
            scanf("%d", &selection);
            clear_newline();

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

            printf("Enter the search query: \n");
            scanf("%99[^\n]",query);
            clear_newline();
            printf("%s query \r", query);
            find_by_param(&address_list,matched_addresses,matched_size,param,&matches,query);
            printf("Search results: \n");
            print_search_results(matched_addresses,matches);

            break;
        case 7:
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

    if(matched_addresses != NULL){
        free(matched_addresses);
    }

    return 0;
}

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

FILE *open_address_file(char *file_name){
    char *home_path = getenv("HOME");
    if(home_path == NULL){
        return NULL;
    }

    char full_path[150];
    strcpy(full_path,home_path);
    strcat(full_path,file_name);
    FILE *file = fopen(full_path, "r");
    return file;
}




void print_menu_commands(){
    printf("Here are the available actions: \n");
    printf("1. Read addresses from file \n");
    printf("2. Read address from console and insert to position \n");
    printf("3. Display all adress book records \n");
    printf("4. Delete address \n");
    printf("5. Find address by position \n");
    printf("6. Find addresses by criteria \n");
    printf("7. Exit \n");

}

void print_search_submenu(){
    printf("Here are the available search criteria: \n");
    printf("1. By name or part of it \n");
    printf("2. By surname or part of it \n");
    printf("3. By email or part of it \n");
    printf("4. By phone or part of it \n");
}

void print_address(struct address *to_print){
    if(to_print != NULL){
        printf("%s %s %s %s", to_print->name,to_print->surname,to_print->email, to_print->phone);
    }
}

void print_search_results(struct address **matched_addresses,int matches){
    if(matched_addresses == NULL || matches == 0){
        return;
    }
    for(int i = 0; i < matches; i++){
        print_address(matched_addresses[i]);
    }
}

void clear_newline(){
    int c;
    while ( (c = getchar()) != EOF && c != '\n') { }
}

int check_if_csv(char *line, int needed_commas){
    if(line == NULL){
        return 0;
    }
    int comma_count = 0;
    for(int i = 0; i < strlen(line); i++){
        if(line[i] == ','){
            comma_count++;
        }
    }

    if(comma_count == needed_commas){
        return 1;
    }else{
        return 0;
    }

}

