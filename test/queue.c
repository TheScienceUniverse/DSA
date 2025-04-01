#include "../include/test.h"

void test_queue (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Queue]\n" RESET_STYLE);

	Queue* queue = create_queue ();

	TEST (NULL != queue, "Created Queue exists");

	Node* node = create_node (N_Queue);
	set_node_name (node, 1, "A");

	int n = 10;
	Data* data = create_data (DT_Integer, sizeof (int), &n);
	set_node_data (node, data);

	enqueue (queue, node);
	peek_data_from_queue (queue);

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	enqueue (queue, node);

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	enqueue (queue, node);
	peek_data_from_queue (queue);

	display_queue (queue);
	display_queue_details (queue);

	Node* del_node = dequeue (queue);
	printf ("Served Node :=> ");
	display_node (del_node);
	printf ("\n");
	delete_node (&del_node);
	display_queue (queue);
	peek_data_from_queue (queue);

	++*(node -> name -> address);
	*((int*)(node -> data -> address)) += 10;
	enqueue (queue, node);
	display_queue (queue);

	del_node = dequeue (queue);
	printf ("Served Node :=> ");
	display_node (del_node);
	printf ("\n");
	delete_node (&del_node);
	display_queue (queue);
	peek_data_from_queue (queue);

	del_node = dequeue (queue);
	printf ("Served Node :=> ");
	display_node (del_node);
	printf ("\n");
	delete_node (&del_node);
	display_queue (queue);

	del_node = dequeue (queue);
	printf ("Served Node :=> ");
	display_node (del_node);
	printf ("\n");
	delete_node (&del_node);
	display_queue (queue);
	peek_data_from_queue (queue);

	del_node = dequeue (queue);
	printf ("Served Node :=> ");
	display_node (del_node);
	printf ("\n");
	delete_node (&del_node);

	delete_node (&node);

	delete_queue (&queue);

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Queue]\n" RESET_STYLE);
}
