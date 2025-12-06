#include "../inc/test.h"

void test_Stack (void) {
	display_unit_test_message ("Stack", true);

	Stack* stack = create_Stack ();

	TEST (NULL != stack, "Created Stack exists");

	Node* node = create_Node (N_Stack);
	set_Node_name (node, 1, "A");

	int n = 10;
	Data* data = create_Data (DT_Integer, sizeof (int), &n);
	set_Node_Data (node, data);
	delete_Data (&data);

	push_Node_onto_Stack (stack, node);

	TEST (1 == stack -> size, "Stack size increased");
	TEST (Cmp_Equivalent == compare_Nodes (node, stack -> top_node), "Compared pushed node with stack's top node");

	++*(node -> name -> text);
	*((int*)(node -> data -> address)) += 10;
	push_Node_onto_Stack (stack, node);

	TEST ('B' == *((char*)(stack -> top_node -> name -> text + 0)), "Compared pushed node's name (B) with stack's top node name");
	TEST (20 == *((int*)(stack -> top_node -> data -> address + 0)), "Compared pushed node's data (20) with stack's top node data");

	++*(node -> name -> text);
	*((int*)(node -> data -> address)) += 10;
	push_Node_onto_Stack (stack, node);

	TEST ('C' == *((char*)(stack -> top_node -> name -> text + 0)), "Compared pushed node's name (C) with stack's top node name");
	TEST (30 == *((int*)(stack -> top_node -> data -> address + 0)), "Compared pushed node's data (30) with stack's top node data");

	Node* del_node = pop_Node_from_Stack (stack);
	TEST ('C' == *((char*)(del_node -> name -> text + 0)), "Compared popped node's name (C) with expected node name");
	TEST (30 == *((int*)(del_node -> data -> address + 0)), "Compared popped node's data (30) with expected node data");
	delete_Node (&del_node);

	++*(node -> name -> text);
	*((int*)(node -> data -> address)) += 10;
	push_Node_onto_Stack (stack, node);
	TEST ('D' == *((char*)(stack -> top_node -> name -> text + 0)), "Compared pushed node's name (D) with stack's top node name");
	TEST (40 == *((int*)(stack -> top_node -> data -> address + 0)), "Compared pushed node's data (40) with stack's top node data");

	del_node = pop_Node_from_Stack (stack);
	TEST ('D' == *((char*)(del_node -> name -> text + 0)), "Compared popped node's name (D) with expected node name");
	TEST (40 == *((int*)(del_node -> data -> address + 0)), "Compared popped node's data (40) with expected node data");
	delete_Node (&del_node);

	del_node = pop_Node_from_Stack (stack);
	TEST ('B' == *((char*)(del_node -> name -> text + 0)), "Compared popped node's name (B) with expected node name");
	TEST (20 == *((int*)(del_node -> data -> address + 0)), "Compared popped node's data (20) with expected node data");
	delete_Node (&del_node);

	del_node = pop_Node_from_Stack (stack);
	TEST ('A' == *((char*)(del_node -> name -> text + 0)), "Compared popped node's name (A) with expected node name");
	TEST (10 == *((int*)(del_node -> data -> address + 0)), "Compared popped node's data (10) with expected node data");
	delete_Node (&del_node);

	data = create_Data (DT_Integer, sizeof (int), &n);

	*((int*)(data -> address)) = -10;
	push_Data_onto_Stack (stack, data);
	TEST (-10 == *((int*)(stack -> top_node -> data -> address)), "Compared pushed data (-10) with stack's top node data");

	*((int*)(data -> address)) = -20;
	push_Data_onto_Stack (stack, data);
	TEST (-20 == *((int*)(stack -> top_node -> data -> address)), "Compared pushed data (-20) with stack's top node data");

	delete_Data (&data);

	data = pop_Data_from_Stack (stack);
	TEST (-20 == *((int*)(data -> address)), "Compared popped data (-20) with expected data");
	delete_Data (&data);

	data = pop_Data_from_Stack (stack);
	TEST (-10 == *((int*)(data -> address)), "Compared popped data (-20) with expected data");
	delete_Data (&data);

	del_node = pop_Node_from_Stack (stack);
	TEST (0 == stack -> size, "Compared stack's expected size emptiness");
	TEST (NULL == del_node, "Compared popped node does not exist");
	if (NULL == del_node) {delete_Node (&del_node);}

	delete_Node (&node);

	delete_Stack (&stack);
	TEST (NULL == stack, "Deleted stack successfully");

	display_unit_test_message ("Stack", false);
}
