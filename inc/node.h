#ifndef NODE_H
#define NODE_H

// ---------- x ----------

#include "data.h"
#include "list.h"

// ---------- x ----------

typedef enum NODE_TYPE {
	N_Undefined
	, N_LinkedList
	, N_Stack
	, N_Queue
	, N_Tree
	, N_Graph
} Node_Type;

typedef struct NODE {
	Node_Type type;
	String* name;
	List* address_list;
	Data* data;
} Node;

// ---------- x ----------

Node* create_Node (Node_Type type);
void set_Node_name (Node* node, size_t name_length, char* name_address);
void prepare_Node_address_list (Node* node);
void set_Node_Data (Node* node, Data* data);
Node* duplicate_Node (Node* node);
void display_Node (Node* node);
void display_special_Node (Node* node);
void display_Node_details (Node* node);
void delete_Node (Node** node_address);
void delete_temporary_Node (Node** node_address);
Compare_Status compare_Nodes (Node* node_1, Node* node_2);
void clear_Node_address_list (Node* node);

#endif	// NODE_H