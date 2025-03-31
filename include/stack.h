#ifndef STACK_H
#define STACK_H

// ---------- x ----------

#include "node.h"

// ---------- x ----------

typedef struct STACK {
	String* name;
	size_t size;
	Node* top_node;
} Stack;

// ---------- x ----------

Stack* create_stack (void);
void delete_stack (Stack** stack_address);
void display_stack (Stack* stack);
void display_stack_details (Stack* stack);
void push_node_onto_stack (Stack* stack, Node* node);
Node* pop_node_from_stack (Stack* stack);

#endif	// STACK_H