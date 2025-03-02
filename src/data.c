#include "../include/data.h"

Data* create_data (Data_Type data_type, size_t block_size, void* address) {
	if (data_type == DT_Undefined || block_size == 0) {
		return NULL;
	}

	Data* data = (Data*) malloc (sizeof (Data));

	if (data != NULL) {
		data -> type = DT_Undefined;
		data -> size = 0;
		data -> address = NULL;
	}

	if (block_size > 0) {
		data -> type = data_type;
		data -> size = block_size;
		data -> address = malloc (block_size);

		if (data -> address != NULL) {
			if (data_type == DT_Address) {
				data -> address = address;
			} else {
				data -> address = memcpy (data -> address, address, block_size);
			}
		}
	}

	return data;
}

void delete_data (Data** data_address) {
	if (*data_address == NULL) {
		// perror ("Data does not exist to delete!");
		return;
	}

	Data* data = *data_address;

	if (data -> address != NULL) {
		ERASE (&(data -> address), data -> size);
	}

	data = NULL;
	ERASE (data_address, sizeof (Data));
}

void forget_data (Data** data_address) {
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

Data* duplicate_data (Data* data) {
	if (data == NULL) {
		return NULL;
	}

	return create_data (data -> type, data -> size, data -> address);
}

void display_data (Data* data) {
	if (data == NULL) {
		// perror ("Data does not exist to display!");
		printf ("(nil)");
		return;
	}

	if (data -> address == NULL) {
		// perror ("Address does not exist to display!");
		printf ("N/A");
		return;
	}

	switch (data -> type) {
		case DT_Undefined:
			printf ("N/A");
			break;
		case DT_Address:
			printf ("%p", data -> address);
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
			display_range_data (data);
			break;
		default:
			display_byte_stream (data -> size, data -> address);
			break;
	}
}

void display_data_properties (Data* data) {
	if (data == NULL) {
		perror ("Data is empty");
		exit (1);
	}

	switch (data -> type) {
		case DT_Binary:
			printf ("Data (Binary) : ");
			display_binary_data (data -> size, (BYTE*) data -> address);
			printf ("\n");
			break;
		case DT_Integer:
			printf ("Data (Integer) : %d\n", *((int*) data -> address));
			break;
		case DT_String:
			printf ("Data (String) [%zu]: ", data -> size);
			display_raw_string (data -> size, (char*) data -> address);
			printf ("\n");
			break;
		default:
			break;
	}
}

void display_binary_data (size_t size, BYTE* address) {
	for (size_t i = 0; i < size; i++) {
		printf ("%02x", *(address + i));
	}
}

Data* create_range_data (int start, int end) {
	int block_size = 2 * sizeof (int);
	int* address = malloc (block_size);

	*(address + 0) = start;
	*(address + 1) = end;

	Data* data = create_data (DT_Range, block_size, address);
	ERASE (&address, block_size);

	return data;
}

void display_range_data (Data* data) {
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

bool are_data_equal (Data* data1, Data* data2) {
	if (data1 == data2) {
		return true;
	}

	if (data1 == NULL) {
		// printf ("Data-1 is NULL\n");
		return false;
	}

	if (data2 == NULL) {
		// printf ("Data-2 is NULL\n");
		return false;
	}

	bool result = false;
	BYTE* ptr1;
	BYTE* ptr2;
	size_t i;

	if (data1 -> type == data2 -> type
		&& data1 -> size == data2 -> size
	) {
		ptr1 = data1 -> address;
		ptr2 = data2 -> address;

		for (i = 0; i < data1 -> size; i++) {
			if (*ptr1 != *ptr2) {
				result = false;
				break;
			}

			++ptr1;
			++ptr2;
		}

		if (i == data1 -> size) {
			result = true;
		}
	}

	return result;
}

bool is_data_memory_erased (void** data_addresses) {
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

void** capture_data_addresses (Data* data) {
	if (NULL == data) {
		return NULL;
	}

	void** addresses = malloc (4 * sizeof (void*));

	*(addresses + 0) = &(data);	// base address
	*(addresses + 1) = &(data -> type);
	*(addresses + 1) = &(data -> size);
	*(addresses + 2) = &(data -> address);

	return addresses;
}

void copy_data (Data* src_data, Data* dst_data) {
	if (NULL == src_data) {
		perror ("Source Data does not exist to copy from!");
		return;
	}

	if (NULL == dst_data) {
		perror ("Destination Data does not exist to copy into!");
		return;
	}

	if (NULL != src_data -> address) {
		// ERASE (&(data -> address), data -> size);
	}

	dst_data -> type = src_data -> type;
	dst_data -> size = src_data -> size;

	free (dst_data -> address);
	dst_data -> address = malloc (src_data -> size);
	copy_byte_stream (src_data -> size, src_data -> address, dst_data -> address);
}

void empty_data (Data* data) {
	if (NULL == data) {
		// perror ("Data does not exist to delete!");
		return;
	}

	if (data -> address != NULL) {
		ERASE (&(data -> address), data -> size);
	}

	data -> type = DT_Undefined;
	data -> size = 0;
	data -> address = NULL;
}