#include "../inc/tree.h"

Tree* create_Tree () {
	Tree* tree = (Tree*) malloc (sizeof (Tree));

	if (tree != NULL) {
		log_memory (DS_Tree, sizeof (Tree), tree, true);

		tree -> root_node = NULL;
		tree -> node_count = 0;
		tree -> breadth = 0;
		tree -> height = 0;
	}

	return tree;
}

void set_Tree_root_Node (Tree* tree, Node* node) {
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

	tree -> root_node = duplicate_Node (node);
	tree -> root_node -> address_list -> head_chunk -> first_data_address -> address = NULL;
	++ tree -> node_count;
}

void print_Node_depth_whitespace (size_t node_depth) {
	display_N_characters (' ', 4);

	if (0 == node_depth) {
		return;
	}

	for (ssize_t i = 0; i < (ssize_t) node_depth; i++) {
		putchar ('|');
		display_N_characters (' ', 4);
	}

	ENDL();
	display_N_characters (' ', 4);

	for (ssize_t i = 0; i < (ssize_t)(node_depth - 1); i++) {
		putchar ('|');
		display_N_characters (' ', 4);
	}

	putchar ('+');
	display_N_characters ('-', 3);
}

void display_Tree (Tree* tree) {
	if (tree == NULL) {
		perror ("Tree does not exist to display");
		return;
	}

	if (tree -> node_count == 0) {
		perror ("Tree does not have any node to display");
		return;
	}

	puts ("Tree :=>");
	printf ("- node count: %zu\n", tree -> node_count);
	printf ("- breadth: %zu\n", tree -> breadth);
	printf ("- height: %zu\n", tree -> height);
	puts ("- structure:");
	display_N_characters ('.', 4 * (tree -> height + 3));
	ENDL();

	ssize_t i;
	size_t address_count, depth = 0;
	Node* node;
	Node* x_node;
	Stack* stack = create_Stack ();
	Node* stack_node = create_Node (N_Stack);
	size_t visited_node_count = 1;

	stack_node -> data = create_address_Data (tree -> root_node);
	push_Node_onto_Stack (stack, stack_node);

	while (
		tree -> node_count >= visited_node_count
		&& stack -> size > 0
	) {
		x_node = pop_Node_from_Stack (stack);
		node = x_node -> data -> address;
		x_node -> data -> address = NULL;
		delete_Node (&x_node);

		depth = get_Tree_Node_depth (tree, node);
		print_Node_depth_whitespace (depth);
		display_Node (node);
		printf ("\n");

		address_count = node -> address_list -> item_count;

		if (1 > address_count) {
			continue;
		}

		i = address_count;

		while (--i) {	// storing backwards to pick up in proper order
			Data* data = get_List_Data_at_index (node -> address_list, i);
			stack_node -> data -> address = data -> address;
			delete_Data (&data);
			push_Node_onto_Stack (stack, stack_node);
		}

		++ visited_node_count;
	}

	delete_Node (&stack_node);

	node = NULL;
	delete_Stack (&stack);

	display_N_characters ('.', 4 * (tree -> height + 3));
	ENDL();
}

void delete_Tree (Tree** tree_address) {
	if (*tree_address == NULL) {
		// perror ("Tree does not exists to delete!");
		return;
	}

	if ((*tree_address) -> node_count == 0) {
		log_memory (DS_Tree, sizeof (Tree), *tree_address, false);
		ERASE (tree_address, sizeof (Tree));
		return;
	}

	Tree* tree = *tree_address;
	ssize_t i;
	size_t address_count;
	Node* t_node;
	Node* x_node;
	Stack* stack = create_Stack ();
	Node* stack_node = create_Node (N_Stack);
	size_t visited_node_count = 1;

	stack_node -> data = create_address_Data (tree -> root_node);
	push_Node_onto_Stack (stack, stack_node);

	while (
		tree -> node_count >= visited_node_count
		&& stack -> size > 0
	) {
		x_node = pop_Node_from_Stack (stack);
		t_node = x_node -> data -> address;
		x_node -> data -> address = NULL;
		delete_Node (&x_node);

		address_count = t_node -> address_list -> item_count;

		if (1 > address_count) {
			clear_Node_address_list (t_node);
			delete_Node (&t_node);
			continue;
		}

		i = address_count;

		while (--i) {	// storing backwards to pick up in proper order
			Data* data = get_List_Data_at_index (t_node -> address_list, i);
			stack_node -> data -> address = data -> address;
			delete_Data (&data);
			push_Node_onto_Stack (stack, stack_node);
		}

		clear_Node_address_list (t_node);
		delete_Node (&t_node);

		++ visited_node_count;
	}

	delete_Node (&stack_node);

	t_node = NULL;
	delete_Stack (&stack);

	log_memory (DS_Tree, sizeof (Tree), *tree_address, false);
	ERASE (tree_address, sizeof (Tree));
}











void append_child_Node (Tree* tree, Node* parent_node, Node* child_node) {
	if (NULL == tree) {
		perror ("Tree does not Exist to add child node to parent!");
		return;
	}

	if (parent_node == NULL) {
		perror ("Parent Node does not Exist to add child node!");
		return;
	}

	if (child_node == NULL) {
		perror ("Child Node does not Exist to add child node!");
		return;
	}

	child_node = duplicate_Node (child_node);
	clear_Node_address_list (child_node);	// address sanity

	Data* addr_data = create_address_Data (parent_node);
	insert_Data_into_List (child_node -> address_list, addr_data);

	size_t address_count = parent_node -> address_list -> item_count;

	if (0 == address_count) {
		addr_data -> address = NULL;
		insert_Data_into_List (parent_node -> address_list, addr_data);
	}

	addr_data -> address = child_node;
	insert_Data_into_List (parent_node -> address_list, addr_data);

	delete_Data (&addr_data);

	tree -> node_count++;

	size_t depth = get_Tree_Node_depth (tree, child_node);

	if (tree -> height < depth) {
		tree -> height = depth;
	}
}

void append_sibling_Node (Tree* tree, Node* node, Node* sibling_node) {
	if (NULL == tree) {
		perror ("Tree does not Exist to add child node to parent!");
		return;
	}

	if (node == NULL) {
		perror ("Parent Node does not Exist to add child node!");
		return;
	}

	if (sibling_node == NULL) {
		perror ("Child Node does not Exist to add child node!");
		return;
	}

	// get parent node
	Node* parent_node = node -> address_list -> head_chunk -> first_data_address -> address;

	append_child_Node (tree, parent_node, sibling_node);
}

Node* remove_child_Node (Tree* tree, Node* parent_node) {
	if (parent_node == NULL) {
		perror ("Parent Node does not Exist to add child node!");
		return NULL;
	}

	if (2 > parent_node -> address_list -> item_count) {
		perror ("Parent has no child nodes to remove!");
		return NULL;
	}

	Data* data = remove_Data_from_List (parent_node -> address_list);
	Node* node = data -> address;
	clear_Node_address_list (node);
	delete_Data (&data);

	tree -> node_count--;

	return node;
}

size_t get_Tree_Node_depth (Tree* tree, Node* node) {
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
		display_Node (node);
		putchar ('\n');
		return;
	}

	ssize_t height = tree -> height;

	while (
		height--
		&& NULL != node
	) {
		display_Node (node);
		node = node -> address_list -> head_chunk -> first_data_address -> address;

		if (NULL != node) {
			printf ("->");
		}
	}

	putchar ('\n');
}

void display_child_Node_List (Node* node) {
	if (node == NULL) {
		perror ("Node does not exist to display Root!");
		return;
	}

	if (node -> type != N_Tree) {
		perror ("Given Node doesn't belong to a tree");
		return;
	}

	printf ("Children of ");
	display_Node (node);
	printf (": [");

	ssize_t address_count = node -> address_list -> item_count;

	for (ssize_t i = 1; i < address_count; i++) {
		Data* data = get_List_Data_at_index (node -> address_list, i);
		Node* node = data -> address;
		delete_Data (&data);

		display_Node (node);

		if (i < address_count - 1) {
			printf (", ");
		}
	}

	printf ("]\n");
}

Node* get_parent_Node (Node* child_node) {
	if (NULL == child_node) {
		perror ("Given Node doesn't exists");
		return NULL;
	}

	if (child_node -> type != N_Tree) {
		perror ("Given Node doesn't belong to a tree");
		return NULL;
	}

	Data* addr_data = get_List_Data_at_index (child_node -> address_list, 0);
	Node* parent_node = duplicate_Node (addr_data -> address);
	clear_Node_address_list (parent_node);
	delete_Data (&addr_data);

	return parent_node;
}

Node* get_Nth_child_Node (Node* parent_node, size_t n) {
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

	Data* addr_data = get_List_Data_at_index (parent_node -> address_list, n + 1);	// 0 based index
	Node* child_node = duplicate_Node (addr_data -> address);
	clear_Node_address_list (child_node);
	delete_Data (&addr_data);

	return child_node;
}

Node* get_first_child_Node (Node* parent_node) {
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

	Data* addr_data = get_List_Data_at_index (parent_node -> address_list, 1);
	Node* child_node = duplicate_Node (addr_data -> address);
	clear_Node_address_list (child_node);
	delete_Data (&addr_data);

	return child_node;
}

Node* get_last_child_Node (Node* parent_node) {
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

	Data* addr_data = get_List_Data_at_index (parent_node -> address_list, address_count - 1);	// 0 based index
	Node* child_node = duplicate_Node (addr_data -> address);
	clear_Node_address_list (child_node);
	delete_Data (&addr_data);

	return child_node;
}

void display_sub_Tree (Tree* tree, Node* node) {
	if (node == NULL) {
		perror ("Node does not Exist to add to sub-tree to delete");
		return;
	}

	if (node -> type != N_Tree) {
		perror ("Node does not belong to a tree to add to sub-tree to delete");
		return;
	}

	size_t depth = get_Tree_Node_depth (tree, node);

	Tree* sub_tree = create_Tree ();
	sub_tree -> root_node = node;
	sub_tree -> height = tree -> height - depth;
	sub_tree -> node_count = count_Tree_Nodes (sub_tree);

	display_Tree (sub_tree);

	sub_tree -> root_node = NULL;
	sub_tree -> node_count = 0;

	delete_Tree (&sub_tree);
}

size_t count_Tree_Nodes (Tree* tree) {
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
	Queue* queue = create_Queue ();
	Node* queue_node = create_Node (N_Queue);
	size_t node_count = 0;

	queue_node -> data = create_address_Data (tree -> root_node);
	enQueue (queue, queue_node);

	while (queue -> size > 0) {
		x_node = deQueue (queue);
		node = x_node -> data -> address;
		x_node -> data -> address = NULL;
		delete_Node (&x_node);

		address_count = node -> address_list -> item_count;

		if (1 > address_count) {
			continue;
		}

		i = address_count;

		while (--i) {
			Data* data = get_List_Data_at_index (node -> address_list, i);
			queue_node -> data -> address = data -> address;
			delete_Data (&data);
			enQueue (queue, queue_node);
		}

		++ node_count;
	}

	delete_Queue (&queue);
	delete_Node (&queue_node);
	node = NULL;

	return node_count;
}

bool does_Tree_contain_Node (Tree* tree, Node* node) {
	if (NULL == tree) {
		perror ("Tree does not exist to find node");
		exit (EXIT_FAILURE);
	}

	if (NULL == node) {
		perror ("Node does not exist to find in tree");
		exit (EXIT_FAILURE);
	}

	if (NULL == tree -> root_node) {
		perror ("Tree does not have any node to find given node");
		return false;
	}

	bool decision = false;
	ssize_t i;
	size_t address_count;
	Node* t_node;
	Node* x_node;
	Queue* queue = create_Queue ();
	Node* queue_node = create_Node (N_Queue);
	size_t node_count = 0;

	queue_node -> data = create_address_Data (tree -> root_node);
	enQueue (queue, queue_node);

	while (queue -> size > 0) {
		x_node = deQueue (queue);
		t_node = x_node -> data -> address;
		x_node -> data -> address = NULL;
		delete_Node (&x_node);

		if (node == t_node) {
			decision = true;
			break;
		}

		address_count = t_node -> address_list -> item_count;

		if (1 > address_count) {
			continue;
		}

		i = address_count;

		while (--i) {
			Data* data = get_List_Data_at_index (t_node -> address_list, i);
			queue_node -> data -> address = data -> address;
			delete_Data (&data);
			enQueue (queue, queue_node);
		}

		++ node_count;
	}

	delete_Queue (&queue);
	delete_Node (&queue_node);
	t_node = NULL;

	return decision;
}

Tree* duplicate_Tree (Tree* tree) {
	if (tree == NULL) {
		perror ("Tree does not exist to display");
		exit (EXIT_FAILURE);
	}

	Tree* new_tree = create_Tree ();
	new_tree -> node_count = tree -> node_count;
	new_tree -> breadth = tree -> breadth;
	new_tree -> height = tree -> height;

	if (tree -> node_count == 0) {
		return new_tree;
	}

	size_t visited_node_count = 0;
	size_t address_count;
	Node* anchor;

	Node* t_node;	// tree-node
	Node* x_node;	// to be deleted node
	Queue* queue = create_Queue ();
	Node* queue_node = create_Node (N_Queue);
	Node* child_node;

	new_tree -> root_node = duplicate_Node (tree -> root_node);
	anchor = new_tree -> root_node;

	queue_node -> data = create_address_Data (anchor);
	enQueue (queue, queue_node);

	while (
		queue -> size > 0
		&& visited_node_count++ < tree -> node_count
	) {
		x_node = deQueue (queue);	// a queue node
		t_node = x_node -> data -> address;
		x_node -> data -> address = NULL;
		delete_Node (&x_node);

		address_count = t_node -> address_list -> item_count;

		if (1 > address_count) {
			continue;
		}

		for (ssize_t i = 1; i < (ssize_t) address_count; i++) {
			Data* addr_data = get_List_Data_at_index (t_node -> address_list, i);

			child_node = addr_data -> address;
			child_node = duplicate_Node (child_node);

			(child_node -> address_list -> head_chunk -> first_data_address + 0) -> address = t_node;	// parent node

			addr_data -> address = child_node;
			put_List_Data_at_index (t_node -> address_list, addr_data, i);

			queue_node -> data -> address = addr_data -> address;
			delete_Data (&addr_data);
			enQueue (queue, queue_node);
		}
	}

	clear_Node_address_list (queue_node);
	delete_Node (&queue_node);
	delete_Queue (&queue);

	t_node = NULL;
	x_node = NULL;

	return new_tree;
}

Node* get_last_child_Node_address (Node* parent_node) {
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

	Data* addr_data = get_List_Data_at_index (parent_node -> address_list, address_count - 1);	// 0 based index
	Node* child_node = addr_data -> address;
	delete_Data (&addr_data);

	return child_node;
}

Node* get_parent_Node_address (Node* child_node) {
	if (NULL == child_node) {
		perror ("Given Node doesn't exists");
		return NULL;
	}

	if (child_node -> type != N_Tree) {
		perror ("Given Node doesn't belong to a tree");
		return NULL;
	}

	Data* addr_data = get_List_Data_at_index (child_node -> address_list, 0);
	Node* parent_node = addr_data -> address;
	delete_Data (&addr_data);

	return parent_node;
}