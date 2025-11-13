#include "../inc/stack.h"

Stack* create_Stack (void) {
	Stack* stack = (Stack*) malloc (sizeof (Stack));

	if (stack != NULL) {
		log_memory (DS_Stack, sizeof (Stack), stack, true);

		stack -> name = NULL;
		stack -> size = 0;
		stack -> top_node = NULL;
	}

	return stack;
}

void display_Stack (Stack* stack) {
	if (stack == NULL) {
		perror ("Stack does not exist to display!");
		return;
	}

	if (stack -> size == 0) {
		perror ("Stack is empty to display!");
		return;
	}

	printf ("Stack :=>\n");

	Node* node = stack -> top_node;

	printf ("+--------+");

	for (size_t i = 0; i < stack -> size; i++) {
		printf ("\n|\t");
		display_Node (node);
		printf ("\n+--------+");
		node = (node -> address_list -> head_chunk -> first_data_address + 1) -> address;
	}

	printf ("\n");
}

void display_Stack_details (Stack* stack) {
	if (stack == NULL) {
		perror ("Stack does not exist to display details!");
		return;
	}

	if (stack -> size == 0) {
		perror ("Stack is empty to display details!");
		return;
	}

	printf ("Stack (%zu) :=>\n", stack -> size);

	Node* node = stack -> top_node;

	for (size_t i = 0; i < stack -> size; i++) {
		display_Node_details (node);
		node = (node -> address_list -> head_chunk -> first_data_address + 1) -> address;
	}

	printf ("\n");
}

void delete_Stack (Stack** stack_address) {
	if (*stack_address == NULL) {
		perror ("Stack does not exist to delete!");
		return;
	}

	Stack* stack = *stack_address;

	Node* node = stack -> top_node;
	Node* del_node;

	for (size_t i = 0; i < stack -> size; i++) {
		del_node = node;
		node = (node -> address_list -> head_chunk -> first_data_address + 1) -> address;
		delete_Node (&del_node);
	}

	stack = NULL;

	log_memory (DS_Stack, sizeof (Stack), *stack_address, false);
	ERASE (stack_address, sizeof (Stack));
}

void push_Node_onto_Stack (Stack* stack, Node* node) {
	if (stack == NULL) {
		perror ("Stack does not exist to push node onto\n");
		exit (EXIT_FAILURE);
	}

	if (node == NULL) {
		perror ("Node does not exist to push into stack\n");
		exit (EXIT_FAILURE);
	}

	Node* new_node = duplicate_Node (node);

	(new_node -> address_list -> head_chunk -> first_data_address + 1) -> address = stack -> top_node;

	if (NULL == stack -> top_node) {
		stack -> top_node = new_node;
		++ stack -> size;
		return;
	}

	Node* temp_node = stack -> top_node;

	(temp_node -> address_list -> head_chunk -> first_data_address + 0) -> address = new_node;

	stack -> top_node = new_node;

	++ stack -> size;
}

Node* pop_Node_from_Stack (Stack* stack) {
	if (stack == NULL) {
		// perror ("Stack does not exist to pop node from!");
		// exit (EXIT_FAILURE);
		return NULL;
	}

	if (stack -> size == 0) {
		// perror ("Stack is empty to pop node from!\n");
		return NULL;
	}

	Node* node = NULL;

	if (1 == stack -> size) {
		stack -> size = 0;
		node = stack -> top_node;
		stack -> top_node = NULL;
		return node;
	}

	node = stack -> top_node;
	stack -> top_node = (stack -> top_node -> address_list -> head_chunk -> first_data_address + 1) -> address;
	(stack -> top_node -> address_list -> head_chunk -> first_data_address + 0) -> address = NULL;

	-- stack -> size;

	(node -> address_list -> head_chunk -> first_data_address + 0) -> address = NULL;
	(node -> address_list -> head_chunk -> first_data_address + 1) -> address = NULL;

	return node;
}

void peek_Data_from_Stack (Stack* stack) {
	if (NULL == stack) {
		// perror ("Stack does not exist to peek data from!");
		// exit (EXIT_FAILURE);
		return;
	}

	if (0 == stack -> size) {
		// perror ("Stack is empty to peek data from!\n");
		return;
	}

	printf ("Peeked ");
	display_Data_details (stack -> top_node -> data);
	printf ("\n");
}

void push_Data_onto_Stack (Stack* stack, Data* data) {
	if (stack == NULL) {
		perror ("Stack does not exist to push node onto\n");
		exit (EXIT_FAILURE);
	}

	if (data == NULL) {
		perror ("Data does not exist to push into stack\n");
		exit (EXIT_FAILURE);
	}

	Node* node = create_Node (N_Stack);
	node -> data = data;

	push_Node_onto_Stack (stack, node);

	node -> data = NULL;
	delete_Node (&node);
}

Data* pop_Data_from_Stack (Stack* stack) {
	if (stack == NULL) {
		// perror ("Stack does not exist to pop node from!");
		// exit (EXIT_FAILURE);
		return NULL;
	}

	if (stack -> size == 0) {
		// perror ("Stack is empty to pop node from!\n");
		return NULL;
	}

	Data* data;
	Node* node = pop_Node_from_Stack (stack);

	data = node -> data;

	node -> data = NULL;
	delete_Node (&node);

	return data;
}