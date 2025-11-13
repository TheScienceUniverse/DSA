#include "../inc/test.h"

void test_Queue (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Queue]\n" RESET_STYLE);

	Queue* queue = create_Queue ();

	TEST (NULL != queue, "Created Queue exists");

	Node* node = create_Node (N_Queue);
	set_Node_name (node, 1, "A");

	int n = 10;
	Data* data = create_Data (DT_Integer, sizeof (int), &n);
	set_Node_Data (node, data);
	delete_Data (&data);

	enQueue (queue, node);
	TEST ('A' == *((char*)(queue -> front_node -> name -> text + 0)), "Compared enqueued node's name (A) with queue's front node name");
	TEST (10 == *((int*)(queue -> front_node -> data -> address + 0)), "Compared enqueued node's data (10) with queue's front node data");
	TEST ('A' == *((char*)(queue -> rear_node -> name -> text + 0)), "Compared enqueued node's name (A) with queue's rear node name");
	TEST (10 == *((int*)(queue -> rear_node -> data -> address + 0)), "Compared enqueued node's data (10) with queue's rear node data");

	++*(node -> name -> text);
	*((int*)(node -> data -> address)) += 10;
	enQueue (queue, node);
	TEST ('A' == *((char*)(queue -> front_node -> name -> text + 0)), "Compared enqueued node's name (A) with queue's front node name");
	TEST (10 == *((int*)(queue -> front_node -> data -> address + 0)), "Compared enqueued node's data (10) with queue's front node data");
	TEST ('B' == *((char*)(queue -> rear_node -> name -> text + 0)), "Compared enqueued node's name (B) with queue's rear node name");
	TEST (20 == *((int*)(queue -> rear_node -> data -> address + 0)), "Compared enqueued node's data (20) with queue's rear node data");

	++*(node -> name -> text);
	*((int*)(node -> data -> address)) += 10;
	enQueue (queue, node);
	TEST ('A' == *((char*)(queue -> front_node -> name -> text + 0)), "Compared enqueued node's name (A) with queue's front node name");
	TEST (10 == *((int*)(queue -> front_node -> data -> address + 0)), "Compared enqueued node's data (10) with queue's front node data");
	TEST ('C' == *((char*)(queue -> rear_node -> name -> text + 0)), "Compared enqueued node's name (C) with queue's rear node name");
	TEST (30 == *((int*)(queue -> rear_node -> data -> address + 0)), "Compared enqueued node's data (30) with queue's rear node data");

	Node* del_node = deQueue (queue);
	TEST ('A' == *((char*)(del_node -> name -> text + 0)), "Compared served node's name (A) with dequeued node name");
	TEST (10 == *((int*)(del_node -> data -> address + 0)), "Compared served node's data (10) with dequeued node data");
	TEST ('B' == *((char*)(queue -> front_node -> name -> text + 0)), "Compared expected node's name (B) with queue's front node name");
	TEST (20 == *((int*)(queue -> front_node -> data -> address + 0)), "Compared expected node's data (20) with queue's front node data");
	TEST ('C' == *((char*)(queue -> rear_node -> name -> text + 0)), "Compared expected node's name (C) with queue's rear node name");
	TEST (30 == *((int*)(queue -> rear_node -> data -> address + 0)), "Compared expected node's data (30) with queue's rear node data");
	delete_Node (&del_node);

	++*(node -> name -> text);
	*((int*)(node -> data -> address)) += 10;
	enQueue (queue, node);
	TEST ('B' == *((char*)(queue -> front_node -> name -> text + 0)), "Compared expected node's name (B) with queue's front node name");
	TEST (20 == *((int*)(queue -> front_node -> data -> address + 0)), "Compared expected node's data (20) with queue's front node data");
	TEST ('D' == *((char*)(queue -> rear_node -> name -> text + 0)), "Compared expected node's name (D) with queue's rear node name");
	TEST (40 == *((int*)(queue -> rear_node -> data -> address + 0)), "Compared expected node's data (40) with queue's rear node data");

	del_node = deQueue (queue);
	TEST ('B' == *((char*)(del_node -> name -> text + 0)), "Compared served node's name (B) with dequeued node name");
	TEST (20 == *((int*)(del_node -> data -> address + 0)), "Compared served node's data (20) with dequeued node data");
	TEST ('C' == *((char*)(queue -> front_node -> name -> text + 0)), "Compared expected node's name (C) with queue's front node name");
	TEST (30 == *((int*)(queue -> front_node -> data -> address + 0)), "Compared expected node's data (30) with queue's front node data");
	TEST ('D' == *((char*)(queue -> rear_node -> name -> text + 0)), "Compared expected node's name (D) with queue's rear node name");
	TEST (40 == *((int*)(queue -> rear_node -> data -> address + 0)), "Compared expected node's data (40) with queue's rear node data");
	delete_Node (&del_node);

	del_node = deQueue (queue);
	TEST ('C' == *((char*)(del_node -> name -> text + 0)), "Compared served node's name (C) with dequeued node name");
	TEST (30 == *((int*)(del_node -> data -> address + 0)), "Compared served node's data (30) with dequeued node data");
	TEST ('D' == *((char*)(queue -> front_node -> name -> text + 0)), "Compared expected node's name (D) with queue's front node name");
	TEST (40 == *((int*)(queue -> front_node -> data -> address + 0)), "Compared expected node's data (40) with queue's front node data");
	TEST ('D' == *((char*)(queue -> rear_node -> name -> text + 0)), "Compared expected node's name (D) with queue's rear node name");
	TEST (40 == *((int*)(queue -> rear_node -> data -> address + 0)), "Compared expected node's data (40) with queue's rear node data");
	delete_Node (&del_node);

	del_node = deQueue (queue);
	TEST ('D' == *((char*)(del_node -> name -> text + 0)), "Compared served node's name (D) with dequeued node name");
	TEST (40 == *((int*)(del_node -> data -> address + 0)), "Compared served node's data (40) with dequeued node data");
	delete_Node (&del_node);

	del_node = deQueue (queue);
	TEST (0 == queue -> size, "Compared queue's expected size emptiness");
	TEST (NULL == del_node, "Compared dequeued node does not exist");
	if (NULL == del_node) {delete_Node (&del_node);}

	display_Queue (queue);

	delete_Node (&node);

	delete_Queue (&queue);
	TEST (NULL == queue, "Deleted queue successfully");

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Queue]\n" RESET_STYLE);
}
