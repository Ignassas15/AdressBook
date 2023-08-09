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

    int matched_size = 20;

    struct address **matched_addresses = (struct address**) malloc(sizeof(struct address) * matched_size);
    if(matched_addresses == NULL){
        printf("ERROR: Could not allocate memory \n");
        exit(1);
    }

    address_file = open_address_file("/addresses.csv");
    
    read_addresses(address_file,&address_list);


    print_addresses(&address_list);
    enum search_param param = phone;
    int matches = 0;
    char query[] = "";
    find_by_param(&address_list,matched_addresses,matched_size,param,&matches,query);


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

void read_addresses(FILE *file, struct address **head){
    char line[500];

    if(file == NULL){
        return;
    }

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