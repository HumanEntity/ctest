#include <stdio.h>
#include <stdarg.h>

#define CTEST_SUCCES 0
#define CTEST_FAILURE 1

typedef char RESULT;
typedef RESULT(*TEST)();

// Checks `value`. Returns string when assertion failed
#define ctest_assert(value) do { \
	if (!value) { \
		char buffer[128]; \
		sprintf(buffer, "%s:%d Assertion Failed", __FILE__, __LINE__); \
		printf("%s\n", buffer); \
		return CTEST_FAILURE; \
	}\
} while(0)

#define ctest_succes() return CTEST_SUCCES;

// Runs `test`. `test` must have no arguments.
#define ctest_run(test) do { \
	char message = test(); \
	++run; \
	if (message != CTEST_SUCCES) { \
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
	for(int i=0; i<=count; ++i) {
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
