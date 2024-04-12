# `ctest`

`ctest` is simple c testing library

## Usage

To use this just clone this repo and include `ctest.h`

Example usage:

```c
#include <ctest.h>

RESULT test1() {
    ctest_assert("This works!", 1);
}

int main(int argc, char **argv) {
    #ifdef CTEST_ENABLE
    ctest_create(test1);
    #else
    // Your code
    #endif
}
```

