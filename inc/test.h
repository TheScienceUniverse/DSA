#ifndef TEST_H
#define TEST_H

#include "./text_style.h"

#define COLOR_PASSED BOLD_GREEN
#define COLOR_FAILED BOLD_RED 
#define COLOR_OFF RESET_STYLE

//#define clean_errno() (errno == 0 ? "None" : strerror(errno))
//#define log_error(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
//#define assertf(A, M, ...) if(!(A)) {log_error(M, ##__VA_ARGS__); assert(A); }

#define TEST(cond, msg) {													\
	if (cond) {																\
		printf ("\t[" COLOR_PASSED "PASSED" COLOR_OFF "]: (%s)\n", msg);	\
	} else {																\
		printf ("\t[" COLOR_FAILED "FAILED" COLOR_OFF "]: (%s)				\
			file:%s line:%d\n", msg, __FILE__, __LINE__);					\
	}																		\
}

#include "./basic.h"
void test_basic (void);

#include "./stream.h"
void test_Stream (void);

#include "./string.h"
void test_String (void);

#include "./data.h"
void test_Data (void);

#include "./chunk.h"
void test_Chunk (void);

#include "./bare_list.h"
void test_Bare_List (void);

#include "./list.h"
void test_List (void);

#include "./iterator.h"
void test_Iterator (void);

#include "./node.h"
void test_Node (void);

#include "./linked_list.h"
void test_Linked_List (void);

#include "./stack.h"
void test_Stack (void);

#include "./queue.h"
void test_Queue (void);

#include "./tree.h"
void test_Tree (void);

#include "./graph.h"
void test_Graph (void);

#include "./hashmap.h"
void test_HashMap (void);

void test_route (char* option);

#endif // TEST_H
