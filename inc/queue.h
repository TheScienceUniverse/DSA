#ifndef QUEUE_H
#define QUEUE_H

// ---------- x ----------

#include "node.h"

// ---------- x ----------

typedef struct QUEUE {
	String* name;
	size_t size;
	Node* front_node;
	Node* rear_node;
} Queue;

// ---------- x ----------

Queue* create_Queue (void);
void display_Queue (Queue* queue);
void display_Queue_details (Queue* queue);
void delete_Queue (Queue** queue_address);
void enQueue (Queue* queue, Node* node);
Node* deQueue (Queue* queue);
void peek_Data_from_Queue (Queue* queue);

#endif // QUEUE_H