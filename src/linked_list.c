#include "../inc/linked_list.h"

Linked_List* create_Linked_List (void) {
	Linked_List* linked_list = (Linked_List*) malloc (sizeof (Linked_List));

	if (linked_list != NULL) {
		log_memory (DS_Linked_List, sizeof (Linked_List), linked_list, true);

		linked_list -> name = NULL;
		linked_list -> size = 0;
		linked_list -> head_node = NULL;
		linked_list -> tail_node = NULL;
	}

	return linked_list;
}

void display_Linked_List (Linked_List* linked_list) {
	if (linked_list == NULL) {
		perror ("Linked List does not Exist to display!");
		return;
	}

	if (0 == linked_list -> size) {
		printf ("Empty!");
		return;
	}

	if (NULL == linked_list -> head_node) {
		perror ("Linked-List node does not exist to display!\n");
		return;
	}

	Node* node = linked_list -> head_node;

	for (size_t i = 0; i < linked_list -> size; i++) {
		if (i > 0) {
			printf ("---");
		}

		display_Node (node);
		node = (node -> address_list -> head_chunk -> first_data_address + 1) -> address;
	}
}

void display_Linked_List_details (Linked_List* linked_list) {
	if (linked_list == NULL) {
		perror ("Linked List does not Exist to display details!");
		return;
	}

	printf ("Linked-List :=>\n");

	if (0 == linked_list -> size) {
		printf ("Empty!\n");
		return;
	}

	if (NULL == linked_list -> head_node) {
		perror ("Linked-List node does not exist to display details!\n");
		return;
	}

	Node* node = linked_list -> head_node;

	for (size_t i = 0; i < linked_list -> size; i++) {
		putchar ('\t');
		display_Node_details (node);
		node = (node -> address_list -> head_chunk -> first_data_address + 1) -> address;
	}

	ENDL();
}

void delete_Linked_List (Linked_List** linked_list_address) {
	if (*linked_list_address == NULL) {
		perror ("Linked List does not exist to delete!");
		return;
	}

	Linked_List* linked_list = *linked_list_address;

	Node* node = linked_list -> head_node;
	Node* del_node;

	for (size_t i = 0; i < linked_list -> size; i++) {
		del_node = node;
		node = (node -> address_list -> head_chunk -> first_data_address + 1) -> address;
		clear_Node_address_list (del_node);
		delete_Node (&del_node);
	}

	linked_list = NULL;

	log_memory (DS_Linked_List, sizeof (Linked_List), *linked_list_address, false);
	ERASE (linked_list_address, sizeof (Linked_List));
}

void attach_Node_at_last (Linked_List* linked_list, Node* node) {
	if (linked_list == NULL) {
		perror ("Linked-list does not exist to attah node at last\n");
		exit (EXIT_FAILURE);
	}

	if (node == NULL) {
		perror ("Node does not exist to attach at last of linked-list\n");
		exit (EXIT_FAILURE);
	}

	Node* new_node = duplicate_Node (node);
	clear_Node_address_list (new_node);

	if (
		NULL == linked_list -> head_node
		|| NULL == linked_list -> tail_node
	) {
		linked_list -> head_node = new_node;
		linked_list -> tail_node = new_node;
		linked_list -> size = 1;
		return;
	}

	Node* temp_node = linked_list -> tail_node;

	(new_node -> address_list -> head_chunk -> first_data_address + 0) -> address = temp_node;
	(temp_node -> address_list -> head_chunk -> first_data_address + 1) -> address = new_node;

	linked_list -> tail_node = new_node;
	linked_list -> size++;
}

void attach_Node_at_first (Linked_List* linked_list, Node* node) {
	if (linked_list == NULL) {
		perror ("Linked-list does not exist to attah node at last\n");
		exit (EXIT_FAILURE);
	}

	if (node == NULL) {
		perror ("Node does not exist to attach at last of linked-list\n");
		exit (EXIT_FAILURE);
	}

	Node* new_node = duplicate_Node (node);
	clear_List (new_node -> address_list);

	if (
		NULL == linked_list -> head_node
		|| NULL == linked_list -> tail_node
	) {
		linked_list -> head_node = new_node;
		linked_list -> tail_node = new_node;
		linked_list -> size = 1;
		return;
	}

	Node* temp_node = linked_list -> head_node;

	(new_node -> address_list -> head_chunk -> first_data_address + 1) -> address = temp_node;
	(temp_node -> address_list -> head_chunk -> first_data_address + 0) -> address = new_node;

	linked_list -> head_node = new_node;
	linked_list -> size++;
}

Node* detach_head_from_Linked_List (Linked_List* linked_list) {
	if (linked_list == NULL) {
		// perror ("Linked List does not Exist to detach node from!");
		// exit (EXIT_FAILURE);
		return NULL;
	}

	if (linked_list -> size == 0) {
		// perror ("Linked List is Empty to detach node from!\n");
		return NULL;
	}

	Node* node;

	if (linked_list -> head_node == linked_list -> tail_node) {
		linked_list -> size = 0;
		node = linked_list -> head_node;
		linked_list -> head_node = NULL;
		linked_list -> tail_node = NULL;
		return node;
	}

	node = linked_list -> head_node;
	linked_list -> head_node = (linked_list -> head_node -> address_list -> head_chunk -> first_data_address + 1) -> address;
	(linked_list -> head_node -> address_list -> head_chunk -> first_data_address + 0) -> address = NULL;

	-- linked_list -> size;

	(node -> address_list -> head_chunk -> first_data_address + 0) -> address = NULL;
	(node -> address_list -> head_chunk -> first_data_address + 1) -> address = NULL;

	return node;
}

Node* detach_tail_from_Linked_List (Linked_List* linked_list) {
	if (linked_list == NULL) {
		// perror ("Linked List does not Exist to detach node from!");
		// exit (EXIT_FAILURE);
		return NULL;
	}

	if (linked_list -> size == 0) {
		// perror ("Linked List is Empty to detach node from!\n");
		return NULL;
	}

	Node* node;

	if (linked_list -> head_node == linked_list -> tail_node) {
		linked_list -> size = 0;
		node = linked_list -> head_node;
		linked_list -> head_node = NULL;
		linked_list -> tail_node = NULL;
		return node;
	}

	node = linked_list -> tail_node;
	linked_list -> tail_node = (linked_list -> tail_node -> address_list -> head_chunk -> first_data_address + 0) -> address;
	(linked_list -> tail_node -> address_list -> tail_chunk -> first_data_address + 1) -> address = NULL;

	-- linked_list -> size;

	(node -> address_list -> head_chunk -> first_data_address + 0) -> address = NULL;
	(node -> address_list -> head_chunk -> first_data_address + 1) -> address = NULL;

	return node;
}