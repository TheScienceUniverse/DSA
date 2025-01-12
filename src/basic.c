#include "../include/basic.h"

void fill_with_zero (void* pointer, size_t data_length) {
	if (pointer == NULL || data_length == 0) {
		return;
	}

	BYTE* ptr = pointer;

	while (data_length--) {
		*ptr++ = 0;
	}
}
