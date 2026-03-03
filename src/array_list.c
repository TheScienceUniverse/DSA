#include "../inc/array_list.h"

ArrayList* create_ArrayList (const size_t item_count) {
	ArrayList* array_list = (ArrayList*) malloc (sizeof (ArrayList));

	if (NULL == array_list) {
		return NULL;
	}

	log_memory (DS_ArrayList, sizeof (ArrayList), array_list, true);

	array_list -> item_count = 0;
	array_list -> capacity = 0;
	array_list -> container = NULL;

	size_t capacity = calculate_ArrayList_capacity (item_count);
	array_list -> capacity = capacity;

	array_list -> container = malloc (capacity * sizeof (Data));

	if (NULL == array_list -> container) {
		return NULL;
	}
	log_memory (DS_Raw, capacity * sizeof (Data), array_list -> container, true);

	fill_mem_zero(array_list -> container, array_list -> capacity * sizeof (Data));

	return array_list;
}

size_t calculate_ArrayList_capacity (const size_t item_count) {
	const size_t MIN_CHUNK_CAP = 10;	// minimum chunk capacity
	const size_t MAX_CHUNK_CAP = 1000;	// maximum chunk capacity

	size_t digit_count = get_number_of_digits (item_count, 10);
	size_t capacity = exponentiate (10, digit_count);

	if (item_count > capacity) {
		capacity *= 10;
	}

	if (((capacity - item_count) / digit_count) < 50) {
		capacity >>= 1;	// capacity /= 2
	}

	if (MIN_CHUNK_CAP > capacity) {
		capacity = MIN_CHUNK_CAP;
	} else if (MAX_CHUNK_CAP < capacity) {
		capacity = MAX_CHUNK_CAP;
	}

	return capacity;
}

ArrayList* duplicate_ArrayList (const ArrayList* const old_array_list) {
	if (NULL == old_array_list) {
		perror ("ArrayList does not exist to Duplicate!");
		return NULL;
	}

	ArrayList* new_array_list = create_ArrayList (old_array_list -> item_count);
	Data* src_data = old_array_list -> container;
	Data* dst_data = new_array_list -> container;

	if (new_array_list != NULL) {
		for (size_t i = 0; i < new_array_list -> item_count; i++) {
			copy_Data (src_data++, dst_data++);
		}
	}

	return new_array_list;
}

void display_ArrayList (const ArrayList* const array_list) {
	if (NULL == array_list) {
		perror ("ArrayList does not exist to display!");
		return;
	}

	if (0 == array_list -> item_count) {
		perror ("ArrayList is Empty to display!");
		return;
	}

	printf ("ArrayList (%lu) : [", array_list -> item_count);

	for (size_t i = 0; i < array_list -> item_count; i++) {
		if (i != 0) {
			printf (", ");
		}

		display_Data ((Data*)(array_list -> container) + i);
	}

	printf ("]\n");
}

void display_ArrayList_details (const ArrayList* const array_list) {
	if (NULL == array_list) {
		perror ("ArrayList does not exist to display!");
		return;
	}

	printf ("ArrayList (@%p) :=> Item-Count: %zu, Capacity: %zu, Conetent: [\n", array_list, array_list -> item_count, array_list -> capacity);

	Data* data_ptr = array_list -> container;

	for (size_t i = 0; i < array_list -> capacity; i++) {
		putchar ('\t');
		if (i != 0) {
			printf (", ");
		}

		display_Data_details (data_ptr++);
	}

	printf ("\n]\n");
}

void delete_ArrayList (ArrayList** const array_list_address) {
	if (NULL == *array_list_address) {
		perror ("ArrayList does not exist to Delete!");
		return;
	}

	ArrayList* array_list = *array_list_address;
	__attribute__((unused)) Data* data;

	for (size_t i = 0; i < array_list -> item_count; i++) {
		data = (Data*)(array_list -> container) + i;
		empty_Data (data);
	}

	log_memory (DS_Raw, (array_list -> capacity) * sizeof (Data), array_list -> container, false);
	ERASE (&(array_list -> container), (array_list -> capacity) * sizeof (Data));

	array_list = NULL;

	log_memory (DS_ArrayList, sizeof (ArrayList), *array_list_address, false);
	ERASE (array_list_address, sizeof (ArrayList));
}

void extend_ArrayList (ArrayList* const array_list) {
	// collect old container
	size_t old_size = array_list -> capacity * sizeof (Data);
	void* old_container = array_list -> container;

	// reallocate container to twice big space
	size_t new_capacity = array_list -> capacity << 1;
	size_t new_size = new_capacity * sizeof (Data);
	log_memory (DS_Raw, old_size, old_container, false);
	void* new_container = realloc (old_container, new_size);
	
	if (NULL == new_container) {
		perror ("Unable to allocate memory for ArrayList content to add Data!");
		return;
	}

	log_memory (DS_Raw, new_size, new_container, true);

	// fill uninialized space created by realloc
	fill_mem_zero ((Data*) new_container + array_list -> item_count, (new_capacity - array_list -> item_count) * sizeof (Data));

	// re-assign array-list to correct container address and capacity
	array_list -> container = new_container;
	array_list -> capacity = new_capacity;
}

void add_to_ArrayList (ArrayList* const array_list, Data* data) {
	if (NULL == array_list) {
		perror ("ArrayList does not exist to add data!");
		return;
	}

	if (NULL == array_list -> container) {
		perror ("ArrayList does not have container to add data!");
		return;
	}

	if (array_list -> capacity <= array_list -> item_count) {
		extend_ArrayList (array_list);
	}

	copy_Data (data, (Data*)(array_list -> container) + array_list -> item_count++);
}

Data* get_ArrayList_Data_at_index (const ArrayList* const array_list, const size_t index) {
	if (NULL == array_list) {
		perror ("ArrayList does not exist to get data!");
		return NULL;
	}

	if (NULL == array_list -> container) {
		perror ("ArrayList does not have container to get data!");
		return NULL;
	}

	if (index >= array_list -> item_count) {
		perror ("ArrayList intex out-of-range to get data!");
		return NULL;
	}

	return duplicate_Data ((Data*)(array_list -> container) + index);
}

Data* get_item_from_ArrayList (const ArrayList* const array_list, const size_t index) {
	if (NULL == array_list) {
		perror ("ArrayList does not exist to get data from!");
		return NULL;
	}

	if (
		NULL == array_list -> container
		|| 0 == array_list -> item_count
	) {
		perror ("ArrayList does not have data to get data from!");
		return NULL;
	}

	if (array_list -> item_count <= index) {
		perror ("ArrayList index out-of-bound to get data from!");
		return NULL;
	}

	return NULL;
}