#ifndef TEST_H
#define TEST_H

#include "./text_style.h"

#define COLOR_PASSED BOLD_GREEN
#define COLOR_FAILED BOLD_RED 
#define COLOR_OFF RESET_STYLE

//#define clean_errno() (errno == 0 ? "None" : strerror(errno))
//#define log_error(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
//#define assertf(A, M, ...) if(!(A)) {log_error(M, ##__VA_ARGS__); assert(A); }

#define TEST(cond, msg) {												\
	if (cond) {															\
		printf ("[" COLOR_PASSED "PASSED" COLOR_OFF "]: (%s)\n", msg);	\
	} else {															\
		printf ("[" COLOR_FAILED "FAILED" COLOR_OFF "]: (%s)			\
			file:%s line:%d\n", msg, __FILE__, __LINE__);				\
	}																	\
}

#endif // TEST_H
