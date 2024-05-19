#ifndef BASIC_H
#define BASIC_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

// ---------- x ----------

#define BYTE unsigned char

// updated version of free to avoid dangling pointer
#define ERASE(address) {	\
	if (*address != NULL) {	\
		free (*address);	\
	}						\
	*address = NULL;		\
}

void test_basic (void);

#endif	// BASIC_H