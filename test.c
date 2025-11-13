#include "./inc/test.h"
#include "./inc/mgc.h"

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

	Data* data = create_Data (DT_String, strlen (option), option);
	display_Data (data);

	//	display_memory_log ();
	manage_memory ();

	return EXIT_SUCCESS;
}

void test_route (char* option) {
	if (compare_raw_strings_shh (5, "basic", 5, option)) {
		test_basic ();
	} else if (compare_raw_strings_shh (6, "stream", 6, option)) {
		test_Stream ();
	} else if (compare_raw_strings_shh (6, "string", 6, option)) {
		test_String ();
	} else if (compare_raw_strings_shh (4, "data", 4, option)) {
		test_Data ();
	} else if (compare_raw_strings_shh (5, "chunk", 5, option)) {
		test_Chunk ();
	} else if (compare_raw_strings_shh (9, "bare_list", 9, option)) {
		test_Bare_List ();
	} else if (compare_raw_strings_shh (4, "list", 4, option)) {
		test_List ();
	} else if (compare_raw_strings_shh (8, "iterator", 8, option)) {
		test_Iterator ();
	} else if (compare_raw_strings_shh (4, "node", 4, option)) {
		test_Node ();
	} else if (compare_raw_strings_shh (11, "linked_list", 11, option)) {
		test_Linked_List ();
	} else if (compare_raw_strings_shh (5, "stack", 5, option)) {
		test_Stack ();
	} else if (compare_raw_strings_shh (5, "queue", 5, option)) {
		test_Queue ();
	} else if (compare_raw_strings_shh (4, "tree", 4, option)) {
		test_Tree ();
	} else if (compare_raw_strings_shh (5, "graph", 5, option)) {
		//test_Graph ();
	} else if (compare_raw_strings_shh (3, "all", 3, option)) {
		test_basic ();
		test_String ();
		test_Data ();
		test_Chunk ();
		test_Bare_List ();
		test_List ();
		test_Iterator ();
		test_Node ();
		test_Linked_List ();
		test_Stack ();
		test_Queue ();
		test_Tree ();
		//test_graph ();
	}
}
