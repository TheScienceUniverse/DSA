#include "../include/linked_list.h"

Linked_List *create_linked_list () {
	Linked_List* linked_list = (Linked_List*) malloc (sizeof (Linked_List));

	if (linked_list != NULL) {
		linked_list -> name = NULL;
		linked_list -> size = 0;
		linked_list -> first_node = NULL;
		linked_list -> last_node = NULL;
	}

	return linked_list;
}

void delete_linked_list (Linked_List** linked_list_address) {
	if (*linked_list_address == NULL) {
		perror ("Linked List does not exist to delete!");
		return;
	}

	Linked_List* linked_list = *linked_list_address;

	Node* node = linked_list -> first_node;
	Node* old_node;

	while (node != NULL) {
		old_node = node;
		node = *(node -> address_list -> item_addresses + 1);
		forget_list (&(old_node -> address_list));
		delete_node (&old_node);
	}

	linked_list = NULL;
	ERASE (linked_list_address);
}

void display_linked_list (Linked_List* linked_list) {
	if (linked_list == NULL) {
		perror ("Linked List does not Exist to display!");
		return;
	}

	if (linked_list -> size == 0) {
		perror ("Linked List is Empty to display!");
		return;
	}

	Node* node = linked_list -> first_node;

	while (node != NULL) {
		display_node (node);

		node = *(node -> address_list -> item_addresses + 1);

		if (node  != NULL) {
			printf (" -> ");
		}
	}

	printf ("\n");
}

void display_linked_list_details (Linked_List* linked_list) {
	if (linked_list == NULL) {
		perror ("Linked List does not Exist to display!");
		return;
	}

	printf ("<Linked List>(%d) :=\n", linked_list -> size);

	if (linked_list -> size == 0) {
		perror ("Linked List is Empty!");
		return;
	}

	Node* node = linked_list -> first_node;

	while (node != NULL) {
		printf ("\t-> ");
		display_node_details (node);
		node = *(node -> address_list -> item_addresses + 1);
	}

	printf ("\n");
}

void attach_node_at_last (Linked_List* linked_list, Node* node) {
	if (linked_list == NULL) {
		perror ("Empty list is given\n");
		exit (1);
	}

	if (node == NULL) {
		perror ("Empty node is given to add in Linked List\n");
		exit (1);
	}

	Node* new_node = duplicate_node (node);

	if (new_node != NULL) {
		*(new_node -> address_list -> item_addresses + 0) = linked_list -> last_node;
	}

	if (linked_list -> first_node == NULL) {
		linked_list -> first_node = new_node;
		linked_list -> last_node = new_node;
	} else {
		*(linked_list -> last_node -> address_list -> item_addresses + 1) = new_node;
		linked_list -> last_node = new_node;
	}

	++ linked_list -> size;																			// not guranteed -- to be fixed
}

void attach_node_at_first (Linked_List* linked_list, Node* node) {
	if (linked_list == NULL) {
		perror ("Empty list is given\n");
		exit (1);
	}

	if (node == NULL) {
		perror ("Empty node is given to add in Linked List\n");
		exit (1);
	}

	Node* new_node = duplicate_node (node);

	if (
		new_node != NULL																			// to check if new node is created
		&& new_node -> type != N_Tree																// don't overwrite addresses for tree node
	) {
		*(new_node -> address_list -> item_addresses + 1) = linked_list -> first_node;
	}

	if (linked_list -> first_node == NULL) {
		linked_list -> first_node = new_node;
		linked_list -> last_node = new_node;
	} else {
		*(linked_list -> first_node -> address_list -> item_addresses + 0) = new_node;
		linked_list -> first_node = new_node;
	}

	++ linked_list -> size;																			// not guranteed -- to be fixed
}

void detach_node_from_first (Linked_List* linked_list, bool node_delete_needed) {
	Node* node;

	if (linked_list == NULL) {
		perror ("Linked List does not Exist to detach node from!");
		exit (1);
	}

	if (linked_list -> size == 0) {
		perror ("Linked List is Empty to detach node from!\n");
		return;
	}

	if (linked_list -> first_node == linked_list -> last_node) {
		linked_list -> size = 0;
		linked_list -> first_node = NULL;
		linked_list -> last_node = NULL;
		return;
	}

	node = linked_list -> first_node;																// keep first node address at hand
	linked_list -> first_node = *(linked_list -> first_node -> address_list -> item_addresses + 1);	// node switch / hop
	*(linked_list -> first_node -> address_list -> item_addresses + 0) = NULL;						// forget previous node address
	-- linked_list -> size;																			// decrease node count

	if (node_delete_needed) {
		forget_list (&(node -> address_list));
		delete_node (&node);
	}
}

void detach_node_from_last (Linked_List* linked_list, bool node_delete_needed) {
	Node* node;

	if (linked_list == NULL) {
		perror ("Linked List does not exist to detach node from!");
		exit (1);
	}

	if (linked_list -> size == 0) {
		perror ("Linked List is empty to detach node from!");
		return;
	}

	if (linked_list -> first_node == linked_list -> last_node) {
		linked_list -> size = 0;
		linked_list -> first_node = NULL;
		linked_list -> last_node = NULL;
		return;
	}

	node = linked_list -> last_node;																// keep last node address at hand
	linked_list -> last_node = *(linked_list -> last_node -> address_list -> item_addresses + 0);	// node switch / hop
	*(linked_list -> last_node -> address_list -> item_addresses + 1) = NULL;						// forget next node address
	-- linked_list -> size;																			// decrease node count

	if (node_delete_needed) {
		forget_list (&(node -> address_list));
		delete_node (&node);
	}
}