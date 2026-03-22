#ifndef contact_h
#define contact_h

typedef struct {
    char name[64];
    char email[64];
    char number[16];
} contact;

void view_all_contacts(const contact *contacts, int contact_count);
void view_contact(const contact *c, int highest_index);
void add_contact(contact *contact, int *index, char *name, char *number, char *email);
void save_contacts(contact *contact_list, int max_contactss);
void load_contacts(contact **contact_list, int* max_contacts, int *contact_index);

#endif