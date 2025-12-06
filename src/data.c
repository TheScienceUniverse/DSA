#include "../inc/data.h"

Data* create_Data (Data_Type data_type, size_t block_size, void* address) {
	if (data_type == DT_Undefined || block_size == 0) {
		return NULL;
	}

	Data* data = (Data*) malloc (sizeof (Data));

	if (NULL == data) {
		perror ("Unable to allocate memory for Data!");
		return NULL;
	}

	log_memory (DS_Data, sizeof (Data), data, true);

	// default values
	data -> type = DT_Empty;	// 0 enum
	data -> size = 0;
	data -> address = NULL;	// (void*)(0)

	if (DT_Empty == data_type) {
		return data;
	}

	if (DT_Address == data_type) {
		data -> type = DT_Address;
		data -> address = address;
		return data;
	}

	if (
		DT_Undefined == data_type
		|| 0 == block_size
	) {
		data -> type = DT_Undefined;
		return data;
	}

	data -> type = data_type;
	data -> size = block_size;
	data -> address = malloc (block_size);

	if (NULL == data -> address) {
		perror ("Unable to allocate container memory for Data!");
		return data;
	}

	log_memory (DS_Raw, block_size, data -> address, true);
	data -> address = memcpy (data -> address, address, block_size);

	return data;
}

Data* duplicate_Data (Data* data) {
	if (data == NULL) {
		return NULL;
	}

	if (DT_Key_Value == data -> type) {
		return duplicate_key_value_Data (data);
	}

	return create_Data (data -> type, data -> size, data -> address);
}

void display_Data_Type (Data_Type data_type) {
	switch (data_type) {
		case DT_Empty:
			put_s ("<Empty>");
			break;
		case DT_Address:
			put_s ("<Address>");
			break;
		case DT_Character:
			put_s ("<Character>");
			break;
		case DT_Binary:
			put_s ("<Binary>");
			break;
		case DT_Integer:
			put_s ("<Integer>");
			break;
		case DT_String:
			put_s ("<String>");
			break;
		case DT_Range:
			put_s ("<Range>");
			break;
		case DT_Key_Value:
			put_s ("<Key-Value>");
			break;
		case DT_Undefined:
		default:
			put_s ("<Undefined>");
			break;
	}
}

void display_Data (Data* data) {
	if (data == NULL) {
		printf ("(nil)");
		return;
	}

	if (
		DT_Address != data -> type
		&& data -> address == NULL
	) {
		data -> type = DT_Empty;
	}

	switch (data -> type) {
		case DT_Empty:
			printf ("...");
			break;
		case DT_Address:
			printf ("%p", data -> address);
			break;
		case DT_Character:
			printf ("%c", *((char*) data -> address));
			break;
		case DT_Binary:
			display_binary_data (data -> size, (BYTE*) data -> address);
			break;
		case DT_Integer:
			printf ("%d", *((int*) data -> address));
			break;
		case DT_String:
			display_raw_string (data -> size, data -> address);
			break;
		case DT_Range:
			display_range_Data (data);
			break;
		case DT_Key_Value:
			display_key_value_Data (data);
			break;
		case DT_Undefined:
			printf ("~_~");
			break;
		default:
			display_raw_bytes (data -> size, data -> address);
			break;
	}
}

void display_Data_details (Data* data) {
	if (data == NULL) {
		perror ("Data does not exist to display details\n");
		return;
	}

	if (
		DT_Address != data -> type
		&& data -> address == NULL
	) {
		data -> type = DT_Empty;
	}

	printf ("Data :=> Address: (%p) Type: ", data);

	switch (data -> type) {
		case DT_Empty:
			printf ("<Empty>");
			break;
		case DT_Address:
			printf ("<Address> Value: (%p)", data -> address);
			break;
		case DT_Character:
			printf ("<Character> Value: %c", *((char*) data -> address));
			break;
		case DT_Binary:
			printf ("<Binary> Size: %zu Value: 0x", data -> size);
			display_binary_data (data -> size, (BYTE*) data -> address);
			break;
		case DT_Integer:
			printf ("<Integer> Value: %d", *((int*) data -> address));
			break;
		case DT_String:
			printf ("<String> Length: %zu Value: \"", data -> size);
			display_raw_string (data -> size, (char*) data -> address);
			putchar ('"');
			break;
		case DT_Key_Value:
			printf ("<Key-Value>: ");
			display_key_value_Data (data);
			break;
		case DT_Undefined:
		default:
			printf ("<Undefined>");
			break;
	}

	printf ("\n");
}

void display_binary_data (size_t size, BYTE* address) {
	for (size_t i = 0; i < size; i++) {
		printf ("%02x", *(address + i));
	}
}

void delete_Data (Data** data_address) {
	if (*data_address == NULL) {
		// perror ("Data does not exist to delete!");
		return;
	}

	Data* data = *data_address;

	if (DT_Address == data -> type) {
		data -> address = NULL;
	}

	if (DT_Key_Value == data -> type) {
		return delete_key_value_Data (data_address);
	}

	if (data -> address != NULL) {
		log_memory (DS_Raw, data -> size, data -> address, false);
		ERASE (&(data -> address), data -> size);
	}

	data = NULL;

	log_memory (DS_Data, sizeof (Data), *data_address, false);
	ERASE (data_address, sizeof (Data));
}

void forget_Data (Data** data_address) {
	if (*data_address == NULL) {
		// perror ("Data does not exist to forget!");
		return;
	}

	// NEED TO ADD LOGIC
	empty_Data (*data_address);
}

void copy_Data (Data* src_data, Data* dst_data) {
	if (dst_data == src_data) {
		return;
	}

	if (NULL == src_data) {
		perror ("Source Data does not exist to copy from!");
		return;
	}

	if (NULL == dst_data) {
		perror ("Destination Data does not exist to copy into!");
		return;
	}

	if (
		DT_Address == dst_data -> type
		&& 0 != dst_data -> size
	) {
		log_memory (DS_Raw, dst_data -> size, dst_data -> address, false);
		ERASE (&(dst_data -> address), dst_data -> size);
		dst_data -> size = 0;
	}

	// erase pre-allocated memory of different size
	if (
		DT_Empty != dst_data -> type
		&& DT_Address != dst_data -> type
		&& DT_Undefined != dst_data -> type
		&& NULL != dst_data -> address
		&& dst_data -> size != src_data -> size
	) {
		log_memory (DS_Raw, dst_data -> size, dst_data -> address, false);
		ERASE (&(dst_data -> address), dst_data -> size);
	}

	// copy particulars
	dst_data -> type = src_data -> type;
	dst_data -> size = src_data -> size;

	if (
		DT_Empty == src_data -> type
		|| DT_Undefined == src_data -> type
	) {
		dst_data -> address = NULL;
		dst_data -> size = 0;
		return;
	}

	if (DT_Address == src_data -> type) {
		dst_data -> type = DT_Address;
		dst_data -> address = src_data -> address;
		return;
	}

	// no pre-allocation
	if (
		DT_Empty != src_data -> type
		&& DT_Address != src_data -> type
		&& DT_Undefined != src_data -> type
		&& NULL == dst_data -> address
	) {
		dst_data -> address = malloc (src_data -> size);
	}

	if (NULL == dst_data -> address) {
		perror ("Unable to allocate container memory to copy Data!");
		empty_Data (dst_data);
		return;
	}

	log_memory (DS_Raw, dst_data -> size, dst_data -> address, true);
	copy_raw_bytes (src_data -> size, (BYTE*)(src_data -> address), (BYTE*)(dst_data -> address));
}

void swap_Data (Data* data_1, Data* data_2) {
	if (data_1 == data_2) {
		return;
	}

	if (NULL == data_1) {
		perror ("Data-1 does not exist to swap!");
		exit (EXIT_FAILURE);
	}

	if (NULL == data_2) {
		perror ("Data-2 does not exist to swap!");
		exit (EXIT_FAILURE);
	}

	Data* temp_data = data_1;
	data_1 = data_2;
	data_2 = temp_data;
}

Compare_Status compare_Data (Data* data_1, Data* data_2) {
	if (NULL == data_1) {
		perror ("Data_1 does not exist to compare!");
		exit (EXIT_FAILURE);
	}

	if (NULL == data_2) {
		perror ("Data_2 does not exist to compare!");
		exit (EXIT_FAILURE);
	}

	if (data_1 == data_2) {
		return Cmp_Identical;
	}

	if (
		data_1 -> type != data_2 -> type
		|| data_1 -> size != data_2 -> size
	) {
		return Cmp_Different;
	}

	Compare_Status cmp_stat = Cmp_Equivalent;
	BYTE* b1 = data_1 -> address;
	BYTE* b2 = data_2 -> address;

	for (size_t i = 0; i < data_1 -> size; i++) {
		if (*b1 != *b2) {
			cmp_stat = Cmp_Different;
			break;
		}

		b1 = b1 + 1;
		b2 = b2 + 1;
	}

	return cmp_stat;
}

bool is_Data_memory_erased (void** data_addresses) {
	if (NULL == data_addresses) {
		return false;
	}

	bool status = true;

	if (
		!check_mem_zero (*(data_addresses + 0), sizeof (void*))
		&& !check_mem_zero (*(data_addresses + 1), sizeof (void*))
		&& !check_mem_zero (*(data_addresses + 2), sizeof (void*))
		&& !check_mem_zero (*(data_addresses + 3), sizeof (void*))
	) {
		status = false;
	}

	return status;
}

void** capture_Data_addresses (Data* data) {
	if (NULL == data) {
		return NULL;
	}

	void** addresses = malloc (4 * sizeof (void*));
	log_memory (DS_Raw, 4 * sizeof (void*), addresses, true);

	*(addresses + 0) = &(data);	// base address
	*(addresses + 1) = &(data -> type);
	*(addresses + 1) = &(data -> size);
	*(addresses + 2) = &(data -> address);

	return addresses;
}

void empty_Data (Data* data) {
	if (NULL == data) {
		// perror ("Data does not exist to delete!");
		return;
	}

	if (DT_Address == data -> type) {
		data -> size = 0;
		data -> address = NULL;
		return;
	}

	if (NULL != data -> address) {
		log_memory (DS_Raw, data -> size, data -> address, false);
		ERASE (&(data -> address), data -> size);
	}

	data -> type = DT_Empty;
	data -> size = 0;
	data -> address = NULL;
}

Data* create_empty_Data (void) {
	Data* data = (Data*) malloc (sizeof (Data));
	log_memory (DS_Data, sizeof (Data), data, true);

	if (NULL == data) {
		perror ("Unable to allocate memory for empty Data!\n");
		return NULL;
	}

	data -> type = DT_Empty;
	data -> size = 0;
	data -> address = NULL;

	return data;
}

Data* create_range_Data (int start, int end) {
	int block_size = 2 * sizeof (int);
	int* address = malloc (block_size);
	log_memory (DS_Raw, block_size, address, true);

	*(address + 0) = start;
	*(address + 1) = end;

	Data* data = create_Data (DT_Range, block_size, address);

	log_memory (DS_Raw, block_size, address, false);
	ERASE (&address, block_size);

	return data;
}

void display_range_Data (Data* data) {
	if (data == NULL) {
		perror ("Range data does not exist to display");
		return;
	}

	if (data -> type != DT_Range) {
		perror ("Data is not identified as Range data to display");
		return;
	}

	printf ("[%d, %d]\n", *((int*)(data -> address) + 0), *((int*)(data -> address) + 1));
}

Data* create_address_Data (void* address) {
	Data* data = (Data*) malloc (sizeof (Data));
	log_memory (DS_Data, sizeof (Data), data, true);

	if (NULL == data) {
		perror ("Memory allocation error for Data!\n");
		exit (EXIT_FAILURE);
	}

	data -> type = DT_Address;
	data -> size = sizeof (void*);
	data -> address = address;

	return data;
}

Data* create_key_value_Data (String* key, Data* value) {
	if (
		NULL == key
		|| 0 == key -> length
		|| NULL == key -> text
	) {
		perror ("Key String does not exist to create key-value Data!");
		return NULL;
	}

	if (
		NULL == value
		|| 0 == value -> size
		|| NULL == value -> address
	) {
		perror ("Value Data does not exist to create key-value Data!");
		return NULL;
	}

	int block_size = sizeof (String) + sizeof (Data);
	void* block_addr = malloc (block_size);

	if (NULL == block_addr) {
		perror ("Unable to allocate memory for key-value block!");
		return NULL;
	}
	
	log_memory (DS_Raw, block_size, block_addr, true);

	// manually copying key (String)
	String* string = (String*) block_addr;
	string -> length = key -> length;
	string -> text = malloc (string -> length * sizeof (char));

	if (NULL == string -> text) {
		perror ("Unable to allocate memory for key in key-value block!");
		return NULL;
	}

	log_memory (DS_Raw, string -> length, string -> text, true);
	copy_raw_bytes (string -> length, (BYTE*)(key -> text), (BYTE*)(string -> text));

	// manually copying value (Data)
	Data* data = (Data*)((String*) block_addr + 1);
	data -> type = value -> type;
	data -> size = value -> size;
	data -> address = malloc (data -> size);

	if (NULL == data -> address) {
		perror ("Unable to allocate memory for value in key-value block!");
		return NULL;
	}

	log_memory (DS_Raw, data -> size, data -> address, true);
	copy_raw_bytes (data -> size, (BYTE*)(value -> address), (BYTE*)(data -> address));

	Data* kv_data = create_empty_Data ();
	kv_data -> type = DT_Key_Value;
	kv_data -> size = block_size;
	kv_data -> address = block_addr;

	return kv_data;
}

Data* duplicate_key_value_Data (Data* kv_data) {
	if (NULL == kv_data) {
		perror ("Key-Value Data does not exist to duplicate!");
		return NULL;
	}

	if (
		DT_Key_Value != kv_data -> type
		|| 0 == kv_data -> size
		|| kv_data -> size != sizeof (String) + sizeof (Data)
	) {
		perror ("Given Data is not key-value Data to duplicate!");
		return NULL;
	}

	Data* new_kv_data = create_empty_Data ();
	new_kv_data -> type = DT_Key_Value;
	new_kv_data -> size = sizeof (String) + sizeof (Data);
	new_kv_data -> address = malloc (kv_data -> size);

	if (NULL == new_kv_data -> address) {
		perror ("Unable to allocate container memory to duplicate key-value Data!");
		return NULL;
	}

	log_memory (DS_Raw, new_kv_data -> size, new_kv_data -> address, true);
	copy_raw_bytes (kv_data -> size, (BYTE*)(kv_data -> address), (BYTE*)(new_kv_data -> address));

	String* old_key = (String*)(kv_data -> address);
	Data* old_value = (Data*)((String*)(kv_data -> address) + 1);
	String* new_key = (String*)(new_kv_data -> address);
	Data* new_value = (Data*)((String*)(new_kv_data -> address) + 1);

	new_key -> text = malloc (old_key -> length);

	if (NULL == new_key -> text) {
		perror ("Unable to allocate memory to duplicate key in key-value block!");
		return new_kv_data;
	}

	log_memory (DS_Raw, new_key -> length, new_key -> text, true);
	copy_raw_bytes (old_key -> length, (BYTE*)(old_key -> text), (BYTE*)(new_key -> text));

	new_value -> address = malloc (old_value -> size);

	if (NULL == new_value -> address) {
		perror ("Unable to allocate memory to duplicate value in key-value block!");
		return NULL;
	}

	log_memory (DS_Raw, new_value -> size, new_value -> address, true);
	copy_raw_bytes (old_value -> size, (BYTE*)(old_value -> address), (BYTE*)(new_value -> address));

	return new_kv_data;
}

void display_key_value_Data (Data* kv_data) {
	if (NULL == kv_data) {
		perror ("Key-Value pair data does not exist to display");
		return;
	}

	if (DT_Key_Value != kv_data -> type) {
		perror ("Data is not identified as Key-Value pair data to display");
		return;
	}

	printf ("[Key: \"");
	display_String ((String*)(kv_data -> address + 0));
	printf ("\", Value: \"");
	display_Data ((Data*)((String*)(kv_data -> address) + 1));
	printf ("\"]");
}

void delete_key_value_Data (Data** kv_data_address) {
	if (NULL == *kv_data_address) {
		perror ("Key-Value pair data does not exist to delete");
		return;
	}

	Data* kv_data = *kv_data_address;

	if (DT_Key_Value != kv_data -> type) {
		perror ("Data is not identified as Key-Value pair data to delete");
		return;
	}

	String* key = (String*)(kv_data -> address);
	Data* value = (Data*)((String*)(kv_data -> address) + 1);

	log_memory (DS_String, key -> length, key -> text, false);
	ERASE (&(key -> text), key -> length);
	log_memory (DS_Data, value -> size, value -> address, false);
	ERASE (&(value -> address), value -> size);

	log_memory (DS_Raw, kv_data -> size, kv_data -> address, false);
	ERASE (&(kv_data -> address), kv_data -> size);

	kv_data = NULL;

	log_memory (DS_Data, sizeof (Data), *kv_data_address, false);
	ERASE (kv_data_address, sizeof (Data));
}
