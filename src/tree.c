#include "../include/tree.h"

Tree* create_tree () {
	Tree* tree = (Tree*) malloc (sizeof (Tree));

	if (tree != NULL) {
		tree -> root_node = NULL;
		tree -> node_count = 0;
		tree -> breadth = 0;
		tree -> height = 0;
	}

	return tree;
}

void delete_tree (Tree** tree_address) {
	if (*tree_address == NULL) {
		// perror ("Tree does not exists to delete!");
		return;
	}

	if ((*tree_address) -> node_count == 0) {
		ERASE (tree_address, sizeof (Tree));
		return;
	}

	Tree* tree = *tree_address;
	ssize_t i;
	size_t address_count;
	Node* node;
	Node* x_node;
	Stack* stack = create_stack ();
	Node* stack_node = create_node (N_Stack);
	size_t visited_node_count = 1;

	stack_node -> data = create_address_data (tree -> root_node);
	push_node_onto_stack (stack, stack_node);

	while (
		tree -> node_count >= visited_node_count
		&& stack -> size > 0
	) {
		x_node = pop_node_from_stack (stack);
		node = x_node -> data -> address;
		x_node -> data -> address = NULL;
		delete_node (&x_node);
		address_count = node -> address_list -> item_count;

		if (1 > address_count) {
			delete_node (&node);
			continue;
		}

		i = address_count;

		while (--i) {	// storing backwards to pick up in proper order
			Data* data = get_list_data_at_index (node -> address_list, i);
			stack_node -> data -> address = data -> address;
			delete_data (&data);
			push_node_onto_stack (stack, stack_node);
		}

		delete_node (&node);

		++ visited_node_count;
	}

	delete_node (&stack_node);

	node = NULL;
	delete_stack (&stack);

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

	printf ("Tree :=> node_count: (%lu) breadth: (%lu) height: (%lu)\n", tree -> node_count, tree -> breadth, tree -> height);

	ssize_t i;
	size_t address_count, depth = 0;
	Node* node;
	Node* x_node;
	Stack* stack = create_stack ();
	Node* stack_node = create_node (N_Stack);
	size_t visited_node_count = 1;

	stack_node -> data = create_address_data (tree -> root_node);
	push_node_onto_stack (stack, stack_node);

	while (
		tree -> node_count >= visited_node_count
		&& stack -> size > 0
	) {
		x_node = pop_node_from_stack (stack);
		node = x_node -> data -> address;
		x_node -> data -> address = NULL;
		delete_node (&x_node);

		depth = get_tree_node_depth (tree, node);

		putchar ('\t');

		if (0 != depth) {
			for (ssize_t i = 0; i < (ssize_t) depth; i++) {
				printf ("|\t");
			}

			printf ("\n\t");

			for (ssize_t i = 0; i < (ssize_t)(depth - 1); i++) {
				printf ("|\t");
			}

			putchar ('+');
			display_N_characters ('-', depth - 1 + 3);
		}

		display_node (node);
		printf ("\n");

		address_count = node -> address_list -> item_count;

		if (1 > address_count) {
			continue;
		}

		i = address_count;

		while (--i) {	// storing backwards to pick up in proper order
			Data* data = get_list_data_at_index (node -> address_list, i);
			stack_node -> data -> address = data -> address;
			delete_data (&data);
			push_node_onto_stack (stack, stack_node);
		}

		++ visited_node_count;
	}

	delete_node (&stack_node);

	node = NULL;
	delete_stack (&stack);
}

void set_tree_root_node (Tree* tree, Node* node) {
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
	tree -> root_node -> address_list -> head_chunk -> first_data_address -> address = NULL;
	++ tree -> node_count;
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
	clear_node_address_list (child_node);	// address sanity

	Data* addr_data = create_address_data (parent_node);
	insert_data_into_list (child_node -> address_list, addr_data);

	size_t address_count = parent_node -> address_list -> item_count;

	if (0 == address_count) {
		addr_data -> address = NULL;
		insert_data_into_list (parent_node -> address_list, addr_data);
	}

	addr_data -> address = child_node;
	insert_data_into_list (parent_node -> address_list, addr_data);

	delete_data (&addr_data);

	tree -> node_count++;

	size_t depth = get_tree_node_depth (tree, child_node);

	if (tree -> height < depth) {
		tree -> height = depth;
	}
}

Node* remove_child_node (Tree* tree, Node* parent_node) {
	if (parent_node == NULL) {
		perror ("Parent Node does not Exist to add child node!");
		return NULL;
	}

	if (2 > parent_node -> address_list -> item_count) {
		perror ("Parent has no child nodes to remove!");
		return NULL;
	}

	Data* data = remove_data_from_list (parent_node -> address_list);
	Node* node = data -> address;
	clear_node_address_list (node);

	tree -> node_count--;

	return node;
}

size_t get_tree_node_depth (Tree* tree, Node* node) {
	if (tree == NULL) {
		perror ("Tree does not exist to get depth!");
		return EXIT_FAILURE;
	}

	if (node == NULL) {
		perror ("Node does not exist to get depth!");
		return EXIT_FAILURE;
	}

	if (node -> type != N_Tree) {
		perror ("Given Node doesn't belong to a tree to get depth!");
		return EXIT_FAILURE;
	}

	if (NULL == tree -> root_node) {
		return -1;
	}

	if (node == tree -> root_node) {
		return 0;
	}

	size_t depth = 0;
	Node* child_node = node;
	Node* parent_node = child_node -> address_list -> head_chunk -> first_data_address -> address;

	do {
		if (child_node == tree -> root_node) {
			break;
		}

		child_node = parent_node;
		parent_node = parent_node -> address_list -> head_chunk -> first_data_address -> address;

		++ depth;
	} while (parent_node != NULL);

	child_node = NULL;
	parent_node = NULL;

	return depth;
}

void display_path_towards_root (Tree* tree, Node* node) {
	if (tree == NULL) {
		perror ("Tree does not exist to display path towards Root!");
		return;
	}

	if (node == NULL) {
		perror ("Node does not exist to display path towards Root!");
		return;
	}

	if (node -> type != N_Tree) {
		perror ("Given Node doesn't belong to a tree to display path towards Root!");
		return;
	}

	printf ("Walking towards Root node ... ");

	if (tree -> root_node == node) {
		display_node (node);
		putchar ('\n');
		return;
	}

	ssize_t height = tree -> height;

	while (
		height--
		&& NULL != node
	) {
		display_node (node);
		node = node -> address_list -> head_chunk -> first_data_address -> address;

		if (NULL != node) {
			printf ("->");
		}
	}

	putchar ('\n');
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

	printf ("Children of ");
	display_node (node);
	printf (": [");

	ssize_t address_count = node -> address_list -> item_count;

	for (ssize_t i = 1; i < address_count; i++) {
		Data* data = get_list_data_at_index (node -> address_list, i);
		Node* node = data -> address;
		delete_data (&data);

		display_node (node);

		if (i < address_count - 1) {
			printf (", ");
		}
	}

	printf ("]\n");
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

	size_t address_count = parent_node -> address_list -> item_count;

	if (address_count < n + 1) {	// 0 based index
		perror ("Child index out of bound to get Nth child!");
		return NULL;
	}

	Data* addr_data = get_list_data_at_index (parent_node -> address_list, n + 1);	// 0 based index
	Node* child_node = duplicate_node (addr_data -> address);
	delete_data (&addr_data);

	return child_node;
}

Node* get_first_child_node (Node* parent_node) {
	if (parent_node == NULL) {
		perror ("Given Node doesn't exists");
		return NULL;
	}

	if (parent_node -> type != N_Tree) {
		perror ("Given Node doesn't belong to a tree");
		return NULL;
	}

	size_t address_count = parent_node -> address_list -> item_count;

	if (address_count < 2) {
		perror ("Child does not exist to get first child!");
		return NULL;
	}

	Data* addr_data = get_list_data_at_index (parent_node -> address_list, 1);
	Node* child_node = duplicate_node (addr_data -> address);
	delete_data (&addr_data);

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

	size_t address_count = parent_node -> address_list -> item_count;

	if (address_count < 2) {	// 0 based index
		perror ("Child does not exist to get last child!");
		return NULL;
	}

	Data* addr_data = get_list_data_at_index (parent_node -> address_list, address_count - 1);	// 0 based index
	Node* child_node = duplicate_node (addr_data -> address);
	delete_data (&addr_data);

	return child_node;
}

void display_sub_tree (Tree* tree, Node* node) {
	if (node == NULL) {
		perror ("Node does not Exist to add to sub-tree to delete");
		return;
	}

	if (node -> type != N_Tree) {
		perror ("Node does not belong to a tree to add to sub-tree to delete");
		return;
	}

	size_t depth = get_tree_node_depth (tree, node);

	Tree* sub_tree = create_tree ();
	sub_tree -> root_node = node;
	sub_tree -> height = tree -> height - depth;
	sub_tree -> node_count = count_tree_nodes (sub_tree);

	display_tree (sub_tree);

	sub_tree -> root_node = NULL;
	sub_tree -> node_count = 0;

	delete_tree (&sub_tree);
}

size_t count_tree_nodes (Tree* tree) {
	if (tree == NULL) {
		perror ("Tree does not exist to count nodes");
		exit (EXIT_FAILURE);
	}

	if (tree -> root_node == NULL) {
		perror ("Tree does not have any node to count");
		return 0;
	}

	ssize_t i;
	size_t address_count;
	Node* node;
	Node* x_node;
	Queue* queue = create_queue ();
	Node* queue_node = create_node (N_Queue);
	size_t node_count = 0;

	queue_node -> data = create_address_data (tree -> root_node);
	enqueue (queue, queue_node);

	while (queue -> size > 0) {
		x_node = dequeue (queue);
		node = x_node -> data -> address;
		x_node -> data -> address = NULL;
		delete_node (&x_node);

		address_count = node -> address_list -> item_count;

		if (1 > address_count) {
			continue;
		}

		i = address_count;

		while (--i) {
			Data* data = get_list_data_at_index (node -> address_list, i);
			queue_node -> data -> address = data -> address;
			delete_data (&data);
			enqueue (queue, queue_node);
		}

		++ node_count;
	}

	delete_queue (&queue);
	node = NULL;

	return node_count;
}


/*
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
*/