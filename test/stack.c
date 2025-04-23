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
	delete_data (&data);

	push_node_onto_stack (stack, node);

	TEST (1 == stack -> size, "Stack size increased");
	TEST (Cmp_Equivalent == compare_nodes (node, stack -> top_node), "Compared pushed node with stack's top node");

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	push_node_onto_stack (stack, node);

	TEST ('B' == *((char*)(stack -> top_node -> name -> address + 0)), "Compared pushed node's name (B) with stack's top node name");
	TEST (20 == *((int*)(stack -> top_node -> data -> address + 0)), "Compared pushed node's data (20) with stack's top node data");

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	push_node_onto_stack (stack, node);

	TEST ('C' == *((char*)(stack -> top_node -> name -> address + 0)), "Compared pushed node's name (C) with stack's top node name");
	TEST (30 == *((int*)(stack -> top_node -> data -> address + 0)), "Compared pushed node's data (30) with stack's top node data");

	Node* del_node = pop_node_from_stack (stack);
	TEST ('C' == *((char*)(del_node -> name -> address + 0)), "Compared popped node's name (C) with expected node name");
	TEST (30 == *((int*)(del_node -> data -> address + 0)), "Compared popped node's data (30) with expected node data");
	delete_node (&del_node);

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	push_node_onto_stack (stack, node);
	TEST ('D' == *((char*)(stack -> top_node -> name -> address + 0)), "Compared pushed node's name (D) with stack's top node name");
	TEST (40 == *((int*)(stack -> top_node -> data -> address + 0)), "Compared pushed node's data (40) with stack's top node data");

	del_node = pop_node_from_stack (stack);
	TEST ('D' == *((char*)(del_node -> name -> address + 0)), "Compared popped node's name (D) with expected node name");
	TEST (40 == *((int*)(del_node -> data -> address + 0)), "Compared popped node's data (40) with expected node data");
	delete_node (&del_node);

	del_node = pop_node_from_stack (stack);
	TEST ('B' == *((char*)(del_node -> name -> address + 0)), "Compared popped node's name (B) with expected node name");
	TEST (20 == *((int*)(del_node -> data -> address + 0)), "Compared popped node's data (20) with expected node data");
	delete_node (&del_node);

	del_node = pop_node_from_stack (stack);
	TEST ('A' == *((char*)(del_node -> name -> address + 0)), "Compared popped node's name (A) with expected node name");
	TEST (10 == *((int*)(del_node -> data -> address + 0)), "Compared popped node's data (10) with expected node data");
	delete_node (&del_node);

	data = create_data (DT_Integer, sizeof (int), &n);

	*((int*)(data -> address)) = -10;
	push_data_onto_stack (stack, data);
	TEST (-10 == *((int*)(stack -> top_node -> data -> address)), "Compared pushed data (-10) with stack's top node data");

	*((int*)(data -> address)) = -20;
	push_data_onto_stack (stack, data);
	TEST (-20 == *((int*)(stack -> top_node -> data -> address)), "Compared pushed data (-20) with stack's top node data");

	delete_data (&data);

	data = pop_data_from_stack (stack);
	TEST (-20 == *((int*)(data -> address)), "Compared popped data (-20) with expected data");
	delete_data (&data);

	data = pop_data_from_stack (stack);
	TEST (-10 == *((int*)(data -> address)), "Compared popped data (-20) with expected data");
	delete_data (&data);

	del_node = pop_node_from_stack (stack);
	TEST (0 == stack -> size, "Compared stack's expected size emptiness");
	TEST (NULL == del_node, "Compared popped node does not exist");
	if (NULL == del_node) {delete_node (&del_node);}

	delete_node (&node);

	delete_stack (&stack);
	TEST (NULL == stack, "Deleted stack successfully");

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Stack]\n" RESET_STYLE);
}
