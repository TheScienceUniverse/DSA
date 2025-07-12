#include "../inc/test.h"

void test_tree (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Tree]\n" RESET_STYLE);

	Tree* tree = create_tree ();
	TEST (NULL != tree, "Created tree");

	Node* node = create_node (N_Tree);
	Node* anchor;

// String* append_integer_to_raw_string (char* str, int number);
	set_node_name (node, 1, "A");

	int n = 10;
	Data* data = create_data (DT_Integer, sizeof (int), &n);
	set_node_data (node, data);

	delete_data (&data);

	set_tree_root_node (tree, node);
	anchor = tree -> root_node;

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	append_child_node (tree, anchor, node);

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	append_child_node (tree, anchor, node);

//	display_node_details (anchor);
	anchor = (anchor -> address_list -> head_chunk -> first_data_address + 1) -> address;
//	display_node_details (anchor);

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	append_child_node (tree, anchor, node);

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	append_child_node (tree, anchor, node);

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	append_child_node (tree, anchor, node);

//	display_list (anchor -> address_list);


	data = get_list_data_at_index (tree -> root_node -> address_list, 2);
	anchor = data -> address;

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	append_child_node (tree, anchor, node);

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	append_child_node (tree, anchor, node);


//	display_node_details (anchor);
//	data = get_list_data_at_index (anchor -> address_list, 3);
	//anchor = anchor -> address_list -> tail_chunk -> first_data_address -> address;
//	display_data (data);
//	anchor = data -> address;
	//display_node_details (anchor);
//	delete_data (&data);

	display_tree (tree);

	display_path_towards_root (tree, anchor);

	anchor = (tree -> root_node -> address_list -> head_chunk -> first_data_address + 1 ) -> address;

	display_child_node_list (anchor);
	
	delete_node (&node);

	node = get_first_child_node (anchor);
	printf ("First Node :=> ");
	display_node (node);
	putchar ('\n');
	delete_node (&node);

	node = get_last_child_node (anchor);
	printf ("Last Node :=> ");
	display_node (node);
	putchar ('\n');
	delete_node (&node);

	node = get_Nth_child_node (anchor, 1);
	printf ("2nd Node :=> ");
	display_node (node);
	putchar ('\n');
	delete_node (&node);

	node = remove_child_node (tree, anchor);
	printf ("Deleted node: ");
	display_node (node);
	putchar ('\n');

	printf ("Is node belong to tree? %s\n", (does_tree_contain_node (tree, anchor)) ? "Yes" : "No");
	printf ("Is node belong to tree? %s\n", (does_tree_contain_node (tree, node)) ? "Yes" : "No");

	delete_node (&node);

	display_child_node_list (anchor);

	display_sub_tree (tree, anchor);

	display_tree (tree);

	Tree* test_tree = duplicate_tree (tree);
	display_tree (test_tree);
	delete_tree (&test_tree);

	delete_tree (&tree);

	TEST (NULL == tree, "Deleted tree");

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Tree]\n" RESET_STYLE);
}
