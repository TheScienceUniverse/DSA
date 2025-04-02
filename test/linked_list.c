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

	attach_node_at_first (linked_list, node);
	TEST ('A' == *((char*)(linked_list -> head_node -> name -> address + 0)), "Compared inserted node's name (A) with linked-list's head node name");
	TEST (10 == *((int*)(linked_list -> head_node -> data -> address + 0)), "Compared inserted node's data (10) with linked-list's head node data");
	TEST ('A' == *((char*)(linked_list -> head_node -> name -> address + 0)), "Compared inserted node's name (A) with linked-list's tail node name");
	TEST (10 == *((int*)(linked_list -> head_node -> data -> address + 0)), "Compared inserted node's data (10) with linked-list's tail node data");
// A
	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	attach_node_at_last (linked_list, node);
	TEST ('A' == *((char*)(linked_list -> head_node -> name -> address + 0)), "Compared inserted node's name (A) with linked-list's head node name");
	TEST (10 == *((int*)(linked_list -> head_node -> data -> address + 0)), "Compared inserted node's data (10) with linked-list's head node data");
	TEST ('B' == *((char*)(linked_list -> tail_node -> name -> address + 0)), "Compared inserted node's name (B) with linked-list's tail node name");
	TEST (20 == *((int*)(linked_list -> tail_node -> data -> address + 0)), "Compared inserted node's data (20) with linked-list's tail node data");
// A - B
	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	attach_node_at_first (linked_list, node);
	TEST ('C' == *((char*)(linked_list -> head_node -> name -> address + 0)), "Compared inserted node's name (C) with linked-list's head node name");
	TEST (30 == *((int*)(linked_list -> head_node -> data -> address + 0)), "Compared inserted node's data (30) with linked-list's head node data");
	TEST ('B' == *((char*)(linked_list -> tail_node -> name -> address + 0)), "Compared inserted node's name (B) with linked-list's tail node name");
	TEST (20 == *((int*)(linked_list -> tail_node -> data -> address + 0)), "Compared inserted node's data (20) with linked-list's tail node data");
// C - A - B
	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	attach_node_at_last (linked_list, node);
	TEST ('C' == *((char*)(linked_list -> head_node -> name -> address + 0)), "Compared inserted node's name (C) with linked-list's head node name");
	TEST (30 == *((int*)(linked_list -> head_node -> data -> address + 0)), "Compared inserted node's data (30) with linked-list's head node data");
	TEST ('D' == *((char*)(linked_list -> tail_node -> name -> address + 0)), "Compared inserted node's name (D) with linked-list's tail node name");
	TEST (40 == *((int*)(linked_list -> tail_node -> data -> address + 0)), "Compared inserted node's data (40) with linked-list's tail node data");
// C - A - B - D
	Node* del_node = detach_head_from_linked_list (linked_list);
	TEST ('C' == *((char*)(del_node -> name -> address + 0)), "Compared deleted node's name (C) with expected node name");
	TEST (30 == *((int*)(del_node -> data -> address + 0)), "Compared deleted node's data (30) with expected node data");
	TEST ('A' == *((char*)(linked_list -> head_node -> name -> address + 0)), "Compared inserted node's name (A) with linked-list's head node name");
	TEST (10 == *((int*)(linked_list -> head_node -> data -> address + 0)), "Compared inserted node's data (10) with linked-list's head node data");
	TEST ('D' == *((char*)(linked_list -> tail_node -> name -> address + 0)), "Compared inserted node's name (D) with linked-list's tail node name");
	TEST (40 == *((int*)(linked_list -> tail_node -> data -> address + 0)), "Compared inserted node's data (40) with linked-list's tail node data");
	delete_node (&del_node);
// A - B - D
	del_node = detach_tail_from_linked_list (linked_list);
	TEST ('D' == *((char*)(del_node -> name -> address + 0)), "Compared deleted node's name (D) with expected node name");
	TEST (40 == *((int*)(del_node -> data -> address + 0)), "Compared deleted node's data (40) with expected node data");
	TEST ('A' == *((char*)(linked_list -> head_node -> name -> address + 0)), "Compared inserted node's name (A) with linked-list's head node name");
	TEST (10 == *((int*)(linked_list -> head_node -> data -> address + 0)), "Compared inserted node's data (10) with linked-list's head node data");
	TEST ('B' == *((char*)(linked_list -> tail_node -> name -> address + 0)), "Compared inserted node's name (B) with linked-list's tail node name");
	TEST (20 == *((int*)(linked_list -> tail_node -> data -> address + 0)), "Compared inserted node's data (20) with linked-list's tail node data");
	delete_node (&del_node);
// A - B

	delete_node (&node);

	delete_linked_list (&linked_list);
	TEST (NULL == linked_list, "Deleted linked-list successfully");

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Linked-List]\n" RESET_STYLE);
}
