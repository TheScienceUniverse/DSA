#include "../include/stack.h"

Stack *create_stack (void) {
	Stack* stack = (Stack*) malloc (sizeof (Stack));

	if (stack != NULL) {
		stack -> name = NULL;
		stack -> size = 0;
		stack -> first_node = NULL;
		stack -> last_node = NULL;
	}

	return stack;
}

void delete_stack (Stack** stack_address) {
	if (*stack_address == NULL) {
		perror ("Linked List does not exist to delete!");
		return;
	}

	Stack* stack = *stack_address;

	Node* node = stack -> first_node;
	Node* old_node;

	while (node != NULL) {
		old_node = node;
		node = *(node -> address_list -> item_addresses + 1);
		forget_list (&(old_node -> address_list));
		delete_node (&old_node);
	}

	stack = NULL;
	ERASE (stack_address, sizeof (Stack));
}

void display_stack (Stack* stack) {
	if (stack == NULL) {
		perror ("Linked List does not Exist to display!");
		return;
	}

	if (stack -> size == 0) {
		perror ("Linked List is Empty to display!");
		return;
	}

	Node* node = stack -> first_node;

	while (node != NULL) {
		display_node (node);

		node = *(node -> address_list -> item_addresses + 1);

		if (node  != NULL) {
			printf (" -> ");
		}
	}

	printf ("\n");
}

void display_stack_details (Stack* stack) {
	if (stack == NULL) {
		perror ("Linked List does not Exist to display!");
		return;
	}

	printf ("<Linked List>(%zu) :=\n", stack -> size);

	if (stack -> size == 0) {
		perror ("Linked List is Empty!");
		return;
	}

	Node* node = stack -> first_node;

	while (node != NULL) {
		printf ("\t-> ");
		display_node_details (node);
		node = *(node -> address_list -> item_addresses + 1);
	}

	printf ("\n");
}

void push (Stack* stack, Node* node) {
	if (stack == NULL) {
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
		*(new_node -> address_list -> item_addresses + 1) = stack -> first_node;
	}

	if (stack -> first_node == NULL) {
		stack -> first_node = new_node;
		stack -> last_node = new_node;
	} else {
		*(stack -> first_node -> address_list -> item_addresses + 0) = new_node;
		stack -> first_node = new_node;
	}

	++ stack -> size;																			// not guranteed -- to be fixed
}

Node* pop (Stack* stack) {
	if (stack == NULL) {
		perror ("Linked List does not Exist to detach node from!");
		exit (1);
	}

	if (stack -> size == 0) {
		perror ("Linked List is Empty to detach node from!\n");
		return NULL;
	}

	if (stack -> first_node == stack -> last_node) {
		stack -> size = 0;
		stack -> first_node = NULL;
		stack -> last_node = NULL;
		return NULL;
	}

	Node* node = stack -> first_node;																// keep first node address at hand
	stack -> first_node = *(stack -> first_node -> address_list -> item_addresses + 1);	// node switch / hop
	*(stack -> first_node -> address_list -> item_addresses + 0) = NULL;						// forget previous node address
	-- stack -> size;																			// decrease node count

	return node;
}