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

struct address *find_by_position(struct address **head, int position){
    struct address *tmp = *head;

    if(position <= 0){
        return NULL;
    }

    int list_pos = 1;
    while (tmp != NULL)
    {
        
        if(list_pos == position){
            
            return tmp;
        }    
        tmp = tmp->next;
        list_pos++;
    }

    return NULL;

}

void find_by_param(struct address **head, struct address **matched, int matched_size,
                   enum search_param param, int *match_count, char* query){
    
    struct address *tmp = *head;
    *match_count = 0;
    if(tmp == NULL){
        
        return;
    }


    while(tmp != NULL){
    switch (param)
    {
        
    case name:
        if(strstr(tmp->name,query) != NULL){
            matched[(*match_count)++] = tmp;
        }

        break;
    case surname:
        if(strstr(tmp->surname,query) != NULL){
            matched[(*match_count)++] = tmp;
        }
        break;
    case email:
        if(strstr(tmp->email,query) != NULL){
            matched[(*match_count)++] = tmp;
        }
        break;
    case phone:
        if(strstr(tmp->phone,query) != NULL){
            matched[(*match_count)++] = tmp;
        }
        break;
    default:
        break;
    }

    tmp = tmp->next;
    if((*match_count) >= matched_size){
        printf("Breaking the search, not enough space to store all matches\n");
        return;
    }

    }

}