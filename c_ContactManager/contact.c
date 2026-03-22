#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "contact.h"
#include "util.h"

//#define DEBUG

void view_all_contacts(const contact *contacts, int contact_count){
    printf("\nAll contacts:\n\n");
    for (int i = 0; i < contact_count; i++){
        if (strlen(contacts[i].name) == 0) {
            continue; 
        }
        printf("%d. %s | %s | %s\n", 
               i + 1, contacts[i].name, contacts[i].number, contacts[i].email);
    }
    printf("\n");
}


void view_contact(const contact *c, int highest_index) {
    int knows_contact_num;;
    printf("Do you know which contact you want to view? (1 - Yes / 0 - No): ");
    knows_contact_num = get_choice(0,1);

    if (!knows_contact_num) {
    }

    printf("Enter the number of the contact you want to view: ");
    int selection;

    selection = get_choice(1, highest_index + 1) - 1;
    clear_input_buffer();

    printf("%s's phone number: %s\n" 
           "%s's email address: %s\n", 
           c[selection].name, c[selection].number, 
           c[selection].name, c[selection].email);
}

void add_contact(contact *contact, int *index, char *name, char *number, char *email){
    
    strncpy(contact[*index].name, name, sizeof(contact->name) - 1);
    strncpy(contact[*index].number, number, sizeof(contact->number) - 1);
    strncpy(contact[*index].email, email, sizeof(contact->email) - 1);
    *index += 1;

    #ifdef DEBUG
    printf("DEBUG: Contact added. Current index: %d\n", *index);
    #endif
}

void save_contacts(contact *contact_list, int max_contacts){
    FILE *fp = fopen("contacts.csv", "w");
    if (fp == NULL){
        perror("File open error.\n");
        return;
    }

    for(int contact_num = 0; contact_num < max_contacts; contact_num++){
        fprintf(fp, "%s,%s,%s\n",
                    contact_list[contact_num].name,
                    contact_list[contact_num].email,
                    contact_list[contact_num].number);
    }
    
    if (ferror(fp)){
        perror("ERror writing to file");
    }
    
    fclose(fp);
    
    #ifdef DEBUG
    printf("DEBUG: Contacts saved successfully.\n");
    #endif
}

void load_contacts(contact **contact_list, int* max_contacts, int *contact_index){
    FILE *fp = fopen("contacts.csv", "r");
    if (fp == NULL){
        perror("File Open Error.\n");
        return;
    }

    int read_info = 0;
    while (true){

        #ifdef DEBUG
        printf("DEBUG: Retrieving contact #%d\n", *contact_index + 1);
        #endif

        read_info = fscanf(fp,
                "%63[^,],%63[^,],%15[^\n]\n",
                (*contact_list)[*contact_index].name,
                (*contact_list)[*contact_index].email,
                (*contact_list)[*contact_index].number);

        if (read_info < 3) {
            fclose(fp);
            return;
        }
        *contact_index += 1;

        if (*contact_index == *max_contacts){
            resize_contacts(contact_list, max_contacts);
        }

    } 
    fclose(fp);
}


// void free_contacts(contact *contacts){
//     free(contacts);
// }