#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// ---------- x ----------

#include "node.h"

// ---------- x ----------

typedef struct LINKED_LIST {
	String* name;
	size_t size;
	Node* head_node;
	Node* tail_node;
} Linked_List;

// ---------- x ----------

Linked_List* create_Linked_List (void);
void display_Linked_List (Linked_List* linked_list);
void display_Linked_List_details (Linked_List* linked_list);
void delete_Linked_List (Linked_List** linked_list_address);
void attach_Node_at_first (Linked_List* linked_list, Node* node);
void attach_Node_at_last (Linked_List* linked_list, Node* node);
Node* detach_head_from_Linked_List (Linked_List* linked_list);
Node* detach_tail_from_Linked_List (Linked_List* linked_list);

#endif	// LINKED_LIST_H