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
#include <math.h>
#include <locale.h>

#include "./text_style.h"

// ---------- x ----------

#define BYTE uint8_t

typedef enum COMPARE_STATUS {
	Cmp_Identical
	, Cmp_Equivalent
	, Cmp_Different
} Compare_Status;

typedef enum DATA_STRUCTURE_TYPE {
	DS_Raw
	, DS_String
	, DS_Stream
	, DS_Data
	, DS_Bare_List
	, DS_Chunk
	, DS_List
	, DS_Iterator
	, DS_Node
	, DS_Linked_List
	, DS_Stack
	, DS_Queue
	, DS_Tree
	, DS_Graph
} DS_Type;

void fill_mem_zero (void* base_address, size_t num_bytes);
bool check_mem_zero (void* base_address, size_t num_bytes);
void copy_byte_stream (size_t length, BYTE* src_addr, BYTE* dst_addr);
void display_byte_stream (size_t num_bytes, BYTE* base_address);
void display_bit_stream (size_t num_bytes, BYTE* base_address);
size_t get_number_of_digits (size_t number, size_t base);
size_t exponentiate (size_t base, size_t power);
void put_s (char const str [static 1]);	// own puts function without newline
void log_memory (DS_Type data_structure_type, size_t size, void* start_address, bool exists);
void display_memory_log (void);

// updated version of free to avoid dangling pointer
// can not fill_mem_zero to pointer_address becase it will corrupt memory
#define ERASE(pointer_address,data_length) {	\
	if (NULL != *pointer_address) {				\
		free (*pointer_address);				\
	}											\
												\
	*pointer_address = NULL;					\
}

#define ENDL(void) { putchar ('\n'); }

#endif	// BASIC_H