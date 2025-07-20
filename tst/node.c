#include "../inc/test.h"

void test_node (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Node]\n" RESET_STYLE);

	Node* node = create_node (N_Undefined);

	TEST (NULL != node, "Created node exists");

	char* name_str = "ABC";
	String* name = create_string (3, name_str);
	set_node_name (node, 3, name_str);
	TEST (Cmp_Different != compare_strings (name, node -> name), "Matched node-name with set name");
	delete_string (&name);

	uint16_t x = 0x0ff0;
	Data* data = create_data (DT_Binary, sizeof (uint16_t), &x);
	set_node_data (node, data);
	TEST (Cmp_Equivalent == compare_data (data, node -> data), "Compared node data with set data");
	delete_data (&data);

	// display_node_details (node);

	Node* test_node = duplicate_node (node);

	TEST (NULL != node, "Created duplicate node exists");

	// display_node_details (test_node);

	TEST (Cmp_Equivalent == compare_nodes (node, test_node), "Compared duplicated node with original");

	delete_node (&node);

	TEST (NULL == node, "Deleted node successfully");

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Node]\n" RESET_STYLE);
}
