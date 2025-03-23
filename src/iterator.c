#include "../include/iterator.h"

Iterator* create_iterator (List* list, ssize_t stride) {
	if (NULL == list) {
		perror ("List does not exist to get iterator!\n");
		exit (EXIT_FAILURE);
	}

	if (list -> item_count < (size_t) stride) {
		perror ("Stride (jump index) out of list bound!\n");
		exit (EXIT_FAILURE);
	}

	Iterator* iterator = malloc (sizeof (Iterator));

	iterator -> list = list;
	iterator -> chunk = list -> head_chunk;
	iterator -> list_data_index = 0;
	iterator -> chunk_data_index = 0;
	iterator -> stride = stride;

	if (NULL != iterator -> chunk) {
		iterator -> data = iterator -> chunk -> first_data_address;
	}

	return iterator;
}

void delete_iterator (Iterator** iterator_address) {
	if (NULL == *iterator_address) {
		perror ("Iterator does not exist to delete!\n");
		exit (EXIT_FAILURE);
	}

	ERASE (iterator_address, sizeof (Iterator));
}

void display_iterator_details (Iterator* iterator) {
	printf ("Iterator:");
	printf (" List [%lu]", iterator -> list_data_index);
	printf (" Chunk_%lu [%lu]", iterator -> chunk -> id, iterator -> chunk_data_index);
	printf (" Stride: (%s) %li", (0 > iterator -> stride) ? "<=" : "=>", (iterator -> stride & 0x0fffffff));
	printf (" Data: ");
	display_data (iterator -> data);
	printf ("\n");
}

void update_iterator_stride (Iterator* iterator, ssize_t stride) {
	if ((stride & 0x0fffffff) > (iterator -> list -> item_count)) {
		perror ("Stride index out of bound\n");
		exit (EXIT_FAILURE);
	}

	iterator -> stride = stride;
}

void move_iterator (Iterator* iterator) {
	// ssize_t chunk_data_index = iterator -> chunk_data_index;
	iterator -> list_data_index += iterator -> stride;
	iterator -> chunk_data_index += iterator -> stride;
	iterator -> data = iterator -> chunk -> first_data_address + iterator -> chunk_data_index;
}