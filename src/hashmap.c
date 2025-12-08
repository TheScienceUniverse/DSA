#include "../inc/hashmap.h"

HashMap* create_HashMap (size_t capacity) {
	if (0 == capacity) {
		return NULL;
	}

	HashMap* hashmap = malloc (sizeof (HashMap));

	if (NULL == hashmap) {
		perror ("Unable to allocate memory for hashmap!");
		return NULL;
	}

	log_memory (DS_HashMap, sizeof (HashMap), hashmap, true);

	hashmap -> capacity = capacity;
	hashmap -> buckets = create_address_List (capacity);
	hashmap -> item_count = 0;
	hashmap -> bucket_count = capacity;

	if (NULL == hashmap -> buckets) {
		perror ("Unable to create list for hashmap!");
		hashmap -> capacity = 0;
		hashmap -> bucket_count = 0;
		return hashmap;
	}

	Iterator* iterator = create_Iterator (hashmap -> buckets, 1);

	for (size_t i = 0; i < capacity - 1; i++) {
		iterator -> data -> address = create_Linked_List ();
		move_Iterator (iterator);
	}

	iterator -> data -> address = create_Linked_List ();

	delete_Iterator (&iterator);

	return hashmap;
}

void display_HashMap (HashMap* hashmap) {
	if (NULL == hashmap) {
		perror ("Hashmap does not exist to display!");
		return;
	}

	printf ("HashMap (%zu / %zu) => \n", hashmap -> item_count, hashmap -> bucket_count);

	if (NULL == hashmap -> buckets) {
		perror ("Unable to display key-value pair list!");
		return;
	}

	Iterator* iterator = create_Iterator (hashmap -> buckets, 1);
	size_t i;

	for (i = 0; i < hashmap -> capacity - 1; i++) {
		printf ("\tBucket-[%zu] -> ", i);
		display_Linked_List (iterator -> data -> address);
		move_Iterator (iterator);
		ENDL();
	}

	printf ("\tBucket-[%zu] -> ", i);
	display_Linked_List (iterator -> data -> address);
	ENDL();

	delete_Iterator (&iterator);
}

void display_HashMap_details (HashMap* hashmap) {
	if (NULL == hashmap) {
		perror ("Hashmap does not exist to display!");
		return;
	}

	printf ("HashMap => item-count: %zu, bucket-count: %zu\n", hashmap -> item_count, hashmap -> bucket_count);

	if (NULL == hashmap -> buckets) {
		perror ("Unable to display key-value pair list!");
		return;
	}

	Iterator* iterator = create_Iterator (hashmap -> buckets, 1);
	size_t i;

	for (i = 0; i < hashmap -> capacity - 1; i++) {
		printf ("\tBucket-[%zu] (%p): ", i, iterator -> data -> address);
		display_Linked_List (iterator -> data -> address);
		move_Iterator (iterator);
		ENDL();
	}

	printf ("\tBucket-[%zu] (%p): ", i, iterator -> data -> address);
	display_Linked_List (iterator -> data -> address);
	ENDL();

	delete_Iterator (&iterator);
}

void delete_HashMap (HashMap** hashmap_address) {
	HashMap* hashmap = *hashmap_address;

	if (NULL == hashmap) {
		perror ("HashMap does not exist to delete!");
		return;
	}

	if (NULL == hashmap -> buckets) {
		perror ("HashMap bucket-list does not exist to delete!");
		return;
	}

	Iterator* iterator = create_Iterator (hashmap -> buckets, 1);
	Linked_List* linked_list;

	for (size_t i = 0; i < hashmap -> capacity - 1; i++) {
		linked_list = iterator -> data -> address;
		delete_Linked_List (&linked_list);
		iterator -> data -> address = NULL;
		move_Iterator (iterator);
	}

	linked_list = iterator -> data -> address;
	delete_Linked_List (&linked_list);
	iterator -> data -> address = NULL;

	delete_Iterator (&iterator);
	delete_List (&(hashmap -> buckets));
	hashmap = NULL;

	log_memory (DS_HashMap, sizeof (HashMap), *hashmap_address, false);
	ERASE (hashmap_address, sizeof (HashMap));
}

uint32_t hash_djb2 (String* key) {
	// fast & efficient string hashing by Daniel J. Bernstein
	uint32_t hash = 5381;
	// 5381 => prime number for spreading and mixing 1's faster and better
	// 33 => magic number, 33 = 32 + 1 = (2 ^ 5) + 1
	char* c_ptr = key -> text;

	for (size_t i = 0; i < key -> length; i++) {
		// hash = hash * 33 + c;	// slow multiplication
		hash = ((hash << 5) + hash) + *c_ptr++;
	}

	return hash;
}

void put_into_HashMap (HashMap* hashmap, String* key, Data* value) {
	if (NULL == hashmap) {
		perror ("HashMap does not exist to insert key-value into!");
		return;
	}

	if (NULL == hashmap -> buckets) {
		perror ("HashMap buckets do not exist!");
		return;
	}

	Data* kv_data = get_reference_from_HashMap (hashmap, key);

	if (NULL != kv_data) {
		Data* kv_value = (Data*)((String*)(kv_data -> address) + 1);
		display_Data_details (kv_value);
	
		log_memory (DS_Raw, kv_value -> size, kv_value -> address, false);
		ERASE (&(kv_value -> address), kv_value -> size);

		kv_value -> type = value -> type;
		kv_value -> size = value -> size;
		kv_value -> address = malloc (value -> size);

		if (NULL == kv_value -> address) {
			perror ("Unable to allocate content memory for updating value in key-value data!");
			return;
		}

		log_memory (DS_Raw, kv_value -> size, kv_value -> address, true);
		copy_raw_bytes (value -> size, value -> address, kv_value -> address);

		return;
	}

	uint32_t hash = hash_djb2 (key);
//	printf ("hash = %" PRIu32 "\n", hash);	// PRIu32 macro from inttypes.h expands depending on compiler and system
	hash %= (hashmap -> capacity);
//	printf ("hash = %" PRIu32 "\n", hash);

	Iterator* iterator = create_Iterator (hashmap -> buckets, 1);

	for (size_t i = 0; i < hash; i++) {
		move_Iterator (iterator);
	}

	Linked_List* linked_list = iterator -> data -> address;

	delete_Iterator (&iterator);

	Data* data = create_key_value_Data (key, value);

	Node* node = create_Node (N_LinkedList);
	set_Node_Data (node, data);

	attach_Node_at_first (linked_list, node);

	delete_Node (&node);

	delete_key_value_Data (&data);

	linked_list = NULL;

	hashmap -> item_count++;
}

Data* get_reference_from_HashMap (HashMap* hashmap, String* key) {
	if (NULL == hashmap) {
		perror ("HashMap does not exist to get key reference!");
		return NULL;
	}

	if (NULL == hashmap -> buckets) {
		perror ("HashMap buckets do not exist to get key reference!");
		return NULL;
	}

	if (0 == hashmap -> item_count) {
//		perror ("HashMap is empty to get key reference!");
		return NULL;
	}

	uint32_t hash = hash_djb2 (key) % (hashmap -> capacity);

	Iterator* iterator = create_Iterator (hashmap -> buckets, 1);

	for (size_t i = 0; i < hash; i++) {
		move_Iterator (iterator);
	}

	Linked_List* linked_list = iterator -> data -> address;

	delete_Iterator (&iterator);

	Node* node = linked_list -> head_node;
	Data* kv_data;
	String* kv_key;
	bool found_flag = false;

	for (size_t i = 0; i < linked_list -> size; i++) {
		kv_data = node -> data;
		kv_key = (String*)(kv_data -> address);

		if (Cmp_Different != compare_Strings (key, kv_key)) {
			found_flag = true;
			break;
		}

		node = (node -> address_list -> head_chunk -> first_data_address + 1) -> address;
	}

	if (found_flag) {
		return kv_data;
	}

	return NULL;
}

void get_location_from_HashMap (HashMap* hashmap, String* key, size_t* bucket_index, size_t* linked_list_index) {
	if (NULL == hashmap) {
		perror ("HashMap does not exist to get key reference!");
		return;
	}

	if (NULL == hashmap -> buckets) {
		perror ("HashMap buckets do not exist to get key reference!");
		return;
	}

	if (0 == hashmap -> item_count) {
		perror ("HashMap is empty to get key reference!");
		return;
	}

	uint32_t hash = hash_djb2 (key) % 10;
	*bucket_index = hash;

	Iterator* iterator = create_Iterator (hashmap -> buckets, 1);

	for (size_t i = 0; i < hash; i++) {
		move_Iterator (iterator);
	}

	Linked_List* linked_list = iterator -> data -> address;

	delete_Iterator (&iterator);

	Node* node = linked_list -> head_node;
	Data* kv_data;
	String* kv_key;
	bool found_flag = false;

	for (size_t i = 0; i < linked_list -> size; i++) {
		kv_data = node -> data;
		kv_key = (String*)(kv_data -> address);

		if (Cmp_Different != compare_Strings (key, kv_key)) {
			found_flag = true;
			*linked_list_index = i;
			break;
		}

		node = (node -> address_list -> head_chunk -> first_data_address + 1) -> address;
	}

	if (!found_flag) {
		*linked_list_index = -1;
	}
}

Data* get_value_from_HashMap (HashMap* hashmap, String* key) {
	if (NULL == hashmap) {
		perror ("HashMap does not exist to get key reference!");
		return NULL;
	}

	if (NULL == hashmap -> buckets) {
		perror ("HashMap buckets do not exist to get key reference!");
		return NULL;
	}

	if (0 == hashmap -> item_count) {
		perror ("HashMap is empty to get key reference!");
		return NULL;
	}

	Data* kv_data = get_reference_from_HashMap (hashmap, key);

	if (NULL == kv_data) {
		return NULL;
	}

	return duplicate_Data ((Data*)((String*)(kv_data -> address) + 1));
}

void delete_from_HashMap (HashMap* hashmap, String* key) {
	if (NULL == hashmap) {
		perror ("HashMap does not exist to delete key-value entry from!");
		return;
	}

	if (NULL == key) {
		perror ("Key does not exist to delete key-value entry from HashMap!");
		return;
	}

	uint32_t hash = hash_djb2 (key) % (hashmap -> capacity);

	Iterator* iterator = create_Iterator (hashmap -> buckets, 1);

	for (size_t i = 0; i < hash; i++) {
		move_Iterator (iterator);
	}

	Linked_List* linked_list = iterator -> data -> address;

	delete_Iterator (&iterator);

	Node* node = linked_list -> head_node;
	Data* kv_data;
	String* kv_key;
	bool found_flag = false;

	for (size_t i = 0; i < linked_list -> size; i++) {
		kv_data = node -> data;
		kv_key = (String*)(kv_data -> address);

		if (Cmp_Different != compare_Strings (key, kv_key)) {
			found_flag = true;
			break;
		}

		node = (node -> address_list -> head_chunk -> first_data_address + 1) -> address;
	}

	if (found_flag) {
		node = detach_from_Linked_List (linked_list, node);
		delete_Node (&node);
	}

	hashmap -> item_count--;
}
