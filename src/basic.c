#include "../include/basic.h"

void fill_mem_zero (void* base_address, size_t num_bytes) {
	if (base_address == NULL || num_bytes == 0) {
		return;
	}

	BYTE* ptr = base_address;

	while (num_bytes--) {
		*ptr++ = 0;
	}
}

bool check_mem_zero (void* base_address, size_t num_bytes) {
	if (base_address == NULL || num_bytes == 0) {
		return false;
	}

	bool status = true;
	BYTE* ptr = base_address;

	while (num_bytes--) {
		if (0 != *ptr++) {
			status = false;
			break;
		}
	}

	return status;
}

void copy_byte_stream (size_t length, BYTE* src_addr, BYTE* dst_addr) {
	if (
		0 == length
		|| NULL == src_addr
		|| NULL == dst_addr
	) {
		return;
	}

	BYTE *s = src_addr;
	BYTE *d = dst_addr;

	while (length--) {
		*d = *s;
		s = s + 1;
		d = d + 1;
	}
}

void display_byte_stream (size_t num_bytes, BYTE* base_address) {
	if (base_address == NULL || num_bytes == 0) {
		return;
	}

	BYTE* ptr = base_address;

	while (num_bytes--) {
		printf ("%02x", *ptr++);
	}

	printf ("\n");
}

size_t get_number_of_digits (size_t number, size_t base) {
	size_t count = 0;

	while (number != 0) {
		++count;
		number /= base;
	}

	return count;
}

size_t exponentiate (size_t base, size_t exponent) {
	size_t result = base;

	for (size_t i = 2; i < exponent; i++) {
		result *= base;
	}

	return result;
}

void put_s (char const str [static 1]) {
	for (size_t i = 0; str [i]; ++i) {
		if (putchar (str [i]) == EOF) {
			return;
		}
	}
}

void log_memory (DS_Type data_structure_type, size_t size, void* start_address, bool exists) {
	FILE* file = fopen ("./log/memory.log", "ab");

	if (NULL == file) {
		perror ("Error opening memory file!");
		return;
	}

	size_t written_size __attribute__((__unused__));

	written_size = fprintf (file, "\n");
	written_size = fwrite (&start_address, sizeof (void*), 1, file);
	written_size = fwrite (&size, sizeof (size_t), 1, file);
	written_size = fwrite (&data_structure_type, sizeof (DS_Type), 1, file);
	written_size = fwrite (&exists, sizeof (bool), 1, file);

	fclose (file);
}

void display_memory_log (void) {
	FILE* file = fopen ("./log/memory.log", "rb");

	if (NULL == file) {
		perror ("Error opening memory file!");
		return;
	}

	size_t read_size __attribute__((__unused__));
	void* start_address = NULL;
	DS_Type data_structure_type;
	size_t size;
	char c;
	bool exists;

	printf (" Stats | Memory Address | Size | Data Structure\n");
	printf (" ----- + -------------- + ---- + --------------\n");

	while ((c = fgetc (file)) != EOF) {
		read_size = fread (&start_address, sizeof (void*), 1, file);
		read_size = fread (&size, sizeof (size_t), 1, file);
		read_size = fread (&data_structure_type, sizeof (DS_Type), 1, file);
		read_size = fread (&exists, sizeof (bool), 1, file);

		if (exists) {
			//printf (" ⊕");
			printf (NORMAL_RED "   ✗  " RESET_STYLE);
		} else {
			//printf (" ⊖");
			printf (NORMAL_GREEN "   ✓  " RESET_STYLE);
		}

		printf (" | %p", start_address);	// "%018p"

		printf (" | %c%03lu |", (exists) ? '-' : '+', size);

		if (exists) {
			put_s (" Created ");
		} else {
			put_s (" Deleted ");
		}

		switch (data_structure_type) {
			case DS_Raw:
				puts ("Raw");
				break;
			case DS_String:
				puts ("String");
				break;
			case DS_Data:
				puts ("Data");
				break;
			case DS_Bare_List:
				puts ("Bare_List");
				break;
			case DS_Chunk:
				puts ("Chunk");
				break;
			case DS_List:
				puts ("List");
				break;
			case DS_Node:
				puts ("Node");
				break;
			case DS_Linked_List:
				puts ("Linked_List");
				break;
			case DS_Stack:
				puts ("Stack");
				break;
			case DS_Queue:
				puts ("Queue");
				break;
			case DS_Tree:
				puts ("Tree");
				break;
			case DS_Graph:
				puts ("Graph");
				break;
			default:
				puts ("N/A");
				break;
		}

		// putchar (c);
	}

	printf (" ----- + -------------- + ---- + --------------\n");

	fclose (file);
}
