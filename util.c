#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "util.h"
#include "contact.h"

//#define DEBUG

void print_separator(void) {
	printf("\n========================================\n\n");
}

void clear_input_buffer(void) {
	int c;
	while ((c = getchar()) != '\n' && c != -1 /*EOF*/) {}
}

int get_choice(int min, int max){
	int selection = -1;
	while (selection == -1) {
		scanf(" %d", &selection);
		clear_input_buffer();
		if(selection > max || selection < min) {
			printf("\nPlease select an option %d - %d\nSelection: ", min, max);
			selection = -1;		
		}
	}
	return selection;
}

void resize_contacts(contact **contact_list, int *max_contacts){
	#ifdef DEBUG
	printf("\nDEBUG: Resizing contact list from %d, to %d\n", *max_contacts, *max_contacts * 2);
	#endif

	*max_contacts *= 2;

	#ifdef DEBUG
	printf("\nDEBUG: The max amount of contacts is now %d\n", *max_contacts);
	#endif

	contact *temp_resized_list = realloc(*contact_list, *max_contacts * sizeof(**contact_list));

	if(temp_resized_list == NULL) {
		perror("Memory re-allocation failure.\n");
		exit(1);
	} else {
		*contact_list = temp_resized_list;
	}
	#ifdef DEBUG
	printf("\nDEBUG: The new size of the contact list is %d\n", *max_contacts);
	#endif
}

void search_for_contact(contact *contact_list, char* name, int contact_count){
	int name_comparison = 0;
	for (int contact_index = 0; contact_index < contact_count; contact_index++) {
		name_comparison = strcmp(contact_list[contact_index].name , name) ;
		if(name_comparison == 0) {
			printf("%s's phone number: %s\n" 
				   "%s's email address: %s\n", 
				   contact_list[contact_index].name, contact_list[contact_index].number, 
				   contact_list[contact_index].name, contact_list[contact_index].email);
		}
	}
	if (name_comparison != 0){
		printf("\nNo contact found with the name %s. " 
			   "Please check spelling/ capitalization and try again.\n", name);
	}
}

void delete_contact(contact *contact_list, int *contact_count) {
	int contact_num;
	printf("Enter the number of the contact you want to delete: ");
	contact_num = get_choice(1, *contact_count) - 1;


	for (int i = contact_num; i < *contact_count - 1; i++) {
		contact_list[i] = contact_list[i + 1];
	}

	//memset(&contact_list[*contact_count - 1], 0, sizeof(contact));
	contact_list[*contact_count - 1] = (contact) {0};

	*contact_count -= 1;
	printf("Contact deleted.\n");
}

