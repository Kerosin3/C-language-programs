#ifndef MISC
#define MISC
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

#define LIKELY(x)      __builtin_expect(!!(x), 1)
#define UNLIKELY(x)    __builtin_expect(!!(x), 0)

_Noreturn void die(const char *message);


#endif
