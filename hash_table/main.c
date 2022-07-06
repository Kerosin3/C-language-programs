#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
//#include "spookyhash/src/spookyhash_api.h"
#include "BSD_strings.c"

typedef union {
	uint8_t byte0;
	uint8_t byte1;
	uint8_t byte2;
	uint8_t byte3;
} utf8_generic;

typedef struct {
	utf8_generic symbl;
	unsigned long s_count;
	unsigned long hash;

} utf8_char;


int main(int argc, char *argv[])
{
	unsigned a = 0b1000;
	printf("youvalue is %u\n",a);

        //char u_input[21];
	//fgets(u_input,21,stdin);
	//unsigned len = strnlen(u_input,20);
	//printf("you entered:%s, length is %d\n",u_input,len);
	FILE* fp_r;
	if ((fp_r = fopen(argv[1],"rb")) == NULL) {
		printf("error opening file, aborting...\n");
		exit(1);
	}

	fclose(fp_r);
	return 0;
}
