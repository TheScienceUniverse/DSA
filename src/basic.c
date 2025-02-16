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
