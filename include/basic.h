#ifndef BASIC_H
#define BASIC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

// ---------- x ----------

#define BYTE unsigned char

void fill_with_zero (void* pointer, size_t data_length);

// updated version of free to avoid dangling pointer
#define ERASE(pointer_address,data_length) {		\
	if (*pointer_address != NULL) {					\
		free (*pointer_address);					\
	}												\
													\
	fill_with_zero (*pointer_address, data_length);	\
	*pointer_address = NULL;						\
}

void test_basic (void);

#endif	// BASIC_H