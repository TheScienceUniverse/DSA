#include "../include/test.h"

void test_linked_list (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Linked-List]\n" RESET_STYLE);

	Linked_List* linked_list = create_linked_list ();

	TEST (NULL != linked_list, "Created linked list exists");

	Node* node = create_node (N_LinkedList);
	set_node_name (node, 1, "A");

	int n = 10;
	Data* data = create_data (DT_Integer, sizeof (int), &n);
	set_node_data (node, data);

	attach_node_at_last (linked_list, node);

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	attach_node_at_last (linked_list, node);

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	attach_node_at_last (linked_list, node);

	display_linked_list (linked_list);
	display_linked_list_details (linked_list);


	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	attach_node_at_first (linked_list, node);

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	attach_node_at_first (linked_list, node);

	display_linked_list (linked_list);
	display_linked_list_details (linked_list);

	Node* del_node = detach_head_from_linked_list (linked_list);
	printf ("Detached ");
	display_node_details (del_node);
	delete_node (&del_node);
	display_linked_list (linked_list);
	display_linked_list_details (linked_list);

	del_node = detach_tail_from_linked_list (linked_list);
	printf ("Detached ");
	display_node_details (del_node);
	delete_node (&del_node);
	display_linked_list (linked_list);
	display_linked_list_details (linked_list);


	delete_node (&node);

	delete_linked_list (&linked_list);

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Linked-List]\n" RESET_STYLE);
}
