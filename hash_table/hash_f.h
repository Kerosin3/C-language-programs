
#ifndef HASH_F
#define HASH_F 
#include <stdint.h>
#include <stdio.h>
#include <tgmath.h>
//#include "BSD_strings.c"
#define SALT 15
unsigned long long calc_hash(uint8_t*);

#endif /* ifndef HASH_F */
