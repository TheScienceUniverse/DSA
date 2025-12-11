#include "../inc/test.h"

void test_Tree (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Tree]\n" RESET_STYLE);

	Tree* tree = create_Tree ();
	TEST (NULL != tree, "Created tree");

	Node* node = create_Node (N_Tree);
	Node* anchor;

// String* append_integer_to_raw_string (char* str, int number);
	set_Node_name (node, 1, "A");

	int n = 10;
	Data* data = create_Data (DT_Integer, sizeof (int), &n);
	set_Node_Data (node, data);
	delete_Data (&data);

	set_Tree_root_Node (tree, node);
	anchor = tree -> root_node;

	++*(node -> name -> text);
	*((int*)(node -> data -> address)) += 10;
	append_child_Node (tree, anchor, node);

	++*(node -> name -> text);
	*((int*)(node -> data -> address)) += 10;
	append_child_Node (tree, anchor, node);

//	display_node_details (anchor);
	anchor = (anchor -> address_list -> head_chunk -> first_data_address + 1) -> address;
//	display_node_details (anchor);

	++*(node -> name -> text);
	*((int*)(node -> data -> address)) += 10;
	append_child_Node (tree, anchor, node);

	++*(node -> name -> text);
	*((int*)(node -> data -> address)) += 10;
	append_child_Node (tree, anchor, node);

	++*(node -> name -> text);
	*((int*)(node -> data -> address)) += 10;
	append_child_Node (tree, anchor, node);

//	display_list (anchor -> address_list);


	data = get_List_Data_at_index (tree -> root_node -> address_list, 2);
	anchor = data -> address;
	delete_Data (&data);

	++*(node -> name -> text);
	*((int*)(node -> data -> address)) += 10;
	append_child_Node (tree, anchor, node);

	++*(node -> name -> text);
	*((int*)(node -> data -> address)) += 10;
	append_child_Node (tree, anchor, node);


//	display_Node_details (anchor);
//	data = get_List_Data_at_index (anchor -> address_list, 3);
	//anchor = anchor -> address_list -> tail_chunk -> first_data_address -> address;
//	display_Data (data);
//	anchor = data -> address;
	//display_Node_details (anchor);
//	delete_Data (&data);

	display_Tree (tree);

	display_path_towards_root (tree, anchor);

	anchor = (tree -> root_node -> address_list -> head_chunk -> first_data_address + 1 ) -> address;

	display_child_Node_List (anchor);
	
	delete_Node (&node);

	node = get_parent_Node (anchor);
	printf ("Parent Node :=> ");
	display_Node (node);
	putchar ('\n');
	delete_Node (&node);

	node = get_first_child_Node (anchor);
	printf ("First Node :=> ");
	display_Node (node);
	putchar ('\n');
	delete_Node (&node);

	node = get_last_child_Node (anchor);
	printf ("Last Node :=> ");
	display_Node (node);
	putchar ('\n');
	delete_Node (&node);

	node = get_Nth_child_Node (anchor, 1);
	printf ("2nd Node :=> ");
	display_Node (node);
	putchar ('\n');
	delete_Node (&node);

	node = remove_child_Node (tree, anchor);
	printf ("Deleted node: ");
	display_Node (node);
	putchar ('\n');

	printf ("Does node belong to tree? %s\n", (does_Tree_contain_Node (tree, anchor)) ? "Yes" : "No");
	printf ("Does node belong to tree? %s\n", (does_Tree_contain_Node (tree, node)) ? "Yes" : "No");

	delete_Node (&node);

	display_child_Node_List (anchor);

	display_sub_Tree (tree, anchor);

	display_Tree (tree);

	Tree* test_tree = duplicate_Tree (tree);
	display_Tree (test_tree);
	delete_Tree (&test_tree);

	display_Tree (tree);
	delete_Tree (&tree);

	TEST (NULL == tree, "Deleted tree");

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Tree]\n" RESET_STYLE);
}
