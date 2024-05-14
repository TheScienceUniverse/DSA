#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// ---------- x ----------

#include "node.h"

// ---------- x ----------

typedef struct LINKED_LIST {
	String* name;
	int size;
	Node* first_node;
	Node* last_node;
} Linked_List;

// ---------- x ----------

Linked_List* create_linked_list (void);
void delete_linked_list (Linked_List** linked_list_address);
void display_linked_list (Linked_List* linked_list);
void display_linked_list_details (Linked_List* linked_list);
void attach_node_at_first (Linked_List* linked_list, Node* node);
void attach_node_at_last (Linked_List* linked_list, Node* node);
void detach_node_from_first (Linked_List* linked_list, bool node_delete_needed);
void detach_node_from_last (Linked_List* linked_list, bool node_delete_needed);

#endif	// LINKED_LIST_H