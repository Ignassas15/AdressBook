#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"
#define DELIMITER ","


struct address *create_address(char *line){
    struct address *new_address = (struct address*) malloc(sizeof(struct address));
        char *name;
        char *surname;
        char *email;
        char *phone;

        name = strtok(line,DELIMITER);
        surname = strtok(NULL,DELIMITER);
        email = strtok(NULL,DELIMITER);
        phone = strtok(NULL,DELIMITER);

        //Add check for name and etc size

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

int insert_to_position(struct address **head, struct address *to_insert, int position){
   

    if(position <= 0){
        return 1;
    }

    if(position == 1){
        if(*head == NULL){
            *head = to_insert;
        }else{
            to_insert->next = (*head)->next;
            *head = to_insert;
        }
        
        return 0;   
    }

    int list_pos = 1;
    struct address *tmp = *head;

    while (tmp->next != NULL && list_pos+1 < position)
    {
        tmp = tmp->next;
        list_pos++;
    }

    if(tmp->next == NULL && list_pos+1 < position){
        return 1;
    }else{
        to_insert->next = tmp->next;
        tmp->next = to_insert;
    }

    return 0;
    

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

int delete_position(struct address **head, int position) {
    
    struct address *tmp_free;
    if (position <= 0 || *head == NULL)  {
        return 1;
    } else if (position == 1) {
        tmp_free = *head;
        *head = (*head)->next;
        free(tmp_free);
    } else {
        struct address *tmp = *head;
        int list_pos = 1;

        while (list_pos + 1 < position && tmp->next != NULL) {
            tmp = tmp->next;
            list_pos++;
        }

        
        if (tmp->next != NULL) {
            tmp_free = tmp->next;
            tmp->next = tmp->next->next;
            free(tmp_free);
        }else{
            return 1;
        }
    }

    return 0;
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