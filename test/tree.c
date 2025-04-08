#include "../include/test.h"

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

	delete_node (&node);

	delete_tree (&tree);
	TEST (NULL == tree, "Deleted tree");

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Tree]\n" RESET_STYLE);
}
