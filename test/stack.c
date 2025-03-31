#include "../include/test.h"

void test_stack (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Stack]\n" RESET_STYLE);

	Stack* stack = create_stack ();

	TEST (NULL != stack, "Created Stack exists");

	Node* node = create_node (N_Stack);
	set_node_name (node, 1, "A");

	int n = 10;
	Data* data = create_data (DT_Integer, sizeof (int), &n);
	set_node_data (node, data);

	push_node_onto_stack (stack, node);

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	push_node_onto_stack (stack, node);

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	push_node_onto_stack (stack, node);

	display_stack (stack);
	display_stack_details (stack);

	Node* del_node = pop_node_from_stack (stack);
	printf ("Popped Node :=> ");
	display_node (del_node);
	printf ("\n");
	delete_node (&del_node);
	display_stack_details (stack);

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	push_node_onto_stack (stack, node);
	display_stack_details (stack);

	del_node = pop_node_from_stack (stack);
	printf ("Popped Node :=> ");
	display_node (del_node);
	printf ("\n");
	delete_node (&del_node);
	display_stack_details (stack);

	del_node = pop_node_from_stack (stack);
	printf ("Popped Node :=> ");
	display_node (del_node);
	printf ("\n");
	delete_node (&del_node);
	display_stack_details (stack);

	del_node = pop_node_from_stack (stack);
	printf ("Popped Node :=> ");
	display_node (del_node);
	printf ("\n");
	delete_node (&del_node);
	display_stack_details (stack);

	del_node = pop_node_from_stack (stack);
	printf ("Popped Node :=> ");
	display_node (del_node);
	printf ("\n");
	delete_node (&del_node);


	/*

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

*/
	delete_node (&node);

	delete_stack (&stack);

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Stack]\n" RESET_STYLE);
}
