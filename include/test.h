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

#include "./string.h"
void test_string (void);

#include "./data.h"
void test_data (void);

#include "./chunk.h"
void test_chunk (void);

#include "./list.h"
void test_list (void);

#include "./node.h"
void test_node (void);

#include "./linked_list.h"
void test_linked_list (void);

#include "./stack.h"
void test_stack (void);

#include "./queue.h"
void test_queue (void);

#include "./tree.h"
void test_tree (void);

#include "./graph.h"
void test_graph (void);

#endif // TEST_H
