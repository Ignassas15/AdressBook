#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"



struct address *create_address(char *name, char *surname, char *email, char *phone){
    struct address *new_address = (struct address*) malloc(sizeof(struct address));

    if(new_address == NULL){
        return NULL;
    }
    
    strncpy(new_address->name,name,sizeof(new_address->name));
    strncpy(new_address->surname,surname,sizeof(new_address->surname));
    strncpy(new_address->email,email,sizeof(new_address->email));
    strncpy(new_address->phone,phone,sizeof(new_address->phone));
    new_address->next = NULL;

    return new_address;
}

void insert_address(struct address **head ,struct address *to_insert){
    
    struct address* tmp = *head;

    if(tmp == NULL){
        *head = to_insert;
        return;
    }

    while(tmp->next != NULL){
        tmp = tmp->next;
    }

    tmp->next = to_insert;
}



void delete_addresses(struct address **head){
    struct address *to_delete = *head;

    while (*head != NULL)
    {   
        *head = (*head)->next;
        free(to_delete);
        to_delete = *head;
    }
    

}

void print_addresses(struct address **head){
    if(*head == NULL){
        return;
    }

    struct address *tmp = *head;
    while(tmp != NULL){
        printf("%s %s %s %s", tmp->name,tmp->surname,tmp->email, tmp->phone);
        tmp = tmp->next;
    }
}