#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

#define DELIMITER ","

void read_addresses(FILE *file, struct address **head);
FILE *open_address_file(char *file_name);

int main(void){

    FILE *address_file;
    struct address *address_list = NULL;

    address_file = open_address_file("/addresses.csv");

    read_addresses(address_file,&address_list);


    print_addresses(&address_list);


    delete_addresses(&address_list);

    if (address_file != NULL)
    {
        fclose(address_file);
    }

    return 0;
}

void read_addresses(FILE *file, struct address **head){
    char line[500];

    while(fgets(line,sizeof(line), file)){
        
        if(strcmp(line,"\n") == 0){
            continue;
        }
        
        struct address *new_address = NULL;
        char *name;
        char *surname;
        char *email;
        char *phone;

        name = strtok(line,DELIMITER);
        surname = strtok(NULL,DELIMITER);
        email = strtok(NULL,DELIMITER);
        phone = strtok(NULL,DELIMITER);
        new_address = create_address(name,surname,email,phone);
        insert_address(head,new_address);
    }

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