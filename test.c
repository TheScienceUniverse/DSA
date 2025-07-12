#include "./inc/test.h"

int main (void) {
	setlocale (LC_ALL, "");	// for UTF-8 support

	test_basic ();
	test_string ();
	test_data ();
	test_chunk ();
	test_bare_list ();
	test_list ();
	test_iterator ();
	test_node ();
	test_linked_list ();
	test_stack ();
	test_queue ();
	test_tree ();
//	test_graph ();

//	display_memory_log ();

	return EXIT_SUCCESS;
}
