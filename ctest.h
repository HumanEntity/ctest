#include <stdio.h>
#include <stdarg.h>

#define CTEST_SUCCES 0
#define CTEST_FAILURE 1

typedef struct {
	char status;
	char* message;
	char* filename;
	unsigned int line;
} RESULT;
typedef RESULT(*TEST)();

// Checks `value`. Returns string when assertion failed
#define ctest_assert(message, value) do { \
	if (!value) { \
		RESULT failure = { \
			CTEST_FAILURE, \
			message, \
			__FILE__, \
			__LINE__, \
		}; \
		return failure; \
	}\
} while(0)

#define ctest_succes() do { RESULT succes = { CTEST_SUCCES, NULL, NULL, 0 }; return succes; } while(0)

// Runs `test`. `test` must have no arguments.
#define ctest_run(test) do { \
	RESULT result = test(); \
	++run; \
	if (result.status != CTEST_SUCCES) { \
		fprintf(stderr, "%s:%d %s\n", result.filename, result.line, result.message); \
		++failed; \
	} \
} while(0)

#define ctest_summary() do { \
	printf("\n-----------------\n"); \
	printf("Succeded: %d\n", run - failed); \
	printf("Failed: %d\n", failed); \
	printf("Total: %d\n", run); \
} while(0)

#define ctest_create(...) do { \
	execute_tests(sizeof(#__VA_ARGS__) / sizeof(TEST), __VA_ARGS__); \
} while(0)

static unsigned int run = 0;
static unsigned int failed = 0;

static void execute_tests(unsigned int count, ...) {
	va_list list;
	va_start(list, count);
	int i;
	for(i=0; i<=count; ++i) {
		RESULT (*test)();
		test = va_arg(list, TEST);
		ctest_run(test);
	}
	va_end(list);

	ctest_summary();
}

/*
 * Basic example is something like this:
 * ```
 * #ifdef CTEST_ENABLE
 *
 * int main(int argc, char **argv) {
 *     ctest_run(test1);
 *     ctest_run(test2);
 * }
 * 
 * #else
 *
 * int main(int argc, char **argv) {
 *     // Your normal app code
 * }
 *
 * #endif
 * ```
 * */
