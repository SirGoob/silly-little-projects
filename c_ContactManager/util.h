#ifndef UTILS_H
#define UTILS_H
#include "contact.h"

void print_separator(void);
void clear_input_buffer(void);
int get_choice(int min, int max);
void resize_contacts(contact **contact_list, int *max_contacts);
void search_for_contact(contact *contact_list, char* name, int contact_count);
void delete_contact(contact *contact_list, int *contact_count); 

#endif /* UTILS_H */
