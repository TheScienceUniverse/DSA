#include "../inc/iterator.h"

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

	if (NULL == iterator) {
		perror ("Unable to allocate memory for iterator!\n");
		exit (EXIT_FAILURE);
	}

	log_memory (DS_Iterator, sizeof (Iterator), iterator, true);

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

	log_memory (DS_Iterator, sizeof (Iterator), *iterator_address, false);
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
	iterator -> stride = stride;

	if (stride > 1024) {
		iterator -> stride = 1024;
	}

	if (stride < -1024) {
		iterator -> stride = -1024;
	}
}

void move_iterator (Iterator* iterator) {
	Chunk* chunk = iterator -> chunk;
	ssize_t list_data_index = iterator -> list_data_index;
	ssize_t chunk_data_index = iterator -> chunk_data_index;

	ssize_t start_index = list_data_index;
	ssize_t end_index = list_data_index + iterator -> stride;
	size_t index_difference = iterator -> list_data_index + iterator -> stride;

	if (end_index > start_index) {						// moving forward
		while (index_difference > chunk -> capacity) {
			index_difference -= chunk -> capacity;
			chunk = chunk -> next_chunk;
		}

		chunk_data_index = index_difference;
	} else {											// moving backward
		// unable to calculate fast forward due to unavailability of left chunk's capacity information
		for (ssize_t idx = start_index; idx > end_index; idx--) {
			--chunk_data_index;

			if (chunk_data_index == 0) {
				chunk = chunk -> previous_chunk;
				chunk_data_index = chunk -> capacity;
			}
		}
	}

	iterator -> list_data_index += iterator -> stride;
	iterator -> chunk_data_index = chunk_data_index;
	iterator -> chunk = chunk;
	iterator -> data = chunk -> first_data_address + chunk_data_index;
}