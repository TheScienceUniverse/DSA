#include "../inc/test.h"

void test_Node (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Node]\n" RESET_STYLE);

	Node* node = create_Node (N_Undefined);

	TEST (NULL != node, "Created node exists");

	char* name_str = "ABC";
	String* name = create_String (3, name_str);
	set_Node_name (node, 3, name_str);
	TEST (Cmp_Different != compare_Strings (name, node -> name), "Matched node-name with set name");
	delete_String (&name);

	uint16_t x = 0x0ff0;
	Data* data = create_Data (DT_Binary, sizeof (uint16_t), &x);
	set_Node_Data (node, data);
	TEST (Cmp_Equivalent == compare_Data (data, node -> data), "Compared node data with set data");
	delete_Data (&data);

	// display_node_details (node);

	Node* test_node = duplicate_Node (node);

	TEST (NULL != test_node, "Created duplicate node exists");

	// display_node_details (test_node);

	TEST (Cmp_Equivalent == compare_Nodes (node, test_node), "Compared duplicated node with original");

	delete_Node (&test_node);
	delete_Node (&node);

	TEST (NULL == node, "Deleted node successfully");

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Node]\n" RESET_STYLE);
}
