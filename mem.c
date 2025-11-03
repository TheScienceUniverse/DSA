#include "./inc/mgc.h"

int main (int argc, char* argv[]) {
	if (argc < 2) {
		perror ("No option is given!");
		return EXIT_FAILURE;
	}

	if (compare_raw_strings_shh (4, argv [1], 4, "show")) {
		display_memory_log ();
	}

	if (compare_raw_strings_shh (5, argv [1], 5, "check")) {
//		display_memory_log ();
		perror ("Feature not implemented!");
		exit (EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
