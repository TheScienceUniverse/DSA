#ifndef BASIC_H
#define BASIC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>

// ---------- x ----------

#define BYTE unsigned char

#define IDENTICAL 0		// everything same
#define EQUAL 1			// just value same
#define DIFFERENT -1	// completely not same


void fill_mem_zero (void* base_address, size_t num_bytes);
bool check_mem_zero (void* base_address, size_t num_bytes);
void copy_byte_stream (size_t length, BYTE* src_addr, BYTE* dst_addr);
void display_byte_stream (size_t num_bytes, BYTE* base_address);

// updated version of free to avoid dangling pointer
// can not fill_mem_zero to pointer_address becase it will corrupt memory
#define ERASE(pointer_address,data_length) {	\
	if (NULL != *pointer_address) {				\
		free (*pointer_address);				\
	}											\
												\
	*pointer_address = NULL;					\
}

#endif	// BASIC_H