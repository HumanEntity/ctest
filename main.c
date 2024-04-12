#include "ctest.h"

RESULT test1() {
	ctest_assert(0);
	ctest_succes();
}
RESULT test2() {
	ctest_assert(1);
	ctest_succes();
}

int main() {
	ctest_run(test1);
	ctest_run(test2);
	ctest_summary();
}
