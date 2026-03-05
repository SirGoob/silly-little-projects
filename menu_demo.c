#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "util.h"
#include "contact.h"

//#define DEBUG

int main (void) {
	//Low for testing sake
	int max_contacts = 4; 
#ifdef DEBUG
	printf("DEBUG: Start of program max contacts is %d\n", max_contacts);
#endif
	
	int contact_count = 0;
	int* index = &contact_count;
	contact *contacts = calloc(max_contacts, sizeof(*contacts));
	if (contacts == NULL) {
		perror("Memory allocation failure.\n");
		return 1;
	}

	load_contacts(&contacts, &max_contacts, index);

#ifdef DEBUG
	printf("DEBUG: Max contacts after loading previous contacts is %d\n", max_contacts);
#endif

	while(true){
		printf("What would you like to do?\n"
	    "(1) Add Contact    (2) View All Contacts\n"
        "(3) View Contact   (4) Search\n"
	    "(5) Delete Contact	(6) Option 7\n"
	    "(7) Quit\n"
	    "Selection: ");

		
		switch (get_choice(1,7)) {
			case 1:	

				if(contact_count >= max_contacts) {
					resize_contacts(&contacts, &max_contacts);
				}

				char add_name[64];
				char add_number[15];
				char add_email[64];

				printf("Enter contact name: ");
				scanf(" %s", add_name);
				clear_input_buffer();

				printf("Enter contact number: ");
				scanf(" %s", add_number);
				clear_input_buffer();
				
				printf("Enter contact email: ");
				scanf(" %s", add_email);
				clear_input_buffer();
				
				add_contact(contacts, index, add_name, add_number, add_email);
				
				print_separator();
				break;

			case 2:
				view_all_contacts(contacts, contact_count);
				
				print_separator();
				break;

			case 3:
				if (contact_count == 0) {
					printf("No contacts to view.\n");
					
					print_separator();
					break;
				} else {
					view_contact(contacts, *index);
					
					print_separator();
					break;
			}

			case 4:
				if (contact_count == 0) {
					printf("No contacts to search through.\n");
					
					print_separator();
					break;
				} else {
					char search_name[64];
					printf("Enter the contacts name: ");
					scanf(" %s", search_name);
					clear_input_buffer();

					search_for_contact(contacts, search_name, contact_count);
					
					print_separator();
					break;
				}

			case 5:
				delete_contact(contacts, &contact_count);
				
				print_separator();
				break;

			case 6:
				printf("Option 6 selected.\n");
				perror("Uh oh!!!!!!!");
				
				print_separator();
				break;

			case 7:
				save_contacts(contacts, max_contacts);
				printf("Goodbye!\n");
				return 0;
				break;

			default:
				printf("Invalid selection. Please try again.\n");
		}
	}

	free(contacts);
	contacts = NULL;
	return 0;
	//exit();
}
