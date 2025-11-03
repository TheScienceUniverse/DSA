#include "../inc/list.h"

List* create_list (size_t item_count) {
	List* list = (List*) malloc (sizeof (List));

	auto size_t chunk_capacity = 0;
	auto size_t chunk_count = 0;

	if (list == NULL) {
		return NULL;
	}

	log_memory (DS_List, sizeof (List), list, true);

	list -> item_count = 0;
	list -> chunk_count = 0;
	list -> head_chunk = NULL;
	list -> tail_chunk = NULL;

	if (item_count == 0) {
		return list;
	}

	set_list_chunk_cap_count (item_count, &chunk_capacity, &chunk_count);

	list -> head_chunk = create_chunk (0, chunk_capacity);	// first (0th) and default chunk
	list -> tail_chunk = list -> head_chunk;
	list -> chunk_count = 1;

	return list;
}

List* duplicate_list (List* old_list) {
	if (NULL == old_list) {
		perror ("Old List does not exist to duplicate list from!\n");
		exit (EXIT_FAILURE);
	}

	List* new_list = create_list (0);
	new_list -> head_chunk = NULL;
	new_list -> tail_chunk = NULL;

	Chunk* old_chunk = old_list -> head_chunk;
	Chunk* new_chunk = NULL;
	Chunk* tmp_chunk;

	while (old_chunk != NULL) {
		tmp_chunk = duplicate_chunk (old_chunk);
		old_chunk = old_chunk -> next_chunk;
		tmp_chunk -> previous_chunk = new_chunk;

		if (NULL == new_list -> head_chunk) {
			new_list -> head_chunk = tmp_chunk;
		}

		if (NULL == new_chunk) {
			new_chunk = tmp_chunk;
			continue;
		}

		new_chunk -> next_chunk = tmp_chunk;
		new_chunk = new_chunk -> next_chunk;
	}

	new_list -> tail_chunk = new_chunk;
	new_list -> head_chunk -> previous_chunk = NULL;
	new_list -> tail_chunk -> next_chunk = NULL;
	new_list -> item_count = old_list -> item_count;

	return new_list;
}

void display_list (List* list) {
	if (NULL == list) {
		perror ("List does not exist to Display!");
		return;
	}

	display_linked_chunks (list -> head_chunk);
}

void display_list_details (List* list) {
	if (NULL == list) {
		perror ("List does not exist to Display details!");
		return;
	}

	printf ("List :=> Address: (%p) Size: (%lu) Elements: ", list, list -> item_count);
	display_linked_chunks (list -> head_chunk);
	putchar ('\n');
}

void display_list_subset (List* list, size_t start_index, size_t end_index) {
	Chunk* chunk = list -> head_chunk;
	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Data* chunk_data;
	bool first_item = true;

	// move to start position
	while (
		list_data_index < start_index
	) {
		++chunk_data_index;
		++list_data_index;

		if (
			NULL != chunk
			&& chunk -> capacity == chunk_data_index
		) {
			chunk = chunk -> next_chunk;
			chunk_data_index = 0;
		}
	}

	// print metadata
	printf ("List [%zu] (%zu - %zu) => ", list -> item_count, start_index, end_index);

	// start printing data
	while (list_data_index <= end_index) {
		chunk_data = chunk -> first_data_address + chunk_data_index;

		if (!first_item) {
			putchar (',');
		} else {
			first_item = false;
		}

		printf (" (%zu) ", list_data_index);
		display_data (chunk_data);

		++chunk_data_index;
		++list_data_index;

		if (
			NULL != chunk
			&& chunk -> capacity == chunk_data_index
		) {
			chunk = chunk -> next_chunk;
			chunk_data_index = 0;
		}
	}

	ENDL();
}

void delete_list (List** list_address) {
	if (*list_address == NULL) {
		perror ("List does not exist to Delete!");
		return;
	}

	List* list = *list_address;

	delete_linked_chunks (&(list -> head_chunk));

	list -> item_count = 0;
	list -> chunk_count = 0;
	list -> head_chunk = NULL;
	list -> tail_chunk = NULL;

	list = NULL;

	log_memory (DS_List, sizeof (List), *list_address, false);
	ERASE (list_address, sizeof (List));
}

void forget_list (List** list_address) {
	if (NULL != list_address) {
		list_address = NULL;
	}
}

void set_list_chunk_cap_count (size_t item_count, size_t* chunk_capacity, size_t* chunk_count) {
	if (5 >= item_count) {
		*chunk_capacity = item_count;
		*chunk_count = 1;
		return;
	}

	const size_t MIN_CHUNK_CAP = 10;	// minimum chunk capacity
	const size_t MAX_CHUNK_CAP = 1000;	// maximum chunk capacity

	size_t digit_count = get_number_of_digits (item_count, 10);
	size_t capacity = exponentiate (10, digit_count);

	if (item_count > capacity) {
		capacity *= 10;
	}

	if ((capacity - item_count) / digit_count < 50) {
		capacity /= 2;
	}

	if (MIN_CHUNK_CAP > capacity) {
		capacity = MIN_CHUNK_CAP;
	} else if (MAX_CHUNK_CAP < capacity) {
		capacity = MAX_CHUNK_CAP;
	}

	*chunk_capacity = capacity;
	*chunk_count = item_count / capacity;

	if (0 == *chunk_count) {
		*chunk_count = 1;
	}
}

bool is_list_empty (List* list) {
	return 0 == list -> item_count;
}

bool compare_lists (List* list_1, List* list_2) {
	if (NULL == list_1) {
		perror ("List-1 does not exist to compare with!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == list_2) {
		perror ("List-2 does not exist to compare with!\n");
		exit (EXIT_FAILURE);
	}

	if (list_1 -> item_count != list_2 -> item_count) {
		return false;
	}

	size_t total_item_count = list_1 -> item_count;
	Chunk* chunk_1 = list_1 -> head_chunk;
	Chunk* chunk_2 = list_2 -> head_chunk;
	size_t list_data_index = 0;
	size_t chunk_1_data_index = 0;
	size_t chunk_2_data_index = 0;
	Data* data_1 = NULL;
	Data* data_2 = NULL;
	bool compare_status = true;

	for ( ; list_data_index < total_item_count; list_data_index++) {
		data_1 = chunk_1 -> first_data_address + chunk_1_data_index++;
		data_2 = chunk_2 -> first_data_address + chunk_2_data_index++;

		if (Cmp_Different == compare_data (data_1, data_2)) {
			compare_status = false;
			break;
		}

		if (chunk_1 -> capacity == chunk_1_data_index) {
			chunk_1_data_index = 0;
			chunk_1 = chunk_1 -> next_chunk;
		}

		if (chunk_2 -> capacity == chunk_2_data_index) {
			chunk_2_data_index = 0;
			chunk_2 = chunk_2 -> next_chunk;
		}
	}

	return compare_status;
}

bool does_list_contain_data (List* list, Data* data) {
	if (NULL == list) {
		perror ("List does not exist to search data from!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to search inside list\n");
		exit (EXIT_FAILURE);
	}

	Chunk* chunk = list -> head_chunk;
	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Data* list_data = NULL;
	bool search_status = false;

	for ( ; list_data_index < list -> item_count; list_data_index++) {
		list_data = chunk -> first_data_address + chunk_data_index++;

		if (Cmp_Different == compare_data (data, list_data)) {
			search_status = true;
			break;
		}

		if (chunk -> capacity == chunk_data_index) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}

	return search_status;
}

void insert_data_into_list (List* list, Data* data) {
	if (NULL == list) {
		perror ("List does not exist to insert data into!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to insert into list!\n");
		exit (EXIT_FAILURE);
	}

	Chunk* chunk = list -> tail_chunk;
	insert_data_into_chunk (chunk, data);
	list -> tail_chunk = get_last_chunk_reference (chunk);
	list -> item_count++;
}

List* search_data_in_list (List* list, Data* data) {
	if (NULL == list) {
		perror ("List does not exist to search data from!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to search from list!\n");
		exit (EXIT_FAILURE);
	}

	List* index_list = create_list (list -> item_count / 4);
	Chunk* chunk = list -> head_chunk;
	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Data* index_data = create_empty_data ();
	Data* chunk_data;

	index_data -> type = DT_Integer;
	index_data -> size = sizeof (list_data_index);
	index_data -> address = &list_data_index;

	for ( ; list_data_index < list -> item_count; list_data_index++) {
		chunk_data = chunk -> first_data_address + chunk_data_index++;

		if (
			Cmp_Identical == compare_data (data, chunk_data)
			|| Cmp_Equivalent == compare_data (data, chunk_data)
		) {
			insert_data_into_list (index_list, index_data);
		}

		if (chunk -> data_count == chunk_data_index) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}

	index_data -> size = 0;
	index_data -> address = NULL;

	delete_data (&index_data);

	return index_list;
}

void delete_data_from_list (List* list, Data* data) {
	if (NULL == list) {
		perror ("List does not exist to delete data from!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to delete from list!\n");
		exit (EXIT_FAILURE);
	}

	Chunk* chunk = list -> tail_chunk;
	Data* deleted_data = remove_data_from_chunk (chunk);
	delete_data (&deleted_data);
	list -> tail_chunk = get_last_chunk_reference (chunk);
}

Data* remove_data_from_list (List* list) {
	if (NULL == list) {
		perror ("List does not exist to delete data from!\n");
		exit (EXIT_FAILURE);
	}

	Chunk* chunk = list -> tail_chunk;
	Data* deleted_data = remove_data_from_chunk (chunk);
	chunk = NULL;	// data removal may "reduce" chunk

	list -> tail_chunk = get_last_chunk_reference (list -> head_chunk);
	list -> item_count--;

	return deleted_data;
}

Data* get_list_data_at_index (List* list, size_t index) {
	if (NULL == list) {
		perror ("List does not exist to get data from!\n");
		exit (EXIT_FAILURE);
	}

	if (index >= list -> item_count) {
		perror ("List Index out of bound!\n");
		exit (EXIT_FAILURE);
	}

	Data* data = NULL;
	Chunk* chunk = list -> head_chunk;

	while (index >= chunk -> capacity) {
		chunk = chunk -> next_chunk;
		index -= chunk -> capacity;
	}

	data = chunk -> first_data_address + index;
	return duplicate_data (data);
}

size_t get_first_list_index_of_data (List* list , Data* data) {
	if (NULL == list) {
		perror ("List does not exist to get data index from!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to get index from list!\n");
		exit (EXIT_FAILURE);
	}

	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Chunk* chunk = list -> head_chunk;
	Data* chunk_data = NULL;

	for ( ; list_data_index < list -> item_count; list_data_index++) {
		chunk_data = chunk -> first_data_address + chunk_data_index++;

		if (
			Cmp_Identical == compare_data (data, chunk_data)
			|| Cmp_Equivalent == compare_data (data, chunk_data)
		) {
			break;
		}

		if (chunk -> data_count == chunk_data_index) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}

	return list_data_index;
}

size_t get_last_list_index_of_data (List* list , Data* data) {
	if (NULL == list) {
		perror ("List does not exist to get data index from!\n");
		exit (EXIT_FAILURE);
	}

	if (0 == list -> item_count) {
//		perror ("List is empty to get index from list!\n");
		return -1;
	}

	if (NULL == data) {
		perror ("Data does not exist to get index from list!\n");
		exit (EXIT_FAILURE);
	}

	size_t list_data_index = list -> item_count - 1;
	Chunk* chunk = list -> tail_chunk;
	size_t chunk_data_index = chunk -> data_count - 1;
	Data* chunk_data = NULL;

	for ( ; list_data_index != (size_t)(-1) && list_data_index < list -> item_count; list_data_index--) {
		chunk_data = chunk -> first_data_address + chunk_data_index--;

		if (Cmp_Different != compare_data (data, chunk_data)) {
			break;
		}

		if ((size_t)(-1) == chunk_data_index) {	// -1 = 0xffffffff
			chunk = chunk -> previous_chunk;

			if (NULL != chunk) {
				chunk_data_index = chunk -> data_count - 1;
			}
		}
	}

	return list_data_index;
}

void insert_into_list_at_index (List* list, Data* data, size_t index) {
	if (NULL == list) {
		perror ("List does not exist to insert data at index!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to insert into list at index!\n");
		exit (EXIT_FAILURE);
	}

	if (index >= list -> item_count) {
		perror ("Index out of bound to insert data into list at index!\n");
		exit (EXIT_FAILURE);
	}

	Chunk* chunk = list -> tail_chunk;

	if (chunk -> capacity == chunk -> data_count) {
		chunk = extend_chunk (chunk);
		chunk -> previous_chunk = list -> tail_chunk;
		list -> tail_chunk = chunk;
	}

	size_t list_data_index = list -> item_count;
	size_t chunk_data_index = chunk -> data_count;
	Data* left_data = NULL;
	Data* right_data = chunk -> first_data_address + chunk_data_index--;

	for ( ; list_data_index > index; list_data_index--) {
		if (
			0 == chunk_data_index
			|| chunk -> capacity < chunk_data_index
		) {
			chunk = chunk -> previous_chunk;
			chunk_data_index = chunk -> data_count - 1;
		}

		left_data = chunk -> first_data_address + chunk_data_index--;
		copy_data (left_data, right_data);
		right_data = left_data;	// pointer exchange
	}

	copy_data (data, right_data);

	list -> tail_chunk -> data_count++;
	list -> item_count++;
}

void insert_all_into_list (List* list, List* from_list) {
	if (NULL == list) {
		perror ("List does not exist to insert data from new list!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == from_list) {
		perror ("Data does not exist to insert into list at index!\n");
		exit (EXIT_FAILURE);
	}

	Chunk* chunk = from_list -> head_chunk;
	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Data* data = chunk -> first_data_address;

	for ( ; list_data_index < from_list -> item_count; list_data_index++) {
		if (chunk -> capacity == chunk_data_index) {
			chunk = chunk -> next_chunk;
			chunk_data_index = 0;
		}

		data = chunk -> first_data_address + chunk_data_index++;
		insert_data_into_list (list, data);
	}
}

void insert_all_into_list_from_index (List* list, List* from_list, size_t from_index) {
	if (NULL == list) {
		perror ("List does not exist to insert data at index!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == from_list) {
		perror ("New list does not exist to insert from, from index!\n");
		exit (EXIT_FAILURE);
	}

	if (from_index >= list -> item_count) {
		perror ("Index out of bound to insert data into list at index!\n");
		exit (EXIT_FAILURE);
	}

	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Chunk* chunk = from_list -> head_chunk;
	Data* chunk_data = NULL;

	for ( ; list_data_index < from_list -> item_count; list_data_index++) {
		chunk_data = chunk -> first_data_address + chunk_data_index++;
		insert_into_list_at_index (list, chunk_data, from_index++);

		if (chunk -> data_count == chunk_data_index) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}
}

List* get_sub_list (List* list, size_t start_index, size_t end_index) {
	if (NULL == list) {
		perror ("List does not exist to create sub-list!\n");
		exit (EXIT_FAILURE);
	}

	if (start_index > list -> item_count) {
		perror ("Start index out of bound to create sub-list!\n");
		exit (EXIT_FAILURE);
	}

	if (end_index > list -> item_count) {
		perror ("End index out of bound to create sub-list!\n");
		exit (EXIT_FAILURE);
	}

	List* sub_list = create_list (list -> head_chunk -> capacity / 2);	// to reduce the chunk size
	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Chunk* chunk = list -> head_chunk;
	Data* chunk_data = NULL;

	// move to start position
	for ( ; list_data_index < start_index; list_data_index++) {
		if (chunk -> data_count == chunk_data_index++) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}

	// start copying data
	for ( ; list_data_index <= end_index; list_data_index++) {
		chunk_data = chunk -> first_data_address + chunk_data_index++;
		insert_data_into_list (sub_list, chunk_data);

		if (chunk -> data_count == chunk_data_index) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}

	return sub_list;
}

void delete_from_list_at_index (List* list, size_t index) {
	if (NULL == list) {
		perror ("List does not exist to delete data from index!\n");
		exit (EXIT_FAILURE);
	}

	if (0 == list -> item_count) {
		// perror ("List is empty to delete data from index!\n");
		return;
	}

	if (index > list -> item_count) {
		perror ("Index out of bound to delete data from index!\n");
		exit (EXIT_FAILURE);
	}

	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Chunk* chunk = list -> head_chunk;
	Data* left_data = NULL;
	Data* right_data = NULL;

	// move to start position
	for ( ; list_data_index < index; list_data_index++) {
		if (chunk -> capacity - 1 == chunk_data_index++) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}

	left_data = chunk -> first_data_address + chunk_data_index;
//printf ("list-index: %ld chunk-index: %ld\n");
//printf ("Left data: ");
//display_data (left_data);
//ENDL();
	// start copying data
	for ( ; list_data_index < list -> item_count; list_data_index++) {
		if (chunk -> capacity == chunk_data_index) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}

		right_data = chunk -> first_data_address + chunk_data_index++;
		copy_data (right_data, left_data);
		left_data = right_data;
	}

	empty_data (right_data);

	chunk -> data_count--;
	list -> item_count--;

	if (0 == chunk -> data_count) {
		list -> tail_chunk = reduce_chunk (chunk);
	}
}

Data* remove_from_list_at_index (List* list, size_t index) {
	if (NULL == list) {
		perror ("List does not exist to delete data from index!\n");
		exit (EXIT_FAILURE);
	}

	if (index > list -> item_count) {
		perror ("Index out of bound to delete data from index!\n");
		exit (EXIT_FAILURE);
	}

	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Chunk* chunk = list -> head_chunk;
	Data* left_data = NULL;
	Data* right_data = NULL;
	Data* index_data = NULL;

	// move to start position
	for ( ; list_data_index < index; list_data_index++) {
		if (chunk -> data_count == chunk_data_index++) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}

	left_data = chunk -> first_data_address + chunk_data_index;
	index_data = duplicate_data (left_data);

	// start copying data
	for ( ; list_data_index < list -> item_count; list_data_index++) {

		if (chunk -> data_count == chunk_data_index) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}

		right_data = chunk -> first_data_address + chunk_data_index++;
		copy_data (right_data, left_data);
		left_data = right_data;
	}

	empty_data (right_data);

	chunk -> data_count--;
	list -> item_count--;

	if (
		0 == chunk -> data_count
		&& 0 != chunk -> id
	) {
		list -> tail_chunk = reduce_chunk (chunk);
	}

	return index_data;
}

void clear_list (List* list) {
	if (NULL == list) {
		perror ("List does not exist to clear!\n");
		exit (EXIT_FAILURE);
	}

	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Chunk* chunk = list -> head_chunk;
	Data* data = NULL;

	for ( ; list_data_index < list -> item_count; list_data_index++) {
		data = chunk -> first_data_address + chunk_data_index++;
		empty_data (data);

		if (chunk -> data_count == chunk_data_index) {
			chunk -> data_count = 0;
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}

	list -> item_count = 0;
}

void delete_first_instance_from_list (List* list, Data* data) {
	if (NULL == list) {
		perror ("List does not exist to delete data's first instance from!\n");
		exit (EXIT_FAILURE);
	}

	if (0 == list -> item_count) {
		perror ("List is empty to delete data's first instance from!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to search and delete first instance from list!\n");
		exit (EXIT_FAILURE);
	}

	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Chunk* chunk = list -> head_chunk;
	Data* left_data = NULL;
	Data* right_data = NULL;
	Compare_Status cmp_stat;

	// move to first instance position
	for ( ; list_data_index < list -> item_count; list_data_index++) {
		left_data = chunk -> first_data_address + chunk_data_index;
		cmp_stat = compare_data (left_data, data);

		if (
			Cmp_Identical == cmp_stat
			|| Cmp_Equivalent == cmp_stat
		) {
			break;
		}

		if (chunk -> capacity == chunk_data_index++) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}

	// start copying data
	for ( ; list_data_index < list -> item_count; list_data_index++) {

		if (chunk -> capacity == chunk_data_index) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}

		right_data = chunk -> first_data_address + chunk_data_index++;
		copy_data (right_data, left_data);
		left_data = right_data;
	}

	empty_data (right_data);

	chunk -> data_count--;
	list -> item_count--;

	if (
		0 == chunk -> data_count
		&& 0 != chunk -> id
	) {
		list -> tail_chunk = reduce_chunk (chunk);
	}
}

void delete_last_instance_from_list (List* list, Data* data) {
	if (NULL == list) {
		perror ("List does not exist to delete data's last instance from!\n");
		exit (EXIT_FAILURE);
	}

	if (0 == list -> item_count) {
		// perror ("List is empty to delete data's last instance from!\n");
		return;
	}

	if (NULL == data) {
		perror ("Data does not exist to search and delete last instance from list!\n");
		exit (EXIT_FAILURE);
	}

	size_t index = get_last_list_index_of_data (list, data);

	if ((size_t)(-1) != index) {
		delete_from_list_at_index (list, index);
	}
}

void delete_all_instances_from_list (List* list, Data* data) {
	if (NULL == list) {
		perror ("List does not exist to delete data from index!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to search an delete from list!\n");
		exit (EXIT_FAILURE);
	}

	Chunk* chunk = list -> head_chunk;
	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Data* left_data = NULL;
	Data* right_data = NULL;
	Compare_Status compare_status;
	size_t instance_count = 0;
	bool copy_flag = false;

	for ( ; list_data_index < list -> item_count; list_data_index++) {
		copy_flag = true;

		left_data = chunk -> first_data_address + chunk_data_index;
		compare_status = compare_data (data, left_data);

		right_data = chunk -> first_data_address + chunk_data_index++ + instance_count;

		compare_status = compare_data (data, right_data);

		if (
			Cmp_Identical == compare_status
			|| Cmp_Equivalent == compare_status
		) {
			// empty_data (left_data);
			copy_flag = false;
			++instance_count;
			--chunk_data_index;
		}

		if (
			right_data != left_data
			&& instance_count > 0
			&& copy_flag
		) {
			copy_data (right_data, left_data);
			empty_data (right_data);
		}
	}

	for ( ; list_data_index < list -> item_count; list_data_index++) {
		left_data = chunk -> first_data_address + chunk_data_index++;
		empty_data (left_data);
	}

	chunk -> data_count -= instance_count;
	list -> item_count -= instance_count;

	if (
		0 == chunk -> data_count
		&& 0 != chunk -> id
	) {
		list -> tail_chunk = reduce_chunk (chunk);
	}
}

void defragment_list (List* list) {
	Chunk* chunk = list -> tail_chunk;
	Chunk* prev_chunk = chunk -> previous_chunk;

	while (
		NULL != chunk
		&& 0 != chunk -> id
	) {
		if (0 != chunk -> data_count) {
			continue;
		}

		prev_chunk = chunk -> previous_chunk;

		if (list -> item_count > chunk -> capacity) {
			list -> item_count -= chunk -> capacity;
		}

		delete_chunk (&chunk);
		chunk = prev_chunk;
	}

	list -> tail_chunk = get_last_chunk_reference (list -> head_chunk);
}