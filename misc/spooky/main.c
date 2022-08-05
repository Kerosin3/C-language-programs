#include <stdio.h>
#include <stdint.h>
#include "spookyhash_api.h"
#include <string.h>
#include <alloca.h>

int main(int argc, char *argv[])
{
	char *some = "asdasd";
	void* data = (void*) some;
	uint64_t seed1 = 0xabcdef;
	uint64_t hash64 = spookyhash_64(data, strlen(some), seed1);
	printf("your string is %s hash is %llu \n",some,hash64);
	
	unsigned long long z = 556677;

	void* str_placer = alloca((21)+1); //plus terminating
	snprintf(str_placer,(21+1), "%llu", z );// get the size
	printf("your string is %s\n",str_placer);	
	printf("size of syth is %u\n",strlen(str_placer));
	hash64 = spookyhash_64(str_placer, strlen(str_placer), seed1);
	printf("your string is %s hash is %llu \n",str_placer,hash64);

	printf("sizeof LLU is %u, size of UINT64 is %u \n",sizeof(unsigned long long), sizeof(uint64_t));
	return 0;
}
