#ifndef TREE_H
#define TREE_H

// ---------- x ----------

#include "node.h"
#include "stack.h"
#include "queue.h"

// ---------- x ----------

typedef struct TREE {
	Node* root_node;
	size_t node_count;
	size_t breadth;
	size_t height;
} Tree;

// ---------- x ----------

Tree* create_Tree (void);
void set_Tree_root_Node (Tree* tree, Node* root_node);
Tree* duplicate_Tree (Tree* source_tree);
void display_Tree (Tree* tree);
void delete_Tree (Tree** tree_address);
// utilities
void push_Tree_Node_to_Stack (Stack* stack, Node* tree_node);
void enQueue_Tree_Node_to_Queue (Queue* queue, Node* node);
Node* search_Tree_by_Node_name (Tree* tree, String* node_name);
size_t count_Tree_Nodes (Tree* tree);
void print_Node_depth_whitespace (size_t node_depth);
size_t get_Tree_Node_depth (Tree* tree, Node* tree_node);
void display_Tree_Node (Node* node);
void export_Tree_Data_for_web_view (Tree* tree);
bool does_Tree_contain_Node (Tree* tree, Node* node);
// parent-children queries related
Node* get_Nth_child_Node (Node* parent_node, size_t child_number);
Node* get_first_child_Node (Node* parent_node);
Node* get_last_child_Node (Node* parent_node);
Node* get_parent_Node (Node* child_node);
void display_relation_with_root (Tree* tree, Node* node);
// parent-children update related
void append_child_Node (Tree* tree, Node* parent_node, Node* child_node);
void append_sibling_Node (Tree* tree, Node* node, Node* sibling_node);
void display_child_Node_List (Node* parent_node);
void display_sub_Tree (Tree* tree, Node* node);
void delete_Node_from_Tree (Tree* tree, Node* node);
Tree* create_sub_Tree_from_Node (Node* node);
void detach_Node_from_parent (Node* child_node);
void delete_Tree_Nodes_by_name (Tree* tree, String* node_name);
void display_path_towards_root (Tree* tree, Node* node);
Node* remove_child_Node (Tree* tree, Node* parent_node);
Node* get_last_child_Node_address (Node* parent_node); // returns actual address; handle with care
Node* get_parent_Node_address (Node* child_node); // returns actual address; handle with care

#endif	// TREE_H