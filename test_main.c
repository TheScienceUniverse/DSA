#include "./include/test.h"

int main (void) {
	test_basic ();
	test_string ();
	test_data ();
	test_list ();
	test_node ();
	test_linked_list ();
	test_stack ();
	test_queue ();
	test_tree ();
	test_graph ();

	return 0;
}
