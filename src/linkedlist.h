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


struct address *create_address(char *name, char *surname, char *email, char *phone);
struct address *find_by_position(struct address **head, int position);
void find_by_param(struct address **head, struct address **matched, int matched_size,
                   enum search_param param, int *match_count, char* query);
void insert_address(struct address **head ,struct address *to_insert);
void print_addresses(struct address **head);
void remove_address(struct address **head, struct address *to_remove);
void delete_addresses(struct address **head);
void delete_position(struct address **head, int position);




#endif