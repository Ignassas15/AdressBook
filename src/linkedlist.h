#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct address{
    char name[20];
    char surname[20];
    char email[35];
    char phone[15];

    struct address *next;
};


struct address* create_address(char *name, char *surname, char *email, char *phone);

void insert_address(struct address **head ,struct address *to_insert);
void remove_address(struct address **head, struct address *to_remove);
void delete_addresses(struct address **head);
int delete_position(struct address **head, int position);
int find_by_position(struct address **head, int position, struct address ** found);



#endif