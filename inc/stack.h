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

Stack* create_Stack (void);
void display_Stack (Stack* stack);
void display_Stack_details (Stack* stack);
void delete_Stack (Stack** stack_address);
void push_Node_onto_Stack (Stack* stack, Node* node);
Node* pop_Node_from_Stack (Stack* stack);
void peek_Data_from_Stack (Stack* stack);
void push_Data_onto_Stack (Stack* stack, Data* data);
Data* pop_Data_from_Stack (Stack* stack);

#endif	// STACK_H