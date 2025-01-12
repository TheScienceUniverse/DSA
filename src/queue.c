#include "../include/queue.h"

Queue *create_queue () {
	Queue* queue = (Queue*) malloc (sizeof (Queue));

	if (queue != NULL) {
		queue -> name = NULL;
		queue -> size = 0;
		queue -> first_node = NULL;
		queue -> last_node = NULL;
	}

	return queue;
}

void delete_queue (Queue** queue_address) {
	if (*queue_address == NULL) {
		perror ("Linked List does not exist to delete!");
		return;
	}

	Queue* queue = *queue_address;

	Node* node = queue -> first_node;
	Node* old_node;

	while (node != NULL) {
		old_node = node;
		node = *(node -> address_list -> item_addresses + 1);
		forget_list (&(old_node -> address_list));
		delete_node (&old_node);
	}

	queue = NULL;
	ERASE (queue_address, sizeof (Queue));
}

void display_queue (Queue* queue) {
	if (queue == NULL) {
		perror ("Linked List does not Exist to display!");
		return;
	}

	if (queue -> size == 0) {
		perror ("Linked List is Empty to display!");
		return;
	}

	Node* node = queue -> first_node;

	while (node != NULL) {
		display_node (node);

		node = *(node -> address_list -> item_addresses + 1);

		if (node  != NULL) {
			printf (" -> ");
		}
	}

	printf ("\n");
}

void display_queue_details (Queue* queue) {
	if (queue == NULL) {
		perror ("Linked List does not Exist to display!");
		return;
	}

	printf ("<Linked List>(%zu) :=\n", queue -> size);

	if (queue -> size == 0) {
		perror ("Linked List is Empty!");
		return;
	}

	Node* node = queue -> first_node;

	while (node != NULL) {
		printf ("\t-> ");
		display_node_details (node);
		node = *(node -> address_list -> item_addresses + 1);
	}

	printf ("\n");
}

void enqueue (Queue* queue, Node* node) {
	if (queue == NULL) {
		perror ("Empty list is given\n");
		exit (1);
	}

	if (node == NULL) {
		perror ("Empty node is given to add in Linked List\n");
		exit (1);
	}

	Node* new_node = duplicate_node (node);

	if (new_node != NULL) {
		*(new_node -> address_list -> item_addresses + 0) = queue -> last_node;
	}

	if (queue -> first_node == NULL) {
		queue -> first_node = new_node;
		queue -> last_node = new_node;
	} else {
		*(queue -> last_node -> address_list -> item_addresses + 1) = new_node;
		queue -> last_node = new_node;
	}

	++ queue -> size;																			// not guranteed -- to be fixed
}

Node* dequeue (Queue* queue, bool node_delete_needed) {
	Node* node;

	if (queue == NULL) {
		perror ("Linked List does not Exist to detach node from!");
		exit (1);
	}

	if (queue -> size == 0) {
		perror ("Linked List is Empty to detach node from!\n");
		return NULL;
	}

	if (queue -> first_node == queue -> last_node) {
		queue -> size = 0;
		queue -> first_node = NULL;
		queue -> last_node = NULL;
		return NULL;
	}

	node = queue -> first_node;																// keep first node address at hand
	queue -> first_node = *(queue -> first_node -> address_list -> item_addresses + 1);	// node switch / hop
	*(queue -> first_node -> address_list -> item_addresses + 0) = NULL;						// forget previous node address
	-- queue -> size;																			// decrease node count

	if (node_delete_needed) {
		forget_list (&(node -> address_list));
		delete_node (&node);
	}

	return node;
}