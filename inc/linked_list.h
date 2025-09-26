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

Linked_List* create_linked_list (void);
void display_linked_list (Linked_List* linked_list);
void display_linked_list_details (Linked_List* linked_list);
void delete_linked_list (Linked_List** linked_list_address);
void attach_node_at_first (Linked_List* linked_list, Node* node);
void attach_node_at_last (Linked_List* linked_list, Node* node);
Node* detach_head_from_linked_list (Linked_List* linked_list);
Node* detach_tail_from_linked_list (Linked_List* linked_list);

#endif	// LINKED_LIST_H