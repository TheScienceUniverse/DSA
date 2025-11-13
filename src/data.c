#include "../inc/data.h"

Data* create_Data (Data_Type data_type, size_t block_size, void* address) {
	if (data_type == DT_Undefined || block_size == 0) {
		return NULL;
	}

	Data* data = (Data*) malloc (sizeof (Data));

	if (data != NULL) {
		log_memory (DS_Data, sizeof (Data), data, true);

		data -> type = DT_Undefined;
		data -> size = 0;
		data -> address = NULL;
	}

	if (DT_Address == data_type) {
		data -> type = DT_Address;
		data -> size = 0;
		data -> address = address;
		return data;
	}

	if (block_size > 0) {
		data -> type = data_type;
		data -> size = block_size;
		data -> address = malloc (block_size);

		if (data -> address != NULL) {
			log_memory (DS_Raw, block_size, data -> address, true);

			if (data_type == DT_Address) {
				data -> address = address;
			} else {
				data -> address = memcpy (data -> address, address, block_size);
			}
		}
	}

	return data;
}

Data* duplicate_Data (Data* data) {
	if (data == NULL) {
		return NULL;
	}

	return create_Data (data -> type, data -> size, data -> address);
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
		case DT_Undefined:
			printf ("~_~");
			break;
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
		default:
			display_raw_bytes (data -> size, data -> address);
			break;
	}
}

void display_Data_details (Data* data) {
	if (data == NULL) {
		perror ("Data does not exist\n");
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
		case DT_Undefined:
			printf ("(Undefined)");
			break;
		case DT_Empty:
			printf ("(Empty)");
			break;
		case DT_Address:
			printf ("(Address) Value: (%p)", data -> address);
			break;
		case DT_Character:
			printf ("(Character) Value: %c", *((char*) data -> address));
			break;
		case DT_Binary:
			printf ("(Binary) Size: %zu Value: ", data -> size);
			display_binary_data (data -> size, (BYTE*) data -> address);
			break;
		case DT_Integer:
			printf ("(Integer) Value: %d", *((int*) data -> address));
			break;
		case DT_String:
			printf ("(String) Length: [%zu] Value: ", data -> size);
			display_raw_string (data -> size, (char*) data -> address);
			break;
		default:
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

	Data* data = *data_address;

	if (data -> address != NULL) {
		data -> address = NULL;
		data -> type = DT_Undefined;
	}
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

	if (NULL != dst_data -> address) {
		ERASE (&(dst_data -> address), dst_data -> size);
	}

	dst_data -> type = src_data -> type;
	dst_data -> size = src_data -> size;

	free (dst_data -> address);

	if (
		NULL == src_data -> address
		|| DT_Address == dst_data -> type
	) {
		dst_data -> address = src_data -> address;
		return;
	}

	dst_data -> address = malloc (src_data -> size);
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

	if (
		DT_Address != data -> type
		&& data -> address != NULL
	) {
		log_memory (DS_Raw, data -> size, data -> address, false);
		ERASE (&(data -> address), data -> size);
		data -> type = DT_Empty;
	}

	data -> size = 0;
	data -> address = NULL;
}

Data* create_empty_Data (void) {
	Data* data = (Data*) malloc (sizeof (Data));
	log_memory (DS_Data, sizeof (Data), data, true);

	if (NULL == data) {
		perror ("Memory allocation error for Data!\n");
		exit (EXIT_FAILURE);
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
	int block_size = sizeof (String) + sizeof (Data);
	void* address = malloc (block_size);
	log_memory (DS_Raw, block_size, address, true);

	String* temp_string = address;
	Data* temp_data = (Data*)((String*) address + 1);

	temp_string -> length = key -> length;
	temp_string -> text = malloc (key -> length * sizeof (char));
	copy_raw_bytes (key -> length, (BYTE*)(key -> text), (BYTE*)(temp_string -> text));

	copy_Data (value, temp_data);

	Data* data = create_Data (DT_Key_Value, block_size, address);

	log_memory (DS_Raw, block_size, address, false);
	ERASE (&address, block_size);

	return data;
}

void delete_key_value_Data (Data** key_value_data_address) {
	if (NULL == *key_value_data_address) {
		perror ("Key-Value pair data does not exist to delete");
		return;
	}

	Data* key_value_data = *key_value_data_address;

	if (DT_Key_Value != key_value_data -> type) {
		perror ("Data is not identified as Key-Value pair data to delete");
		return;
	}

	void* address = key_value_data -> address;

	String* key = address;
	Data* value = (Data*)((String*) address + 1);

	log_memory (DS_String, key -> length, key -> text, false);
	ERASE (&(key -> text), key -> length);
	log_memory (DS_Data, value -> size, value -> address, false);
	ERASE (&(value -> address), value -> size);

	delete_Data (key_value_data_address);
	key_value_data = NULL;
}

void display_key_value_Data (Data* key_value_data) {
	if (NULL == key_value_data) {
		perror ("Key-Value pair data does not exist to display");
		return;
	}

	if (DT_Key_Value != key_value_data -> type) {
		perror ("Data is not identified as Key-Value pair data to display");
		return;
	}

	printf ("[Key: \"");
	display_String ((String*)(key_value_data -> address + 0));
	printf ("\", Value: \"");
	display_Data ((Data*)((String*)(key_value_data -> address) + 1));
	printf ("\"]\n");
}
