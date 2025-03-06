#include "../include/chunk.h"

Chunk* create_chunk (size_t chunk_id, size_t capacity) {
	Chunk* chunk = (Chunk*) malloc (sizeof (Chunk));

	if (chunk == NULL) {
		return NULL;
	}

	chunk -> id = 0;
	chunk -> capacity = 0;
	chunk -> data_count = 0;
	chunk -> first_data_address = NULL;
	chunk -> next_chunk = NULL;
	chunk -> previous_chunk = NULL;

	if (capacity == 0) {
		return chunk;
	}

	chunk -> id = chunk_id;
	chunk -> capacity = capacity;
	chunk -> first_data_address = (Data*) calloc (capacity, sizeof (Data));

	if (chunk -> first_data_address == NULL) {
		perror ("Unable to allocate memory!\n");
		exit (1);
	}

	return chunk;
}

void delete_chunk (Chunk** chunk_address) {
	if (*chunk_address == NULL) {
		perror ("Chunk does not exist to Delete!");
		return;
	}

	Chunk* chunk = *chunk_address;

	/* Unlink and re-link chunk in betwwen the chunk-list */
	Chunk* previous_chunk = chunk -> previous_chunk;
	Chunk* next_chunk = chunk -> next_chunk;

	if (previous_chunk != NULL) {
		previous_chunk -> next_chunk = next_chunk;
	}

	if (next_chunk != NULL) {
		next_chunk -> previous_chunk = previous_chunk;
	}

	previous_chunk = NULL;
	next_chunk = NULL;

	ERASE (&(chunk -> first_data_address), sizeof (Data) * chunk -> capacity);
	
	chunk = NULL;
	ERASE (chunk_address, sizeof (Chunk));
}

void display_chunk_details (Chunk* chunk) {
	if (chunk == NULL) {
		perror ("Chunk does not exist!");
		return;
	}

	Data* data;

	printf ("Chunk id = %lu\n", chunk -> id);
	printf ("Chunk capacity = %lu\n", chunk -> capacity);
	printf ("Chunk data count = %lu\n", chunk -> data_count);

	printf ("Chunk data list: [ ");

	for (size_t i = 0; i < chunk -> capacity; i++) {
		data = chunk -> first_data_address + i;

		if (i != 0) {
			printf (" | ");
		}

		display_data (data);
	}

	printf (" ]\n");
}

void display_chunk (Chunk* chunk) {
	if (chunk == NULL) {
		perror ("Chunk does not exist!");
		return;
	}

	Data* data;

	printf ("Chunk_%lu (%lu / %lu): [ ", chunk -> id, chunk -> data_count, chunk -> capacity);

	for (size_t i = 0; i < chunk -> capacity; i++) {
		data = chunk -> first_data_address + i;

		if (i != 0) {
			printf (" | ");
		}

		display_data (data);
	}

	printf (" ]\n");
}

void display_linked_chunks (Chunk* chunk) {
	Chunk* c = chunk;

	printf ("----------\n");

	while (c != NULL) {
		display_chunk (c);
		c = c -> next_chunk;
	}
	
	printf ("----------\n");
}

/*
Chunk* duplicate_chunk (Chunk* old_chunk) {
	if (old_chunk == NULL) {
		perror ("Chunk does not exist to Duplicate!");
		return NULL;
	}

	Chunk* new_chunk = create_chunk (old_chunk -> item_count);

	if (new_chunk != NULL) {
		for (size_t i = 0; i < new_chunk -> item_count; i++) {
			*(new_chunk -> item_addresses + i) = *(old_chunk -> item_addresses + i);
		}
	}

	return new_chunk;
}

void forget_chunk (Chunk** chunk_address) {
	if (*chunk_address == NULL) {
		perror ("Chunk does not exist to Forget!");
		return;
	}

	Chunk* chunk = *chunk_address;

	for (size_t i = 0; i < chunk -> item_count; i++) {
		*(chunk -> item_addresses + i) = NULL;
	}
}
*/

Chunk* get_first_chunk (Chunk* chunk) {
	if (NULL == chunk) {
		perror ("Provided chunk does not exist!\n");
		return NULL;
	}

	Chunk *first_chunk = chunk;

	if (NULL == chunk -> previous_chunk) {
		return chunk;
	}

	while (NULL != first_chunk -> previous_chunk) {
		first_chunk = first_chunk -> previous_chunk;
	}

	return first_chunk;
}

Chunk* get_last_chunk (Chunk* chunk) {
	if (NULL == chunk) {
		perror ("Provided chunk does not exist!\n");
		return NULL;
	}

	if (NULL == chunk -> next_chunk) {
		return chunk;
	}

	Chunk *last_chunk = chunk;

	while (NULL != last_chunk -> next_chunk) {
		last_chunk = last_chunk -> next_chunk;
	}

	return last_chunk;
}

Chunk* extend_chunk (Chunk* chunk) {
	Chunk* last_chunk = get_last_chunk (chunk);

	Chunk* new_chunk = create_chunk (last_chunk -> id + 1, last_chunk -> capacity);
	last_chunk -> next_chunk = new_chunk;
	new_chunk -> previous_chunk = last_chunk;

	return new_chunk;
}

Chunk* reduce_chunk (Chunk* chunk) {
	if (NULL == chunk) {
		perror ("Chunk does not exist!\n");
		return NULL;
	}

	if (0 == chunk -> id && chunk == get_first_chunk (chunk)) {
		return chunk;
	}

	Chunk* last_chunk = get_last_chunk (chunk);
	Chunk* penultimate_chunk = last_chunk -> previous_chunk;	// [Latin] "paene" (almost), "ultima" (last)

	penultimate_chunk -> next_chunk = NULL;
	last_chunk -> previous_chunk = NULL;

//	delete_chunk (&last_chunk);

	return penultimate_chunk;
}

void insert_data_into_chunk (Chunk* chunk, Data* data) {
	if (chunk == NULL) {
		perror ("Provided chunk does not exist to insert into!\n");
		return;
	}

	if (data == NULL) {
		perror ("Provided data does not exist to insert!\n");
		return;
	}

	Chunk* last_chunk = get_last_chunk (chunk);

	if (last_chunk -> capacity == last_chunk -> data_count) {
		last_chunk = extend_chunk (last_chunk);
	}

	copy_data (data, last_chunk -> first_data_address + last_chunk -> data_count++);
}

Data* remove_data_from_chunk (Chunk* chunk) {
	if (NULL == chunk) {
		perror ("Provided chunk does not exist to remove from!\n");
		return NULL;
	}

	Chunk* last_chunk = get_last_chunk (chunk);
	Chunk* first_chunk = get_first_chunk (chunk);

	if (
		last_chunk == first_chunk
		&& last_chunk -> data_count == 0
	) {
		return NULL;
	}

	Data* data = last_chunk -> first_data_address + last_chunk -> data_count - 1;
	Data* real_data = duplicate_data (data);

	empty_data (data);

	-- (last_chunk -> data_count);

	if (
		last_chunk -> id != 0
		&& last_chunk -> data_count == 0
	) {
		last_chunk = reduce_chunk (last_chunk);
	}

	return real_data;
}
