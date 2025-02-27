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
