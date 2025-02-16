#include "../include/tree.h"

Tree* create_tree () {
	Tree* tree = (Tree*) malloc (sizeof (Tree));

	if (tree != NULL) {
		tree -> root_node = NULL;
		tree -> node_count = 0;
		tree -> breadth = 0;
		tree -> depth = 0;
	}

	return tree;
}

Tree* duplicate_tree (Tree* tree) {
	/*Tree *new_tree = create_tree ();
	return new_tree;*/
	return tree;
}

void delete_tree (Tree** tree_address) {
	if (*tree_address == NULL) {
		perror ("Tree does not exists to delete!");
		return;
	}

	if ((*tree_address) -> node_count == 0) {
		ERASE (tree_address, sizeof (Tree));
		return;
	}

	Tree* tree = *tree_address;
	List* list = create_list (tree -> node_count);
	size_t i, list_index = 0;
	Node* node;
	Node* child_node;
	Node* x_node;
	Stack* stack = create_stack ();

	node = get_root_node (tree);
	push_tree_node_to_stack (stack, node);

	while (stack -> size > 0) {
		x_node = pop (stack);
		node = x_node -> data -> address;
		*(list -> item_addresses + list_index++) = node;
		delete_temporary_node (&x_node);

		i = node -> address_list -> item_count;

		while (i--) {
			child_node = *(node -> address_list -> item_addresses + i);
			push_tree_node_to_stack (stack, child_node);
		}
	}

	delete_stack (&stack);

	for (i = 0; i < list -> item_count; i++) {
		node = *(list -> item_addresses + i);
		forget_list (&(node -> address_list));
		delete_node (&node);
	}

	forget_list (&list);
	delete_list (&list);

	node = NULL;
	tree = NULL;
	ERASE (tree_address, sizeof (Tree));
}

void display_tree (Tree* tree) {
	if (tree == NULL) {
		perror ("Tree does not exist to display");
		return;
	}

	if (tree -> node_count == 0) {
		perror ("Tree does not have any node to display");
		return;
	}

	size_t i, depth = 0;
	Node* node;
	Node* child_node;
	Node* x_node;
	Stack* stack = create_stack ();

	stack -> name = create_string (10, "Node Stack");

	node = get_root_node (tree);
	push_tree_node_to_stack (stack, node);

	while (stack -> size > 0) {
		x_node = pop (stack);
		node = x_node -> data -> address;
		depth = get_tree_node_depth (tree, node);
		delete_temporary_node (&x_node);

		print_node_depth_whitespace (depth);
		display_node (node);
		printf ("\n");

		i = node -> address_list -> item_count;

		while (--i) {													
			if (i <= 0) {
				break;
			}

			child_node = *(node -> address_list -> item_addresses + i);
			push_tree_node_to_stack (stack, child_node);
		}
	}

	node = NULL;
	delete_stack (&stack);
}

void set_root_node (Tree* tree, Node* node) {
	if (tree == NULL) {
		perror ("Tree does not exist to add Root!");
		return;
	}

	if (node == NULL) {
		perror ("Node does not exist to add Root!");
		return;
	}

	if (tree -> root_node != NULL) {
		perror ("Tree already have root node!");
		return;
	}

	tree -> root_node = duplicate_node (node);
	*(tree -> root_node -> address_list -> item_addresses + 0) = NULL;
	++ tree -> node_count;
}

Node* get_root_node (Tree* tree) {
	if (tree == NULL) {
		perror ("Tree does not exist to add Root!");
		return NULL;
	}

	return tree -> root_node;
}

void display_relation_with_root (Tree* tree, Node* node) {
	if (tree == NULL) {
		perror ("Tree does not exist to display Root!");
		return;
	}

	if (node == NULL) {
		perror ("Node does not exist to display Root!");
		return;
	}

	if (node -> type != N_Tree) {
		perror ("Given Node doesn't belong to a tree to display Root!");
		return;
	}

	Stack* stack = create_stack ();
	Node* stack_node;

	do {
		stack_node = create_node (N_Stack);
		set_node_name (stack_node, node -> name -> length, node -> name -> address);
		push (stack, stack_node);
		delete_node (&stack_node);
	} while ((node = get_parent_node (node)) != NULL);

	display_stack (stack);
	delete_stack (&stack);
}

size_t get_tree_node_depth (Tree* tree, Node* node) {
	if (tree == NULL) {
		perror ("Tree does not exist to get depth!");
		return -1;
	}

	if (node == NULL) {
		perror ("Node does not exist to get depth!");
		return -1;
	}

	if (node -> type != N_Tree) {
		perror ("Given Node doesn't belong to a tree get depth!");
		return -1;
	}

	size_t depth = 0;
	Node* parent_node;

	while ((parent_node = get_parent_node (node)) != NULL) {
		++ depth;
		node = parent_node;
	}

	if (node != get_root_node (tree)) {
		depth = -1;
	}

	node = NULL;
	parent_node = NULL;

	return depth;
}

void display_child_node_list (Node* node) {
	if (node == NULL) {
		perror ("Node does not exist to display Root!");
		return;
	}

	if (node -> type != N_Tree) {
		perror ("Given Node doesn't belong to a tree");
		return;
	}

	printf ("[");

	for (size_t i = 1; i < node -> address_list -> item_count; i++) {
		display_node (*(node -> address_list -> item_addresses + i));

		if (i < node -> address_list -> item_count - 1) {
			printf (",");
		}
	}

	printf ("]\n");
}

Node* get_parent_node (Node* node) {
	if (node == NULL) {
		perror ("Given Node doesn't exists");
		return NULL;
	}

	if (node -> type != N_Tree) {
		perror ("Given Node doesn't belong to a tree");
		return NULL;
	}

	return *(node -> address_list -> item_addresses + 0);
}

Node* get_Nth_child_node (Node* parent_node, size_t n) {
	if (parent_node == NULL) {
		perror ("Given Node doesn't exists");
		return NULL;
	}

	if (parent_node -> type != N_Tree) {
		perror ("Given Node doesn't belong to a tree");
		return NULL;
	}

	Node* child_node = NULL;

	if (parent_node -> address_list -> item_count > n) {
		child_node = *(parent_node -> address_list -> item_addresses + n);
	}

	return child_node;
}

Node* get_last_child_node (Node* parent_node) {
	if (parent_node == NULL) {
		perror ("Given Node doesn't exists");
		return NULL;
	}

	if (parent_node -> type != N_Tree) {
		perror ("Given Node doesn't belong to a tree");
		return NULL;
	}

	int child_count = parent_node -> address_list -> item_count - 1;
	Node* child_node = NULL;

	if (child_count > 0) {
		child_node = get_Nth_child_node (parent_node, child_count);
	}

	return child_node;
}

void append_child_node (Tree* tree, Node* parent_node, Node* child_node) {
	if (parent_node == NULL) {
		perror ("Parent Node does not Exist to add child node!");
		return;
	}

	if (child_node == NULL) {
		perror ("Child Node does not Exist to add child node!");
		return;
	}

	child_node = duplicate_node (child_node);
	*(child_node -> address_list -> item_addresses + 0) = parent_node;
	add_to_list (parent_node -> address_list, child_node, false);
	++(tree -> node_count);
}

void push_tree_node_to_stack (Stack* stack, Node* node) {
	Node* stack_node = create_node (N_Stack);
	stack_node -> name = duplicate_string (node -> name);
	stack_node -> data = create_data (DT_Address, sizeof (void*), node);

	push (stack, stack_node);
	delete_temporary_node (&stack_node);
}

void enqueue_tree_node_to_queue (Queue* queue, Node* node) {
	Node* queue_node = create_node (N_Queue);
	queue_node -> name = duplicate_string (node -> name);
	queue_node -> data = create_data (DT_Address, sizeof (void*), node);

	enqueue (queue, queue_node);
	delete_temporary_node (&queue_node);
}

Node* search_tree_by_node_name (Tree* tree, String* name) {
	if (tree == NULL) {
		perror ("Tree does not exist to search");
		return NULL;
	}

	if (name == NULL) {
		perror ("Search item does not exist to search into tree");
		return NULL;
	}

	if (tree -> root_node == NULL) {
		perror ("Tree does not have node to search");
		return NULL;
	}

	Node* x_node;
	Node* node;
	size_t i;
	bool found = false;
	void** address;
	Queue* queue = create_queue ();

	node = get_root_node (tree);
	enqueue_tree_node_to_queue (queue, node);

	while (queue -> size > 0) {
		x_node = dequeue (queue, true);
		node = x_node -> data -> address;
		delete_temporary_node (&x_node);

		if (are_strings_equal (node -> name, name)) {
			found = true;
			break;
		}

		i = node -> address_list -> item_count;
		address = node -> address_list -> item_addresses;

		while (i--) {													
			++address;
			enqueue_tree_node_to_queue (queue, *(address));
		}	
	}

	if (queue -> size > 0) {
		x_node = queue -> first_node;
		i = queue -> size;

		while (i--) {
			forget_data (&(x_node -> data));
			x_node = *(x_node -> address_list -> item_addresses + 1);
		}
	}

	delete_queue (&queue);

	if (!found) {
		node = NULL;
	}

	return node;
}

void display_sub_tree (Node* node) {
	if (node == NULL) {
		perror ("Node does not Exist to add to sub-tree to delete");
		return;
	}

	if (node -> type != N_Tree) {
		perror ("Node does not belong to a tree to add to sub-tree to delete");
		return;
	}

	Tree* tree = create_tree ();
	set_root_node (tree, node);
	display_tree (tree);
	tree -> root_node = NULL;
	tree -> node_count = 0;
	delete_tree (&tree);
}

size_t count_tree_nodes (Tree* tree) {
	if (tree -> root_node == NULL) {
		perror ("Tree does not exist to count nodes");
		return -1;
	}

	if (tree -> root_node == NULL) {
		perror ("Tree does not have any node to count");
		return -1;
	}
	
	size_t i, node_count = 0;
	Node* node;
	Node* child_node;
	Node* x_node;
	Stack* stack = create_stack ();

	node = get_root_node (tree);
	push_tree_node_to_stack (stack, node);

	while (stack -> size > 0) {
		x_node = pop (stack);
		node = x_node -> data -> address;
		delete_temporary_node (&x_node);

		++node_count;
		i = node -> address_list -> item_count;

		while (i--) {
			child_node = *(node -> address_list -> item_addresses + i);
			push_tree_node_to_stack (stack, child_node);
		}
	}

	delete_stack (&stack);
	node = NULL;

	return node_count;
}

Tree* create_sub_tree_from_node (Node* node) {
	if (node == NULL) {
		perror ("Node does not Exist to create sub-tree");
		return NULL;
	}

	if (node -> type != N_Tree) {
		perror ("Node does not belong to a tree to create sub-tree");
		return NULL;
	}

	Tree* sub_tree = create_tree ();

	if (sub_tree != NULL) {
		set_root_node (sub_tree, node);
		sub_tree -> node_count = count_tree_nodes (sub_tree);
	}

	return sub_tree;
}

void detach_node_from_parent (Node* node) {
	if (node == NULL) {
		perror ("Node does not belong to a tree to detach from parent");
		return;
	}

	Node* parent_node = get_parent_node (node);

	if (parent_node != NULL) {
		remove_address_from_list (parent_node -> address_list, node);
		*(node -> address_list -> item_addresses + 0) = NULL;
	}

	parent_node = NULL;
}

void delete_node_from_tree (Tree* tree, Node* node)  {
	if (tree == NULL) {
		perror ("Tree does not Exist to delete node from");
		return;
	}

	if (node == NULL) {
		perror ("Node does not Exist to delete from tree");
		return;
	}

	if (node -> type != N_Tree) {
		perror ("Node does not belong to a tree to delete from");
		return;
	}

	Tree* sub_tree = create_sub_tree_from_node (node);

	if (sub_tree != NULL && sub_tree -> node_count > 0) {
		detach_node_from_parent (node);
		tree -> node_count -= sub_tree -> node_count;
		delete_tree (&sub_tree);
	}

	sub_tree = NULL;
}

void print_node_depth_whitespace (size_t depth) {
	size_t i;

	if (depth > 0) {
		for (i = 0; i < depth; i++) {
			printf ("\t|");
		}

		printf ("\n");

		for (i = 1; i < depth; i++) {
			printf ("\t|");
		}

		printf ("\t+--->");
	}
}

void delete_tree_nodes_by_name (Tree* tree, String* node_name) {
	if (tree == NULL) {
		perror ("Tree does not exist to delete all nodes by name!");
		return;
	}

	if (node_name == NULL) {
		perror ("Name is not provided to delete all nodes by name!");
		return;
	}

	Node* node;

	while ((node = search_tree_by_node_name (tree, node_name)) != NULL) {
		delete_node_from_tree (tree, node);
	}
}

void display_tree_node (Node* node) {
	display_node (node);
	printf (" => [");
	display_data (node -> data);
	printf ("]");
}

void export_tree_data_for_web_view (Tree* tree) {
	if (tree == NULL) {
		perror ("Tree does not exist to export");
		return;
	}

	FILE* fpo = fopen ("../web/tree/data.js", "wb+");

	List* list = create_list (tree -> node_count);
	size_t list_index = 0;
	size_t i, linked_address_count, j;

	Node* node;
	Node* child_node;
	Node* x_node;
	Queue* queue = create_queue ();

	node = get_root_node (tree);
	enqueue_tree_node_to_queue (queue, node);

	while (queue -> size > 0) {
		x_node = dequeue (queue, false);
		node = x_node -> data -> address;
		*(list -> item_addresses + list_index++) = node;
		delete_temporary_node (&x_node);

		linked_address_count = node -> address_list -> item_count;

		for (i = 1 ; i < linked_address_count; i++) {
			child_node = *(node -> address_list -> item_addresses + i);
			enqueue_tree_node_to_queue (queue, child_node);
		}
	}

	delete_queue (&queue);

	Node* parent_node = NULL;

	fprintf (fpo, "const tree_node_list = [");

	for (i = 0; i < list -> item_count; i++) {
		node = *(list -> item_addresses + i);
		parent_node = *(node -> address_list -> item_addresses + 0);

		fprintf (fpo, "\n\t");

		if (i > 0) {
			fprintf (fpo, ", ");
		}

		fprintf (fpo, "[\"%s\", ", node -> name -> address);

		if (parent_node == NULL) {
			fprintf (fpo, "null");
		} else {
			fprintf (fpo, "\"%s\"", parent_node -> name -> address);
		}

		fprintf (fpo, ", [");

		for (j = 1; j < node -> address_list -> item_count; j++) {
			child_node = *(node -> address_list -> item_addresses + j);

			if (j > 1) {
				fprintf (fpo, ", ");
			}

			fprintf (fpo, "\"%s\"", child_node -> name -> address);
		}

		fprintf (fpo, "]]");
	}

	forget_list (&list);
	delete_list (&list);

	fprintf (fpo, "\n];");

	fclose (fpo);
}