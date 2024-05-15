#ifndef QUEUE_H
#define QUEUE_H

// ---------- x ----------

#include "node.h"

// ---------- x ----------

typedef struct QUEUE {
	String* name;
	int size;
	Node* first_node;
	Node* last_node;
} Queue;

// ---------- x ----------

Queue* create_queue (void);
void delete_queue (Queue** queue_address);
void display_queue (Queue* queue);
void display_queue_details (Queue* queue);
void enqueue (Queue* queue, Node* node);
Node* dequeue (Queue* queue, bool node_delete_needed);

#endif // QUEUE_H