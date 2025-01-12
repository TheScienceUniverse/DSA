#ifndef STACK_H
#define STACK_H

// ---------- x ----------

#include "node.h"

// ---------- x ----------

typedef struct STACK {
	String* name;
	size_t size;
	Node* first_node;
	Node* last_node;
} Stack;

// ---------- x ----------

Stack* create_stack (void);
void delete_stack (Stack** stack_address);
void display_stack (Stack* stack);
void display_stack_details (Stack* stack);
void push (Stack* stack, Node* node);
Node* pop (Stack* stack);

#endif	// STACK_H