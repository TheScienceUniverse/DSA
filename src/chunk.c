#include "../include/chunk.h"

Chunk* create_chunk (size_t chunk_id, size_t capacity) {
	Chunk* chunk = (Chunk*) malloc (sizeof (Chunk));

	if (chunk == NULL) {
		return NULL;
	}

	chunk -> id = 0;
	chunk -> capacity = 0;
	chunk -> data_count = 0;
	chunk -> data_addresses = NULL;
	chunk -> next_chunk = NULL;

	if (capacity == 0) {
		return chunk;
	}

	chunk -> id = chunk_id;
	chunk -> capacity = capacity;
	chunk -> data_addresses = (Data**) calloc (capacity, sizeof (Data*));

	if (chunk -> data_addresses == NULL) {
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
	Data** data_address = chunk -> data_addresses;

	for (size_t i = 0; i < chunk -> data_count; i++) {
		delete_data (data_address);
		data_address = data_address + 1;
	}

	chunk = NULL;
	ERASE (chunk_address, sizeof (Chunk));
}

void display_chunk_properties (Chunk* chunk) {
	if (chunk == NULL) {
		perror ("Chunk does not exist!");
		return;
	}

	Data* data;

	printf ("Chunk id = %lu\n", chunk -> id);
	printf ("Chunk capacity = %lu\n", chunk -> capacity);
	printf ("Chunk data count = %lu\n", chunk -> data_count);

	printf ("Chunk data list: [");

	for (size_t i = 0; i < chunk -> data_count; i++) {
		data = *(chunk -> data_addresses + i);

		if (i != 0) {
			printf (", ");
		}

		display_data (data);
	}

	printf ("]\n");
}

void display_chunk (Chunk* chunk) {
	if (chunk == NULL) {
		perror ("Chunk does not exist!");
		return;
	}

	Data* data;

	printf ("Chunk_%lu (%lu / %lu): [", chunk -> id, chunk -> data_count, chunk -> capacity);

	for (size_t i = 0; i < chunk -> data_count; i++) {
		data = *(chunk -> data_addresses + i);

		if (i != 0) {
			printf (", ");
		}

		display_data (data);
	}

	printf ("]\n");
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

void display_chunk (Chunk* chunk) {
	if (chunk -> item_count == 0) {
		perror ("Chunk is Empty!");
		return;
	}

	Data* data;

	printf ("Chunk (%lu) : [", chunk -> item_count);

	for (size_t i = 0; i < chunk -> item_count; i++) {
		data = *(chunk -> item_addresses + i);

		if (i != 0) {
			printf (", ");
		}

		display_data (data);
	}

	printf ("]\n");
}*/

Chunk* extend_chunk (Chunk* chunk) {
	Chunk* new_chunk = create_chunk (chunk -> id + 1, chunk -> capacity);
	chunk -> next_chunk = new_chunk;
	return new_chunk;
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

	if (chunk -> capacity == chunk -> data_count) {
		chunk = extend_chunk (chunk);
	}

	*(chunk -> data_addresses + chunk -> data_count++) = duplicate_data (data);
}

Data* delete_data_from_chunk (Chunk* chunk) {
	Data* data = *(chunk -> data_addresses + chunk -> data_count - 1);
	delete_data (chunk -> data_addresses + chunk -> data_count-- - 1);
	return data;
}
