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
	size_t depth;
} Tree;

// ---------- x ----------

Tree* create_tree (void);
Tree* duplicate_tree (Tree* source_tree);
void delete_tree (Tree** tree_address);
void display_tree (Tree* tree);
void set_tree_root_node (Tree* tree, Node* root_node);
Node* get_Nth_child_node (Node* parent_node, size_t child_number);
Node* get_last_child_node (Node* parent_node);
Node* get_parent_node (Node* child_node);
void append_child_node (Tree* tree, Node* parent_node, Node* child_node);
void push_tree_node_to_stack (Stack* stack, Node* tree_node);
void enqueue_tree_node_to_queue (Queue* queue, Node* node);
void display_relation_with_root (Tree* tree, Node* node);
void display_child_node_list (Node* parent_node);
Node* search_tree_by_node_name (Tree* tree, String* node_name);
void display_sub_tree (Node* node);
size_t count_tree_nodes (Tree* tree);
void delete_node_from_tree (Tree* tree, Node* node);
Tree* create_sub_tree_from_node (Node* node);
void detach_node_from_parent (Node* child_node);
void print_node_depth_whitespace (size_t node_depth);
size_t get_tree_node_depth (Tree* tree, Node* tree_node);
void delete_tree_nodes_by_name (Tree* tree, String* node_name);
void display_tree_node (Node* node);
void export_tree_data_for_web_view (Tree* tree);

#endif	// TREE_H