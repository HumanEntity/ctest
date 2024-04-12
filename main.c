#include "ctest.h"

RESULT test1() {
	ctest_assert("This always fails", 0);
	ctest_succes();
}
RESULT test2() {
	ctest_assert("This always passes", 1);
	ctest_succes();
}

RESULT test3() {
	ctest_assert("This too!", 1);
	ctest_succes();
}

int main() {
	ctest_create(test1, test2, test3);
}
