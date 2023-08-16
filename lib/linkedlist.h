#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct address{
    char name[20];
    char surname[20];
    char email[35];
    char phone[15];

    struct address *next;
};

enum search_param{
    name = 1,
    surname = 2,
    email = 3,
    phone = 4
};


struct address *create_address(char *line);
struct address *find_by_position(struct address **head, int position); 
int insert_to_position(struct address **head, struct address *to_insert, int position);
int delete_position(struct address **head, int position);
void find_by_param(struct address **head, struct address **matched,enum search_param param, char* query);
void insert_address(struct address **head ,struct address *to_insert);
void print_addresses(struct address **head);
void remove_address(struct address **head, struct address *to_remove);
void delete_addresses(struct address **head);





#endif