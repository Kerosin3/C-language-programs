#include "misc.h"

_Noreturn void die(const char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}
