#include <stdio.h>
#include <stdint.h>
#include "spookyhash/src/spookyhash_api.h"
#include "BSD_strings.c"

int main(int argc, char *argv[])
{
	uint32_t seedx = 0x12ab;

        char u_input[21];
	fgets(u_input,21,stdin);
	unsigned len = strnlen(u_input,20);
	printf("you entered:%s, length is %d\n",u_input,len);
	uint32_t hash32 = spookyhash_32(u_input, len-1, seedx);
	printf("hash value is %lu \n",hash32);
	return 0;
}
