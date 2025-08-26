#include "./inc/test.h"

int main (int argc, char* argv[]) {
	setlocale (LC_ALL, "");	// for UTF-8 support

	char* option;

	// argv [0] is the program itself
	for (int i = 1; i < argc; i++) {
		option = argv [i];
		test_route (option);
	}

	if (argc < 2) {
		option = "all";
		test_route (option);
	}

	//	display_memory_log ();

	return EXIT_SUCCESS;
}

void test_route (char* option) {
	if (compare_raw_strings_shh (5, "basic", 5, option)) {
		test_basic ();
	} else if (compare_raw_strings_shh (6, "stream", 6, option)) {
		test_stream ();
	} else if (compare_raw_strings_shh (6, "string", 6, option)) {
		test_string ();
	} else if (compare_raw_strings_shh (4, "data", 4, option)) {
		test_data ();
	} else if (compare_raw_strings_shh (5, "chunk", 5, option)) {
		test_chunk ();
	} else if (compare_raw_strings_shh (9, "bare_list", 9, option)) {
		test_bare_list ();
	} else if (compare_raw_strings_shh (4, "list", 4, option)) {
		test_list ();
	} else if (compare_raw_strings_shh (8, "iterator", 8, option)) {
		test_iterator ();
	} else if (compare_raw_strings_shh (4, "node", 4, option)) {
		test_node ();
	} else if (compare_raw_strings_shh (11, "linked_list", 11, option)) {
		test_linked_list ();
	} else if (compare_raw_strings_shh (5, "stack", 5, option)) {
		test_stack ();
	} else if (compare_raw_strings_shh (5, "queue", 5, option)) {
		test_queue ();
	} else if (compare_raw_strings_shh (4, "tree", 4, option)) {
		test_tree ();
	} else if (compare_raw_strings_shh (5, "graph", 5, option)) {
		//test_graph ();
	} else if (compare_raw_strings_shh (3, "all", 3, option)) {
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
		//test_graph ();
	}
}
