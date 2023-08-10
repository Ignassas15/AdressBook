#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"
#define DELIMITER ","


/**
 * create_address() - creates new adress node from .csv format line
 * @param line: Line that will be parsed for data
 * @return: pointer to address or NULL if unsucsessful
 */
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


/**
 * insert_address() - Inserts address node to the end of the linked list
 * @param head: pointer to the first linked list element
 * @param to_insert: address node to insert
 */
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


/**
 * insert_to_position() - inserts address node to specified position on the linked list
 * @param head: pointer to the first linked list element
 * @param to_insert: address node to insert
 * @param position: position to which to insert
 * @return: 0 if successfull 1 if not
 */
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



/**
 * delete_addresses() - deletes all addresses from linked list and frees the allocated memory
 * @param head: pointer to the first linked list element
 */
void delete_addresses(struct address **head){
    struct address *to_delete = *head;

    while (*head != NULL)
    {   
        *head = (*head)->next;
        free(to_delete);
        to_delete = *head;
    }
    

}


/**
 * delete_position() - deletes the node in the selected position
 * @param head: pointer to the first linked list element
 * @param position: position from which to delete
 * @return: 0 if successfull 1 if not
 */
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


/**
 * print_addresses() - prints all the addresses in the linked list to console
 * @param head: pointer to the first linked list element
 */
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

/**
 * find_by_position()) - finds the address node at specified location
 * @param head: pointer to the first linked list element
 * @param position: position for which to look
 * @return: pointer to the addres node or NULL if unsucsessful
 */
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


/**
 * find_by_param() - finds nodes that match a certain query with their parameters
 * @param head: pointer to the first linked list element
 * @param matched: pointer to linked list that will hold all matched addresses
 * @param param: Parameter to match the query to
 * @param query: The query string for matching
 */
void find_by_param(struct address **head, struct address **matched,enum search_param param, char* query){
    
    struct address *tmp = *head;
    if(tmp == NULL){
        
        return;
    }

    while(tmp != NULL){

        struct address *insertee = (struct address*) malloc(sizeof(struct address));
        if(insertee == NULL){
            continue;
        }else{
            strcpy(insertee->name, tmp->name);
            strcpy(insertee->surname, tmp->surname);
            strcpy(insertee->email, tmp->email);
            strcpy(insertee->phone, tmp->phone);
        }
        

    switch (param)
    {
        
    case name:
        if(strstr(insertee->name,query) != NULL){
            insert_address(matched,insertee);
        }else{
            free(insertee);
        }

        break;
    case surname:
        if(strstr(insertee->surname,query) != NULL){
            insert_address(matched,insertee);
        }else{
            free(insertee);
        }
        break;
    case email:
        if(strstr(insertee->email,query) != NULL){
            insert_address(matched,insertee);
        }else{
            free(insertee);
        }
        break;
    case phone:
        if(strstr(insertee->phone,query) != NULL){
            printf("%s \n",insertee->phone);
            insert_address(matched,insertee);
        }else{
            free(insertee);
        }
        break;
    default:
        break;
    }

    tmp = tmp->next;
    }

}