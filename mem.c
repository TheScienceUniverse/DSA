#include "./include/basic.h"
#include "./include/string.h"

int main (int argc, char* argv[]) {
	if (argc < 2) {
		perror ("No option is given!");
		return EXIT_FAILURE;
	}

	if (compare_raw_strings_shh (4, argv [1], 4, "show")) {
		display_memory_log ();
	}

	return EXIT_SUCCESS;
}
