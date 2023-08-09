#include <stdlib.h>
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
    struct address *tmp = *head;

    if(tmp == NULL){
        *head = to_insert;
        return;
    }

    while(tmp->next != NULL){
        tmp->next = tmp->next;
    }

    tmp->next = to_insert;
}



void delete_addresses(struct address **head){
    struct address *to_delete = *head;

    while (*head != NULL)
    {
        free(to_delete);
        *head = (*head)->next;
        to_delete = *head;
    }
    

}