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
	peek_data_from_stack (stack);

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	push_node_onto_stack (stack, node);
	peek_data_from_stack (stack);

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
	peek_data_from_stack (stack);

	del_node = pop_node_from_stack (stack);
	printf ("Popped Node :=> ");
	display_node (del_node);
	printf ("\n");
	delete_node (&del_node);
	display_stack_details (stack);
	peek_data_from_stack (stack);

	del_node = pop_node_from_stack (stack);
	printf ("Popped Node :=> ");
	display_node (del_node);
	printf ("\n");
	delete_node (&del_node);

	delete_node (&node);

	delete_stack (&stack);

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Stack]\n" RESET_STYLE);
}
