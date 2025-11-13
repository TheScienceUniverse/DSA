#include "../inc/queue.h"

Queue* create_Queue (void) {
	Queue* queue = (Queue*) malloc (sizeof (Queue));

	if (queue != NULL) {
		log_memory (DS_Queue, sizeof (Queue), queue, true);

		queue -> name = NULL;
		queue -> size = 0;
		queue -> front_node = NULL;
		queue -> rear_node = NULL;
	}

	return queue;
}

void display_Queue (Queue* queue) {
	if (queue == NULL) {
		perror ("Queue does not exist to display!");
		return;
	}

	if (queue -> size == 0) {
		// perror ("Queue is empty to display!");
		return;
	}

	printf ("Queue :=> [ ");

	Node* node = queue -> front_node;

	for (size_t i = 0; i < queue -> size; i++) {
		if (i > 0) {
			printf (" <- ");
		}

		display_Node (node);
		node = (node -> address_list -> head_chunk -> first_data_address + 1) -> address;
	}

	printf (" ]\n");
}

void display_Queue_details (Queue* queue) {
	if (queue == NULL) {
		perror ("Stack does not exist to display details!");
		return;
	}

	if (queue -> size == 0) {
		perror ("Stack is empty to display details!");
		return;
	}

	printf ("Queue (%zu) :=>\n", queue -> size);

	Node* node = queue -> front_node;

	for (size_t i = 0; i < queue -> size; i++) {
		display_Node_details (node);
		node = (node -> address_list -> head_chunk -> first_data_address + 1) -> address;
	}

	printf ("\n");
}

void delete_Queue (Queue** queue_address) {
	if (*queue_address == NULL) {
		// perror ("Queue does not exist to delete!");
		return;
	}

	Queue* queue = *queue_address;

	Node* node = queue -> front_node;
	Node* del_node;

	for (size_t i = 0; i < queue -> size; i++) {
		del_node = node;
		node = (node -> address_list -> head_chunk -> first_data_address + 1) -> address;
		delete_Node (&del_node);
	}

	queue = NULL;

	log_memory (DS_Queue, sizeof (Queue), *queue_address, false);
	ERASE (queue_address, sizeof (Queue));
}

void enQueue (Queue* queue, Node* node) {
	if (queue == NULL) {
		perror ("Queue does not exist to attach node at last\n");
		exit (EXIT_FAILURE);
	}

	if (node == NULL) {
		perror ("Node does not exist to attach at last of queue\n");
		exit (EXIT_FAILURE);
	}

	Node* new_node = duplicate_Node (node);

	new_node -> address_list -> head_chunk -> first_data_address -> address = queue -> rear_node;

	if (
		NULL == queue -> front_node
		|| NULL == queue -> rear_node
	) {
		queue -> front_node = new_node;
		queue -> rear_node = new_node;
		queue -> size++;
		return;
	}

	Node* temp_node = queue -> rear_node;

	(temp_node -> address_list -> head_chunk -> first_data_address + 1) -> address = new_node;

	queue -> rear_node = new_node;

	queue -> size++;
}

Node* deQueue (Queue* queue) {
	if (queue == NULL) {
		// perror ("Queue does not exist to detach node from first!");
		// exit (EXIT_FAILURE);
		return NULL;
	}

	if (queue -> size == 0) {
		// perror ("Queue is empty to detach node from first!\n");
		return NULL;
	}

	Node* node;

	if (1 == queue -> size) {
		queue -> size = 0;
		node = queue -> front_node;
		queue -> front_node = NULL;
		queue -> rear_node = NULL;
		return node;
	}

	node = queue -> front_node;
	queue -> front_node = (queue -> front_node -> address_list -> head_chunk -> first_data_address + 1) -> address;
	(queue -> front_node -> address_list -> head_chunk -> first_data_address + 0) -> address = NULL;

	queue -> size--;

	(node -> address_list -> head_chunk -> first_data_address + 0) -> address = NULL;
	(node -> address_list -> head_chunk -> first_data_address + 1) -> address = NULL;

	return node;
}

void peek_Data_from_Queue (Queue* queue) {
	if (NULL == queue) {
		// perror ("Stack does not exist to peek data from!");
		// exit (EXIT_FAILURE);
		return;
	}

	if (0 == queue -> size) {
		// perror ("Stack is empty to peek data from!\n");
		return;
	}

	printf ("Peeked ");
	display_Data_details (queue -> front_node -> data);
	printf ("\n");
}